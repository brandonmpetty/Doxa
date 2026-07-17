#!/usr/bin/env bash
# Runs a command (typically doxa_bench) while sampling CPU frequency and
# throttle signals, then reports whether the run was thermally contaminated.
# Companion to bench-monitor.ps1 (Windows).
#
#   Linux:  scaling_cur_freq per core (no root), Intel core/package
#           throttle-event counts, hottest thermal zone, and a warning if
#           the cpufreq governor is not "performance".
#   macOS:  pmset -g therm CPU_Speed_Limit (Intel Macs, no root).  Apple
#           Silicon exposes thermal pressure only via `sudo powermetrics
#           -s thermal`, so without sudo we sample what pmset provides.
#
# Usage:
#   ./bench-monitor.sh './build-bench/Doxa.Bench/doxa_bench --benchmark_filter=^BM_Sauvola$ --benchmark_repetitions=15'
#
# Output: bench-monitor.csv (time,freq_khz,temp_mc,speed_limit) + a verdict.

set -u

COMMAND="${1:?usage: bench-monitor.sh '<command>' [out.csv] [interval_seconds]}"
OUT_CSV="${2:-bench-monitor.csv}"
INTERVAL="${3:-1}"	# ~1 Hz is plenty for thermal effects; sysfs/pmset reads are cheap

OS="$(uname -s)"

sample_linux_freq() {
	# Average current frequency across cores, in kHz.
	awk '{ sum += $1; n++ } END { if (n) printf "%d", sum / n }' \
		/sys/devices/system/cpu/cpu*/cpufreq/scaling_cur_freq 2>/dev/null
}

sample_linux_temp() {
	# Hottest thermal zone, in millidegrees C.
	cat /sys/class/thermal/thermal_zone*/temp 2>/dev/null | sort -n | tail -1
}

sample_linux_throttle_count() {
	# Cumulative Intel throttle events; empty on AMD/ARM.
	cat /sys/devices/system/cpu/cpu*/thermal_throttle/*_throttle_count 2>/dev/null |
		awk '{ sum += $1 } END { if (NR) print sum }'
}

sample_mac_speed_limit() {
	# 100 = unthrottled.  Present on Intel Macs; often absent on Apple Silicon.
	pmset -g therm 2>/dev/null | awk '/CPU_Speed_Limit/ { print $3 }'
}

if [ "$OS" = "Linux" ]; then
	governor="$(cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor 2>/dev/null)"
	if [ -n "$governor" ] && [ "$governor" != "performance" ]; then
		echo "bench-monitor: WARNING - cpufreq governor is '$governor', not 'performance'."
		echo "  sudo cpupower frequency-set --governor performance"
	fi
	throttle_before="$(sample_linux_throttle_count)"
fi

echo "time,freq_khz,temp_mc,speed_limit" > "$OUT_CSV"

bash -c "$COMMAND" &
BENCH_PID=$!

while kill -0 "$BENCH_PID" 2>/dev/null; do
	if [ "$OS" = "Linux" ]; then
		echo "$(date +%H:%M:%S),$(sample_linux_freq),$(sample_linux_temp)," >> "$OUT_CSV"
	else
		echo "$(date +%H:%M:%S),,,$(sample_mac_speed_limit)" >> "$OUT_CSV"
	fi
	sleep "$INTERVAL"
done
wait "$BENCH_PID"
BENCH_EXIT=$?

SAMPLES=$(($(wc -l < "$OUT_CSV") - 1))
echo ""
echo "=== bench-monitor: $SAMPLES samples -> $OUT_CSV ==="

if [ "$SAMPLES" -lt 6 ]; then
	echo "bench-monitor: run too short to judge"
	exit "$BENCH_EXIT"
fi

if [ "$OS" = "Linux" ]; then
	# Clock decay: average of the first third vs the last third.
	tail -n +2 "$OUT_CSV" | awk -F, -v n="$SAMPLES" '
		{ freq[NR] = $2 }
		END {
			third = int(n / 3)
			for (i = 1; i <= third; i++) early += freq[i]
			for (i = n - third + 1; i <= n; i++) late += freq[i]
			early /= third; late /= third
			decay = early > 0 ? 100 * (early - late) / early : 0
			printf "Avg clock first->last third: %.0f -> %.0f kHz  (%.1f%% decay)\n", early, late, decay
			exit (decay > 5) ? 1 : 0
		}'
	decayed=$?

	throttle_after="$(sample_linux_throttle_count)"
	events=0
	if [ -n "${throttle_before:-}" ] && [ -n "$throttle_after" ]; then
		events=$((throttle_after - throttle_before))
		echo "Thermal throttle events during run: $events"
	fi

	if [ "$decayed" -ne 0 ] || [ "$events" -gt 0 ]; then
		echo "VERDICT: CONTAMINATED - clock decayed or thermal throttling fired."
	else
		echo "VERDICT: clean - clock stayed stable across the run."
	fi
else
	tail -n +2 "$OUT_CSV" | awk -F, '
		$4 != "" { if (min == "" || $4 < min) min = $4; n++ }
		END {
			if (!n) { print "No CPU_Speed_Limit data (Apple Silicon?) - use: sudo powermetrics -s thermal"; exit 0 }
			printf "Min CPU_Speed_Limit during run: %d%%\n", min
			if (min < 100) print "VERDICT: CONTAMINATED - macOS capped the CPU during the run."
			else print "VERDICT: clean - no speed limit applied."
		}'
fi

exit "$BENCH_EXIT"
