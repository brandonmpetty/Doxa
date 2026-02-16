window.BENCHMARK_DATA = {
  "lastUpdate": 1771203853118,
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
      }
    ]
  }
}