window.BENCHMARK_DATA = {
  "lastUpdate": 1771651799868,
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
          "id": "0bf99539c13d1fdb9557f9f7df80e1c4e55b7230",
          "message": "Merge pull request #50 from brandonmpetty/matlab\n\nMatlab Bindings",
          "timestamp": "2026-02-20T23:25:49-06:00",
          "tree_id": "a1d5d65a5f62bf077a856e3869430b8af73c0baa",
          "url": "https://github.com/brandonmpetty/Doxa/commit/0bf99539c13d1fdb9557f9f7df80e1c4e55b7230"
        },
        "date": 1771651770859,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_GlobalThreshold_Scalar_mean",
            "value": 12416.196308861916,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12415.21947705917 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_median",
            "value": 12390.370179583195,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12389.20200010658 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_stddev",
            "value": 128.57742841830336,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 128.3122343389199 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_cv",
            "value": 0.010355621417368595,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.010335075797573702 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_mean",
            "value": 12281.163685455165,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12279.973313803692 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_median",
            "value": 12279.654625348576,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12278.48195567006 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_stddev",
            "value": 8.224586854258515,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 8.107824810208914 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_cv",
            "value": 0.0006696911681096688,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0006602477548623869 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_mean",
            "value": 374614.84969044605,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 374574.66040376853 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_median",
            "value": 374518.4904441446,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 374469.62772543705 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_stddev",
            "value": 360.41600100654256,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 362.82015858729636 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_cv",
            "value": 0.0009620974750583529,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.000968619068348613 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_mean",
            "value": 68982.8660945484,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 68976.47429932041 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_median",
            "value": 68939.55781536768,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 68933.18140780783 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_stddev",
            "value": 64.48137060217391,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 63.89606605951818 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_cv",
            "value": 0.0009347447308697683,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0009263457825090332 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_mean",
            "value": 49671.602931758265,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 49665.44800398499 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_median",
            "value": 49609.97979079194,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 49607.45339073505 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_stddev",
            "value": 217.53707186678457,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 211.6213188860591 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_cv",
            "value": 0.004379505774469361,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.004260936473765006 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_mean",
            "value": 37247.95712478821,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 37245.79518824506 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_median",
            "value": 37213.45421028566,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 37211.23687397385 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_stddev",
            "value": 106.69830567947267,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 106.28731169882312 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_cv",
            "value": 0.002864541143075625,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.002853672774648342 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_mean",
            "value": 440421.22901098646,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 440383.52043956035 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_median",
            "value": 439630.27880690293,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 439603.6219780206 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_stddev",
            "value": 2121.091517625931,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2099.48721778432 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_cv",
            "value": 0.0048160519473347645,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.004767406409051721 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_mean",
            "value": 10234.555916697765,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 10233.974949237276 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_median",
            "value": 10232.431560119809,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 10231.898130025846 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_stddev",
            "value": 6.8357463451232094,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6.81287165178051 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_cv",
            "value": 0.0006679084467134162,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0006657111909667383 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_mean",
            "value": 2181440.819844964,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2181298.1218604622 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_median",
            "value": 2177656.21085273,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2177529.742635655 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_stddev",
            "value": 16889.972099974628,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 16904.208499994515 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_cv",
            "value": 0.007742576349687545,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.007749609432376286 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_mean",
            "value": 5306020.225190856,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5305565.278625959 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_median",
            "value": 5303574.0992367165,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5303100.618320617 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_stddev",
            "value": 6835.349419330724,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6870.9479144249735 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_cv",
            "value": 0.0012882252854746438,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0012950454011197122 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_mean",
            "value": 168412.06306674753,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 168403.06838244112 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_median",
            "value": 168431.52146722618,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 168418.952976548 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_stddev",
            "value": 37.36271118203062,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 36.83711566531322 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_cv",
            "value": 0.00022185293916399853,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.00021874373204208263 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_mean",
            "value": 1966848.822503506,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1966708.4717299566 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_median",
            "value": 1963680.2489451647,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1963499.5555555671 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_stddev",
            "value": 8447.404853735361,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 8446.227080779958 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_cv",
            "value": 0.004294892803699611,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.004294600446476181 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_mean",
            "value": 2018310.7896403,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2018172.0397122328 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_median",
            "value": 2018536.6661870677,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2018409.215827351 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_stddev",
            "value": 3269.4902615785263,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3287.709620264207 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_cv",
            "value": 0.001619914176924759,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0016290532004065393 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_mean",
            "value": 3582395.097186692,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3582179.745780047 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_median",
            "value": 3580759.675191822,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3580604.3554987237 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_stddev",
            "value": 5852.188439745538,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5802.182398665458 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_cv",
            "value": 0.0016335965969642343,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0016197351362674257 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_mean",
            "value": 1975396.1385049243,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1975255.161354016 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_median",
            "value": 1975509.8744710577,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1975325.4541607853 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_stddev",
            "value": 944.852984508557,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 954.335980931545 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_cv",
            "value": 0.0004783106365813126,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.00048314567130524954 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_mean",
            "value": 113001060.36666715,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 112992687.23333332 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_median",
            "value": 112987584.00000016,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 112977239.99999931 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_stddev",
            "value": 48235.45259217881,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 48146.852843031054 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_cv",
            "value": 0.00042685840677657224,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0004261059190813503 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_mean",
            "value": 1328151.2676163358,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1328044.3665717 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_median",
            "value": 1328189.0436847003,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1328121.7654320959 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_stddev",
            "value": 619.1953581610899,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 627.4625861117248 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_cv",
            "value": 0.0004662084607820119,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.00047247110255171476 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_mean",
            "value": 58640062.20833342,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 58636134.36666681 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_median",
            "value": 58645462.00000002,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 58642049.66666739 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_stddev",
            "value": 24033.37794695664,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 23926.13139082837 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_cv",
            "value": 0.0004098457102854373,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0004080441463144915 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_mean",
            "value": 518847542.26666516,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 518809449.5999982 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_median",
            "value": 518935603.3333279,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 518898256.3333298 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_stddev",
            "value": 546108.9354466123,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 542433.2798386369 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_cv",
            "value": 0.0010525422035553094,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.001045534695362339 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_mean",
            "value": 11569657.57355373,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 11568733.619834755 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_median",
            "value": 11560832.264462698,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 11559816.636363609 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_stddev",
            "value": 27945.15121237211,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 27992.013489131445 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_cv",
            "value": 0.0024153827401296626,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.002419626417980508 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_mean",
            "value": 33239496.847619016,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 33236611.29999994 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_median",
            "value": 33229859.690475814,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 33225429.571428675 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_stddev",
            "value": 23743.727003144468,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 25029.5261201613 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_cv",
            "value": 0.0007143226960382,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0007530709401822003 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_mean",
            "value": 4369238.354517123,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4368836.307165145 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_median",
            "value": 4370175.059190029,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4369727.358255417 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_stddev",
            "value": 6085.849786792379,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6021.144810959899 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_cv",
            "value": 0.001392885737282001,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.001378203344694987 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_mean",
            "value": 2075740.5444117566,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2075547.607941179 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_median",
            "value": 2057828.2720588078,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2057593.2617647066 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_stddev",
            "value": 40526.52268246762,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 40535.92745315857 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_cv",
            "value": 0.019523886446970385,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.019530232550708786 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_mean",
            "value": 60435948.62608633,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 60432247.86086931 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_median",
            "value": 60415935.000000216,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 60412310.08695693 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_stddev",
            "value": 46304.66760114814,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 45390.88434938346 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_cv",
            "value": 0.0007661775591152278,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0007511036897698234 ns\nthreads: 1"
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
        "date": 1771548558062,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_GlobalThreshold_Scalar_mean",
            "value": 5727.969220025624,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5707.909266748726 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_median",
            "value": 5616.272702152781,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5584.380416488734 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_stddev",
            "value": 406.7414240341772,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 409.6173868682281 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_cv",
            "value": 0.07100970839929856,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.07176312161345019 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_mean",
            "value": 7627.412572055109,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 7575.399862676119 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_median",
            "value": 7280.890556055239,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 7217.546586330422 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_stddev",
            "value": 940.0249269305735,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 943.3212232847194 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_cv",
            "value": 0.12324296320020561,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.12452428127688007 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_mean",
            "value": 315491.32246101927,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 313684.1972187108 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_median",
            "value": 315700.6689844058,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 315369.99578592536 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_stddev",
            "value": 8148.026284819714,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 9391.175672867024 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_cv",
            "value": 0.02582646717906623,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.029938312978894478 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_mean",
            "value": 33964.75508595822,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 33341.32764462293 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_median",
            "value": 33459.827657171685,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 31865.980675116174 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_stddev",
            "value": 2108.873637297479,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2118.508531186394 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_cv",
            "value": 0.06209005870822057,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.06354001717529247 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_mean",
            "value": 89640.54472373752,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 86973.15627223157 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_median",
            "value": 87470.61252074905,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 85625.91889969184 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_stddev",
            "value": 7975.678493294879,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6077.753882051234 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_cv",
            "value": 0.08897400744133203,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.06988080164674573 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_mean",
            "value": 36034.30971797138,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 34987.970243420124 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_median",
            "value": 37151.693229435805,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 34934.90748151979 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_stddev",
            "value": 2449.956864936493,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2495.4976918051802 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_cv",
            "value": 0.06798956006404713,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.07132444878749393 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_mean",
            "value": 482346.95267137035,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 440813.9112903229 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_median",
            "value": 487980.52116935217,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 448275.95766129054 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_stddev",
            "value": 46771.86080146035,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 22283.930225671935 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_cv",
            "value": 0.09696725674833209,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.05055178535641902 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_mean",
            "value": 12869.463220170674,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12106.456223942852 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_median",
            "value": 12834.247399245376,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12226.980345443797 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_stddev",
            "value": 680.1913768360965,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 875.4435896733805 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_cv",
            "value": 0.052853127220567626,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.07231212614819701 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_mean",
            "value": 996365.9711175638,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 987131.3497822905 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_median",
            "value": 973859.7002902804,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 970891.8722786574 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_stddev",
            "value": 86704.0983075167,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 81256.48097754555 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_cv",
            "value": 0.08702033270994386,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0823157738789944 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_mean",
            "value": 3170031.1304904195,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3109476.75906183 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_median",
            "value": 3112588.309168478,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3067805.9701492493 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_stddev",
            "value": 255909.68419136378,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 222098.12419692072 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_cv",
            "value": 0.08072781422552569,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.07142620492327804 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_mean",
            "value": 362389.4370387044,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 352961.5211521139 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_median",
            "value": 358303.86476147675,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 356824.4824482423 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_stddev",
            "value": 32403.46871823415,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 15572.555210713903 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_cv",
            "value": 0.0894161512626356,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.04411969656035873 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_mean",
            "value": 1010001.5479848913,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 996399.9999999969 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_median",
            "value": 1028864.215994972,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1001244.9622166187 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_stddev",
            "value": 90479.03996095277,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 91424.49100323228 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_cv",
            "value": 0.08958307058189403,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.09175480831315996 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_mean",
            "value": 867914.9619543946,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 859041.8241042315 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_median",
            "value": 836525.8143322337,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 831224.1042345217 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_stddev",
            "value": 50559.92708193835,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 46140.51265611262 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_cv",
            "value": 0.05825447111556428,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.053711602114630205 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_mean",
            "value": 1594031.0917721572,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1583252.1097046447 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_median",
            "value": 1570335.2236286965,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1555056.9620253283 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_stddev",
            "value": 91093.7199732143,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 93909.15014766739 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_cv",
            "value": 0.057146764855095296,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.059314084959713784 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_mean",
            "value": 984070.3691576095,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 965668.6141304348 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_median",
            "value": 965048.1487771763,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 957832.8804347845 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_stddev",
            "value": 78033.30537690848,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 65693.81745007553 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_cv",
            "value": 0.07929646885283932,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.06802935964656104 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_mean",
            "value": 130300303.76363638,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 127337527.27272776 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_median",
            "value": 129723102.27272809,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 127057000 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_stddev",
            "value": 6878100.799034171,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 8098090.798208329 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_cv",
            "value": 0.05278652927402983,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.06359547708873031 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_mean",
            "value": 902773.1348769907,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 870015.8224794982 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_median",
            "value": 915537.2247949813,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 880767.969126865 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_stddev",
            "value": 138692.80775083633,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 136184.31332956144 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_cv",
            "value": 0.15362974638111512,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.1565308466936193 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_mean",
            "value": 71504523.15555514,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 68948400.00000057 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_median",
            "value": 73680608.83333291,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 70239444.44444573 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_stddev",
            "value": 8851278.803569358,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6625294.490822955 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_cv",
            "value": 0.12378627830737038,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.09609061980876858 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_mean",
            "value": 582432422.1999992,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 566512333.3333365 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_median",
            "value": 593510514.0000019,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 584150333.3333265 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_stddev",
            "value": 47298008.45477178,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 28452355.114391495 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_cv",
            "value": 0.08120771895924828,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.05022371701420681 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_mean",
            "value": 9195062.902222162,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 9163007.407407383 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_median",
            "value": 9445483.948148118,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 9420548.1481481 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_stddev",
            "value": 403213.3330182941,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 376713.2130094925 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_cv",
            "value": 0.04385106848163594,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.041112398611067066 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_mean",
            "value": 31240780.955102094,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 31010865.306122623 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_median",
            "value": 30968590.979592152,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 30955836.734694123 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_stddev",
            "value": 2708977.055064626,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2472758.2487264047 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_cv",
            "value": 0.08671284687018073,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0797384472931233 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_mean",
            "value": 2328975.8998230034,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2302006.7256637216 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_median",
            "value": 2326154.646017629,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2305481.415929239 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_stddev",
            "value": 146471.83958628838,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 135765.74063155547 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_cv",
            "value": 0.06289109286078051,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.05897712596491701 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_mean",
            "value": 2275303.492446036,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2269083.4532374116 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_median",
            "value": 2228043.0917266635,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2207007.194244584 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_stddev",
            "value": 136517.5556579156,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 138192.08923659084 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_cv",
            "value": 0.05999971261466933,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.060902162518273836 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_mean",
            "value": 60303943.0499995,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 59998749.999999985 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_median",
            "value": 60653163.16666744,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 60080708.33333317 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_stddev",
            "value": 1938918.6273073263,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1786065.8018705647 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_cv",
            "value": 0.03215243530095073,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.02976838353916648 ns\nthreads: 1"
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
          "id": "0bf99539c13d1fdb9557f9f7df80e1c4e55b7230",
          "message": "Merge pull request #50 from brandonmpetty/matlab\n\nMatlab Bindings",
          "timestamp": "2026-02-20T23:25:49-06:00",
          "tree_id": "a1d5d65a5f62bf077a856e3869430b8af73c0baa",
          "url": "https://github.com/brandonmpetty/Doxa/commit/0bf99539c13d1fdb9557f9f7df80e1c4e55b7230"
        },
        "date": 1771651774362,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_GlobalThreshold_Scalar_mean",
            "value": 6338.31370518286,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6199.985476990106 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_median",
            "value": 6590.490265044896,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6141.690115276389 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_stddev",
            "value": 652.9620009173128,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 708.6254410902327 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_cv",
            "value": 0.10301825237576732,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.11429469370858068 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_mean",
            "value": 7117.783672620947,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 7092.406758357302 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_median",
            "value": 7163.05886732248,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 7157.250247758091 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_stddev",
            "value": 125.26287882662288,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 150.1889918213229 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_cv",
            "value": 0.017598579078548754,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.02117602626842411 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_mean",
            "value": 287829.1029153931,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 286304.5871559637 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_median",
            "value": 288717.96636085643,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 288006.9317023444 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_stddev",
            "value": 7707.182503016683,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6926.510055381914 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_cv",
            "value": 0.026776939596973963,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.02419280153415326 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_mean",
            "value": 31115.41742163262,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 30623.42997753289 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_median",
            "value": 31225.34323312308,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 30664.041938589944 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_stddev",
            "value": 658.8070833678289,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 542.5762920970467 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_cv",
            "value": 0.021173011258071733,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.01771768520035515 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_mean",
            "value": 79768.11493226934,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 78042.7806363542 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_median",
            "value": 79857.13976688005,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 78017.95652630492 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_stddev",
            "value": 1678.6062914390543,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 816.2394901913683 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_cv",
            "value": 0.021043574777520436,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.010458872473992097 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_mean",
            "value": 31038.71905332083,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 30957.14499532276 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_median",
            "value": 31439.611000935525,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 31403.33021515436 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_stddev",
            "value": 2410.60757686532,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2318.283170711814 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_cv",
            "value": 0.07766453160403244,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.07488685313397207 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_mean",
            "value": 321044.21851332445,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 318293.68863955105 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_median",
            "value": 320179.83473586,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 316228.1439925194 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_stddev",
            "value": 8144.336206534621,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 7586.540486458971 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_cv",
            "value": 0.02536826934385864,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.023835032729946092 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_mean",
            "value": 8232.228826068185,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 8203.144029318826 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_median",
            "value": 8209.194590832816,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 8202.33585327114 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_stddev",
            "value": 211.29841111553097,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 186.9643931844005 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_cv",
            "value": 0.025667217904151694,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.022791796964209306 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_mean",
            "value": 755154.1818942976,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 752461.95709053 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_median",
            "value": 761975.6671899465,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 751066.9806384153 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_stddev",
            "value": 14688.771335858746,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 14088.071555966973 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_cv",
            "value": 0.019451354025494624,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.01872263630501657 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_mean",
            "value": 2466498.5621521464,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2457526.9016697644 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_median",
            "value": 2462664.0371057405,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2461192.949907235 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_stddev",
            "value": 104319.67369904692,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 97413.88174760636 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_cv",
            "value": 0.04229464200782775,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.03963898896952809 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_mean",
            "value": 307479.72365330224,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 304404.2527339 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_median",
            "value": 303206.2154718523,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 298339.81368975306 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_stddev",
            "value": 13347.564119877585,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 13082.330370903852 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_cv",
            "value": 0.04340957498364213,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.042976831806420215 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_mean",
            "value": 806646.1030588278,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 804215.5294117609 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_median",
            "value": 798375.8823529537,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 796737.0588235249 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_stddev",
            "value": 16818.900853598218,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 15949.09133661178 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_cv",
            "value": 0.020850408611434935,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.019831861924225282 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_mean",
            "value": 812985.5837276379,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 809683.0929024804 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_median",
            "value": 817644.7634160494,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 816532.6024235461 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_stddev",
            "value": 18743.58475678465,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 15967.338233374869 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_cv",
            "value": 0.02305524861934579,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.01972047875686346 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_mean",
            "value": 1492378.7317122647,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1482819.8581560238 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_median",
            "value": 1462774.822695036,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1462255.319148924 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_stddev",
            "value": 48112.28609198467,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 37389.09704842567 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_cv",
            "value": 0.032238657030969314,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.025214861294696498 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_mean",
            "value": 740696.1197361213,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 737788.3452446363 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_median",
            "value": 735741.2726772865,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 735437.6030786148 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_stddev",
            "value": 10010.602339067951,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6414.142994801016 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_cv",
            "value": 0.013515127286793816,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.008693743993305032 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_mean",
            "value": 115207387.15384659,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 114587476.92307682 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_median",
            "value": 115604275.61538562,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 115508692.3076917 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_stddev",
            "value": 2368790.7078733356,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2416324.2772879815 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_cv",
            "value": 0.02056110086682272,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.021087158406586377 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_mean",
            "value": 664166.9640342557,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 663669.2673644142 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_median",
            "value": 664617.3882017181,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 664048.5252140904 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_stddev",
            "value": 2657.311217095066,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2532.2290694421913 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_cv",
            "value": 0.0040009686735307266,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.003815498462808539 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_mean",
            "value": 61219326.08695725,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 61146939.13043489 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_median",
            "value": 61153585.130435444,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 61140304.34782491 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_stddev",
            "value": 563555.5638115464,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 470874.92128219164 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_cv",
            "value": 0.009205517274251925,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0077007112372011 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_mean",
            "value": 500811349.93333006,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 498899466.6666657 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_median",
            "value": 496941291.6666633,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 495499666.6666697 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_stddev",
            "value": 12012276.102869492,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 10127905.732842706 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_cv",
            "value": 0.02398563072595821,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0203004942068009 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_mean",
            "value": 8454373.244444402,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 8451146.198830374 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_median",
            "value": 8522413.257309956,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 8521345.029239673 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_stddev",
            "value": 128506.5929607978,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 127185.29344240951 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_cv",
            "value": 0.01520001415187613,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.01504947263366616 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_mean",
            "value": 26795798.43018877,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 26688554.716981094 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_median",
            "value": 26417439.471697867,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 26376981.132075284 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_stddev",
            "value": 634055.7634287023,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 507050.22132807225 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_cv",
            "value": 0.023662506832203972,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.018998789057897245 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_mean",
            "value": 1889847.4187805105,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1882658.2926829532 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_median",
            "value": 1872506.554878081,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1871434.1463414822 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_stddev",
            "value": 111251.50330374918,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 103144.86341571089 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_cv",
            "value": 0.05886798172073493,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.05478682128168911 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_mean",
            "value": 2070876.9117647023,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2055741.764705889 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_median",
            "value": 2061514.705882296,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2048097.058823577 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_stddev",
            "value": 48131.01179476451,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 33660.22873813268 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_cv",
            "value": 0.02324185060026072,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.016373763142837346 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_mean",
            "value": 61313684.66400091,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 58453224.00000055 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_median",
            "value": 59837469.99999994,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 58770160.00000141 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_stddev",
            "value": 4532306.78560504,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1337461.1903450275 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_cv",
            "value": 0.07391998720093383,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.02288087976712824 ns\nthreads: 1"
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
        "date": 1771548571494,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_GlobalThreshold_Scalar_mean",
            "value": 8558.614750000048,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 8496.093750000002 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_median",
            "value": 8555.16187499994,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 8496.093750000002 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_stddev",
            "value": 46.196196758930725,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 97.6562500000111 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_cv",
            "value": 0.005397625446212598,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.011494252873564524 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_mean",
            "value": 12581.0665354173,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12587.136887781753 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_median",
            "value": 12575.092410301773,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12555.747518984292 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_stddev",
            "value": 29.58248319549744,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 131.31115065479716 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_cv",
            "value": 0.002351349395714504,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.010432169906903929 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_mean",
            "value": 399896.8253047014,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 397199.6517701684 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_median",
            "value": 399349.9999999979,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 399013.34881021467 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_stddev",
            "value": 1110.1603806172504,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2483.506953278617 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_cv",
            "value": 0.0027761170141107367,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.006252540610774876 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_mean",
            "value": 69586.65059514917,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 69528.1502686957 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_median",
            "value": 69378.94631108532,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 69057.3050072824 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_stddev",
            "value": 626.1372311574272,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 701.8946742683642 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_cv",
            "value": 0.00899795040862442,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.01009511502256065 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_mean",
            "value": 111360.21718750212,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 111572.265625 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_median",
            "value": 111329.71093750221,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 111083.984375 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_stddev",
            "value": 464.10379456954007,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 668.6066375792445 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_cv",
            "value": 0.0041675906018404036,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.005992588156508939 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_mean",
            "value": 37653.596549969414,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 37332.92261538049 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_median",
            "value": 37544.93075831073,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 37249.216510861705 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_stddev",
            "value": 317.66643591583676,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 748.6901593429286 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_cv",
            "value": 0.008436549626654317,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.020054421322869637 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_mean",
            "value": 481030.3044982698,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 480103.8062283738 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_median",
            "value": 480490.10380622477,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 481185.12110726646 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_stddev",
            "value": 1398.6505858921644,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2417.893574271261 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_cv",
            "value": 0.002907614287110253,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0050361891384821215 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_mean",
            "value": 15769.358258928634,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 15694.754464285714 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_median",
            "value": 15759.536830357261,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 15694.754464285714 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_stddev",
            "value": 48.16561585232961,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_cv",
            "value": 0.0030543802139226667,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_mean",
            "value": 2562531.4642857485,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2539062.5 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_median",
            "value": 2560750.3571428936,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2539062.5 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_stddev",
            "value": 8846.596828001555,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 19729.541885776394 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_cv",
            "value": 0.003452288079696753,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.007770404188859626 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_mean",
            "value": 6792626.057692258,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6715745.192307693 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_median",
            "value": 6795571.634615253,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6685697.115384616 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_stddev",
            "value": 31867.44832629983,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 85650.19719795059 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_cv",
            "value": 0.004691476912704738,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.012753640101779843 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_mean",
            "value": 168780.46651785594,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 168457.03125 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_median",
            "value": 168898.60491071345,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 169154.57589285713 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_stddev",
            "value": 388.221295700308,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 955.1523393989206 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_cv",
            "value": 0.00230015536578243,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.005670005771272433 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_mean",
            "value": 2614121.8216319047,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2603178.3681214424 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_median",
            "value": 2613232.4478178867,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2609108.159392789 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_stddev",
            "value": 5183.947454743019,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 24806.096612103167 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_cv",
            "value": 0.001983055040452117,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.009529157477596988 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_mean",
            "value": 2742040.2409638683,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2723393.574297189 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_median",
            "value": 2742616.0642570066,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2729668.674698795 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_stddev",
            "value": 2886.3300024381115,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 14031.551063581937 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_cv",
            "value": 0.0010526213143478606,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.005152230362885754 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_mean",
            "value": 5002125.514705867,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4997702.205882354 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_median",
            "value": 4996920.588235303,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4997702.205882354 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_stddev",
            "value": 11221.339466750142,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 40619.64505899758 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_cv",
            "value": 0.0022433142538627352,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.008127664151575056 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_mean",
            "value": 2644255.0664136605,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2638757.115749526 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_median",
            "value": 2643854.838709642,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2638757.115749526 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_stddev",
            "value": 1742.3360355991795,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 20964.978094966493 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_cv",
            "value": 0.0006589137552309837,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.007945020013337413 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_mean",
            "value": 181965548.57142767,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 180803571.42857143 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_median",
            "value": 181703399.99999538,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 180803571.42857143 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_stddev",
            "value": 823339.8648911102,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2733805.516499912 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_cv",
            "value": 0.00452470190843802,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.015120307054221734 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_mean",
            "value": 1841815.9036144703,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1819779.1164658635 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_median",
            "value": 1840524.4979919598,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1819779.1164658635 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_stddev",
            "value": 13413.875668328907,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 20917.001338690465 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_cv",
            "value": 0.007282962234175985,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.011494252873564524 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_mean",
            "value": 94089173.33333269,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 93333333.33333334 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_median",
            "value": 93660880.00000066,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 93750000 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_stddev",
            "value": 847397.5517600464,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 570544.3307332075 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_cv",
            "value": 0.00900632370058077,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.006112974972141508 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_mean",
            "value": 566294500.0000036,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 562500000 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_median",
            "value": 565647450.0000002,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 562500000 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_stddev",
            "value": 1272810.168513102,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5524271.728023671 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_cv",
            "value": 0.002247611743559392,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.009820927516486526 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_mean",
            "value": 12741169.285714349,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12611607.142857146 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_median",
            "value": 12731409.821429096,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12555803.571428573 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_stddev",
            "value": 36169.96988905321,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 159064.65193905105 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_cv",
            "value": 0.0028388265690502752,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.012612560012158386 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_mean",
            "value": 35397660.975609586,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 35137195.12195122 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_median",
            "value": 35397904.87804855,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 35060975.6097561 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_stddev",
            "value": 19887.76486109881,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 318849.09547778015 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_cv",
            "value": 0.0005618383902485049,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.009074403758499947 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_mean",
            "value": 5027847.499999894,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4966517.857142856 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_median",
            "value": 5020241.7857142165,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4966517.857142856 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_stddev",
            "value": 17192.046535924415,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 55803.571428577765 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_cv",
            "value": 0.003419365152965514,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.011235955056181053 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_mean",
            "value": 2903746.5060240715,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2873995.983935743 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_median",
            "value": 2900703.8152610264,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2886546.1847389555 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_stddev",
            "value": 8517.045457032209,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 17185.07020284002 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_cv",
            "value": 0.002933122929072103,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.005979503902892107 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_mean",
            "value": 104417901.53846133,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 103846153.84615386 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_median",
            "value": 104409669.23076409,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 103365384.61538462 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_stddev",
            "value": 124349.20982688855,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 658320.3816164869 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_cv",
            "value": 0.0011908801842860795,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0063393814526032065 ns\nthreads: 1"
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
          "id": "0bf99539c13d1fdb9557f9f7df80e1c4e55b7230",
          "message": "Merge pull request #50 from brandonmpetty/matlab\n\nMatlab Bindings",
          "timestamp": "2026-02-20T23:25:49-06:00",
          "tree_id": "a1d5d65a5f62bf077a856e3869430b8af73c0baa",
          "url": "https://github.com/brandonmpetty/Doxa/commit/0bf99539c13d1fdb9557f9f7df80e1c4e55b7230"
        },
        "date": 1771651796417,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_GlobalThreshold_Scalar_mean",
            "value": 8423.270614611349,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 8324.494051565158 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_median",
            "value": 8400.155491001873,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 8380.995142412885 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_stddev",
            "value": 54.6757942116418,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 84.22685329223468 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_cv",
            "value": 0.006491040916671838,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.010117954649315714 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_mean",
            "value": 12564.26535714275,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12527.901785714288 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_median",
            "value": 12570.108928571752,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12555.803571428569 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_stddev",
            "value": 32.611298689322396,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 116.72154388016402 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_cv",
            "value": 0.002595559530329639,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.009316926798808637 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_mean",
            "value": 396432.8670922842,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 395385.9547301219 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_median",
            "value": 396495.35693558404,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 394479.10621009866 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_stddev",
            "value": 208.4371483462954,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2027.7749360660666 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_cv",
            "value": 0.0005257817039114823,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.00512859627866691 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_mean",
            "value": 69388.79513836527,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 69057.3050072824 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_median",
            "value": 69350.65039425378,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 69057.3050072824 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_stddev",
            "value": 118.07699904854522,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 554.8964620585275 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_cv",
            "value": 0.0017016724215068563,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.008035304331670793 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_mean",
            "value": 110809.36718750058,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 109619.14062500003 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_median",
            "value": 110809.7343750014,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 109863.28125 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_stddev",
            "value": 102.14432394687381,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1591.6021497069544 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_cv",
            "value": 0.0009218022495700689,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.014519381748774351 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_mean",
            "value": 37325.99255350466,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 36998.09819730533 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_median",
            "value": 37332.88243644921,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 37249.216510861705 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_stddev",
            "value": 34.21476711044067,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 374.3450796712649 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_cv",
            "value": 0.0009166472147095826,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.010117954649315714 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_mean",
            "value": 480469.418685128,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 474697.2318339101 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_median",
            "value": 480455.01730105217,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 475778.54671280284 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_stddev",
            "value": 207.47812034374564,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4523.464676324696 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_cv",
            "value": 0.0004318237795686116,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.009529157477596988 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_mean",
            "value": 15826.814508928675,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 15590.122767857141 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_median",
            "value": 15787.370535714295,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 15694.754464285714 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_stddev",
            "value": 90.73167250905097,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 155.97572387686753 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_cv",
            "value": 0.005732781695132954,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0100047784228133 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_mean",
            "value": 2575244.1876046937,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2554438.8609715244 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_median",
            "value": 2563918.592964808,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2538735.3433835846 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_stddev",
            "value": 22237.470327744897,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 39692.605967588475 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_cv",
            "value": 0.008635091939933117,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.01553867918862316 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_mean",
            "value": 6797374.807692391,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6775841.346153846 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_median",
            "value": 6818810.576923248,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6760817.307692309 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_stddev",
            "value": 50466.901081108925,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 62850.062089370134 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_cv",
            "value": 0.007424469373675997,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.009275610050262695 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_mean",
            "value": 171003.65931514866,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 170034.09750435286 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_median",
            "value": 170376.5089959355,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 170034.09750435286 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_stddev",
            "value": 1509.330550426454,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2776.6451850695566 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_cv",
            "value": 0.008826305568378835,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.016329931618559473 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_mean",
            "value": 2629391.0436432804,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2615037.9506641366 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_median",
            "value": 2629535.104364419,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2609108.159392789 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_stddev",
            "value": 7218.792072163529,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 24806.096612123314 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_cv",
            "value": 0.0027454235419320443,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.009485941343919444 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_mean",
            "value": 2748263.4136546208,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2735943.7751004016 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_median",
            "value": 2749064.2570281113,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2729668.674698795 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_stddev",
            "value": 2018.781501445747,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 14031.551063621819 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_cv",
            "value": 0.0007345662324126296,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.00512859627866691 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_mean",
            "value": 5000822.428571487,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4988839.285714285 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_median",
            "value": 5001923.214285649,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5022321.428571428 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_stddev",
            "value": 5269.680098445317,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 49912.2316405976 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_cv",
            "value": 0.00105376269078017,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0100047784228133 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_mean",
            "value": 2649885.9582543024,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2638757.115749526 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_median",
            "value": 2649177.98861483,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2638757.115749526 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_stddev",
            "value": 1692.744417861143,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 20964.978094966493 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_cv",
            "value": 0.0006387989689097008,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.007945020013337413 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_mean",
            "value": 188437565.71428686,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 187053571.42857146 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_median",
            "value": 188181914.28571904,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 187500000 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_stddev",
            "value": 956811.5711060138,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1867544.702081108 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_cv",
            "value": 0.0050776052401183755,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.00998400986315437 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_mean",
            "value": 1811576.8674698812,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1794678.714859438 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_median",
            "value": 1813167.7376171015,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1798862.1151271756 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_stddev",
            "value": 2736.36035117124,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 17500.418895017898 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_cv",
            "value": 0.0015104853679175907,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.009751282360524657 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_mean",
            "value": 95917965.71428567,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 94196428.57142858 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_median",
            "value": 95756985.71428655,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 93750000 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_stddev",
            "value": 354830.0983682854,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1272517.2155124084 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_cv",
            "value": 0.0036993080047718146,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.013509187501174384 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_mean",
            "value": 568183119.9999977,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 565625000 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_median",
            "value": 568325200.0000038,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 570312500 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_stddev",
            "value": 1778273.085245628,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6987712.429683665 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_cv",
            "value": 0.0031297534591411924,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.012353966726512556 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_mean",
            "value": 12564674.799999923,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12468750.000000002 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_median",
            "value": 12558703.999999922,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12500000 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_stddev",
            "value": 38910.10706317758,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 171163.29922020552 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_cv",
            "value": 0.003096785844642618,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.013727382393600438 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_mean",
            "value": 35319035.38461544,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 35096153.84615385 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_median",
            "value": 35206910.256409876,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 35256410.256410256 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_stddev",
            "value": 278046.57748552406,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 456801.0517222034 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_cv",
            "value": 0.007872428407448463,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.01301570119975593 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_mean",
            "value": 5045086.176470695,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5032169.11764706 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_median",
            "value": 5039103.308823787,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5055147.05882353 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_stddev",
            "value": 40094.691658037504,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 65497.20962193358 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_cv",
            "value": 0.007947275875094341,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.01301570119975593 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_mean",
            "value": 2926629.4067796404,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2899894.0677966103 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_median",
            "value": 2908034.1101695336,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2880031.779661017 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_stddev",
            "value": 38542.3646131434,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 44413.42645986783 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_cv",
            "value": 0.013169540538292498,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.015315534092462182 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_mean",
            "value": 108557289.2307692,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 107692307.69230771 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_median",
            "value": 108373553.84615842,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 108173076.92307694 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_stddev",
            "value": 414483.224704295,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 658320.3816152394 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_cv",
            "value": 0.003818105883458398,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.006112974972141508 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}