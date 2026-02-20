window.BENCHMARK_DATA = {
  "lastUpdate": 1771548551660,
  "repoUrl": "https://github.com/brandonmpetty/Doxa",
  "entries": {
    "Doxa Benchmarks (Linux)": [
      {
        "commit": {
          "author": {
            "email": "brandonpetty1981@gmail.com",
            "name": "Brandon M. Petty",
            "username": "brandonmpetty"
          },
          "committer": {
            "email": "noreply@github.com",
            "name": "GitHub",
            "username": "web-flow"
          },
          "distinct": true,
          "id": "b594e6fadd609a9789790c05e26c8dea16ca3d14",
          "message": "Merge pull request #52 from brandonmpetty/simd\n\nSpeed - Google Benchmark, SIMD, and DRDM and TR Singh improvements",
          "timestamp": "2026-02-15T19:00:29-06:00",
          "tree_id": "8d6d3a8b906c85676ac3324e729a0c4c0bc243e3",
          "url": "https://github.com/brandonmpetty/Doxa/commit/b594e6fadd609a9789790c05e26c8dea16ca3d14"
        },
        "date": 1771203852551,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_GlobalThreshold_Scalar_mean",
            "value": 12522.054120073222,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12519.950902238264 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_median",
            "value": 12552.93433661046,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12550.199354655195 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_stddev",
            "value": 60.321510232883405,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 59.884618204489584 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_cv",
            "value": 0.004817221651852329,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.004783135227294196 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_mean",
            "value": 12363.586496515174,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12362.12339110336 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_median",
            "value": 12318.485861546751,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12315.66549473516 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_stddev",
            "value": 90.12885847395765,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 90.60183633439178 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_cv",
            "value": 0.00728986354399361,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.007328986571966684 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_mean",
            "value": 382354.31866812205,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 382336.3433951964 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_median",
            "value": 382333.0240174647,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 382321.6140829692 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_stddev",
            "value": 187.3870363791079,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 183.1925937707969 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_cv",
            "value": 0.0004900874064450077,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.00047913989066282025 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_mean",
            "value": 69169.68548601873,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 69148.30280613502 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_median",
            "value": 69080.1078561919,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 69075.7400996203 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_stddev",
            "value": 166.04073928397892,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 162.99809646424038 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_cv",
            "value": 0.0024004842311671454,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0023572248319850123 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_mean",
            "value": 50058.82316727118,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 50055.82527926441 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_median",
            "value": 49850.71955030364,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 49847.493193491624 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_stddev",
            "value": 525.6388268469456,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 525.0974433685203 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_cv",
            "value": 0.010500423173963306,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.010490236459772078 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_mean",
            "value": 36649.934892067264,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 36648.15903309226 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_median",
            "value": 36655.24835066251,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 36653.072834749604 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_stddev",
            "value": 40.64424632073148,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 40.26525015135944 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_cv",
            "value": 0.0011089854986216841,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.001098697757641824 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_mean",
            "value": 434419.54043343785,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 434394.4013622297 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_median",
            "value": 434468.4272445836,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 434443.4687306501 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_stddev",
            "value": 757.4228600114122,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 762.1248080918766 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_cv",
            "value": 0.0017435285237300813,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0017544535696176285 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_mean",
            "value": 9449.19712581639,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 9448.693342149296 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_median",
            "value": 9409.26978193992,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 9408.908633345913 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_stddev",
            "value": 86.9873793508884,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 86.98162713513456 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_cv",
            "value": 0.009205795814464278,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.00920567786310957 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_mean",
            "value": 2205071.10299213,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2204889.960629917 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_median",
            "value": 2202673.7354330746,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2202457.50236221 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_stddev",
            "value": 6033.434880185028,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6018.844631630086 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_cv",
            "value": 0.002736163415319384,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0027297709813647823 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_mean",
            "value": 5560597.799999973,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5560239.898412699 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_median",
            "value": 5551701.488095145,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5551382.543650844 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_stddev",
            "value": 25594.54241294777,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 25595.155146920064 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_cv",
            "value": 0.004602840078264227,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.004603246553125667 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_mean",
            "value": 168594.68412336605,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 168585.2219608783 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_median",
            "value": 168287.40345613944,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 168274.65822632876 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_stddev",
            "value": 794.1247860938432,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 796.8036822807923 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_cv",
            "value": 0.0047102599362667755,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.004726414765261558 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_mean",
            "value": 1966694.068278804,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1966580.5044096701 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_median",
            "value": 1964813.2005689747,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1964715.2645803522 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_stddev",
            "value": 7956.295790201444,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 7924.322342655994 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_cv",
            "value": 0.004045517764318359,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.004029492982813193 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_mean",
            "value": 2029664.0665706166,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2029578.5296829944 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_median",
            "value": 2023095.6152737974,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2023005.9711815484 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_stddev",
            "value": 13880.538201638545,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 13885.165827287597 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_cv",
            "value": 0.006838835268484372,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.006841403584150233 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_mean",
            "value": 3599816.9892307706,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3599641.4487179653 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_median",
            "value": 3597857.9564102395,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3597755.812820534 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_stddev",
            "value": 5264.1304457050255,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5285.1753143891065 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_cv",
            "value": 0.0014623327967652863,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0014682504881899992 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_mean",
            "value": 1984427.219464032,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1984329.7737658594 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_median",
            "value": 1974111.349788413,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1973934.2708039428 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_stddev",
            "value": 22079.361174788053,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 22079.493992361244 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_cv",
            "value": 0.011126314413663104,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.011126927733618994 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_mean",
            "value": 113620099.40000066,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 113615763.53333311 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_median",
            "value": 113603372.91666886,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 113596298.41666675 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_stddev",
            "value": 85094.58782008974,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 85533.06575335594 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_cv",
            "value": 0.0007489395650017293,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0007528274518725727 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_mean",
            "value": 1303741.9160149016,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1303685.8618249565 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_median",
            "value": 1303589.238361269,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1303529.128491618 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_stddev",
            "value": 640.6495301000839,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 642.4705472865953 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_cv",
            "value": 0.0004913929070090291,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0004928108573542685 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_mean",
            "value": 59162174.70833304,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 59158463.35833297 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_median",
            "value": 59158726.958333574,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 59155898.416666016 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_stddev",
            "value": 14228.107958062017,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 13738.22842748994 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_cv",
            "value": 0.0002404933224345787,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.00023222760781116189 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_mean",
            "value": 565150560.1000025,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 565125616.0000004 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_median",
            "value": 564837534.0000058,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 564815855.9999956 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_stddev",
            "value": 683152.7250964878,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 675714.9703348116 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_cv",
            "value": 0.0012087977493565696,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.001195689862932724 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_mean",
            "value": 11785215.085714187,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 11784761.334453743 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_median",
            "value": 11786605.596638452,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 11786240.042016659 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_stddev",
            "value": 26767.56408645975,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 26745.59070009809 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_cv",
            "value": 0.002271283459128962,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0022695063515546215 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_mean",
            "value": 33505256.114285737,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 33503839.195238005 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_median",
            "value": 33500869.21428607,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 33499039.07142824 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_stddev",
            "value": 18619.62727588114,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 19065.51210488626 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_cv",
            "value": 0.0005557225771493874,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0005690545490558615 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_mean",
            "value": 4587705.199339956,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4587141.119471971 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_median",
            "value": 4585856.633663395,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4585356.138613822 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_stddev",
            "value": 3592.8115002053673,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3768.9156929087976 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_cv",
            "value": 0.0007831391390890317,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0008216262797998767 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_mean",
            "value": 2074022.8300441795,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2073934.9081001412 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_median",
            "value": 2069446.7879234194,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2069349.1752577208 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_stddev",
            "value": 11015.622395927758,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 11042.900381991336 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_cv",
            "value": 0.005311234879556804,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0053246128115502665 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_mean",
            "value": 61160359.66086934,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 61157615.28695662 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_median",
            "value": 61151387.69565252,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 61148952.86956475 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_stddev",
            "value": 33594.346907884945,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 33386.43194688861 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_cv",
            "value": 0.0005492830175323309,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0005459080081889506 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "brandonpetty1981@gmail.com",
            "name": "Brandon M. Petty",
            "username": "brandonmpetty"
          },
          "committer": {
            "email": "noreply@github.com",
            "name": "GitHub",
            "username": "web-flow"
          },
          "distinct": true,
          "id": "81280754d790861e43f3c7290203cfc5e3852879",
          "message": "Merge pull request #53 from brandonmpetty/v0.9.5\n\nv0.9.5",
          "timestamp": "2026-02-19T18:45:27-06:00",
          "tree_id": "fb77028a5a39bb4b743da2b70032b7b5afa1a7b4",
          "url": "https://github.com/brandonmpetty/Doxa/commit/81280754d790861e43f3c7290203cfc5e3852879"
        },
        "date": 1771548550701,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_GlobalThreshold_Scalar_mean",
            "value": 12408.896689892366,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12406.608116589548 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_median",
            "value": 12378.053569845506,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12377.101652394373 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_stddev",
            "value": 89.31812712061851,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 88.84583203858243 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_cv",
            "value": 0.007197910447056291,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.007161170176704612 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_mean",
            "value": 12356.640555692644,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12355.54953986108 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_median",
            "value": 12360.805930679406,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12359.930547230357 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_stddev",
            "value": 29.546097421639757,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 29.45456320151116 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_cv",
            "value": 0.002391110859660639,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0023839136500149825 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_mean",
            "value": 374932.22448543145,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 374894.9943330662 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_median",
            "value": 374714.9788826497,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 374683.7642341623 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_stddev",
            "value": 454.85093906779883,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 454.92526506616815 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_cv",
            "value": 0.0012131550967432853,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.001213473831186983 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_mean",
            "value": 68960.15207010286,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 68954.40728597448 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_median",
            "value": 68976.93250627677,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 68970.53281149993 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_stddev",
            "value": 34.23521944699731,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 33.15976380114013 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_cv",
            "value": 0.00049644930324682,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.00048089404443165914 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_mean",
            "value": 49888.00982483955,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 49884.469314495786 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_median",
            "value": 49851.98760181641,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 49848.193433287626 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_stddev",
            "value": 117.59551192972273,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 117.2457841007135 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_cv",
            "value": 0.002357189880747081,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.002350346424686598 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_mean",
            "value": 37367.731675257055,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 37364.78592271397 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_median",
            "value": 37359.69846464313,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 37356.19196051152 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_stddev",
            "value": 136.43987885224206,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 136.16781990115817 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_cv",
            "value": 0.0036512753848151115,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0036442820837461845 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_mean",
            "value": 438887.030460669,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 438846.5921027893 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_median",
            "value": 438735.9542463148,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 438696.5427765595 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_stddev",
            "value": 378.1481628215404,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 376.40986987321094 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_cv",
            "value": 0.0008616070573437193,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0008577254025594575 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_mean",
            "value": 10254.468269463494,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 10253.620033004514 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_median",
            "value": 10247.131614654061,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 10246.67157578201 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_stddev",
            "value": 16.087742787211916,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 16.216041911669684 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_cv",
            "value": 0.0015688519740335223,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0015814943268302544 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_mean",
            "value": 2176810.9450000096,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2176656.207812502 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_median",
            "value": 2178611.442187517,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2178475.945312497 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_stddev",
            "value": 3799.7090974268676,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3841.1578339163834 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_cv",
            "value": 0.001745539320332134,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0017647057997168389 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_mean",
            "value": 5354053.90229011,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5353672.096946573 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_median",
            "value": 5354421.255725192,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5354026.900763371 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_stddev",
            "value": 7431.357954692462,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 7445.596551116696 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_cv",
            "value": 0.001387987138402514,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0013907457192537506 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_mean",
            "value": 168624.08723199266,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 168613.7102384967 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_median",
            "value": 168534.37605396163,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 168523.31642977498 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_stddev",
            "value": 209.78506052316146,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 209.65700022152842 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_cv",
            "value": 0.0012440990131768047,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0012434160895040969 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_mean",
            "value": 1964320.6042134825,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1964188.629494389 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_median",
            "value": 1963641.182584297,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1963459.0955056183 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_stddev",
            "value": 4439.689694403378,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4427.377231022875 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_cv",
            "value": 0.002260165517217612,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.00225404890576245 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_mean",
            "value": 2019346.0889208757,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2019246.6526618705 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_median",
            "value": 2019783.3798561194,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2019678.682014394 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_stddev",
            "value": 3903.7555060852937,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3922.1729804598313 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_cv",
            "value": 0.0019331780359509514,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0019423941970087854 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_mean",
            "value": 3583526.2857142887,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3583274.143877548 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_median",
            "value": 3584003.8188775093,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3583784.066326514 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_stddev",
            "value": 7691.98240118068,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 7779.969512195287 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_cv",
            "value": 0.0021464841577539793,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0021711901461651476 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_mean",
            "value": 1976493.618335678,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1976381.6866008453 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_median",
            "value": 1975563.6149506331,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1975488.4880112745 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_stddev",
            "value": 4041.3664190631594,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4012.2866713527465 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_cv",
            "value": 0.0020447151367309867,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0020301173090980363 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_mean",
            "value": 114618087.46666643,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 114608898.23333342 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_median",
            "value": 114580141.91666642,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 114566858.83333388 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_stddev",
            "value": 199105.03044543666,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 199601.55575554096 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_cv",
            "value": 0.0017371170191907183,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0017415886447941426 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_mean",
            "value": 1330183.2034155573,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1330097.1620493399 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_median",
            "value": 1329780.6935483734,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1329708.9098671789 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_stddev",
            "value": 832.2776902411118,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 845.5169878221765 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_cv",
            "value": 0.0006256865130337263,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0006356806193913313 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_mean",
            "value": 59729798.34782614,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 59725625.426087044 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_median",
            "value": 59836937.21739028,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 59834384.21739112 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_stddev",
            "value": 195276.5598074406,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 196157.84412418428 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_cv",
            "value": 0.0032693323133334783,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0032843162834173714 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_mean",
            "value": 516895029.5333351,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 516860453.66666543 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_median",
            "value": 517075537.00000143,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 517056128.3333276 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_stddev",
            "value": 1051099.05512012,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1053956.9766014745 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_cv",
            "value": 0.002033486481905382,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.002039151900913654 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_mean",
            "value": 11570554.851239704,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 11569787.361983428 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_median",
            "value": 11573932.652892567,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 11573517.58677673 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_stddev",
            "value": 22459.563156099575,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 22634.841830194684 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_cv",
            "value": 0.0019410964681346454,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.001956374920473418 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_mean",
            "value": 33244417.21428557,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 33241100.21428583 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_median",
            "value": 33237902.476190448,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 33233857.99999996 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_stddev",
            "value": 17415.581754365063,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 17122.76082939765 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_cv",
            "value": 0.0005238648535213712,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0005151081257544811 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_mean",
            "value": 4391373.753605003,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4390575.989968641 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_median",
            "value": 4391972.7053291425,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4390124.128526661 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_stddev",
            "value": 2435.0715738873982,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2438.7375155547124 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_cv",
            "value": 0.0005545124852760208,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0005554481965752586 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_mean",
            "value": 2063225.896023561,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2063029.4730485869 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_median",
            "value": 2062758.1723122045,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2062584.3343151447 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_stddev",
            "value": 1400.5280660671908,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1434.0156031668587 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_cv",
            "value": 0.000678805005678931,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0006951018499254789 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_mean",
            "value": 61720660.19130398,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 61714427.69565201 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_median",
            "value": 61730471.91304294,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 61724578.78260897 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_stddev",
            "value": 37119.905567738264,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 37944.39213692415 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_cv",
            "value": 0.0006014178307990329,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0006148382728921824 ns\nthreads: 1"
          }
        ]
      }
    ],
    "Doxa Benchmarks (macOS)": [
      {
        "commit": {
          "author": {
            "email": "brandonpetty1981@gmail.com",
            "name": "Brandon M. Petty",
            "username": "brandonmpetty"
          },
          "committer": {
            "email": "noreply@github.com",
            "name": "GitHub",
            "username": "web-flow"
          },
          "distinct": true,
          "id": "b594e6fadd609a9789790c05e26c8dea16ca3d14",
          "message": "Merge pull request #52 from brandonmpetty/simd\n\nSpeed - Google Benchmark, SIMD, and DRDM and TR Singh improvements",
          "timestamp": "2026-02-15T19:00:29-06:00",
          "tree_id": "8d6d3a8b906c85676ac3324e729a0c4c0bc243e3",
          "url": "https://github.com/brandonmpetty/Doxa/commit/b594e6fadd609a9789790c05e26c8dea16ca3d14"
        },
        "date": 1771203874907,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_GlobalThreshold_Scalar_mean",
            "value": 5899.521801090481,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5846.628487466363 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_median",
            "value": 5794.2298983854735,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5782.865387338901 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_stddev",
            "value": 250.54919156338028,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 170.45156173776684 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_cv",
            "value": 0.04246940684532571,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.029153821232727584 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_mean",
            "value": 8046.521978650952,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 7914.420926541141 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_median",
            "value": 7828.807433807936,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 7787.135110256162 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_stddev",
            "value": 488.53961544947026,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 349.8696234604323 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_cv",
            "value": 0.060714382778753906,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.04420659789361705 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_mean",
            "value": 371978.43038815254,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 367605.5158324825 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_median",
            "value": 375076.27885597764,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 372102.40040858154 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_stddev",
            "value": 19318.75918197186,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 16622.584636810592 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_cv",
            "value": 0.05193515968604173,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.04521853976855311 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_mean",
            "value": 34202.20575550646,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 33337.77663274507 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_median",
            "value": 33267.91938683461,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 33093.57207265244 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_stddev",
            "value": 2381.3846191535476,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1004.1434554526928 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_cv",
            "value": 0.06962663859099646,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.03012028865975428 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_mean",
            "value": 84916.00765727105,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 81884.46762162508 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_median",
            "value": 84355.14443197582,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 81833.85041916912 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_stddev",
            "value": 3537.108285082818,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4328.307872058641 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_cv",
            "value": 0.04165419904523677,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.052858716650135085 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_mean",
            "value": 38441.16743255841,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 36754.06922569934 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_median",
            "value": 38073.86670757485,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 36570.44158087299 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_stddev",
            "value": 2364.009641949114,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1808.5898239175044 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_cv",
            "value": 0.06149682228294856,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.04920787988974277 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_mean",
            "value": 383661.219261478,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 365542.31536926155 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_median",
            "value": 359902.861027948,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 355569.61077844293 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_stddev",
            "value": 44219.58112740963,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 21072.405936367617 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_cv",
            "value": 0.11525684355726477,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.057646967397142 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_mean",
            "value": 12946.660476116707,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 9668.732476735997 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_median",
            "value": 13652.705755370805,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 9424.36830245795 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_stddev",
            "value": 3772.3708829049983,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1320.1374338863652 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_cv",
            "value": 0.29137791091873166,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.13653676291724454 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_mean",
            "value": 913086.3890058498,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 894546.5497076031 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_median",
            "value": 901812.694736839,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 898747.3684210579 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_stddev",
            "value": 64750.79722992274,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 70709.96130350753 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_cv",
            "value": 0.07091420703403772,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.07904559167616289 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_mean",
            "value": 3642263.157894728,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3455297.4828375345 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_median",
            "value": 3445734.0778031657,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3342951.945080091 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_stddev",
            "value": 643782.201874146,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 428606.2516852959 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_cv",
            "value": 0.17675334646776591,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.12404322748307013 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_mean",
            "value": 399206.28597743536,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 394881.8788855637 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_median",
            "value": 393887.63527515007,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 384911.58185586083 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_stddev",
            "value": 27140.1113600326,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 27209.281179841542 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_cv",
            "value": 0.06798518037756214,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.06890486151613648 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_mean",
            "value": 1151087.306834249,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1095333.8570306322 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_median",
            "value": 1111404.7195601054,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1085112.3330714977 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_stddev",
            "value": 197697.11252739961,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 102916.74844227316 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_cv",
            "value": 0.17174814747207273,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0939592506720031 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_mean",
            "value": 1136228.5333999977,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1117029.6000000008 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_median",
            "value": 1197174.7089999951,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1188437.999999991 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_stddev",
            "value": 134254.21299505437,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 133037.59620610165 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_cv",
            "value": 0.1181577552830136,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.11909943676165927 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_mean",
            "value": 1627057.0651605213,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1609938.882282995 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_median",
            "value": 1633818.5695600486,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1618029.7265160424 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_stddev",
            "value": 31657.847121491795,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 23436.516809073753 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_cv",
            "value": 0.019457121572050404,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.01455739535642452 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_mean",
            "value": 904788.6839047152,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 899079.3724578761 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_median",
            "value": 885464.119697856,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 876547.9372457868 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_stddev",
            "value": 63778.66387633172,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 62788.28087987114 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_cv",
            "value": 0.07049012107566141,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.06983619333654874 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_mean",
            "value": 131545349.28333373,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 128186633.33333333 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_median",
            "value": 134698079.83333483,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 124966749.99999988 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_stddev",
            "value": 5439733.148559392,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6204956.12914255 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_cv",
            "value": 0.041352531109578226,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.048405640805054426 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_mean",
            "value": 1001501.648960002,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 949137.9199999938 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_median",
            "value": 1033187.6890666686,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 893110.9333333324 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_stddev",
            "value": 126371.99536347653,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 105671.97253158464 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_cv",
            "value": 0.12618251352327386,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.1113346862504296 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_mean",
            "value": 67004366.20000024,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 66872788.8888886 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_median",
            "value": 67187347.2222223,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 66981222.22222322 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_stddev",
            "value": 1911699.2963029728,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1891759.7519114693 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_cv",
            "value": 0.02853096603580687,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.028288931616934535 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_mean",
            "value": 555083697.2666712,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 552427000.0000001 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_median",
            "value": 554462000.0000008,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 553043666.6666579 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_stddev",
            "value": 11875282.585211944,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12917044.392331954 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_cv",
            "value": 0.021393679266186173,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.023382355301844314 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_mean",
            "value": 9893961.397419257,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 9812611.612903252 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_median",
            "value": 9514246.503225686,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 9497883.870967746 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_stddev",
            "value": 724162.4856571818,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 633932.0943917037 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_cv",
            "value": 0.07319237023161143,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.06460380981125396 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_mean",
            "value": 30420463.163158286,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 30278710.52631572 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_median",
            "value": 30256330.052632045,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 30196315.78947281 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_stddev",
            "value": 794193.6967844331,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 615084.2644341826 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_cv",
            "value": 0.026107219095410354,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.020314083847778226 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_mean",
            "value": 2368340.4496350577,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2352748.3211678853 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_median",
            "value": 2376458.636496389,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2370600.0000000075 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_stddev",
            "value": 103204.94298505157,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 97912.64313975212 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_cv",
            "value": 0.043576903397041025,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.04161628435086889 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_mean",
            "value": 2411182.077205902,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2398868.7500000214 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_median",
            "value": 2372003.0643382226,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2364027.573529427 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_stddev",
            "value": 119218.33413836607,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 112156.51418672784 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_cv",
            "value": 0.049443936758404104,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.04675391856546 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_mean",
            "value": 78555228.62608653,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 77581573.91304335 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_median",
            "value": 74595374.99999876,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 74353782.60869578 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_stddev",
            "value": 15639584.607387915,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 14521671.840035552 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_cv",
            "value": 0.19909030730252802,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.18717939205915113 ns\nthreads: 1"
          }
        ]
      }
    ],
    "Doxa Benchmarks (Windows)": [
      {
        "commit": {
          "author": {
            "email": "brandonpetty1981@gmail.com",
            "name": "Brandon M. Petty",
            "username": "brandonmpetty"
          },
          "committer": {
            "email": "noreply@github.com",
            "name": "GitHub",
            "username": "web-flow"
          },
          "distinct": true,
          "id": "b594e6fadd609a9789790c05e26c8dea16ca3d14",
          "message": "Merge pull request #52 from brandonmpetty/simd\n\nSpeed - Google Benchmark, SIMD, and DRDM and TR Singh improvements",
          "timestamp": "2026-02-15T19:00:29-06:00",
          "tree_id": "8d6d3a8b906c85676ac3324e729a0c4c0bc243e3",
          "url": "https://github.com/brandonmpetty/Doxa/commit/b594e6fadd609a9789790c05e26c8dea16ca3d14"
        },
        "date": 1771203918727,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_GlobalThreshold_Scalar_mean",
            "value": 8522.081772089165,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 8369.488463226735 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_median",
            "value": 8512.871438295351,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 8349.608443124058 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_stddev",
            "value": 105.85465044211271,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 247.50425428431885 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_cv",
            "value": 0.01242121975276033,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.029572208071232252 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_mean",
            "value": 12610.56196428549,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12332.589285714288 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_median",
            "value": 12392.18303571375,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12276.785714285714 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_stddev",
            "value": 437.45263947083004,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 159.0646519389815 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_cv",
            "value": 0.03468938503373159,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.012897912048626918 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_mean",
            "value": 391507.0345566575,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 388427.5381730512 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_median",
            "value": 391809.0543798694,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 389264.66648807924 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_stddev",
            "value": 2080.114231127654,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1871.8758182812599 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_cv",
            "value": 0.005313095417259042,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.004819112020444099 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_mean",
            "value": 69924.28501276742,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 69055.6865055981 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_median",
            "value": 69802.15576507626,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 69055.6865055981 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_stddev",
            "value": 1109.955017024982,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 542.5527134181566 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_cv",
            "value": 0.015873669881963273,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.00785674201318922 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_mean",
            "value": 117992.71249999956,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 116699.21875 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_median",
            "value": 117706.72656250093,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 117187.50000000003 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_stddev",
            "value": 1988.9694053817555,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1391.815704464871 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_cv",
            "value": 0.016856713971905364,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.011926521183029521 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_mean",
            "value": 36991.6899258024,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 36663.27377923018 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_median",
            "value": 36978.98909811769,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 36830.68598826775 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_stddev",
            "value": 181.9026380703377,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 477.1982165153063 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_cv",
            "value": 0.004917391944925911,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.01301570119975593 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_mean",
            "value": 389288.62723214435,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 387137.2767857143 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_median",
            "value": 389141.0156250227,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 388009.2075892857 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_stddev",
            "value": 929.7397540000333,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3647.548246252164 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_cv",
            "value": 0.002388304432653261,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.009421847145634417 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_mean",
            "value": 15087.482622845466,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 15004.11828518623 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_median",
            "value": 15100.704126321041,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 15066.897022781148 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_stddev",
            "value": 43.68779959391661,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 85.9633267807254 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_cv",
            "value": 0.0028956321399677726,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.005729315455050642 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_mean",
            "value": 2564438.749999982,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2533482.1428571427 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_median",
            "value": 2561545.1785713257,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2539062.5 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_stddev",
            "value": 16808.802346360862,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 36379.477707587524 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_cv",
            "value": 0.00655457352855902,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.014359476663435426 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_mean",
            "value": 7002123.431372446,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6985294.117647059 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_median",
            "value": 6995245.588235414,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6969975.490196079 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_stddev",
            "value": 36176.78604308705,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 64082.41624798523 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_cv",
            "value": 0.005166545034182044,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.009173903799711568 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_mean",
            "value": 175429.0116635997,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 172651.93370165746 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_median",
            "value": 174133.51749538904,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 172651.93370165746 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_stddev",
            "value": 4448.326145597329,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4890.864327801893 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_cv",
            "value": 0.02535684436350459,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.028327886186628563 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_mean",
            "value": 2653405.6785714356,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2633928.5714285714 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_median",
            "value": 2647825.5357143814,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2622767.857142857 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_stddev",
            "value": 23815.341627769383,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 46688.61755212247 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_cv",
            "value": 0.00897538654571332,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.01772584801978887 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_mean",
            "value": 2960726.9449715563,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2810721.062618596 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_median",
            "value": 2970455.787476351,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2816650.853889943 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_stddev",
            "value": 198731.4458377672,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 89929.73723968188 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_cv",
            "value": 0.06712251738556609,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.03199525503818555 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_mean",
            "value": 4898253.357142964,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4877232.142857143 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_median",
            "value": 4897503.928571365,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4854910.714285714 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_stddev",
            "value": 52548.3664443523,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 84630.30629520063 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_cv",
            "value": 0.010727980488743547,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.01735211772093816 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_mean",
            "value": 2621586.3928570924,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2589285.7142857146 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_median",
            "value": 2627859.999999974,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2594866.0714285714 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_stddev",
            "value": 16405.908210909216,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12478.05791007847 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_cv",
            "value": 0.006258007844261622,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.004819112020444099 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_mean",
            "value": 180332519.9999985,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 180357142.85714287 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_median",
            "value": 180341685.71429226,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 180803571.42857143 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_stddev",
            "value": 1174424.0319750882,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 998244.6328062778 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_cv",
            "value": 0.0065125471100559,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.005534821726450648 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_mean",
            "value": 1749531.339285707,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1736886.160714286 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_median",
            "value": 1751393.9732143008,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1743861.607142857 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_stddev",
            "value": 7761.879098407013,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 9551.523393989208 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_cv",
            "value": 0.004436547619419043,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.005499222464908806 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_mean",
            "value": 92437729.33333428,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 92083333.33333334 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_median",
            "value": 92383873.33333169,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 91666666.66666666 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_stddev",
            "value": 640801.4255856811,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1187682.7344777286 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_cv",
            "value": 0.006932249744851745,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.012897912048626918 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_mean",
            "value": 592335069.9999901,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 592187500 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_median",
            "value": 587533749.9999774,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 585937500 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_stddev",
            "value": 21854866.05829046,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 21678807.696113233 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_cv",
            "value": 0.03689612039734677,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.036608012996075114 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_mean",
            "value": 12916309.800000364,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12500000 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_median",
            "value": 12903703.000000631,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12500000 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_stddev",
            "value": 201975.03345009263,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 247052.9422006547 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_cv",
            "value": 0.015637208814090767,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.01976423537605237 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_mean",
            "value": 36746194.14634114,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 36280487.80487805 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_median",
            "value": 36764070.73170894,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 36204268.29268293 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_stddev",
            "value": 449770.82439202565,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 417471.46151289414 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_cv",
            "value": 0.012239929463193399,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.011506776418170526 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_mean",
            "value": 5635892.148760295,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5630165.289256198 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_median",
            "value": 5636487.190082609,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5617252.0661157025 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_stddev",
            "value": 46633.83881429864,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 54019.88807685786 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_cv",
            "value": 0.008274437761296853,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.009594725074935487 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_mean",
            "value": 3126369.4779116595,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3099899.598393575 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_median",
            "value": 3154672.690763197,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3168925.702811245 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_stddev",
            "value": 186418.40568060224,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 186149.56041906137 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_cv",
            "value": 0.05962775897016667,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.060050190178910154 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_mean",
            "value": 103125246.00000417,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 102812500 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_median",
            "value": 103541850.00001052,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 103125000 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_stddev",
            "value": 1079246.1279166988,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1307281.2914599602 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_cv",
            "value": 0.010465392033262693,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.012715197971647028 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}