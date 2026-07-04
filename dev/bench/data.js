window.BENCHMARK_DATA = {
  "lastUpdate": 1783183418824,
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
          "id": "be67520e93a460853e7ab6e2b87d895dac889677",
          "message": "v0.9.6 (#55)\n\n- Phansalkar: added binarization algorithm and LAB Distance grayscale (C++, Python, WASM, Matlab)\n- Su: fix std-E calc, correct paper's /2 → /Ne, add stroke-width detection + unit tests\n- Gatos: fix divide-by-zero, correct threshold-calc object, document removed post-processing experiment\n  - Implemented, then removed, the post-processing routines.  They appeared to greatly reduce detail.  Holes were closed, even when they were supposed to stay open.  Artificially thicker lines as well.\n- Build: MATLAB now opt-in via the unified preset; broad spelling cleanup",
          "timestamp": "2026-05-08T19:24:38-05:00",
          "tree_id": "a78925911bcde1fbdc5016efe80103daa8368b42",
          "url": "https://github.com/brandonmpetty/Doxa/commit/be67520e93a460853e7ab6e2b87d895dac889677"
        },
        "date": 1778286514729,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_GlobalThreshold_Scalar_mean",
            "value": 11552.669478936223,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 11551.59554181266 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_median",
            "value": 11552.087896207282,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 11551.12706076117 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_stddev",
            "value": 113.4846129912606,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 113.42451447269991 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_cv",
            "value": 0.00982323723518405,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.00981894787279762 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_mean",
            "value": 12605.931195198384,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12604.528264603256 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_median",
            "value": 12581.06121526597,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12580.091976569693 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_stddev",
            "value": 54.89902381465724,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 55.2521047093082 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_cv",
            "value": 0.004355015346709837,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.004383512302040708 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_mean",
            "value": 547158.9498635435,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 547119.1629629626 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_median",
            "value": 547437.71033138,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 547394.341520467 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_stddev",
            "value": 1157.4753722440557,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1161.6870193964028 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_cv",
            "value": 0.0021154280169093814,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0021232797131528064 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_mean",
            "value": 68130.35442828595,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 68127.1531345752 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_median",
            "value": 68109.10592869829,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 68105.77671319491 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_stddev",
            "value": 44.66456528355475,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 44.337649278354476 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_cv",
            "value": 0.0006555751200526735,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.000650807310130396 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_mean",
            "value": 83542.20572213674,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 83538.0538764782 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_median",
            "value": 83452.99145860865,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 83448.66802054683 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_stddev",
            "value": 258.1481319802707,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 258.51325151053527 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_cv",
            "value": 0.0030900325140908688,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.003094556785974216 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_mean",
            "value": 82004.75526730927,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 82000.2968740871 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_median",
            "value": 81858.06988022225,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 81854.3219982472 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_stddev",
            "value": 263.69070038295416,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 264.08827728244626 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_cv",
            "value": 0.003215553775185437,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0032205770875190667 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_mean",
            "value": 587534.3673931364,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 587499.6418273262 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_median",
            "value": 586847.6940486326,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 586818.0620284996 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_stddev",
            "value": 1523.2421546354594,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1520.2649942409314 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_cv",
            "value": 0.002592600942467445,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0025876866741780195 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_mean",
            "value": 10128.206042798847,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 10127.528884578924 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_median",
            "value": 10079.097227549188,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 10078.56156056187 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_stddev",
            "value": 71.21833357189311,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 71.06135772103517 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_cv",
            "value": 0.007031682932885169,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.007016653176792169 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_mean",
            "value": 1634529.530210782,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1634416.6063231882 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_median",
            "value": 1634158.0620608972,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1634021.6943794058 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_stddev",
            "value": 1838.1055616675083,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1856.8481094409613 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_cv",
            "value": 0.0011245471725619262,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.001136092292661024 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_mean",
            "value": 4737800.4256055085,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4737014.798615923 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_median",
            "value": 4750630.820069153,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4749742.861591687 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_stddev",
            "value": 22061.103066794825,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 22211.901845845485 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_cv",
            "value": 0.0046564019344430985,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.004689008329113818 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_mean",
            "value": 178487.1560876209,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 178468.9743504843 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_median",
            "value": 178225.26133469382,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 178204.2396841561 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_stddev",
            "value": 457.5117502974995,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 458.231837183298 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_cv",
            "value": 0.002563275477776692,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0025675714159896753 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_mean",
            "value": 1502614.611373384,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1502468.6248927058 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_median",
            "value": 1501053.9495708481,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1500954.111587985 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_stddev",
            "value": 5068.135679636043,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5039.5404618052735 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_cv",
            "value": 0.0033728779430700385,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0033541735103887155 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_mean",
            "value": 1559208.3324414806,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1559047.8365663318 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_median",
            "value": 1552503.5340022203,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1552405.7814938666 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_stddev",
            "value": 11173.496688520898,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 11173.077675466187 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_cv",
            "value": 0.007166134541511151,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.007166603495678442 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_mean",
            "value": 2878734.586858307,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2878457.38193019 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_median",
            "value": 2875247.7145790793,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2874976.5112936585 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_stddev",
            "value": 11054.312674648212,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 11017.654792086721 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_cv",
            "value": 0.003839990225258065,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0038276247761218126 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_mean",
            "value": 1516277.2279220964,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1516119.4534632019 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_median",
            "value": 1514421.3452381254,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1514218.1233766295 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_stddev",
            "value": 5635.227238914786,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5643.610265476383 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_cv",
            "value": 0.0037164887364544083,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0037224047568184307 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_mean",
            "value": 120083701.69999981,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 120071230.21666667 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_median",
            "value": 120077396.91666567,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 120070107.1666662 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_stddev",
            "value": 120478.93013109679,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 116048.84638541527 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_cv",
            "value": 0.0010032912745485177,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0009665000198299536 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_mean",
            "value": 1167062.8485404511,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1166969.4635529607 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_median",
            "value": 1166399.7272727205,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1166295.0909090934 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_stddev",
            "value": 5809.942904492755,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5820.8233163552795 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_cv",
            "value": 0.0049782605210668554,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.004987982546375442 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_mean",
            "value": 61521586.42608692,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 61516598.973913416 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_median",
            "value": 61478873.347826004,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 61471901.9130432 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_stddev",
            "value": 125501.69438929627,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 124925.43785401454 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_cv",
            "value": 0.002039961933362628,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0020307598264167714 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_mean",
            "value": 701785557.0000052,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 701675087.9 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_median",
            "value": 700012719.9999895,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 699960495.4999938 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_stddev",
            "value": 2934902.6502991626,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2848997.9625981566 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_cv",
            "value": 0.0041820505153245,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.004060280907399387 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_mean",
            "value": 11975478.338461522,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 11974398.810256444 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_median",
            "value": 11963854.051282007,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 11962551.213675229 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_stddev",
            "value": 46928.29243445223,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 46907.729799691304 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_cv",
            "value": 0.00391869878664747,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.003917334852712053 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_mean",
            "value": 291717780.23999876,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 291697912.83999985 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_median",
            "value": 291723209.2000063,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 291694856.3999995 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_stddev",
            "value": 25860.556765409943,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 24968.79628423378 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_cv",
            "value": 0.00008864923058215455,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.00008559813144062328 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_mean",
            "value": 4234156.013897311,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4233745.247129923 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_median",
            "value": 4206241.634441199,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4205913.17824777 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_stddev",
            "value": 62253.86265469404,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 62293.33071470157 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_cv",
            "value": 0.014702779597720286,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.014713528348672024 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_mean",
            "value": 3873907.4861879027,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3873572.1508287378 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_median",
            "value": 3872581.0359116085,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3872155.660220959 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_stddev",
            "value": 4470.372053358706,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4446.391786586843 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_cv",
            "value": 0.0011539697499998254,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0011478789121394195 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_mean",
            "value": 2284159.3302782355,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2283962.979705394 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_median",
            "value": 2284548.1931260764,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2284400.7021276443 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_stddev",
            "value": 1169.3014550959956,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1123.582652560598 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_cv",
            "value": 0.0005119176405936454,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0004919443364644763 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_mean",
            "value": 61288589.93043482,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 61283435.339130245 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_median",
            "value": 61243786.95652102,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 61237215.869565286 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_stddev",
            "value": 204142.59597632856,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 204823.13341451914 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_cv",
            "value": 0.003330841779979588,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.003342226692760759 ns\nthreads: 1"
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
          "id": "5cfb757bdaa849c6fbaa3f70c58c15b6526a07c8",
          "message": "v0.9.7 (#56)\n\n* Wellner Binarization Algorithm - 1994\n\nAn optimized Wellner algorithm.  This is now the fastest local adaptive algorithm in Doxa.\n\nNOTE: While theoretically be the simplest adaptive algorithm, Niblack was still faster before adding the division / shift replacement.  That one change made all the difference.\n\n* Added Bradley and Feng\n\nFeng Note: I am adding Feng, but I made one improvement to it that seems to be working really well.  I am adding a `noise-floor` parameter that, when set, can let you greatly lower your window size without having black sections show up in large background patches!  This greatly increases the parameter range for getting good results.\n\n* Performance Boost\n\nBig wins for any algorithm using Chan (almost all of them).  They will see a 6 to 11% increase in performance simply by optimizing out the division.  This insight came from the Wellner algorithm and his paper.  Gatos got a 15+% jump thanks to звездочёт.\n\n* Update Feng\n\nThe interpolation mechanism for Feng needs to be setup just right.  The parameters before were too complex for normal use.  If you say you want a 9x9 window, I want to make sure it is truly a 9x9 window.\n\nI also updated the CMake system so that the Python src files would auto-copy on build.",
          "timestamp": "2026-05-16T00:22:09-05:00",
          "tree_id": "1e0e4ffa20ab4918bbc648b64d98e26620c4a83e",
          "url": "https://github.com/brandonmpetty/Doxa/commit/5cfb757bdaa849c6fbaa3f70c58c15b6526a07c8"
        },
        "date": 1778909197574,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_GlobalThreshold_Scalar_mean",
            "value": 7936.552615952722,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 7933.5820493386755 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_median",
            "value": 7930.25426114507,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 7929.472410118474 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_stddev",
            "value": 36.252481756369676,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 33.49598655806453 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_cv",
            "value": 0.004567786986443087,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.004222050815098922 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_mean",
            "value": 12250.467683694902,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12249.383939818052 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_median",
            "value": 12235.314503149115,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12234.03739503148 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_stddev",
            "value": 36.70353637258425,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 36.76033036837983 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_cv",
            "value": 0.002996092665216026,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0030009942172590487 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_mean",
            "value": 376051.97717041837,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 376011.52422293695 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_median",
            "value": 375567.3826366555,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 375534.15273311926 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_stddev",
            "value": 905.3095429614237,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 897.9365794646412 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_cv",
            "value": 0.0024074053533061405,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0023880560079117554 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_mean",
            "value": 69060.11060725554,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 69050.96347594642 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_median",
            "value": 69070.01690654541,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 69060.80476143523 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_stddev",
            "value": 36.52417079493446,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 37.111964377264556 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_cv",
            "value": 0.0005288750694687882,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0005374575894251257 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_mean",
            "value": 49377.34993947156,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 49371.77064729763 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_median",
            "value": 49366.75151320919,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 49360.83226518554 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_stddev",
            "value": 103.55107832045908,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 103.00868025599917 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_cv",
            "value": 0.0020971372187327895,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.002086388211431047 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_mean",
            "value": 36821.77152783335,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 36817.99081749911 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_median",
            "value": 36817.85852107227,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 36813.910740532745 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_stddev",
            "value": 75.97264275266569,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 75.45304196178708 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_cv",
            "value": 0.002063253330851788,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.002049352511814013 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_mean",
            "value": 434754.7540749925,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 434706.1949798573 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_median",
            "value": 434338.4989154027,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 434293.17663464305 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_stddev",
            "value": 1288.5997004467913,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1286.6190651247791 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_cv",
            "value": 0.0029639691995743326,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0029597440293768914 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_mean",
            "value": 9429.891485014512,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 9428.896411609494 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_median",
            "value": 9430.955246600362,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 9429.80056829714 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_stddev",
            "value": 23.460291450301472,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 23.45671090468889 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_cv",
            "value": 0.002487864413666195,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0024877472273221075 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_mean",
            "value": 1702373.0650426298,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1702153.3656516434 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_median",
            "value": 1701595.3118148758,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1701392.4823386048 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_stddev",
            "value": 7412.636400715399,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 7397.482473913532 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_cv",
            "value": 0.004354296101677205,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.004345955319414781 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_mean",
            "value": 5209142.431226758,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5208294.695167258 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_median",
            "value": 5209602.646840114,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5208741.925650546 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_stddev",
            "value": 10745.14963137389,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 10641.683193003959 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_cv",
            "value": 0.0020627482878872627,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0020432183307289246 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_mean",
            "value": 168349.05465018688,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 168327.12146885888 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_median",
            "value": 168323.95487819653,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 168309.97827913112 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_stddev",
            "value": 160.3250003588606,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 163.2618799975595 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_cv",
            "value": 0.000952336802199457,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0009699083461589613 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_mean",
            "value": 1409181.2502522697,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1409028.1560040351 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_median",
            "value": 1410100.0595358282,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1409929.7093844493 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_stddev",
            "value": 4456.484783227645,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4438.5052449768455 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_cv",
            "value": 0.003162463865049191,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0031500472336651697 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_mean",
            "value": 1609545.7332566173,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1609387.4338319863 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_median",
            "value": 1611767.371691596,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1611595.6858457895 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_stddev",
            "value": 4915.9758535255405,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4919.415026120414 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_cv",
            "value": 0.0030542629214883976,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0030567002840373742 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_mean",
            "value": 3003802.2159139784,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3003513.152688172 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_median",
            "value": 3007030.0150537617,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3006739.7698924774 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_stddev",
            "value": 8387.376377086233,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 8377.089831968922 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_cv",
            "value": 0.0027922532091661616,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.002789097102661711 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_mean",
            "value": 1478521.187724867,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1478398.1202116387 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_median",
            "value": 1480849.8835978878,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1480675.9777777805 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_stddev",
            "value": 5368.494359078057,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5358.37175746304 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_cv",
            "value": 0.003630989128629966,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.003624444379499053 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_mean",
            "value": 113552693.88333371,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 113541031.69999972 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_median",
            "value": 113550993.0000017,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 113539616.3333328 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_stddev",
            "value": 100254.2283918102,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 100689.09432181512 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_cv",
            "value": 0.0008828872742976348,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0008868079919148328 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_mean",
            "value": 1365229.820487812,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1365132.217756105 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_median",
            "value": 1365186.6243902454,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1365104.9795122002 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_stddev",
            "value": 430.9232055981033,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 407.39335602708303 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_cv",
            "value": 0.0003156415126093054,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0002984277645257861 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_mean",
            "value": 58646746.39166647,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 58633341.28333324 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_median",
            "value": 58494994.125,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 58491456.95833377 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_stddev",
            "value": 251906.41189981374,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 234236.01751729258 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_cv",
            "value": 0.004295317769505605,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.003994928693989936 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_mean",
            "value": 511978748.00000143,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 511937769.7999994 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_median",
            "value": 511107499.3333395,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 511072963.99999315 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_stddev",
            "value": 2250960.83196818,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2249337.2775088963 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_cv",
            "value": 0.004396590367786465,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.004393770903810541 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_mean",
            "value": 11296296.369354855,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 11295191.00645162 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_median",
            "value": 11295404.258064426,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 11294603.362903254 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_stddev",
            "value": 9453.152375542419,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 9530.127320986165 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_cv",
            "value": 0.0008368364343898938,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.000843733170651361 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_mean",
            "value": 270657167.91999763,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 270631527.20000064 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_median",
            "value": 269366296.39999974,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 269340307.2000024 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_stddev",
            "value": 3516302.3485818384,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3515118.122231872 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_cv",
            "value": 0.012991720764702624,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.012988575864016567 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_mean",
            "value": 4262101.881345561,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4261579.812232423 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_median",
            "value": 4238586.874617692,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4238131.67584097 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_stddev",
            "value": 47067.54303551042,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 47003.26160054929 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_cv",
            "value": 0.011043270279745407,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.011029539201784113 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_mean",
            "value": 3621621.517829469,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3621323.9447028427 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_median",
            "value": 3620834.7803617334,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3620479.5581395426 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_stddev",
            "value": 5415.6364358864375,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5383.819914909556 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_cv",
            "value": 0.0014953623423168106,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.001486699339004133 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_mean",
            "value": 565327.6778496366,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 565280.8666127754 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_median",
            "value": 565250.3047696067,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 565216.7942603104 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_stddev",
            "value": 323.08434516813185,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 321.6660592058048 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_cv",
            "value": 0.0005714992522514781,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0005690375850385011 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_mean",
            "value": 678333.3751938032,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 678282.3658914736 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_median",
            "value": 678353.1763566004,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 678297.1569767472 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_stddev",
            "value": 264.86561669106965,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 261.88148191250076 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_cv",
            "value": 0.00039046525849534714,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0003860950764484452 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_mean",
            "value": 904866.1931034529,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 904601.4722186126 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_median",
            "value": 902976.6154846866,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 902885.7423552392 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_stddev",
            "value": 4391.327925716252,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3975.3234230891444 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_cv",
            "value": 0.004853013582765372,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.004394557764027647 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_mean",
            "value": 2315066.938181847,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2314884.1322314027 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_median",
            "value": 2314602.3123967443,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2314382.0214875834 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_stddev",
            "value": 1305.854770063839,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1309.2212481718145 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_cv",
            "value": 0.0005640678239262492,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0005655666432469807 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_mean",
            "value": 61045575.843478106,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 61040120.6434779 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_median",
            "value": 61044348.00000075,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 61039795.391303144 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_stddev",
            "value": 19472.071479874685,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 19249.67070329165 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_cv",
            "value": 0.0003189759652657124,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.00031536095440775415 ns\nthreads: 1"
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
            "email": "brandonpetty1981@gmail.com",
            "name": "Brandon M. Petty",
            "username": "brandonmpetty"
          },
          "distinct": true,
          "id": "600ae1febc4546be6acf0738e11733b80530754b",
          "message": "CodeCov - Update\n\nUse token and their updated action.\nTarget just the Doxa folder.",
          "timestamp": "2026-05-16T12:50:34-05:00",
          "tree_id": "db93904152ca22043777f644f6cb9c92cd93a79d",
          "url": "https://github.com/brandonmpetty/Doxa/commit/600ae1febc4546be6acf0738e11733b80530754b"
        },
        "date": 1778954094692,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_GlobalThreshold_Scalar_mean",
            "value": 8420.804518054183,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 8419.559182298373 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_median",
            "value": 8396.477054782206,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 8395.06486505998 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_stddev",
            "value": 34.66260136605999,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 34.68727992894028 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_cv",
            "value": 0.004116305192899735,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.004119845134157171 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_mean",
            "value": 10339.153213720934,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 10338.134725034362 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_median",
            "value": 10321.734108744866,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 10320.177881560085 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_stddev",
            "value": 44.27771426902202,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 44.196662403370496 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_cv",
            "value": 0.004282528109774186,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0042751099283264175 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_mean",
            "value": 405795.57643994095,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 405746.57325615035 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_median",
            "value": 405682.6095513777,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 405623.6746743845 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_stddev",
            "value": 1290.3091786883883,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1296.531060782287 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_cv",
            "value": 0.003179702425561946,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0031954208519310873 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_mean",
            "value": 77637.31922778238,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 77627.30287362699 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_median",
            "value": 77633.36558304663,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 77622.93337401531 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_stddev",
            "value": 17.748063787174544,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 17.42738194109964 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_cv",
            "value": 0.00022860222330839354,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.00022450067561242552 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_mean",
            "value": 45052.32863251983,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 45046.82916304942 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_median",
            "value": 45043.83241696428,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 45038.349667213326 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_stddev",
            "value": 33.85372844621936,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 33.40917456966031 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_cv",
            "value": 0.0007514312683447608,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0007416543004333115 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_mean",
            "value": 36703.590480191204,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 36699.679776313424 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_median",
            "value": 36700.38564939974,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 36696.98259339972 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_stddev",
            "value": 21.477253321092302,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 20.73257444405013 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_cv",
            "value": 0.0005851540146374372,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0005649252138006739 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_mean",
            "value": 468330.883643621,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 468271.78111702093 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_median",
            "value": 468503.8397606389,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 468429.8111702133 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_stddev",
            "value": 372.98710089846566,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 372.2886029087093 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_cv",
            "value": 0.0007964179043598847,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0007950267727443403 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_mean",
            "value": 9318.975813372641,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 9317.88954073837 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_median",
            "value": 9299.991378050498,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 9298.991643750085 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_stddev",
            "value": 45.43890461942255,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 45.52783285876823 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_cv",
            "value": 0.0048759547754398235,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.004886067028345617 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_mean",
            "value": 1652937.3086186638,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1652739.0939787454 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_median",
            "value": 1652260.0661157065,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1652054.2314049613 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_stddev",
            "value": 2574.8771264713887,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2567.017701666067 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_cv",
            "value": 0.001557758490322405,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0015531899203075784 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_mean",
            "value": 6814245.670873815,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6813316.723300971 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_median",
            "value": 6813011.5291262865,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6812226.985436899 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_stddev",
            "value": 9560.256767963432,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 9327.70320127216 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_cv",
            "value": 0.0014029809357808914,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0013690400109204078 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_mean",
            "value": 173116.3767033504,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 173100.79829355766 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_median",
            "value": 173043.62656114605,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 173028.8577964635 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_stddev",
            "value": 131.38339230550966,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 127.47262531158829 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_cv",
            "value": 0.0007589310428478193,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0007364069176354136 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_mean",
            "value": 1303715.8158878437,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1303575.2435513998 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_median",
            "value": 1303850.106542038,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1303720.116822424 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_stddev",
            "value": 548.3016360281189,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 550.1683925225424 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_cv",
            "value": 0.00042056837030447465,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.00042204575090248664 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_mean",
            "value": 1535304.6960698715,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1535126.9085152843 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_median",
            "value": 1528271.5196506707,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1527984.1593886453 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_stddev",
            "value": 16269.528727740593,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 16275.597917096029 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_cv",
            "value": 0.010596938034116562,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.010602118839045795 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_mean",
            "value": 3023543.982312935,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3023209.458956915 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_median",
            "value": 3022724.324263051,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3022519.444444455 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_stddev",
            "value": 2513.2996071815455,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2533.270885390089 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_cv",
            "value": 0.0008312429459878187,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.00083794091007645 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_mean",
            "value": 1365509.7269005883,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1365347.5161793344 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_median",
            "value": 1365775.0409356894,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1365555.1150097386 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_stddev",
            "value": 862.4040557761109,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 841.1272339293452 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_cv",
            "value": 0.0006315620011975906,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0006160535863302259 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_mean",
            "value": 121084678.83333278,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 121071192.11666653 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_median",
            "value": 121078436.99999896,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 121064500.25000015 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_stddev",
            "value": 65631.24460271266,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 64797.41491275568 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_cv",
            "value": 0.0005420276556462681,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0005352009324424232 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_mean",
            "value": 1207521.7970815457,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1207352.953304719 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_median",
            "value": 1199544.300429187,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1199359.3236051505 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_stddev",
            "value": 18467.085223650036,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 18426.733541312246 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_cv",
            "value": 0.015293376292074444,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.015262093401002017 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_mean",
            "value": 62172799.895652674,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 62165655.08695664 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_median",
            "value": 62171672.826087095,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 62166270.91304338 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_stddev",
            "value": 48912.34354621968,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 48844.59522381446 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_cv",
            "value": 0.0007867161142543265,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.000785716729848518 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_mean",
            "value": 584280154.9999992,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 584217471.4000038 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_median",
            "value": 583972179.4999945,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 583927930.0000015 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_stddev",
            "value": 1641569.85699922,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1649182.9755687802 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_cv",
            "value": 0.0028095594946215873,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0028228922555443617 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_mean",
            "value": 12010761.085470121,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12009415.90256412 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_median",
            "value": 12007773.743589904,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12006718.42735048 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_stddev",
            "value": 6963.2529035190255,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6758.05428110698 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_cv",
            "value": 0.0005797511792939366,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0005627296394709817 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_mean",
            "value": 288727989.32000023,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 288699306.92000026 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_median",
            "value": 288295526.5999954,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 288265094.7999991 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_stddev",
            "value": 1078364.9311898765,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1078607.8546452054 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_cv",
            "value": 0.003734881864863865,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0037360943680550367 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_mean",
            "value": 5854484.969874503,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5853807.70209204 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_median",
            "value": 5854725.430962414,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5853776.8075313745 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_stddev",
            "value": 5203.198405286234,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5261.298117749413 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_cv",
            "value": 0.0008887542511528166,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0008987821919515948 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_mean",
            "value": 3531875.3141413913,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3531443.9767677067 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_median",
            "value": 3531947.7853535963,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3531594.7373737716 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_stddev",
            "value": 1630.5754237577817,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1588.9424831025508 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_cv",
            "value": 0.00046167411891044613,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0004499412969753219 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_mean",
            "value": 530435.068655588,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 530362.4384441109 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_median",
            "value": 529955.1740936576,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 529885.0777945669 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_stddev",
            "value": 2609.6082211593302,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2621.0982063615647 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_cv",
            "value": 0.004919750550757328,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.00494208868571256 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_mean",
            "value": 718127.9795605572,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 718040.7955033224 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_median",
            "value": 716262.9724067574,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 716176.5140521193 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_stddev",
            "value": 4026.3266789113413,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4039.3392908332426 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_cv",
            "value": 0.005606697961239672,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.005625501108195116 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_mean",
            "value": 964865.845316807,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 964741.9061983449 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_median",
            "value": 964615.4524793196,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 964507.5571625333 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_stddev",
            "value": 767.608391330398,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 756.1234346546123 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_cv",
            "value": 0.0007955597092136257,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0007837572202436886 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_mean",
            "value": 2510173.2885304736,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2509844.990322593 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_median",
            "value": 2509705.1594982133,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2509430.2741935137 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_stddev",
            "value": 2077.5392451206108,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2030.5105195651092 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_cv",
            "value": 0.00082764773835071,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0008090182969045133 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_mean",
            "value": 64651931.11428486,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 64643874.28571421 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_median",
            "value": 64641910.04761773,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 64629762.047618866 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_stddev",
            "value": 76913.19117703005,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 77581.49147503344 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_cv",
            "value": 0.0011896503298729163,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0012001367853067921 ns\nthreads: 1"
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
          "id": "ea8007847865c649c7febe964cdbc077179d804f",
          "message": "v0.9.8 - Pseudo Weights, XDoG and BinBench (#57)\n\nThis is a HUGE release.  It is the first release that was driven by AI.\n\n- Utilities: BinBench - A Python script exposing all binarization and grayscale algorithms along with all performance metrics\n- Binarization: XDoG\n- Metrics: bit-exact Pseudo Weight generation!\n- Extras: Canny Edge Detection... for the future :)",
          "timestamp": "2026-07-04T11:26:47-05:00",
          "tree_id": "280b97c25f17cde3c2c5fb9327c68e4363f37353",
          "url": "https://github.com/brandonmpetty/Doxa/commit/ea8007847865c649c7febe964cdbc077179d804f"
        },
        "date": 1783182684961,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_GlobalThreshold_Scalar_mean",
            "value": 7770.604737014401,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 7768.195004459298 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_median",
            "value": 7777.078985989977,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 7775.103021032075 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_stddev",
            "value": 18.254025746627473,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 18.227451957892526 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_cv",
            "value": 0.0023491126320808057,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0023464204937477936 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_mean",
            "value": 12342.149096005847,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12339.878442538411 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_median",
            "value": 12346.402147371842,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12344.7264657399 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_stddev",
            "value": 13.111790963957223,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12.414126960553673 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_cv",
            "value": 0.001062358821139217,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0010060169570033455 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_mean",
            "value": 384104.9926007098,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 384063.78070704296 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_median",
            "value": 383070.71444231016,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 383039.24362839095 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_stddev",
            "value": 2259.616268538823,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2263.3363765758286 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_cv",
            "value": 0.005882808898784012,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.005893126325031576 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_mean",
            "value": 68686.45234635782,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 68678.357255056 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_median",
            "value": 68660.8549970541,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 68651.85622422946 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_stddev",
            "value": 52.92056425049393,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 50.38639548000595 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_cv",
            "value": 0.0007704658261229895,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0007336575523040276 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_mean",
            "value": 56076.73336309383,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 56070.76836979017 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_median",
            "value": 55912.15060265487,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 55906.75540765392 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_stddev",
            "value": 266.6793082110307,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 265.9065982469675 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_cv",
            "value": 0.004755614177528789,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.00474233911854564 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_mean",
            "value": 48708.73760365438,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 48704.32437104709 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_median",
            "value": 48728.071574138725,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 48722.94149683771 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_stddev",
            "value": 83.56989355877542,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 84.57534082260582 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_cv",
            "value": 0.0017157064147050604,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.001736505780847721 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_mean",
            "value": 442781.85142314946,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 442739.56502213876 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_median",
            "value": 443084.8108791845,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 443043.8301707779 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_stddev",
            "value": 688.6189328677862,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 692.7825953435066 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_cv",
            "value": 0.00155521038329482,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.001564763237974597 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_mean",
            "value": 9980.659277999963,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 9979.440242000011 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_median",
            "value": 9953.97064999992,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 9952.512589999998 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_stddev",
            "value": 43.64635870394948,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 43.79929522162926 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_cv",
            "value": 0.004373093749443758,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.004388953103531115 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_mean",
            "value": 1698606.8834549827,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1698430.6004866206 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_median",
            "value": 1697329.133819963,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1697205.8175182478 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_stddev",
            "value": 7101.8527145531525,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 7126.333069566955 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_cv",
            "value": 0.004180986656611162,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0041958341232931 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_mean",
            "value": 6257941.076233181,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6257332.917488769 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_median",
            "value": 6259047.192825144,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6258478.013452898 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_stddev",
            "value": 8383.203618900032,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 8386.457605111887 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_cv",
            "value": 0.001339610507158387,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0013402607333984704 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_mean",
            "value": 169630.5512973577,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 169606.44887318806 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_median",
            "value": 168979.70824704663,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 168960.76793762922 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_stddev",
            "value": 1527.4478967144391,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1523.8184338806727 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_cv",
            "value": 0.00900455657917933,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.008984436877279392 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_mean",
            "value": 1411098.576791118,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1410955.9033299708 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_median",
            "value": 1412036.337033276,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1411965.6407669084 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_stddev",
            "value": 3682.933053431368,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3676.9769319160723 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_cv",
            "value": 0.00260997574089152,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0026060183193805757 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_mean",
            "value": 1618104.8760693616,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1617935.4219653173 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_median",
            "value": 1616449.9630057935,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1616236.5156069333 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_stddev",
            "value": 2814.63231886739,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2805.6764961405206 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_cv",
            "value": 0.0017394622317093483,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.00173410907385441 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_mean",
            "value": 3086878.531125821,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3086573.6445916193 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_median",
            "value": 3088433.902869762,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3088183.4812362166 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_stddev",
            "value": 6084.696718252172,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5999.795946669012 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_cv",
            "value": 0.0019711487371137375,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.001943836965361906 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_mean",
            "value": 1485819.6481953347,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1485660.7390658162 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_median",
            "value": 1486614.0711252731,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1486399.0360934087 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_stddev",
            "value": 5563.064846064772,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5621.584033219382 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_cv",
            "value": 0.0037441050485646945,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0037838948593029624 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_mean",
            "value": 114379181.88333309,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 114367297.4500002 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_median",
            "value": 114396037.58333306,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 114383879.5833337 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_stddev",
            "value": 93184.07908220022,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 94191.21239047102 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_cv",
            "value": 0.0008146944010951931,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0008235851899154138 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_mean",
            "value": 1361759.5610136518,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1361629.7769980533 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_median",
            "value": 1361981.8382066167,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1361910.9074074174 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_stddev",
            "value": 2323.663420240897,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2320.5871585383325 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_cv",
            "value": 0.0017063683536844298,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0017042717467992403 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_mean",
            "value": 59468460.54166623,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 59462788.29999989 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_median",
            "value": 59440517.041666165,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 59435629.29166646 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_stddev",
            "value": 66412.30762188279,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 66689.17923346153 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_cv",
            "value": 0.0011167652065812498,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0011215279528602538 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_mean",
            "value": 599144250.9000137,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 599091428.9000018 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_median",
            "value": 598921715.0000173,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 598877332.9999902 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_stddev",
            "value": 566515.9710111864,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 545617.0668385985 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_cv",
            "value": 0.0009455418626819596,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0009107408994991164 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_mean",
            "value": 11395539.580487866,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 11394434.291056901 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_median",
            "value": 11358219.50406519,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 11357217.04065048 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_stddev",
            "value": 95579.1167557286,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 95732.03013210784 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_cv",
            "value": 0.0083874147494854,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.008401648356272029 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_mean",
            "value": 329204754.44999796,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 329169778.55000055 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_median",
            "value": 329185473.00000966,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 329143681.2499953 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_stddev",
            "value": 524995.866528194,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 525283.3969642831 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_cv",
            "value": 0.0015947396246002098,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0015957825754179709 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_mean",
            "value": 5364425.965909147,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5363215.045454523 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_median",
            "value": 5341780.734848488,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5341238.136363665 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_stddev",
            "value": 77182.4597964084,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 77886.54566009899 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_cv",
            "value": 0.01438783204147133,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.014522361121079796 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_mean",
            "value": 3605142.845244209,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3604708.975321318 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_median",
            "value": 3604283.9151671566,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3603820.318766064 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_stddev",
            "value": 3007.181808788937,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3092.9473391805955 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_cv",
            "value": 0.0008341366591772964,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0008580296940351181 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_mean",
            "value": 568772.5064398546,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 568716.9117861476 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_median",
            "value": 567499.2624544345,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 567456.7942486831 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_stddev",
            "value": 3144.408369449083,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3143.304289815337 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_cv",
            "value": 0.005528411331150711,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.005527010406536496 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_mean",
            "value": 683852.3672514583,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 683781.2738791395 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_median",
            "value": 683728.4839181274,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 683696.2319688126 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_stddev",
            "value": 664.2823348489559,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 664.1501349820627 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_cv",
            "value": 0.0009713826648269738,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0009712903238988866 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_mean",
            "value": 920539.9203400889,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 920450.3449313247 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_median",
            "value": 920547.4931327648,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 920430.7756703775 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_stddev",
            "value": 5992.179811703203,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6010.380355624761 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_cv",
            "value": 0.006509418743610186,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.006529825740978128 ns\nthreads: 1"
          },
          {
            "name": "BM_XDoG_mean",
            "value": 5581860.623199964,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5581068.126400011 ns\nthreads: 1"
          },
          {
            "name": "BM_XDoG_median",
            "value": 5581625.859999804,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5580939.923999949 ns\nthreads: 1"
          },
          {
            "name": "BM_XDoG_stddev",
            "value": 6570.8534073925275,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6659.403913723088 ns\nthreads: 1"
          },
          {
            "name": "BM_XDoG_cv",
            "value": 0.0011771797705019719,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0011932131561380246 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_mean",
            "value": 2067386.3642540532,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2067091.2174298328 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_median",
            "value": 2066714.3426883474,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2066504.2245199424 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_stddev",
            "value": 1477.5346931154388,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1434.766833063962 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_cv",
            "value": 0.0007146872585901754,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0006940994286879673 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_mean",
            "value": 61444522.53912999,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 61423021.94782637 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_median",
            "value": 61317886.17391195,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 61311369.956521966 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_stddev",
            "value": 415968.21093578835,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 392446.9305870967 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_cv",
            "value": 0.006769817613455869,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.006389248170180344 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Generate_mean",
            "value": 92656953.62666824,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 92645342.26666608 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Generate_median",
            "value": 92423405.46666886,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 92405037.1333332 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Generate_stddev",
            "value": 520653.75613524346,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 522197.1316078062 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Generate_cv",
            "value": 0.00561915469650613,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.005636517916947601 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Recall_mean",
            "value": 19537859.01666676,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 19535543.827777803 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Recall_median",
            "value": 19531588.81944401,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 19529802.6944444 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Recall_stddev",
            "value": 78040.70618026979,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 77063.76643548337 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Recall_cv",
            "value": 0.003994332547578382,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.003944797601482973 ns\nthreads: 1"
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
            "email": "brandonpetty1981@gmail.com",
            "name": "Brandon M. Petty",
            "username": "brandonmpetty"
          },
          "distinct": true,
          "id": "16fc9edbf21d15ebfc602f5185fc01c79bc718b2",
          "message": "v0.9.8 - Pseudo Weights, XDoG and BinBench (#57)\n\nThis is a HUGE release.  It is the first release that was driven by AI.\n\n- Utilities: BinBench - A Python script exposing all binarization and grayscale algorithms along with all performance metrics\n- Binarization: XDoG\n- Metrics: bit-exact Pseudo Weight generation!\n- Extras: Canny Edge Detection... for the future :)",
          "timestamp": "2026-07-04T11:38:37-05:00",
          "tree_id": "9d793dfc062bcc18a5c84aa88b6843b9421c0859",
          "url": "https://github.com/brandonmpetty/Doxa/commit/16fc9edbf21d15ebfc602f5185fc01c79bc718b2"
        },
        "date": 1783183418457,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_GlobalThreshold_Scalar_mean",
            "value": 7887.178799246282,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 7886.359661400202 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_median",
            "value": 7914.629192636591,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 7913.736599507174 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_stddev",
            "value": 48.62694914087763,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 48.674387601532594 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_cv",
            "value": 0.006165315935975044,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0061719715675369775 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_mean",
            "value": 12287.520046068803,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12286.655593750822 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_median",
            "value": 12309.430945201048,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12308.62479449284 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_stddev",
            "value": 40.21198145429507,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 40.239980482381654 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_cv",
            "value": 0.0032725872514169575,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0032750963169219383 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_mean",
            "value": 384155.12126027344,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 384132.6461369861 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_median",
            "value": 383393.48109588725,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 383369.9915068493 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_stddev",
            "value": 1737.4459809704433,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1738.2446345325156 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_cv",
            "value": 0.004522771882541911,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.004525115613091207 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_mean",
            "value": 68646.94124166349,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 68634.35029423298 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_median",
            "value": 68657.03099254597,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 68652.69757748125 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_stddev",
            "value": 46.05410204679907,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 32.85938088188814 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_cv",
            "value": 0.000670883526837285,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0004787599903112824 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_mean",
            "value": 56218.699809199,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 56215.128283197366 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_median",
            "value": 56221.54759874963,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 56218.87074250006 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_stddev",
            "value": 170.61099628771885,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 170.80876172845208 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_cv",
            "value": 0.003034773071358046,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0030384838911682536 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_mean",
            "value": 48611.00642922251,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 48608.31432377476 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_median",
            "value": 48602.30999789671,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 48599.02061277432 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_stddev",
            "value": 38.13807460561379,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 38.46248756097013 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_cv",
            "value": 0.0007845563671088094,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.000791273840618616 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_mean",
            "value": 441678.12501575064,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 441650.9481411468 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_median",
            "value": 441635.4543163197,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 441607.2614996845 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_stddev",
            "value": 425.4347472540886,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 424.9743038267964 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_cv",
            "value": 0.0009632234950257435,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0009622402162057156 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_mean",
            "value": 9990.080584,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 9989.482843999995 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_median",
            "value": 9978.268959999923,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 9977.376649999955 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_stddev",
            "value": 42.3361359339577,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 42.31436378138864 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_cv",
            "value": 0.004237817260629787,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.004235891331131722 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_mean",
            "value": 1694809.8041162225,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1694708.972154962 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_median",
            "value": 1692079.4128329277,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1691968.7518159752 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_stddev",
            "value": 6213.71362281297,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6218.417968405143 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_cv",
            "value": 0.0036663191395999617,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.003669313180361531 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_mean",
            "value": 6756225.13333334,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6755596.492753617 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_median",
            "value": 6759236.942029007,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6758545.8309178995 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_stddev",
            "value": 14349.049985154033,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 14168.086838255715 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_cv",
            "value": 0.00212382650103825,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.002097236987652104 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_mean",
            "value": 168870.49247234283,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 168852.73946608935 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_median",
            "value": 168478.3549783567,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 168466.6651034147 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_stddev",
            "value": 752.6213216389666,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 748.1972941269685 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_cv",
            "value": 0.0044567959186962705,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.00443106399394384 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_mean",
            "value": 1407763.3532861471,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1407670.5185035332 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_median",
            "value": 1409748.4732052428,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1409597.1081900818 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_stddev",
            "value": 5270.245000153106,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5257.862457019705 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_cv",
            "value": 0.003743700947926194,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.003735151363835648 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_mean",
            "value": 1610233.0777905593,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1610146.5634062097 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_median",
            "value": 1611987.7617951608,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1611905.8929804272 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_stddev",
            "value": 4286.703380696539,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4278.020314460399 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_cv",
            "value": 0.0026621632854409074,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0026569136075478704 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_mean",
            "value": 3085304.836123332,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3085100.7775330404 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_median",
            "value": 3086493.5572687006,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3086331.2951542055 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_stddev",
            "value": 8285.206763010054,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 8295.640824855931 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_cv",
            "value": 0.002685377038276831,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0026889367392041656 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_mean",
            "value": 1483698.4048832231,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1483571.2906581764 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_median",
            "value": 1484549.064755834,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1484468.113588121 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_stddev",
            "value": 4812.596019855682,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4820.114209600191 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_cv",
            "value": 0.003243648442308911,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0032489939916953907 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_mean",
            "value": 114996869.81666693,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 114958117.46666649 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_median",
            "value": 114930213.5000004,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 114785974.91666658 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_stddev",
            "value": 474845.437029092,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 483805.7696272378 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_cv",
            "value": 0.004129203149495386,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.004208539425391367 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_mean",
            "value": 1360271.297565726,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1360151.109639726 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_median",
            "value": 1359461.9123661097,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1359394.712755603 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_stddev",
            "value": 2478.028690418302,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2448.7928035022264 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_cv",
            "value": 0.0018217165170307274,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0018003829031546775 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_mean",
            "value": 59661197.158333346,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 59656244.1166667 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_median",
            "value": 59619144.08333276,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 59612279.125000596 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_stddev",
            "value": 202917.74425371707,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 202738.38143232063 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_cv",
            "value": 0.003401167826304235,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0033984436069397096 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_mean",
            "value": 598434675.9000005,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 598389517.3999997 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_median",
            "value": 598179850.9999976,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 598135795.4999993 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_stddev",
            "value": 538401.4825498256,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 542055.3121328314 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_cv",
            "value": 0.0008996829632910402,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0009058569650218137 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_mean",
            "value": 11335654.247154495,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 11334884.702439023 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_median",
            "value": 11326284.138211425,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 11325725.276422666 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_stddev",
            "value": 20701.739987570683,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 20599.39479483772 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_cv",
            "value": 0.0018262501251542045,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0018173448901871204 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_mean",
            "value": 328504015.5999994,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 328475495.10000104 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_median",
            "value": 328462492.25000435,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 328437652.4999999 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_stddev",
            "value": 412230.8782061536,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 410612.7771671911 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_cv",
            "value": 0.0012548731785005137,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0012500560415996454 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_mean",
            "value": 5816591.533609942,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5815998.936099596 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_median",
            "value": 5802390.618257231,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5801960.5228215605 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_stddev",
            "value": 33635.301701478784,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 33631.85003767585 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_cv",
            "value": 0.005782648052063535,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.005782643774042795 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_mean",
            "value": 3598510.1778920265,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3598188.1928020334 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_median",
            "value": 3597110.408740395,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3596899.4961439967 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_stddev",
            "value": 2012.2406760372717,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1939.1380917442561 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_cv",
            "value": 0.0005591871570628776,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0005389206978176932 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_mean",
            "value": 565112.8037857432,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 565060.9320982692 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_median",
            "value": 564781.5324204531,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 564750.983890457 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_stddev",
            "value": 1535.3193830698933,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1532.9555368334936 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_cv",
            "value": 0.002716837015166965,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0027129030689506226 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_mean",
            "value": 680482.1315840628,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 680419.7967930037 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_median",
            "value": 679973.5986394561,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 679901.4625850319 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_stddev",
            "value": 1181.7721234660416,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1170.6797170203652 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_cv",
            "value": 0.0017366688537655635,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0017205256556879806 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_mean",
            "value": 913749.2393485479,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 913655.8350488637 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_median",
            "value": 912753.4221498456,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 912685.1530944767 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_stddev",
            "value": 1612.9993043591494,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1606.9494619916452 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_cv",
            "value": 0.0017652537861581451,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0017588126735990288 ns\nthreads: 1"
          },
          {
            "name": "BM_XDoG_mean",
            "value": 5568063.663492056,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5567464.21984127 ns\nthreads: 1"
          },
          {
            "name": "BM_XDoG_median",
            "value": 5565549.59523812,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5564735.361111113 ns\nthreads: 1"
          },
          {
            "name": "BM_XDoG_stddev",
            "value": 8859.643095012598,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 8864.071093113478 ns\nthreads: 1"
          },
          {
            "name": "BM_XDoG_cv",
            "value": 0.0015911533399128204,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.001592119992711187 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_mean",
            "value": 2062294.9655882108,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2062090.160588221 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_median",
            "value": 2062300.0029411118,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2062126.3338234995 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_stddev",
            "value": 1359.7368904399873,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1337.146146494832 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_cv",
            "value": 0.0006593319157195155,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0006484421350972378 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_mean",
            "value": 61092537.69565256,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 61086636.53913051 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_median",
            "value": 61099570.52173899,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 61095428.69565318 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_stddev",
            "value": 58187.948227051435,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 57475.127985505154 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_cv",
            "value": 0.0009524559041388811,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0009408789097217371 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Generate_mean",
            "value": 91427337.7733328,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 91416664.29333326 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Generate_median",
            "value": 91462425.80000034,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 91454290.79999872 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Generate_stddev",
            "value": 225279.96934456384,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 223616.4490294774 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Generate_cv",
            "value": 0.002464032912158935,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0024461234804187128 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Recall_mean",
            "value": 19152542.906849485,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 19149925.60547947 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Recall_median",
            "value": 19146984.054794468,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 19144076.35616446 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Recall_stddev",
            "value": 61483.027415605946,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 61497.616173077295 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Recall_cv",
            "value": 0.0032101756782185777,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0032113762444842425 ns\nthreads: 1"
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
          "id": "be67520e93a460853e7ab6e2b87d895dac889677",
          "message": "v0.9.6 (#55)\n\n- Phansalkar: added binarization algorithm and LAB Distance grayscale (C++, Python, WASM, Matlab)\n- Su: fix std-E calc, correct paper's /2 → /Ne, add stroke-width detection + unit tests\n- Gatos: fix divide-by-zero, correct threshold-calc object, document removed post-processing experiment\n  - Implemented, then removed, the post-processing routines.  They appeared to greatly reduce detail.  Holes were closed, even when they were supposed to stay open.  Artificially thicker lines as well.\n- Build: MATLAB now opt-in via the unified preset; broad spelling cleanup",
          "timestamp": "2026-05-08T19:24:38-05:00",
          "tree_id": "a78925911bcde1fbdc5016efe80103daa8368b42",
          "url": "https://github.com/brandonmpetty/Doxa/commit/be67520e93a460853e7ab6e2b87d895dac889677"
        },
        "date": 1778286510504,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_GlobalThreshold_Scalar_mean",
            "value": 5896.250275826506,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5865.321629198281 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_median",
            "value": 6178.902672395989,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6154.358202816353 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_stddev",
            "value": 820.8003692673323,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 840.6586619230445 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_cv",
            "value": 0.1392071792868861,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.14332695034798162 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_mean",
            "value": 7506.125233420149,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 7108.3580444800655 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_median",
            "value": 7424.4638248848005,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 7045.817471448609 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_stddev",
            "value": 472.61712485553215,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 254.8544712721228 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_cv",
            "value": 0.06296419392941374,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.03585279043027775 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_mean",
            "value": 310265.8628305463,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 302917.3683097103 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_median",
            "value": 301253.5083562498,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 297188.49164374894 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_stddev",
            "value": 20224.966849085245,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 14966.032428300925 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_cv",
            "value": 0.06518592366099665,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.049406319986905735 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_mean",
            "value": 29612.864979595226,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 29230.232655980486 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_median",
            "value": 29162.328915814658,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 28963.50288190494 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_stddev",
            "value": 1048.0789217472488,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 498.4072600234082 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_cv",
            "value": 0.035392689038005236,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.01705108768340352 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_mean",
            "value": 74801.00835133986,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 72466.20570440784 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_median",
            "value": 74984.71261884153,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 72711.75453759736 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_stddev",
            "value": 4282.363239028724,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2128.253428259425 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_cv",
            "value": 0.057250073674334594,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.02936890937743649 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_mean",
            "value": 29820.669735393498,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 29621.441676519746 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_median",
            "value": 30113.20346964563,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 29742.65095608919 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_stddev",
            "value": 1298.4322138369303,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1253.8786430212594 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_cv",
            "value": 0.04354134985425393,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.04233010184697326 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_mean",
            "value": 317643.5361885352,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 317346.56696125085 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_median",
            "value": 317848.8839791575,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 317577.1583956479 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_stddev",
            "value": 7142.031275930785,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6978.342159674394 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_cv",
            "value": 0.022484421882558565,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.02198965700651955 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_mean",
            "value": 8061.5570247746045,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 7991.955931008599 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_median",
            "value": 8110.186690618943,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 7936.341000306956 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_stddev",
            "value": 150.30488580770106,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 124.96530795454214 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_cv",
            "value": 0.018644647100527514,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.015636386015303178 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_mean",
            "value": 791497.693093763,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 778582.2571588974 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_median",
            "value": 791479.1313868674,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 760414.3739472206 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_stddev",
            "value": 31162.299180917245,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 37669.288970012945 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_cv",
            "value": 0.03937130765234672,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.048381900080115996 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_mean",
            "value": 2469257.95567191,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2392409.0750436364 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_median",
            "value": 2466129.6544502894,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2352636.998254777 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_stddev",
            "value": 105562.56043605992,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 78917.53229577359 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_cv",
            "value": 0.04275072201087038,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.032986638079164694 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_mean",
            "value": 317089.7055651448,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 313796.03106126096 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_median",
            "value": 314317.96462467464,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 313580.24158757407 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_stddev",
            "value": 16440.984828901484,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 13232.885889529101 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_cv",
            "value": 0.051849632896782114,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.042170341813359984 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_mean",
            "value": 818108.8876143931,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 817489.6888346581 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_median",
            "value": 814192.2922513732,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 813774.2525930449 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_stddev",
            "value": 11793.24155773695,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 11867.561305792637 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_cv",
            "value": 0.01441524684095055,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.01451707766823334 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_mean",
            "value": 814903.7118505517,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 807137.3029772321 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_median",
            "value": 811360.1383537627,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 810546.4098073603 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_stddev",
            "value": 21532.437007094937,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 16357.492923188223 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_cv",
            "value": 0.026423289885620073,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.02026605989198053 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_mean",
            "value": 1515325.6327672289,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1484115.8841158866 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_median",
            "value": 1482490.0929070893,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1467840.1598401722 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_stddev",
            "value": 72904.69161213528,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 51817.88397076905 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_cv",
            "value": 0.04811156759686007,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0349149850933897 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_mean",
            "value": 757370.3835903093,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 749158.0396475763 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_median",
            "value": 758896.3149779781,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 749846.9162995596 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_stddev",
            "value": 12906.833853670794,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6142.053945974581 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_cv",
            "value": 0.01704164056757281,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.008198609133079538 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_mean",
            "value": 119606569.46666625,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 117188183.33333328 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_median",
            "value": 118160680.58332972,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 117266833.33333318 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_stddev",
            "value": 2885479.240435607,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 557152.8827188569 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_cv",
            "value": 0.02412475546537413,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.004754343542762124 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_mean",
            "value": 722240.3304263533,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 713213.5658914733 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_median",
            "value": 708388.9496123864,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 702928.2945736384 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_stddev",
            "value": 45185.1041217253,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 32054.030345263145 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_cv",
            "value": 0.06256242170116921,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.04494310242850971 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_mean",
            "value": 64386859.49090914,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 61478127.27272709 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_median",
            "value": 63428395.86363621,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 61658545.45454476 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_stddev",
            "value": 1914689.477718272,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 502040.23557759204 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_cv",
            "value": 0.029737270816704606,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.008166160191419934 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_mean",
            "value": 499312269.46667194,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 498061266.6666673 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_median",
            "value": 501488111.33334446,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 501089333.3333305 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_stddev",
            "value": 11075622.991861878,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 9567985.891610121 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_cv",
            "value": 0.02218175612566467,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.019210459700359707 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_mean",
            "value": 8469450.763414612,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 8418521.951219548 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_median",
            "value": 8470256.859755924,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 8411103.65853646 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_stddev",
            "value": 146573.24631214718,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 111963.3600574865 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_cv",
            "value": 0.0173061099717703,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.01329964579367367 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_mean",
            "value": 211479324.9999983,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 209631999.99999914 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_median",
            "value": 211082755.8571405,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 209612714.2857134 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_stddev",
            "value": 2669586.340797548,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1368397.0810510162 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_cv",
            "value": 0.012623391628460936,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.006527615445404432 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_mean",
            "value": 1886183.2870654028,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1883449.2350486908 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_median",
            "value": 1888274.6870654281,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1880842.8372739987 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_stddev",
            "value": 61760.77237819679,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 61003.96639244796 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_cv",
            "value": 0.03274378094733656,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.03238949330687476 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_mean",
            "value": 2063161.926446293,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1978354.8209366344 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_median",
            "value": 2010155.7630853883,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1974099.173553732 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_stddev",
            "value": 167022.50905504823,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 28290.72586413248 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_cv",
            "value": 0.08095462935511673,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.01430012734052352 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_mean",
            "value": 2337661.5543035753,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2212420.970266037 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_median",
            "value": 2246656.2331768265,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2199173.708920182 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_stddev",
            "value": 150669.5127273618,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 44621.857351887506 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_cv",
            "value": 0.0644530909318259,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.020168791541747978 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_mean",
            "value": 60908093.05833272,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 59527491.66666678 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_median",
            "value": 60285086.79166578,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 59503791.66666764 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_stddev",
            "value": 1430600.6741396752,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 442197.7402623457 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_cv",
            "value": 0.023487858547296247,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.007428462511716418 ns\nthreads: 1"
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
          "id": "5cfb757bdaa849c6fbaa3f70c58c15b6526a07c8",
          "message": "v0.9.7 (#56)\n\n* Wellner Binarization Algorithm - 1994\n\nAn optimized Wellner algorithm.  This is now the fastest local adaptive algorithm in Doxa.\n\nNOTE: While theoretically be the simplest adaptive algorithm, Niblack was still faster before adding the division / shift replacement.  That one change made all the difference.\n\n* Added Bradley and Feng\n\nFeng Note: I am adding Feng, but I made one improvement to it that seems to be working really well.  I am adding a `noise-floor` parameter that, when set, can let you greatly lower your window size without having black sections show up in large background patches!  This greatly increases the parameter range for getting good results.\n\n* Performance Boost\n\nBig wins for any algorithm using Chan (almost all of them).  They will see a 6 to 11% increase in performance simply by optimizing out the division.  This insight came from the Wellner algorithm and his paper.  Gatos got a 15+% jump thanks to звездочёт.\n\n* Update Feng\n\nThe interpolation mechanism for Feng needs to be setup just right.  The parameters before were too complex for normal use.  If you say you want a 9x9 window, I want to make sure it is truly a 9x9 window.\n\nI also updated the CMake system so that the Python src files would auto-copy on build.",
          "timestamp": "2026-05-16T00:22:09-05:00",
          "tree_id": "1e0e4ffa20ab4918bbc648b64d98e26620c4a83e",
          "url": "https://github.com/brandonmpetty/Doxa/commit/5cfb757bdaa849c6fbaa3f70c58c15b6526a07c8"
        },
        "date": 1778909210210,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_GlobalThreshold_Scalar_mean",
            "value": 7554.159176093019,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 7016.217478427563 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_median",
            "value": 6883.694591820687,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6874.241774234719 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_stddev",
            "value": 1896.3084501546425,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 783.9026318671379 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_cv",
            "value": 0.2510283945506436,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.11172724253165851 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_mean",
            "value": 13613.240315281602,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 11514.903947013518 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_median",
            "value": 14092.430395300727,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 11241.653430035667 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_stddev",
            "value": 1686.2561864961117,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 924.3698747321727 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_cv",
            "value": 0.12386883265427977,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.08027595184342944 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_mean",
            "value": 376730.22239797213,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 365022.46124644135 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_median",
            "value": 380706.6725719684,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 369514.39417905716 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_stddev",
            "value": 25070.19748954758,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 27453.56764736455 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_cv",
            "value": 0.0665468178527599,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.07521062554238146 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_mean",
            "value": 43868.874655439155,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 43114.50939113843 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_median",
            "value": 43301.19486201121,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 42051.840399986795 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_stddev",
            "value": 4389.326628301524,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3849.553395996924 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_cv",
            "value": 0.10005560121559455,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.08928672621723362 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_mean",
            "value": 114215.53455942453,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 111134.15072748046 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_median",
            "value": 109340.60470818903,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 109085.09073074984 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_stddev",
            "value": 19166.219451808734,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 14600.04919024866 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_cv",
            "value": 0.16780746617122258,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.13137320161873933 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_mean",
            "value": 53240.47328440243,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 52295.36912088998 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_median",
            "value": 51696.92617582156,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 51147.94457426858 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_stddev",
            "value": 4038.980063930788,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4142.669395685124 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_cv",
            "value": 0.07586296317005255,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.07921675408980501 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_mean",
            "value": 426660.4445855599,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 416742.6470588237 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_median",
            "value": 431899.7466577517,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 425500.33422459883 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_stddev",
            "value": 34644.21724376854,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 28604.908929337056 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_cv",
            "value": 0.08119856828401441,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.06863926485858175 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_mean",
            "value": 11995.893923615735,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 11679.277971608919 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_median",
            "value": 12142.003129411083,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 11748.85476868989 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_stddev",
            "value": 1314.5548050428936,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1074.1611031776977 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_cv",
            "value": 0.1095837303508489,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.09197153332499397 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_mean",
            "value": 1138720.1097154052,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1128354.072620215 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_median",
            "value": 1079548.986261021,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1069954.857703642 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_stddev",
            "value": 108788.6699216346,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 103264.88756865528 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_cv",
            "value": 0.09553591702953557,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.09151815912611369 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_mean",
            "value": 3447005.5327957077,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3433906.4516128907 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_median",
            "value": 3539921.1451612725,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3506733.8709677206 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_stddev",
            "value": 223073.54428760608,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 218537.66323759663 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_cv",
            "value": 0.06471516861961095,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.06364112311066321 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_mean",
            "value": 398269.3295677555,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 395873.13709891174 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_median",
            "value": 389601.7523203447,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 388043.2246088545 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_stddev",
            "value": 29596.04206719943,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 29067.085563285706 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_cv",
            "value": 0.07431162750925414,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.07342525379796885 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_mean",
            "value": 1167426.183200007,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1125814.3999999987 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_median",
            "value": 1191119.083000018,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1115530.9999999902 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_stddev",
            "value": 59333.28521579537,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 61143.216568152944 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_cv",
            "value": 0.05082401445987631,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.054310210073839 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_mean",
            "value": 1171096.494460088,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1138990.610328635 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_median",
            "value": 1221881.2600938962,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1220113.615023483 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_stddev",
            "value": 141132.11205792878,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 132729.22544214924 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_cv",
            "value": 0.12051279525261926,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.11653232628832001 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_mean",
            "value": 2055454.3260815847,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1972045.7354758948 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_median",
            "value": 2067945.199011096,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2016097.6514214892 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_stddev",
            "value": 130582.03352045912,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 117815.6902557429 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_cv",
            "value": 0.06352952330952262,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.059742879252905126 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_mean",
            "value": 983153.4909090921,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 965475.0614250606 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_median",
            "value": 1005227.4004914031,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 994788.0835380789 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_stddev",
            "value": 128469.19549556616,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 115169.57308405553 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_cv",
            "value": 0.130670537900216,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.11928798338308494 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_mean",
            "value": 146825794.70909125,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 146344781.81818184 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_median",
            "value": 144770871.27273142,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 144286181.81818044 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_stddev",
            "value": 8313901.513250875,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 8193908.2503824085 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_cv",
            "value": 0.05662425685979337,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.05599043675204277 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_mean",
            "value": 1043934.4670000083,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1042027.1999999955 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_median",
            "value": 1057188.999999994,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1055413.9999999988 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_stddev",
            "value": 83807.41569119887,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 82741.69604074904 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_cv",
            "value": 0.08028034166937625,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.07940454533312508 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_mean",
            "value": 91944794.61176506,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 86784294.11764728 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_median",
            "value": 91990002.47058861,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 88591941.17647128 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_stddev",
            "value": 6732148.66635322,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5587699.97250157 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_cv",
            "value": 0.0732194649493707,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.06438607387791533 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_mean",
            "value": 728160783.3000066,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 713593700.0000013 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_median",
            "value": 669794812.5000153,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 664554500.0000083 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_stddev",
            "value": 91584456.27900258,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 98480342.86000797 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_cv",
            "value": 0.1257750463626235,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.13800618315437455 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_mean",
            "value": 18219755.846753404,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 17062677.922078066 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_median",
            "value": 18051788.96103955,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 17071311.688311733 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_stddev",
            "value": 766628.6490243062,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 939352.785813182 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_cv",
            "value": 0.04207677948444696,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.05505306904947885 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_mean",
            "value": 383699594.4666645,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 363592133.333331 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_median",
            "value": 367532194.6666562,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 359602666.6666698 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_stddev",
            "value": 35620385.435263745,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 15705217.531127429 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_cv",
            "value": 0.09283404504186521,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.043194602114037854 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_mean",
            "value": 4459724.7432099,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4408030.246913596 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_median",
            "value": 4455448.302469154,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4391145.061728392 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_stddev",
            "value": 161600.32977545777,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 164838.33563441745 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_cv",
            "value": 0.03623549413481188,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.03739501010680078 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_mean",
            "value": 2915492.9545189603,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2900710.2040816303 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_median",
            "value": 2683809.40233232,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2665836.7346939286 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_stddev",
            "value": 506663.41513946856,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 500468.93727976567 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_cv",
            "value": 0.17378310393587112,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.17253324257471458 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_mean",
            "value": 904167.5120773038,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 800388.7278582939 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_median",
            "value": 891426.6188942563,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 793362.8556092355 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_stddev",
            "value": 46562.75999307675,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 31786.983477913316 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_cv",
            "value": 0.05149793525106856,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.03971443171491177 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_mean",
            "value": 838465.792587398,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 802580.0000000051 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_median",
            "value": 848302.302097897,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 787488.1118881034 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_stddev",
            "value": 66273.34326034226,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 63546.28582171011 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_cv",
            "value": 0.07904120102005736,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.07917750980800631 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_mean",
            "value": 998297.0681707363,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 949826.2195121963 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_median",
            "value": 996429.2426829155,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 917494.5121951097 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_stddev",
            "value": 87288.40164679415,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 79097.23113810123 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_cv",
            "value": 0.0874373014104309,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.08327547662215865 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_mean",
            "value": 3224336.171662126,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3096226.7029973096 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_median",
            "value": 3154701.8610353917,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2960749.3188011358 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_stddev",
            "value": 375831.35851054254,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 273382.75578921277 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_cv",
            "value": 0.11656084803241955,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.08829545831529839 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_mean",
            "value": 97110269.80000028,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 88794450.00000033 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_median",
            "value": 98496192.68749876,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 89257937.5000011 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_stddev",
            "value": 7271828.048617549,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3092109.782183497 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_cv",
            "value": 0.0748821732613241,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.03482323255770474 ns\nthreads: 1"
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
            "email": "brandonpetty1981@gmail.com",
            "name": "Brandon M. Petty",
            "username": "brandonmpetty"
          },
          "distinct": true,
          "id": "600ae1febc4546be6acf0738e11733b80530754b",
          "message": "CodeCov - Update\n\nUse token and their updated action.\nTarget just the Doxa folder.",
          "timestamp": "2026-05-16T12:50:34-05:00",
          "tree_id": "db93904152ca22043777f644f6cb9c92cd93a79d",
          "url": "https://github.com/brandonmpetty/Doxa/commit/600ae1febc4546be6acf0738e11733b80530754b"
        },
        "date": 1778954084610,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_GlobalThreshold_Scalar_mean",
            "value": 5787.413771554204,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5786.531297020041 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_median",
            "value": 6051.863053603509,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6050.489609322046 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_stddev",
            "value": 936.2896120257549,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 936.259136471117 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_cv",
            "value": 0.1617803131042271,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.16179971876299598 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_mean",
            "value": 6861.303414034175,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6859.339840404171 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_median",
            "value": 6787.42634540967,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6786.636147633404 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_stddev",
            "value": 113.39839071519332,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 111.18872090251814 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_cv",
            "value": 0.016527237446349794,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.016209828276414217 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_mean",
            "value": 278717.9338820317,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 277554.18381344277 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_median",
            "value": 277907.7668038268,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 277836.76268861466 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_stddev",
            "value": 3505.8366001618924,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2382.59069429143 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_cv",
            "value": 0.012578439253377035,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.008584236279763237 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_mean",
            "value": 28450.382768143056,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 28446.32660520651 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_median",
            "value": 28440.7058441218,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 28435.202859115478 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_stddev",
            "value": 27.18057840910228,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 27.15391750661643 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_cv",
            "value": 0.0009553677583395249,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.000954566748932935 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_mean",
            "value": 70768.89154234635,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 70751.64752602777 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_median",
            "value": 70627.65198024848,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 70624.44993023491 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_stddev",
            "value": 672.0327290717313,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 657.1172968014029 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_cv",
            "value": 0.00949616016904269,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.009287660708673475 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_mean",
            "value": 33191.261954173504,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 33150.72269725832 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_median",
            "value": 33867.52959255305,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 33867.48014484386 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_stddev",
            "value": 1740.631594946297,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1785.8560222813012 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_cv",
            "value": 0.052442465048468216,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.05387080211162328 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_mean",
            "value": 306155.6683693576,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 306040.0785854613 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_median",
            "value": 305301.3625846085,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 305263.6978825579 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_stddev",
            "value": 1798.2137688702387,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1806.4748074386468 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_cv",
            "value": 0.005873527602633856,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0059027393267845835 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_mean",
            "value": 7594.309417233909,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 7568.172247871543 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_median",
            "value": 7587.140135419325,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 7586.478455484799 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_stddev",
            "value": 119.55139670829412,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 90.96306075414279 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_cv",
            "value": 0.015742234104524883,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0120191583614822 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_mean",
            "value": 644257.8352350213,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 644081.880419901 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_median",
            "value": 639582.0972159097,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 639449.1099954383 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_stddev",
            "value": 8581.753714570663,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 8527.956398100163 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_cv",
            "value": 0.013320371511570511,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.013240484878320856 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_mean",
            "value": 2176178.3642526316,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2175296.456086281 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_median",
            "value": 2152684.0000002095,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2152485.3620955306 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_stddev",
            "value": 54096.63158710863,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 52621.9779620704 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_cv",
            "value": 0.024858546742186332,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.02419071562169786 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_mean",
            "value": 284650.4817444298,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 284608.27586206986 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_median",
            "value": 283766.21866121463,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 283732.86004056816 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_stddev",
            "value": 2063.0193931050017,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2035.6857472841943 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_cv",
            "value": 0.007247552789871123,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.007152588030401308 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_mean",
            "value": 668632.648118926,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 665833.3488156068 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_median",
            "value": 665297.8592661668,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 665231.3051555968 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_stddev",
            "value": 16925.95576319844,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 11540.162086783026 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_cv",
            "value": 0.0253142825299011,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.01733190761218377 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_mean",
            "value": 722748.8704860025,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 722538.6189258314 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_median",
            "value": 718905.4987212445,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 718492.0716112526 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_stddev",
            "value": 7063.035894202633,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6984.324387378581 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_cv",
            "value": 0.009772462030211397,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.009666368280441385 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_mean",
            "value": 1360086.6602687025,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1359727.4472168912 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_median",
            "value": 1365753.1190018884,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1365589.251439554 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_stddev",
            "value": 13507.907411025832,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 13359.595636677512 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_cv",
            "value": 0.009931652008378035,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.009825201119549449 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_mean",
            "value": 679456.9053398253,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 679322.5242718434 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_median",
            "value": 676802.3257281419,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 676766.9902912655 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_stddev",
            "value": 6962.847664493283,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6911.360937296221 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_cv",
            "value": 0.010247666349068698,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.010173902219280032 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_mean",
            "value": 116977323.45453253,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 116951836.36363712 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_median",
            "value": 115932977.27271917,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 115855090.90909211 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_stddev",
            "value": 2601082.7856390174,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2603412.8827391984 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_cv",
            "value": 0.02223578646548553,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.022260555829533405 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_mean",
            "value": 654824.7269621174,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 654733.5180055383 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_median",
            "value": 654495.056324917,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 654415.9741458878 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_stddev",
            "value": 7015.680367414544,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6972.155961559061 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_cv",
            "value": 0.010713829332563388,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.010648845323816283 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_mean",
            "value": 59939299.26956338,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 59933330.4347828 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_median",
            "value": 60046492.73913658,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 60042260.86956583 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_stddev",
            "value": 657664.7803238727,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 657698.4657366422 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_cv",
            "value": 0.010972179994400248,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.010973834775498167 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_mean",
            "value": 485351399.9333094,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 485244399.99999726 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_median",
            "value": 482954124.9999542,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 482851999.99999887 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_stddev",
            "value": 3677651.510312407,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3591666.1361037283 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_cv",
            "value": 0.007577296595451752,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.007401767307574799 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_mean",
            "value": 8148684.249711503,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 8147452.023121335 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_median",
            "value": 8139030.589597228,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 8138537.572254414 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_stddev",
            "value": 62345.31956298436,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 61583.29613019973 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_cv",
            "value": 0.007650967647346459,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.007558595737100987 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_mean",
            "value": 208386457.14286813,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 208341914.28571346 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_median",
            "value": 207709494.14288357,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 207701285.71428314 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_stddev",
            "value": 1638764.8114406224,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1625407.379389961 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_cv",
            "value": 0.007864065803072308,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.00780163408290916 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_mean",
            "value": 1759872.1266482486,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1750488.1868132048 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_median",
            "value": 1728039.3777472563,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1727451.9230769705 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_stddev",
            "value": 58569.40187840238,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 44406.18699135883 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_cv",
            "value": 0.03328048725332692,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.025367887270465444 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_mean",
            "value": 1809999.0030535595,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1809335.6234096712 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_median",
            "value": 1792209.657761182,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1791517.8117048244 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_stddev",
            "value": 28976.31015129625,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 29055.03327639455 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_cv",
            "value": 0.01600901995106724,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.01605839895068262 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_mean",
            "value": 456616.6238614534,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 456493.6497754992 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_median",
            "value": 456297.5865939525,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 456236.04874920344 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_stddev",
            "value": 10093.200009115122,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 10052.196318087163 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_cv",
            "value": 0.022104320083137403,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.022020451594520034 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_mean",
            "value": 436369.2360850447,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 436338.0863039383 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_median",
            "value": 435780.38367741666,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 435752.03252032073 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_stddev",
            "value": 2223.2809561827103,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2223.386529991395 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_cv",
            "value": 0.005094953475935256,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0050955591541982865 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_mean",
            "value": 498876.1630427283,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 498652.31431646796 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_median",
            "value": 495511.6013634523,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 495471.83351273433 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_stddev",
            "value": 6044.479977516334,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5647.048030750559 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_cv",
            "value": 0.012116193206446366,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.011324620118310891 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_mean",
            "value": 2038021.4784369834,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2037562.0839363288 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_median",
            "value": 2024835.7452966585,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2023931.9826338706 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_stddev",
            "value": 21291.18753792119,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 21113.506216600435 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_cv",
            "value": 0.01044698878946556,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.010362141297707917 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_mean",
            "value": 55492389.99999944,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 55484711.999999724 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_median",
            "value": 55603281.67999615,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 55599559.99999943 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_stddev",
            "value": 396816.37138216785,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 393601.8377995911 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_cv",
            "value": 0.007150825029921614,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.007093879081495333 ns\nthreads: 1"
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
          "id": "ea8007847865c649c7febe964cdbc077179d804f",
          "message": "v0.9.8 - Pseudo Weights, XDoG and BinBench (#57)\n\nThis is a HUGE release.  It is the first release that was driven by AI.\n\n- Utilities: BinBench - A Python script exposing all binarization and grayscale algorithms along with all performance metrics\n- Binarization: XDoG\n- Metrics: bit-exact Pseudo Weight generation!\n- Extras: Canny Edge Detection... for the future :)",
          "timestamp": "2026-07-04T11:26:47-05:00",
          "tree_id": "280b97c25f17cde3c2c5fb9327c68e4363f37353",
          "url": "https://github.com/brandonmpetty/Doxa/commit/ea8007847865c649c7febe964cdbc077179d804f"
        },
        "date": 1783182697117,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_GlobalThreshold_Scalar_mean",
            "value": 5759.855048219724,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5741.0815428914975 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_median",
            "value": 5685.620711113947,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5675.723472103566 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_stddev",
            "value": 286.97893606670914,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 276.82210991183877 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_cv",
            "value": 0.04982398578856765,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.04821776312419649 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_mean",
            "value": 7717.253774201961,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 7674.130036630044 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_median",
            "value": 7959.6712999300335,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 7828.307605093328 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_stddev",
            "value": 967.5562260056633,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 949.1742130460332 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_cv",
            "value": 0.12537571710290402,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.12368492695790258 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_mean",
            "value": 297074.6337741605,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 295841.7904374363 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_median",
            "value": 295838.3011190306,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 291338.5554425236 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_stddev",
            "value": 7408.080026235402,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 7522.986650185963 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_cv",
            "value": 0.024936763977859877,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.025429087077462442 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_mean",
            "value": 33186.170253836775,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 32952.91245677088 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_median",
            "value": 33069.79385637767,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 32976.989670215415 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_stddev",
            "value": 3110.4806757472224,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2942.9213436300747 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_cv",
            "value": 0.0937282202783736,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.08930686619857145 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_mean",
            "value": 70286.61812052233,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 70237.10493046782 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_median",
            "value": 70736.21644543,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 70613.51664559638 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_stddev",
            "value": 1924.7587147786005,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1911.0514134137782 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_cv",
            "value": 0.027384426313955886,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.02720857323640617 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_mean",
            "value": 29578.958199753368,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 29508.30250719276 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_median",
            "value": 29568.977375481027,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 29485.969435414554 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_stddev",
            "value": 1617.2619109032726,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1638.2652308410065 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_cv",
            "value": 0.05467609440405368,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0555187893455299 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_mean",
            "value": 333884.3360468072,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 331959.85754260956 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_median",
            "value": 329405.20859832584,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 329160.5189519196 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_stddev",
            "value": 10557.63166678476,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 7969.207000678796 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_cv",
            "value": 0.03162062584842161,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.024006538199143217 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_mean",
            "value": 8139.952114449037,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 8110.763333673541 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_median",
            "value": 8083.883112759213,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 8078.828292450574 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_stddev",
            "value": 234.3222655397101,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 187.34788667840428 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_cv",
            "value": 0.028786688452843618,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.02309867505325795 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_mean",
            "value": 671098.3778200899,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 671009.7096620658 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_median",
            "value": 668296.9219419302,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 668214.6596858648 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_stddev",
            "value": 12244.204628726988,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12222.882491278579 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_cv",
            "value": 0.018245021942236688,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.018215656666777994 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_mean",
            "value": 2523212.2583177774,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2516506.168224291 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_median",
            "value": 2493536.6822429835,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2492325.2336448566 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_stddev",
            "value": 78089.3644514689,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 66245.7341760984 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_cv",
            "value": 0.030948392943973318,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.026324487105407347 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_mean",
            "value": 299545.29836277565,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 299361.0512710041 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_median",
            "value": 301506.7141318344,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 301468.7634640235 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_stddev",
            "value": 5233.974405237326,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5227.513650346669 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_cv",
            "value": 0.017473064788012544,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.017462237081785008 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_mean",
            "value": 726691.4661538511,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 725656.7307692335 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_median",
            "value": 727632.6721153918,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 726649.5192307702 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_stddev",
            "value": 38105.772329506704,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 37487.48238132372 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_cv",
            "value": 0.052437346665412964,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.05166007671641804 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_mean",
            "value": 789042.1195389633,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 788717.8924259043 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_median",
            "value": 787248.8111964879,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 786993.4138309491 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_stddev",
            "value": 16067.887153195616,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 16333.464379103278 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_cv",
            "value": 0.020363788897079495,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.020708880242168104 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_mean",
            "value": 1527303.5845056144,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1515678.491335373 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_median",
            "value": 1504384.1314984648,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1500764.5259939008 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_stddev",
            "value": 51708.013362608515,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 34392.45467973962 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_cv",
            "value": 0.03385575329435655,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.02269112801715521 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_mean",
            "value": 742615.8593749991,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 741765.5208333329 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_median",
            "value": 732835.0479166801,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 732603.6458333333 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_stddev",
            "value": 20627.32818995679,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 21045.169783028 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_cv",
            "value": 0.027776579141896022,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.028371728250977352 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_mean",
            "value": 130797253.76363638,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 129609854.54545501 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_median",
            "value": 131143234.81818247,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 129529181.81818259 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_stddev",
            "value": 5250242.421161269,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5280634.369213831 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_cv",
            "value": 0.0401403108252485,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.04074253757735589 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_mean",
            "value": 814561.7677298336,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 813624.1400875512 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_median",
            "value": 829311.7836147409,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 828536.5853658572 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_stddev",
            "value": 49481.317898671216,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 49797.334460885584 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_cv",
            "value": 0.060745937090289165,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.061204347323725004 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_mean",
            "value": 74408677.43529359,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 73396717.64705949 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_median",
            "value": 74333254.88235328,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 73924588.23529617 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_stddev",
            "value": 6852105.623816368,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5353867.981724799 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_cv",
            "value": 0.09208745350668296,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.07294424264951162 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_mean",
            "value": 532686811.06666625,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 532039400.0000003 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_median",
            "value": 530831096.99999416,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 530591333.33333844 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_stddev",
            "value": 11131668.124696445,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 11076730.161819724 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_cv",
            "value": 0.02089720994294208,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.020819379470429666 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_mean",
            "value": 9254299.27125002,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 9189406.250000048 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_median",
            "value": 9046280.21249998,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 9043199.999999985 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_stddev",
            "value": 470546.0891569148,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 401810.632554088 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_cv",
            "value": 0.05084621486347891,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.04372541833745634 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_mean",
            "value": 215973497.62857094,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 215798914.28571454 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_median",
            "value": 214191154.85714105,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 213778285.7142838 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_stddev",
            "value": 3761732.0760892676,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3795540.779947807 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_cv",
            "value": 0.017417563346400294,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.017588321945506028 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_mean",
            "value": 2367310.564628095,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2358291.5702479286 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_median",
            "value": 2303012.533884274,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2294390.082644617 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_stddev",
            "value": 161305.86240138422,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 153617.80931978297 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_cv",
            "value": 0.0681388681365199,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.06513944724130656 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_mean",
            "value": 2088878.9778102003,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2084981.3138685985 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_median",
            "value": 2019094.8291970745,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2018702.1897809855 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_stddev",
            "value": 114248.9820414957,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 109254.76423147356 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_cv",
            "value": 0.05469392111996092,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.05240083616325354 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_mean",
            "value": 571337.2257447619,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 564026.4803236474 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_median",
            "value": 581843.9988966625,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 558080.1765354967 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_stddev",
            "value": 59201.76083376977,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 55718.95828338644 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_cv",
            "value": 0.10361964557201363,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.09878784104500556 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_mean",
            "value": 552302.071621035,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 542273.6201651499 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_median",
            "value": 539663.877879214,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 535656.671012609 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_stddev",
            "value": 42932.74120379953,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 36776.491432447154 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_cv",
            "value": 0.07773416651831437,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.06781906783746339 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_mean",
            "value": 623755.2578968657,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 620015.2659358537 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_median",
            "value": 625481.5943970622,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 625200.9744214289 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_stddev",
            "value": 44010.290013512546,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 39914.113348995845 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_cv",
            "value": 0.0705569844203051,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.06437601707878808 ns\nthreads: 1"
          },
          {
            "name": "BM_XDoG_mean",
            "value": 5180853.851515129,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5161172.7272727275 ns\nthreads: 1"
          },
          {
            "name": "BM_XDoG_median",
            "value": 5284836.018939625,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5266128.787878745 ns\nthreads: 1"
          },
          {
            "name": "BM_XDoG_stddev",
            "value": 193818.87741392208,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 196550.72153030155 ns\nthreads: 1"
          },
          {
            "name": "BM_XDoG_cv",
            "value": 0.03741060507955463,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.03808256997323225 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_mean",
            "value": 2519491.3967509377,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2510021.660649834 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_median",
            "value": 2512598.527075731,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2510792.4187725917 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_stddev",
            "value": 165173.27184762945,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 152294.1000448894 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_cv",
            "value": 0.06555818053621143,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.06067441665242884 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_mean",
            "value": 61165393.49565222,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 60301095.652173996 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_median",
            "value": 59337318.86956712,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 59275086.95652167 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_stddev",
            "value": 4231143.488086001,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2549533.0076482072 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_cv",
            "value": 0.06917544785168038,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.04228004450125262 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Generate_mean",
            "value": 74468236.40000156,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 74216431.57894784 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Generate_median",
            "value": 74138817.9473664,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 74123210.52631617 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Generate_stddev",
            "value": 3252460.1806002697,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2912771.353949275 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Generate_cv",
            "value": 0.043675805119512696,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.039246987385142734 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Recall_mean",
            "value": 15362828.531764377,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 15349282.35294133 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Recall_median",
            "value": 15144409.31764645,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 15139670.588235492 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Recall_stddev",
            "value": 503588.7744864525,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 504475.6548115456 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Recall_cv",
            "value": 0.032779691151614825,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.032866400083836796 ns\nthreads: 1"
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
            "email": "brandonpetty1981@gmail.com",
            "name": "Brandon M. Petty",
            "username": "brandonmpetty"
          },
          "distinct": true,
          "id": "16fc9edbf21d15ebfc602f5185fc01c79bc718b2",
          "message": "v0.9.8 - Pseudo Weights, XDoG and BinBench (#57)\n\nThis is a HUGE release.  It is the first release that was driven by AI.\n\n- Utilities: BinBench - A Python script exposing all binarization and grayscale algorithms along with all performance metrics\n- Binarization: XDoG\n- Metrics: bit-exact Pseudo Weight generation!\n- Extras: Canny Edge Detection... for the future :)",
          "timestamp": "2026-07-04T11:38:37-05:00",
          "tree_id": "9d793dfc062bcc18a5c84aa88b6843b9421c0859",
          "url": "https://github.com/brandonmpetty/Doxa/commit/16fc9edbf21d15ebfc602f5185fc01c79bc718b2"
        },
        "date": 1783183404975,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_GlobalThreshold_Scalar_mean",
            "value": 6649.958852239926,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6648.311416462008 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_median",
            "value": 6981.88447269994,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6980.621962466711 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_stddev",
            "value": 659.2071031239507,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 659.0309331462873 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_cv",
            "value": 0.09912950106479347,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.09912756666519089 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_mean",
            "value": 7277.18730511233,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 7275.812380532274 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_median",
            "value": 7265.754741949795,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 7263.63770033818 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_stddev",
            "value": 126.85325041701749,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 126.238099645893 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_cv",
            "value": 0.01743163190645117,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.017350378630387086 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_mean",
            "value": 284418.6293641135,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 284361.5633859864 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_median",
            "value": 283801.2523288818,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 283761.23936816497 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_stddev",
            "value": 4155.269775546787,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4147.218486421776 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_cv",
            "value": 0.01460969622431869,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.014584314550248938 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_mean",
            "value": 30395.769500430684,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 30368.924570732033 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_median",
            "value": 30562.494314958498,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 30561.190391122458 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_stddev",
            "value": 469.9100662004845,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 456.631272183353 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_cv",
            "value": 0.015459719359755843,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.015036135741975865 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_mean",
            "value": 71449.84588175736,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 71416.79636179886 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_median",
            "value": 71804.04244567612,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 71693.07731177381 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_stddev",
            "value": 605.0344237912882,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 589.5509567134674 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_cv",
            "value": 0.00846795981607241,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.008255074250695745 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_mean",
            "value": 27159.15278299437,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 27141.51116793861 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_median",
            "value": 26639.651676189165,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 26572.581611859194 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_stddev",
            "value": 865.2293019071296,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 874.4205734908786 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_cv",
            "value": 0.03185774272196336,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.03221709241170784 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_mean",
            "value": 325867.5707671332,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 325136.08715388115 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_median",
            "value": 324751.9291874853,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 324633.2274171589 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_stddev",
            "value": 3109.302810064636,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2625.377526055686 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_cv",
            "value": 0.00954161472019123,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.008074703577315124 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_mean",
            "value": 7983.481383398449,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 7982.406635263358 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_median",
            "value": 7985.902792490031,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 7985.581149000458 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_stddev",
            "value": 134.09519452744627,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 133.7626848301651 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_cv",
            "value": 0.016796581351876835,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.01675718751776568 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_mean",
            "value": 686314.5461032863,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 683288.8262910811 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_median",
            "value": 688591.6666666812,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 688476.5258215945 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_stddev",
            "value": 16117.680395126245,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12176.170813821958 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_cv",
            "value": 0.023484392814691453,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.01781994721019323 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_mean",
            "value": 2418063.645868443,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2417186.5092748716 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_median",
            "value": 2405255.833052357,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2405030.3541315254 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_stddev",
            "value": 60733.567283710734,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 59915.435979993104 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_cv",
            "value": 0.025116612371837873,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.024787262277898056 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_mean",
            "value": 306644.39434424404,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 306596.7935871749 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_median",
            "value": 307559.6283678501,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 307462.4805165889 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_stddev",
            "value": 7315.400635682668,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 7302.342407935692 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_cv",
            "value": 0.02385629990506293,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0238174128388574 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_mean",
            "value": 700953.384724331,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 700781.9929185616 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_median",
            "value": 693526.5341426102,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 692939.8077895774 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_stddev",
            "value": 16304.510812054132,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 16368.140366098229 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_cv",
            "value": 0.023260478039443838,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.023356964835710873 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_mean",
            "value": 769859.827226875,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 769759.3277310928 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_median",
            "value": 775724.4862745062,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 775528.2913165229 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_stddev",
            "value": 13519.096445104271,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 13531.815136435984 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_cv",
            "value": 0.017560464862547295,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.01757928049579047 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_mean",
            "value": 1448911.508350719,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1448745.9290187887 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_median",
            "value": 1448720.1200417208,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1448664.9269311088 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_stddev",
            "value": 19045.617355803137,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 19026.759691761312 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_cv",
            "value": 0.0131447760929738,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.013133261885779941 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_mean",
            "value": 722555.8232412611,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 722502.1365294419 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_median",
            "value": 724612.8843147733,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 724553.9343408069 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_stddev",
            "value": 7654.899553469622,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 7625.702813473402 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_cv",
            "value": 0.01059419813285991,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.01055457475891167 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_mean",
            "value": 116739627.78333478,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 116729483.33333321 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_median",
            "value": 117440996.50000331,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 117422416.66666687 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_stddev",
            "value": 1836617.3075297885,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1840122.1430622048 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_cv",
            "value": 0.015732595198423068,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.015763987730567985 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_mean",
            "value": 692784.8923818565,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 692662.8736740609 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_median",
            "value": 688546.0462873394,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 688381.8707810952 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_stddev",
            "value": 7994.11152209516,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 8006.044285037276 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_cv",
            "value": 0.01153909620432208,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.011558356293258755 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_mean",
            "value": 62263885.8608693,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 62256304.34782597 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_median",
            "value": 62324769.91304179,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 62313652.17391272 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_stddev",
            "value": 649772.2065671135,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 648613.4848585475 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_cv",
            "value": 0.010435779867948665,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.010418438608799263 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_mean",
            "value": 603132622.2666773,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 595559133.3333322 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_median",
            "value": 606134514.0000185,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 594517333.3333287 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_stddev",
            "value": 38755062.11518432,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 31948246.145220034 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_cv",
            "value": 0.06425628573950462,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.05364412088923287 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_mean",
            "value": 9212329.228787752,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 9204968.181818176 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_median",
            "value": 9193699.492424333,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 9189325.757575668 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_stddev",
            "value": 177181.5826015689,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 180442.8512640155 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_cv",
            "value": 0.019233092760937313,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.019602767516397245 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_mean",
            "value": 218924645.83333248,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 218822099.999999 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_median",
            "value": 216460444.33333603,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 216396000.00000316 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_stddev",
            "value": 4313472.561790787,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4291478.144076959 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_cv",
            "value": 0.01970300121017273,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.01961172177799674 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_mean",
            "value": 2320450.1227940917,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2319680.147058822 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_median",
            "value": 2346240.503676502,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2345345.5882353513 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_stddev",
            "value": 131900.99253710086,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 131647.00392620373 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_cv",
            "value": 0.05684284753264884,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.05675222253944024 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_mean",
            "value": 2131173.6194528844,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2125773.860182346 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_median",
            "value": 2149733.5987842623,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2149404.255319114 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_stddev",
            "value": 149133.3890372236,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 140040.4619863039 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_cv",
            "value": 0.0699771185585101,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.06587740333503368 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_mean",
            "value": 534732.1227331373,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 533091.2763214465 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_median",
            "value": 535631.1237645291,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 535464.1168887115 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_stddev",
            "value": 8131.373056065238,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6906.964147005356 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_cv",
            "value": 0.015206442086373912,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.01295643814445118 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_mean",
            "value": 530894.8048183934,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 530400.9636768026 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_median",
            "value": 524443.5077835649,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 524229.4292068261 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_stddev",
            "value": 37136.200250669346,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 36849.39072413657 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_cv",
            "value": 0.06995020466130343,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.06947459233235967 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_mean",
            "value": 619569.8144554374,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 619220.8910891062 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_median",
            "value": 607313.7995049747,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 606864.8514851455 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_stddev",
            "value": 29853.628411048772,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 30063.90917469227 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_cv",
            "value": 0.04818444623111314,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.04855118683385321 ns\nthreads: 1"
          },
          {
            "name": "BM_XDoG_mean",
            "value": 5064379.271480174,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5056122.021660683 ns\nthreads: 1"
          },
          {
            "name": "BM_XDoG_median",
            "value": 5136090.101082889,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5134927.797833995 ns\nthreads: 1"
          },
          {
            "name": "BM_XDoG_stddev",
            "value": 183789.24947269523,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 176876.18841282564 ns\nthreads: 1"
          },
          {
            "name": "BM_XDoG_cv",
            "value": 0.03629057770370718,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.034982579070496934 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_mean",
            "value": 2482693.37337881,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2447855.6313992944 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_median",
            "value": 2463167.2354948064,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2460470.989761084 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_stddev",
            "value": 223120.47979832307,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 157814.0613040799 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_cv",
            "value": 0.0898703328372236,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.06447033039030448 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_mean",
            "value": 63051646.92631526,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 62511084.21052615 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_median",
            "value": 62923129.36842026,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 62397315.789472654 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_stddev",
            "value": 689882.4500625462,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 881128.7873443107 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_cv",
            "value": 0.010941545283801566,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.014095560786897032 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Generate_mean",
            "value": 77809464.92631349,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 77716336.84210518 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Generate_median",
            "value": 75248326.78946999,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 75211578.94736886 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Generate_stddev",
            "value": 6178107.818669635,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6088636.177179172 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Generate_cv",
            "value": 0.07940046656946398,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0783443536402049 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Recall_mean",
            "value": 15908914.154838827,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 15886739.784946257 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Recall_median",
            "value": 16192536.290321928,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 16098741.935483944 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Recall_stddev",
            "value": 519964.93177326245,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 508972.2337539129 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Recall_cv",
            "value": 0.03268387312374245,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0320375508533348 ns\nthreads: 1"
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
          "id": "be67520e93a460853e7ab6e2b87d895dac889677",
          "message": "v0.9.6 (#55)\n\n- Phansalkar: added binarization algorithm and LAB Distance grayscale (C++, Python, WASM, Matlab)\n- Su: fix std-E calc, correct paper's /2 → /Ne, add stroke-width detection + unit tests\n- Gatos: fix divide-by-zero, correct threshold-calc object, document removed post-processing experiment\n  - Implemented, then removed, the post-processing routines.  They appeared to greatly reduce detail.  Holes were closed, even when they were supposed to stay open.  Artificially thicker lines as well.\n- Build: MATLAB now opt-in via the unified preset; broad spelling cleanup",
          "timestamp": "2026-05-08T19:24:38-05:00",
          "tree_id": "a78925911bcde1fbdc5016efe80103daa8368b42",
          "url": "https://github.com/brandonmpetty/Doxa/commit/be67520e93a460853e7ab6e2b87d895dac889677"
        },
        "date": 1778286536964,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_GlobalThreshold_Scalar_mean",
            "value": 8449.100201294514,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 8437.496233260612 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_median",
            "value": 8445.511252003951,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 8380.995142412885 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_stddev",
            "value": 85.32973294810738,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 142.8135781170541 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_cv",
            "value": 0.010099268669465387,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.01692606125903594 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_mean",
            "value": 12515.125000000082,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12276.785714285714 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_median",
            "value": 12508.290178571611,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12276.785714285714 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_stddev",
            "value": 19.282877829388838,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 220.58298410772736 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_cv",
            "value": 0.0015407658996125658,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.017967486705502158 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_mean",
            "value": 392393.6662946438,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 388881.13839285716 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_median",
            "value": 391988.7834821382,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 388009.2075892857 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_stddev",
            "value": 1335.0344736976226,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1949.696548460844 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_cv",
            "value": 0.0034022834422999097,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.005013605330714738 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_mean",
            "value": 69517.22766310119,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 68586.45974586911 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_median",
            "value": 69270.62930038769,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 69057.3050072824 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_stddev",
            "value": 381.7150613108311,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 701.8946742688629 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_cv",
            "value": 0.005490941945509145,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.010233720720818183 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_mean",
            "value": 116195.10781249966,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 114990.234375 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_median",
            "value": 115909.24999999697,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 115966.796875 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_stddev",
            "value": 591.0561054357902,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1337.213275158489 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_cv",
            "value": 0.005086755514608744,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.011628929034074672 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_mean",
            "value": 37113.98618990196,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 37060.09189619324 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_median",
            "value": 37003.881202351986,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 36899.65859794132 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_stddev",
            "value": 239.91031236636755,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 219.68234106872524 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_cv",
            "value": 0.006464148343937324,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.005927733306330271 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_mean",
            "value": 391760.49665178766,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 392368.8616071429 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_median",
            "value": 391694.5312500023,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 392368.8616071429 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_stddev",
            "value": 137.92348186389015,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_cv",
            "value": 0.000352060718328326,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_mean",
            "value": 15174.077504118346,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 15161.065129173532 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_median",
            "value": 15145.805375869017,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 15223.843866768453 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_stddev",
            "value": 66.95385573829331,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 85.96332678105117 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_cv",
            "value": 0.004412383930431461,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.005670005771272433 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_mean",
            "value": 2593298.9642856997,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2583705.3571428573 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_median",
            "value": 2593005.178571417,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2594866.0714285714 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_stddev",
            "value": 2848.7174304662476,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 15282.437430324815 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_cv",
            "value": 0.0010984917164191675,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.005914930426596559 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_mean",
            "value": 6645107.115384483,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6595552.884615386 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_median",
            "value": 6646199.038461404,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6610576.923076923 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_stddev",
            "value": 15815.352935381161,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 33594.771296365114 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_cv",
            "value": 0.002379999699141959,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.005093548923658456 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_mean",
            "value": 174251.7937384889,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 173802.94659300183 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_median",
            "value": 173638.94413751276,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 172651.93370165746 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_stddev",
            "value": 1018.0927109956574,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2573.7430680234493 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_cv",
            "value": 0.005842652687544645,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.014808397201978626 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_mean",
            "value": 2666193.5863377466,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2668406.0721062617 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_median",
            "value": 2659777.798861541,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2668406.0721062617 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_stddev",
            "value": 13623.771179740997,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 20964.978094966493 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_cv",
            "value": 0.005109820700774567,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.00785674201318922 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_mean",
            "value": 2803407.4698794996,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2748493.9759036144 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_median",
            "value": 2792512.248996024,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2729668.674698795 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_stddev",
            "value": 25928.101063610266,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 47583.30474428951 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_cv",
            "value": 0.009248780757770025,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.01731250101381273 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_mean",
            "value": 4985374.948096936,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4963235.294117648 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_median",
            "value": 4977772.3183391,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4974048.442906575 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_stddev",
            "value": 23625.66424499856,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 24178.935742712612 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_cv",
            "value": 0.004738994456980046,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.004871607794087281 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_mean",
            "value": 2697112.9791271146,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2686195.445920304 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_median",
            "value": 2685165.2751422194,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2698055.0284629976 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_stddev",
            "value": 25072.933652135678,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 53860.003927231635 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_cv",
            "value": 0.009296211855481934,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.02005066459666301 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_mean",
            "value": 187522185.71428332,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 187500000 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_median",
            "value": 187846171.4285647,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 187500000 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_stddev",
            "value": 1049214.474966273,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1578363.350863906 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_cv",
            "value": 0.005595148493868881,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.008417937871274164 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_mean",
            "value": 1819091.4591700514,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1798862.1151271756 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_median",
            "value": 1820390.2275770295,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1798862.1151271756 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_stddev",
            "value": 3978.7722720434444,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 14790.553488684527 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_cv",
            "value": 0.0021872304726551425,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.008222171874267789 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_mean",
            "value": 96046194.2857137,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 94866071.42857143 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_median",
            "value": 96018021.42857099,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 94866071.42857143 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_stddev",
            "value": 284849.5512500161,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 789181.675431953 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_cv",
            "value": 0.002965755732108022,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.008318903308082704 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_mean",
            "value": 566743419.9999888,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 560937500 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_median",
            "value": 565961149.9999641,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 562500000 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_stddev",
            "value": 2277714.0897155493,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6536406.457299801 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_cv",
            "value": 0.004018951097333594,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.01165264660911385 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_mean",
            "value": 13249550.178571418,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 13225446.42857143 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_median",
            "value": 13210761.607142884,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 13253348.214285715 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_stddev",
            "value": 63046.97383784784,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 116721.54388006925 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_cv",
            "value": 0.004758423719154943,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.008825527706037301 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_mean",
            "value": 286313332.0000088,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 285000000 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_median",
            "value": 286043660.0000185,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 284375000 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_stddev",
            "value": 626219.7896226074,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1397542.4859367332 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_cv",
            "value": 0.0021871834791912107,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.004903657845392046 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_mean",
            "value": 4940547.958477481,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4930795.847750866 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_median",
            "value": 4911858.823529624,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4919982.698961938 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_stddev",
            "value": 59181.536258665976,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 70493.10559260429 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_cv",
            "value": 0.011978739353620973,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.014296496502640447 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_mean",
            "value": 4756467.55852833,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4744983.277591974 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_median",
            "value": 4750870.234113602,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4755434.782608695 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_stddev",
            "value": 21204.40452567912,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 43721.78232304008 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_cv",
            "value": 0.004458015168769458,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.009214317472838051 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_mean",
            "value": 2958767.7966101393,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2952860.1694915253 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_median",
            "value": 2950169.703389951,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2946239.406779661 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_stddev",
            "value": 17063.790048450086,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 27696.63753093135 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_cv",
            "value": 0.005767194731536578,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.00937959671002662 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_mean",
            "value": 104884804.0000007,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 103750000.00000001 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_median",
            "value": 104955119.99999961,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 104687500 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_stddev",
            "value": 247969.33042783904,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2369648.5762656177 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_cv",
            "value": 0.0023642064528989096,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.022839986277258965 ns\nthreads: 1"
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
          "id": "5cfb757bdaa849c6fbaa3f70c58c15b6526a07c8",
          "message": "v0.9.7 (#56)\n\n* Wellner Binarization Algorithm - 1994\n\nAn optimized Wellner algorithm.  This is now the fastest local adaptive algorithm in Doxa.\n\nNOTE: While theoretically be the simplest adaptive algorithm, Niblack was still faster before adding the division / shift replacement.  That one change made all the difference.\n\n* Added Bradley and Feng\n\nFeng Note: I am adding Feng, but I made one improvement to it that seems to be working really well.  I am adding a `noise-floor` parameter that, when set, can let you greatly lower your window size without having black sections show up in large background patches!  This greatly increases the parameter range for getting good results.\n\n* Performance Boost\n\nBig wins for any algorithm using Chan (almost all of them).  They will see a 6 to 11% increase in performance simply by optimizing out the division.  This insight came from the Wellner algorithm and his paper.  Gatos got a 15+% jump thanks to звездочёт.\n\n* Update Feng\n\nThe interpolation mechanism for Feng needs to be setup just right.  The parameters before were too complex for normal use.  If you say you want a 9x9 window, I want to make sure it is truly a 9x9 window.\n\nI also updated the CMake system so that the Python src files would auto-copy on build.",
          "timestamp": "2026-05-16T00:22:09-05:00",
          "tree_id": "1e0e4ffa20ab4918bbc648b64d98e26620c4a83e",
          "url": "https://github.com/brandonmpetty/Doxa/commit/5cfb757bdaa849c6fbaa3f70c58c15b6526a07c8"
        },
        "date": 1778909201661,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_GlobalThreshold_Scalar_mean",
            "value": 8705.01052735005,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 8612.937284005182 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_median",
            "value": 8693.870197472552,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 8632.119772388265 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_stddev",
            "value": 22.15494462560137,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 80.24610619780594 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_cv",
            "value": 0.002545079590196166,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.009316926798808637 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_mean",
            "value": 13902.968178713807,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 13779.93290208526 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_median",
            "value": 13903.89830849063,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 13811.32227088272 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_stddev",
            "value": 61.27899880897704,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 131.31115065469052 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_cv",
            "value": 0.004407619870899115,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.009529157477596988 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_mean",
            "value": 437123.6374999513,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 434570.3125 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_median",
            "value": 436847.3750000135,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 434570.3125 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_stddev",
            "value": 1343.1140734204419,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3452.6698300147946 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_cv",
            "value": 0.0030726182667726166,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.007945020013337413 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_mean",
            "value": 78326.96205357235,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 77950.61383928571 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_median",
            "value": 78018.45424107208,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 77601.84151785713 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_stddev",
            "value": 574.3380778691297,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 477.5761696994603 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_cv",
            "value": 0.00733257186045728,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.006126650531374911 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_mean",
            "value": 84342.05370873996,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 83735.06447415121 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_median",
            "value": 84230.53945342344,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 84104.75570803267 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_stddev",
            "value": 390.085616688926,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 506.22057026983896 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_cv",
            "value": 0.004625042900141087,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.006045502842194716 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_mean",
            "value": 36933.50815631847,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 36663.27377923018 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_median",
            "value": 36931.926177916146,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 36830.68598826775 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_stddev",
            "value": 152.86899139677533,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 477.1982165153063 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_cv",
            "value": 0.004139032521626921,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.01301570119975593 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_mean",
            "value": 420907.56251883775,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 418989.1533594456 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_median",
            "value": 421154.4441096236,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 418989.1533594456 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_stddev",
            "value": 1536.975948613273,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4707.7432961740815 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_cv",
            "value": 0.003651575988360831,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.011235955056181053 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_mean",
            "value": 14321.45870535757,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 14229.910714285714 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_median",
            "value": 14318.44642856918,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 14299.66517857143 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_stddev",
            "value": 8.392478009676458,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 95.51523393971108 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_cv",
            "value": 0.0005860072065520033,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.006712286243920088 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_mean",
            "value": 1900801.2315931197,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1895080.321285141 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_median",
            "value": 1899655.0200803224,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1903447.121820616 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_stddev",
            "value": 4694.494571010608,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 11456.713468516595 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_cv",
            "value": 0.0024697451227322737,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.006045502842194716 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_mean",
            "value": 6956956.826923035,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6941105.76923077 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_median",
            "value": 6737533.173076844,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6685697.115384616 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_stddev",
            "value": 482363.6048384096,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 491449.13563089166 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_cv",
            "value": 0.0693354316892825,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0708027152978185 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_mean",
            "value": 176242.59791282195,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 176488.64333947207 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_median",
            "value": 175063.02025779858,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 174570.28852056473 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_stddev",
            "value": 2642.505467281176,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3322.688013291793 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_cv",
            "value": 0.014993568516212443,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.01882663921270376 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_mean",
            "value": 1857528.4337349008,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1857429.718875502 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_median",
            "value": 1857641.900936835,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1861613.1191432395 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_stddev",
            "value": 1843.1867063391612,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 9354.367375694706 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_cv",
            "value": 0.000992279134394243,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0050361891384821215 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_mean",
            "value": 2045650.3338171307,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2036465.8925979682 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_median",
            "value": 2047955.8780839802,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2041001.45137881 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_stddev",
            "value": 4632.481544642416,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 29568.22571298841 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_cv",
            "value": 0.0022645519950608203,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.014519381748774351 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_mean",
            "value": 3893746.3687151186,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3875698.3240223466 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_median",
            "value": 3890646.6480440744,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3884427.3743016757 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_stddev",
            "value": 4654.934893283669,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 36516.23719153005 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_cv",
            "value": 0.0011954900120573933,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.009421847145634417 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_mean",
            "value": 1928340.5354749747,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1928547.5234270417 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_median",
            "value": 1928992.3694776562,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1924364.1231593038 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_stddev",
            "value": 7113.9710683541325,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 17500.418895032108 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_cv",
            "value": 0.0036891674149254297,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.009074403758499947 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_mean",
            "value": 188303385.71428263,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 186607142.85714287 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_median",
            "value": 187801714.2857321,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 187500000 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_stddev",
            "value": 1232557.8916765384,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2545034.4310225914 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_cv",
            "value": 0.006545596017836498,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.013638462022704793 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_mean",
            "value": 1677458.5030674243,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1652607.3619631904 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_median",
            "value": 1661910.9202451212,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1667944.7852760737 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_stddev",
            "value": 26564.51513239264,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 39290.45539094747 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_cv",
            "value": 0.015836168277078923,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.02377482776324617 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_mean",
            "value": 95454778.66667473,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 95416666.66666667 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_median",
            "value": 95110780.00001968,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 95833333.33333333 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_stddev",
            "value": 633126.6979896737,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 570544.3307342886 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_cv",
            "value": 0.00663273967875965,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.005979503902892107 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_mean",
            "value": 565006186.6665967,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 564583333.3333334 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_median",
            "value": 565138933.3332493,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 562500000 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_stddev",
            "value": 1728234.9099938658,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2852721.653671443 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_cv",
            "value": 0.0030587893562547424,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.005052791120894068 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_mean",
            "value": 13108666.999999516,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 13031250.000000004 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_median",
            "value": 13041877.000000568,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12968750.000000002 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_stddev",
            "value": 193849.13787209333,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 261456.2582918328 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_cv",
            "value": 0.014787860418767255,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.020063789605128654 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_mean",
            "value": 312825799.999996,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 311718750.00000006 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_median",
            "value": 312787650.0000184,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 312500000 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_stddev",
            "value": 390741.0935315663,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1746928.107415951 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_cv",
            "value": 0.0012490692696432693,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.005604180394717838 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_mean",
            "value": 5257932.132352876,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5261948.529411765 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_median",
            "value": 5257727.941175757,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5284926.470588235 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_stddev",
            "value": 22939.83206804318,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 31463.841768435035 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_cv",
            "value": 0.004362899993876075,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.005979503902892107 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_mean",
            "value": 3826879.3565686466,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3828753.3512064344 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_median",
            "value": 3823180.4289545654,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3811997.319034852 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_stddev",
            "value": 9995.016779030391,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 22944.141986633593 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_cv",
            "value": 0.0026117930166453893,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.005992588156508939 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_mean",
            "value": 886229.8750000264,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 875000 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_median",
            "value": 882513.2500001587,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 869140.625 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_stddev",
            "value": 9711.570857753886,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 14810.303601656453 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_cv",
            "value": 0.010958297764170495,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.01692606125903594 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_mean",
            "value": 1203364.734375114,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1196289.0625 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_median",
            "value": 1202455.0781251974,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1196289.0625 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_stddev",
            "value": 5873.367771250418,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 14950.498918358891 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_cv",
            "value": 0.004880787680968857,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.01249739664685674 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_mean",
            "value": 964845.6399438285,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 955959.9156118144 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_median",
            "value": 962715.1195500873,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 955959.9156118144 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_stddev",
            "value": 3877.422228455689,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 7769.721136460857 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_cv",
            "value": 0.004018696947919488,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.008127664151575056 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_mean",
            "value": 2801894.2314990354,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2787001.897533207 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_median",
            "value": 2801674.1935484693,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2787001.897533207 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_stddev",
            "value": 2680.7381515505026,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_cv",
            "value": 0.0009567592243181453,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_mean",
            "value": 101640913.99999961,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 101562500 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_median",
            "value": 101614289.9999977,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 101562500 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_stddev",
            "value": 71490.74156516202,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_cv",
            "value": 0.0007033657879656838,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0 ns\nthreads: 1"
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
            "email": "brandonpetty1981@gmail.com",
            "name": "Brandon M. Petty",
            "username": "brandonmpetty"
          },
          "distinct": true,
          "id": "600ae1febc4546be6acf0738e11733b80530754b",
          "message": "CodeCov - Update\n\nUse token and their updated action.\nTarget just the Doxa folder.",
          "timestamp": "2026-05-16T12:50:34-05:00",
          "tree_id": "db93904152ca22043777f644f6cb9c92cd93a79d",
          "url": "https://github.com/brandonmpetty/Doxa/commit/600ae1febc4546be6acf0738e11733b80530754b"
        },
        "date": 1778954124843,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_GlobalThreshold_Scalar_mean",
            "value": 8689.430107397351,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 8682.334293600763 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_median",
            "value": 8664.551064932717,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 8663.50059665152 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_stddev",
            "value": 35.58463633729293,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 42.11342664611734 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_cv",
            "value": 0.0040951634223974675,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.004850472836222934 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_mean",
            "value": 13953.97786170613,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 13842.711639680181 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_median",
            "value": 13975.754349310771,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 13968.269114870021 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_stddev",
            "value": 100.179513876746,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 257.88998034326204 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_cv",
            "value": 0.007179279978053311,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.018630018962760123 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_mean",
            "value": 438615.4999999974,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 434570.3125 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_median",
            "value": 438641.5312499992,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 434570.3125 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_stddev",
            "value": 891.8366866947796,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3452.6698300147946 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_cv",
            "value": 0.002033299522462806,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.007945020013337413 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_mean",
            "value": 78019.27157388245,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 77244.88679864377 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_median",
            "value": 77935.85803347008,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 76903.0952641365 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_stddev",
            "value": 123.50809321178113,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 468.0173335346346 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_cv",
            "value": 0.0015830459669803735,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.0060588778485057195 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_mean",
            "value": 86337.4887500001,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 85742.18750000001 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_median",
            "value": 85556.51249999841,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 85937.5 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_stddev",
            "value": 1762.754034504977,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1878.4554747720267 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_cv",
            "value": 0.02041701768288894,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.02190818230258035 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_mean",
            "value": 37709.31561888975,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 37667.74703345566 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_median",
            "value": 37723.97342833444,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 37667.74703345566 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_stddev",
            "value": 194.6227048038707,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_cv",
            "value": 0.00516113065457964,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_mean",
            "value": 422276.6857487237,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 419930.7020186804 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_median",
            "value": 423044.3205785149,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 418989.1533594456 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_stddev",
            "value": 1276.241272252036,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3938.7806310935825 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_cv",
            "value": 0.003022286844913491,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.00937959671002662 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_mean",
            "value": 14589.521874999942,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 14578.683035714286 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_median",
            "value": 14481.803571428285,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 14474.051339285714 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_stddev",
            "value": 268.95062598547827,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 316.78819274169604 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_cv",
            "value": 0.01843450582478251,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.02172954799590887 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_mean",
            "value": 1926851.164658647,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1924364.1231593038 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_median",
            "value": 1932437.6171352633,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1924364.1231593038 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_stddev",
            "value": 13965.505157305384,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 14790.55348866771 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_cv",
            "value": 0.0072478380341220875,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.007685943273763325 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_mean",
            "value": 6554126.103286498,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6528755.8685446 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_median",
            "value": 6553264.319248916,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6528755.8685446 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_stddev",
            "value": 16376.129943285914,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 51871.09603778094 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_cv",
            "value": 0.002498598544674671,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.007945020013337413 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_mean",
            "value": 175613.06548814953,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 173680.86246149725 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_median",
            "value": 175647.59608946124,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 173680.86246149725 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_stddev",
            "value": 482.0032469790398,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1479.6495856498382 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_cv",
            "value": 0.002744688987913406,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.008519358809482288 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_mean",
            "value": 2004786.9611780543,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1936914.3239625166 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_median",
            "value": 1890254.2168674946,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1861613.1191432395 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_stddev",
            "value": 254998.10498229056,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 170957.30205574213 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_cv",
            "value": 0.12719461464995185,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.08826270730756931 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_mean",
            "value": 2042639.2162554562,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2036465.8925979682 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_median",
            "value": 2043219.8838896218,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2041001.45137881 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_stddev",
            "value": 4211.033622162705,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 10141.8177498749 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_cv",
            "value": 0.0020615650520419975,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.004980106854103379 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_mean",
            "value": 3911854.9720670707,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3858240.223463687 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_median",
            "value": 3907765.363128318,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3884427.3743016757 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_stddev",
            "value": 13078.281978366364,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 39037.49960717132 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_cv",
            "value": 0.0033432430577700185,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.010117954649315714 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_mean",
            "value": 1930097.2423025698,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1911813.922356091 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_median",
            "value": 1929662.9183401023,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1924364.1231593038 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_stddev",
            "value": 5884.339938368217,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 18708.73475149576 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_cv",
            "value": 0.003048727188143283,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.009785855481395067 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_mean",
            "value": 189496882.85714012,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 188839285.71428573 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_median",
            "value": 189084428.57142356,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 189732142.85714287 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_stddev",
            "value": 1568668.0999839716,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1222594.9944283017 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_cv",
            "value": 0.008278068094484569,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.006474261909029304 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_mean",
            "value": 1701130.62500002,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1681082.5892857146 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_median",
            "value": 1695930.5803571872,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1674107.1428571427 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_stddev",
            "value": 15279.979711998178,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 15597.572387686752 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_cv",
            "value": 0.008982249503619392,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.009278290363065447 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_mean",
            "value": 96077964.28571354,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 95982142.85714287 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_median",
            "value": 95883035.71428826,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 95982142.85714287 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_stddev",
            "value": 715312.3223775101,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 789181.675431953 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_cv",
            "value": 0.0074451236315783865,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.008222171874267789 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_mean",
            "value": 568021099.9999986,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 557812500 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_median",
            "value": 568405949.9999989,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 554687500 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_stddev",
            "value": 2267457.22529942,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 8907620.508582966 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_cv",
            "value": 0.0039918538682795855,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.015968843488776183 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_mean",
            "value": 12791821.785714319,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12723214.285714287 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_median",
            "value": 12776641.964285724,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12834821.42857143 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_stddev",
            "value": 32847.42064022548,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 181897.38853805928 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_cv",
            "value": 0.002567845392976698,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.014296496502640447 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_mean",
            "value": 365752680.0000028,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 341406250 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_median",
            "value": 321604825.0000085,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 320312500 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_stddev",
            "value": 65579819.605108276,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 34454807.9237496 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_cv",
            "value": 0.17930099542977446,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.10092026119542216 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_mean",
            "value": 5123590.294117766,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5101102.941176471 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_median",
            "value": 5112652.573529468,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5055147.05882353 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_stddev",
            "value": 38790.23548783445,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 62927.68353684027 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_cv",
            "value": 0.007570908925401063,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.012336093637492286 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_mean",
            "value": 3867294.5810056604,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3840782.122905027 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_median",
            "value": 3853103.6312851505,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3840782.122905027 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_stddev",
            "value": 52341.66321778901,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 69009.20173202644 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_cv",
            "value": 0.013534439159319992,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.017967486705502158 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_mean",
            "value": 899138.4478371848,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 890585.2417302799 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_median",
            "value": 889352.9262087541,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 894561.0687022901 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_stddev",
            "value": 20464.403887260298,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 11332.850519825657 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_cv",
            "value": 0.022760014251960864,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.01272517215511852 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_mean",
            "value": 1203005.6249999888,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1201171.875 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_median",
            "value": 1206017.2656250144,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1196289.0625 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_stddev",
            "value": 4969.123623946985,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6686.066375792444 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_cv",
            "value": 0.004130590514859007,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.005566286153505255 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_mean",
            "value": 961527.5949366812,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 960355.1336146273 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_median",
            "value": 961822.3628693314,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 966947.9606188465 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_stddev",
            "value": 895.2023534228589,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 9828.006230216126 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_cv",
            "value": 0.0009310209692752604,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.010233720720818183 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_mean",
            "value": 2847178.594377412,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2792419.6787148593 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_median",
            "value": 2833980.5220882287,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2792419.6787148593 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_stddev",
            "value": 61448.948329889194,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 38426.985171685505 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_cv",
            "value": 0.021582400363376622,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.013761178330246746 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_mean",
            "value": 102381473.84615542,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 102403846.15384617 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_median",
            "value": 102228900.00000007,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 102163461.53846154 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_stddev",
            "value": 469932.4494973415,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1005600.9934299221 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_cv",
            "value": 0.0045900145001183555,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.009819953363071537 ns\nthreads: 1"
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
          "id": "ea8007847865c649c7febe964cdbc077179d804f",
          "message": "v0.9.8 - Pseudo Weights, XDoG and BinBench (#57)\n\nThis is a HUGE release.  It is the first release that was driven by AI.\n\n- Utilities: BinBench - A Python script exposing all binarization and grayscale algorithms along with all performance metrics\n- Binarization: XDoG\n- Metrics: bit-exact Pseudo Weight generation!\n- Extras: Canny Edge Detection... for the future :)",
          "timestamp": "2026-07-04T11:26:47-05:00",
          "tree_id": "280b97c25f17cde3c2c5fb9327c68e4363f37353",
          "url": "https://github.com/brandonmpetty/Doxa/commit/ea8007847865c649c7febe964cdbc077179d804f"
        },
        "date": 1783182717501,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "BM_GlobalThreshold_Scalar_mean",
            "value": 172247.4990791892,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 169582.56599140578 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_median",
            "value": 167139.05463474724,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 164978.51442602824 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_stddev",
            "value": 8662.727365573235,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6304.3572456854 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_Scalar_cv",
            "value": 0.05029232593728763,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.037175739197181965 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_mean",
            "value": 10532.802499999994,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 10351.562500000002 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_median",
            "value": 10464.329687499996,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 10375.9765625 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_stddev",
            "value": 207.16583033496744,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 54.591503356748476 ns\nthreads: 1"
          },
          {
            "name": "BM_GlobalThreshold_SIMD_cv",
            "value": 0.01966863333238875,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.005273745229934946 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_mean",
            "value": 427888.54474239226,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 424638.4453148539 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_median",
            "value": 427517.86682735634,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 423696.89665561914 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_stddev",
            "value": 1074.9716259508891,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2105.3668061716376 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_Scalar_cv",
            "value": 0.0025122701674522956,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.004958022123057146 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_mean",
            "value": 81101.51006906187,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 80160.75677557889 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_median",
            "value": 81083.4136149961,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 80704.83431025477 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_stddev",
            "value": 274.4373480231967,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 811.0629017101347 ns\nthreads: 1"
          },
          {
            "name": "BM_CompareImages_SIMD_cv",
            "value": 0.003383874699614101,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.010117954649315714 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_mean",
            "value": 80842.79496256784,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 80886.19348848007 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_median",
            "value": 80718.0836863794,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 80704.83431025477 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_stddev",
            "value": 291.26605450629376,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 405.53145085506736 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_cv",
            "value": 0.0036028696761555177,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.005013605330714738 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_mean",
            "value": 39691.145089285616,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 39585.658482142855 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_median",
            "value": 39693.66908482105,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 39672.8515625 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_stddev",
            "value": 48.16977548538624,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 364.75482462580874 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_STD_8x8_cv",
            "value": 0.0012136151621987186,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.009214317472838051 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_mean",
            "value": 623658.1339285736,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 616629.4642857143 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_median",
            "value": 623762.0535714226,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 613839.2857142857 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_stddev",
            "value": 547.5035276779861,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3820.609357588443 ns\nthreads: 1"
          },
          {
            "name": "BM_SumDRDk_cv",
            "value": 0.0008778904625666129,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.006195956532849312 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_mean",
            "value": 14536.784523283364,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 14470.499015629397 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_median",
            "value": 14489.581742938657,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 14439.109646831934 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_stddev",
            "value": 78.09152734383085,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 131.31115065479716 ns\nthreads: 1"
          },
          {
            "name": "BM_NUBN_SIMD_8x8_cv",
            "value": 0.005371994557582713,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.009074403758499947 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_mean",
            "value": 1962165.4082998694,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1962014.7255689427 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_median",
            "value": 1964838.6880856839,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1966198.1258366802 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_stddev",
            "value": 16345.474702681493,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 17500.418895003688 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_Chan_cv",
            "value": 0.00833032456567672,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.008919616487551558 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_mean",
            "value": 6230891.913043468,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6195652.173913044 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_median",
            "value": 6133374.347826039,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6114130.434782608 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_stddev",
            "value": 230667.5295447167,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 188511.37127053592 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_IntegralImage_cv",
            "value": 0.03701998570410886,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.030426396766472463 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_mean",
            "value": 210910.3279164256,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 208575.15960533952 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_median",
            "value": 210684.4457341855,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 208575.15960533952 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_stddev",
            "value": 447.7431265541465,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1603.0968450427715 ns\nthreads: 1"
          },
          {
            "name": "BM_Otsu_cv",
            "value": 0.002122907545483345,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.007685943273763325 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_mean",
            "value": 1935967.684069608,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1928547.5234270417 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_median",
            "value": 1924386.4792503011,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1924364.1231593038 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_stddev",
            "value": 16983.54427365722,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 31024.926736513233 ns\nthreads: 1"
          },
          {
            "name": "BM_Niblack_cv",
            "value": 0.008772638310757348,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.016087198453570765 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_mean",
            "value": 2088003.3091436818,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2072750.3628447026 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_median",
            "value": 2087483.7445573066,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2063679.2452830188 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_stddev",
            "value": 2450.880994694146,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12421.139275782773 ns\nthreads: 1"
          },
          {
            "name": "BM_Sauvola_cv",
            "value": 0.0011737917195635504,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.005992588156508939 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_mean",
            "value": 4002389.720670386,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3997905.0279329615 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_median",
            "value": 3991406.703910587,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 4015363.12849162 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_stddev",
            "value": 19652.057369969414,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 49763.2430647093 ns\nthreads: 1"
          },
          {
            "name": "BM_Wolf_cv",
            "value": 0.0049100809120301665,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.01244732996832554 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_mean",
            "value": 2022854.7460087016,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2018323.657474601 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_median",
            "value": 2017905.0798258106,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2018323.657474601 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_stddev",
            "value": 10932.790194535524,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 16035.621852028073 ns\nthreads: 1"
          },
          {
            "name": "BM_Nick_cv",
            "value": 0.005404634324885181,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.007945020013337413 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_mean",
            "value": 183606622.8571424,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 181250000 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_median",
            "value": 183095200.00000086,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 180803571.42857143 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_stddev",
            "value": 1647570.7008627597,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3310802.896025055 ns\nthreads: 1"
          },
          {
            "name": "BM_Bernsen_cv",
            "value": 0.008973372938429756,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.018266498736689958 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_mean",
            "value": 1704095.165644188,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1690950.9202453985 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_median",
            "value": 1701913.987730058,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1687116.5644171778 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_stddev",
            "value": 3759.6696439404486,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 16040.261244894462 ns\nthreads: 1"
          },
          {
            "name": "BM_TRSingh_cv",
            "value": 0.0022062556832142676,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.009485941343919444 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_mean",
            "value": 92497558.6666657,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 92291666.66666667 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_median",
            "value": 91986486.66666333,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 91666666.66666666 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_stddev",
            "value": 1009684.795462581,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1579765.717510021 ns\nthreads: 1"
          },
          {
            "name": "BM_Wan_cv",
            "value": 0.010915799400730038,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.017117100325165016 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_mean",
            "value": 669583259.999996,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 662500000.0000001 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_median",
            "value": 668865100.000005,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 664062500 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_stddev",
            "value": 1659760.381545883,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6536406.457289184 ns\nthreads: 1"
          },
          {
            "name": "BM_Gatos_cv",
            "value": 0.002478796111996427,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.009866273897794995 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_mean",
            "value": 12581927.857142717,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12500000.000000004 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_median",
            "value": 12611140.178571695,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 12555803.571428573 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_stddev",
            "value": 168787.006766925,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 211575.76573794932 ns\nthreads: 1"
          },
          {
            "name": "BM_ISauvola_cv",
            "value": 0.013415035333484702,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.01692606125903594 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_mean",
            "value": 370261335.0000036,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 370312500.00000006 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_median",
            "value": 371066900.00000244,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 371093750 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_stddev",
            "value": 2490824.443989004,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1746928.107410986 ns\nthreads: 1"
          },
          {
            "name": "BM_Su_cv",
            "value": 0.006727206458079074,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.004717442990476924 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_mean",
            "value": 5197702.573529364,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5193014.705882354 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_median",
            "value": 5187452.20588227,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5170036.764705883 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_stddev",
            "value": 66148.69073835001,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 65497.2096219622 ns\nthreads: 1"
          },
          {
            "name": "BM_Bataineh_cv",
            "value": 0.012726524806407588,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.012612560012158386 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_mean",
            "value": 3894739.6648045047,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3875698.3240223466 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_median",
            "value": 3882308.9385474985,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 3884427.3743016757 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_stddev",
            "value": 21354.724853995453,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 36516.23719153005 ns\nthreads: 1"
          },
          {
            "name": "BM_Phansalkar_cv",
            "value": 0.005482965921181113,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.009421847145634417 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_mean",
            "value": 638964.1160714328,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 636160.7142857143 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_median",
            "value": 635095.8482142843,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 634765.625 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_stddev",
            "value": 7613.220514183025,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 5836.07719401294 ns\nthreads: 1"
          },
          {
            "name": "BM_Wellner_cv",
            "value": 0.01191494220519249,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.009173903799711568 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_mean",
            "value": 1095960.7656250014,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1093750.0000000002 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_median",
            "value": 1094528.9843749874,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1098632.8125 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_stddev",
            "value": 3083.5841171543566,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 6686.066375779776 ns\nthreads: 1"
          },
          {
            "name": "BM_Bradley_cv",
            "value": 0.0028135898782798655,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.006112974972141508 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_mean",
            "value": 961013.2456747427,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 955882.3529411765 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_median",
            "value": 960376.2629757697,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 962370.2422145329 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_stddev",
            "value": 2450.9077536212,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 9671.574297140021 ns\nthreads: 1"
          },
          {
            "name": "BM_Feng_cv",
            "value": 0.002550337120380041,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.010117954649315714 ns\nthreads: 1"
          },
          {
            "name": "BM_XDoG_mean",
            "value": 8373645.930232656,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 8303052.325581396 ns\nthreads: 1"
          },
          {
            "name": "BM_XDoG_median",
            "value": 8360383.139534889,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 8266715.116279068 ns\nthreads: 1"
          },
          {
            "name": "BM_XDoG_stddev",
            "value": 35078.746843079454,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 103576.98265794144 ns\nthreads: 1"
          },
          {
            "name": "BM_XDoG_cv",
            "value": 0.004189184392957109,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.01247456701420809 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_mean",
            "value": 2815234.2168674385,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2811244.979919679 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_median",
            "value": 2807716.6666666945,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 2792419.6787148593 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_stddev",
            "value": 15731.24024850535,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 28063.102127223694 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsu_cv",
            "value": 0.005587897502187148,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.009982446328112427 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_mean",
            "value": 97108881.33333355,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 97083333.33333334 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_median",
            "value": 97811966.66666952,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 97916666.66666666 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_stddev",
            "value": 1544703.8712937857,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1711632.9922035865 ns\nthreads: 1"
          },
          {
            "name": "BM_AdOtsuMS_cv",
            "value": 0.0159069268442242,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.017630554426131363 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Generate_mean",
            "value": 110568158.18181928,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 109659090.90909092 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Generate_median",
            "value": 110522209.0909127,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 109375000 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Generate_stddev",
            "value": 305025.74505629804,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 1188437.5376908728 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Generate_cv",
            "value": 0.00275871236413933,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.010837565110548892 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Recall_mean",
            "value": 22528709.56521724,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 22418478.260869566 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Recall_median",
            "value": 22524272.463768095,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 22644927.536231883 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Recall_stddev",
            "value": 108275.8616322625,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 320247.6364069873 ns\nthreads: 1"
          },
          {
            "name": "BM_PseudoWeights_Recall_cv",
            "value": 0.004806127990545579,
            "unit": "ns/iter",
            "extra": "iterations: 5\ncpu: 0.014284985478517736 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}