<#
.SYNOPSIS
Runs a command (typically doxa_bench) while sampling CPU frequency and
throttle counters, then reports whether the run was thermally contaminated.

.DESCRIPTION
Samples three Windows performance counters every IntervalMs:

  % Processor Performance   actual clock vs nominal; >100 = turbo boost,
                            a downward drift across the run = throttling
  % Performance Limit       how hard firmware is capping the CPU (100 = uncapped)
  Performance Limit Flags   nonzero = firmware is actively limiting, with the
                            cause encoded in the bits (thermal / power / PROCHOT)

Samples are written to a CSV, and a summary compares the first third of the
run against the last third: if the average clock decayed by more than 5%, or
limit flags fired, the run should not be trusted for A/B comparison.

.EXAMPLE
.\bench-monitor.ps1 -Command '.\build-bench\Doxa.Bench\Release\doxa_bench.exe --benchmark_filter=^BM_Sauvola$ --benchmark_repetitions=15'
#>
param(
	[Parameter(Mandatory = $true)][string]$Command,
	[string]$OutCsv = "bench-monitor.csv",
	# Get-Counter blocks for ~1s per call, so the effective sampling period is
	# ~(1s + IntervalMs) regardless of this value.  ~1 Hz is plenty for thermal
	# effects; this small sleep just minimizes dead time so short benchmark
	# bursts still collect enough samples to judge.
	[int]$IntervalMs = 100
)

$counters = @(
	'\Processor Information(_Total)\% Processor Performance',
	'\Processor Information(_Total)\% Performance Limit',
	'\Processor Information(_Total)\Performance Limit Flags'
)

$proc = Start-Process -FilePath cmd.exe -ArgumentList '/c', $Command -NoNewWindow -PassThru

$samples = New-Object System.Collections.Generic.List[object]
while (-not $proc.HasExited)
{
	$counter = Get-Counter -Counter $counters -ErrorAction SilentlyContinue
	if ($null -ne $counter)
	{
		$values = $counter.CounterSamples
		$samples.Add([pscustomobject]@{
			Time         = $counter.Timestamp.ToString('HH:mm:ss.fff')
			PerfPct      = [math]::Round($values[0].CookedValue, 1)
			PerfLimitPct = [math]::Round($values[1].CookedValue, 1)
			LimitFlags   = [int]$values[2].CookedValue
		})
	}
	Start-Sleep -Milliseconds $IntervalMs
}

$samples | Export-Csv -NoTypeInformation -Encoding utf8 $OutCsv

if ($samples.Count -lt 6)
{
	Write-Host "bench-monitor: run too short to judge ($($samples.Count) samples)"
	exit $proc.ExitCode
}

$third = [int][math]::Floor($samples.Count / 3)
$early = ($samples | Select-Object -First $third | Measure-Object -Property PerfPct -Average).Average
$late = ($samples | Select-Object -Last $third | Measure-Object -Property PerfPct -Average).Average
$overall = $samples.PerfPct | Measure-Object -Minimum -Maximum -Average
$flagged = @($samples | Where-Object { $_.LimitFlags -ne 0 }).Count
$decayPct = if ($early -gt 0) { [math]::Round(100 * ($early - $late) / $early, 1) } else { 0 }

Write-Host ""
Write-Host "=== bench-monitor: $($samples.Count) samples -> $OutCsv ==="
Write-Host ("% Processor Performance:  min {0}  avg {1}  max {2}" -f $overall.Minimum, [math]::Round($overall.Average, 1), $overall.Maximum)
Write-Host ("Clock decay first->last third: {0} -> {1}  ({2}%)" -f [math]::Round($early, 1), [math]::Round($late, 1), $decayPct)
Write-Host ("Performance Limit Flags nonzero: {0} of {1} samples" -f $flagged, $samples.Count)

if ($decayPct -gt 5 -or $flagged -gt 0)
{
	Write-Host "VERDICT: CONTAMINATED - clock decayed or firmware throttled during the run." -ForegroundColor Red
}
else
{
	Write-Host "VERDICT: clean - clock stayed stable across the run." -ForegroundColor Green
}

exit $proc.ExitCode
