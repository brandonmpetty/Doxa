#include <chrono>
#include <thread>
#include "CppUnitTest.h"
#include "../Algorithms.hpp"
#include "../ShafaitCalculator.hpp"
#include "../PNM.hpp"
#include "../Performance.hpp"
#include "../MetricUtils.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Binarization::UnitTests
{
	TEST_CLASS(MetricUtilsTests)
	{
		TEST_METHOD(MetricUtilsTimeTest)
		{
			double seconds = MetricUtils::Time([](){ 
				std::this_thread::sleep_for(std::chrono::seconds(1));
			});

			Assert::IsTrue(1.0 <= seconds && seconds < 1.1);
		}

		TEST_METHOD(MetricUtilsCalculateMeasureRankAccuracy)
		{
			MetricUtils::Scores scores;

			scores.push_back(MetricUtils::Score { "test", 0, 0, 1.0, 0, 0, 0, 0, 0 });
			scores.push_back(MetricUtils::Score { "test", 0, 0, 1.2, 0, 0, 0, 0, 0 });
			scores.push_back(MetricUtils::Score { "test", 0, 0, 0.99, 0, 0, 0, 0, 0 });

			MetricUtils::CalculateMeasureRank(scores, MetricUtils::rankAccuracy);

			Assert::AreEqual(1.2, scores[0].accuracy);
			Assert::AreEqual(1.0, scores[0].score);

			Assert::AreEqual(1.0, scores[1].accuracy);
			Assert::AreEqual(2.0, scores[1].score);

			Assert::AreEqual(0.99, scores[2].accuracy);
			Assert::AreEqual(3.0, scores[2].score);
		}

		TEST_METHOD(MetricUtilsCalculateMeasureRankFMeasure)
		{
			MetricUtils::Scores scores;

			scores.push_back(MetricUtils::Score{ "test", 0, 0, 0, 1.0, 0, 0, 0, 0 });
			scores.push_back(MetricUtils::Score{ "test", 0, 0, 0, 1.2, 0, 0, 0, 0 });
			scores.push_back(MetricUtils::Score{ "test", 0, 0, 0, 0.99, 0, 0, 0, 0 });

			MetricUtils::CalculateMeasureRank(scores, MetricUtils::rankFMeasure);

			Assert::AreEqual(1.2, scores[0].fmeasure);
			Assert::AreEqual(1.0, scores[0].score);

			Assert::AreEqual(1.0, scores[1].fmeasure);
			Assert::AreEqual(2.0, scores[1].score);

			Assert::AreEqual(0.99, scores[2].fmeasure);
			Assert::AreEqual(3.0, scores[2].score);
		}

		TEST_METHOD(MetricUtilsCalculateMeasureRankPSNR)
		{
			MetricUtils::Scores scores;

			scores.push_back(MetricUtils::Score{ "test", 0, 0, 0, 0, 1.0, 0, 0, 0 });
			scores.push_back(MetricUtils::Score{ "test", 0, 0, 0, 0, 1.2, 0, 0, 0 });
			scores.push_back(MetricUtils::Score{ "test", 0, 0, 0, 0, 0.99, 0, 0, 0 });

			MetricUtils::CalculateMeasureRank(scores, MetricUtils::rankPSNR);

			Assert::AreEqual(1.2, scores[0].psnr);
			Assert::AreEqual(1.0, scores[0].score);

			Assert::AreEqual(1.0, scores[1].psnr);
			Assert::AreEqual(2.0, scores[1].score);

			Assert::AreEqual(0.99, scores[2].psnr);
			Assert::AreEqual(3.0, scores[2].score);
		}

		TEST_METHOD(MetricUtilsCalculateMeasureRankDRDM)
		{
			MetricUtils::Scores scores;

			scores.push_back(MetricUtils::Score{ "test", 0, 0, 0, 0, 0, 1.0, 0, 0 });
			scores.push_back(MetricUtils::Score{ "test", 0, 0, 0, 0, 0, 1.2, 0, 0 });
			scores.push_back(MetricUtils::Score{ "test", 0, 0, 0, 0, 0, 0.99, 0, 0 });

			MetricUtils::CalculateMeasureRank(scores, MetricUtils::rankDRDM);

			Assert::AreEqual(0.99, scores[0].drdm);
			Assert::AreEqual(1.0, scores[0].score);

			Assert::AreEqual(1.0, scores[1].drdm);
			Assert::AreEqual(2.0, scores[1].score);

			Assert::AreEqual(1.2, scores[2].drdm);
			Assert::AreEqual(3.0, scores[2].score);
		}

		TEST_METHOD(MetricUtilsCalculateMeasureRankTime)
		{
			MetricUtils::Scores scores;

			scores.push_back(MetricUtils::Score{ "test", 0, 0, 0, 0, 0, 0, 1.0, 0 });
			scores.push_back(MetricUtils::Score{ "test", 0, 0, 0, 0, 0, 0, 1.2, 0 });
			scores.push_back(MetricUtils::Score{ "test", 0, 0, 0, 0, 0, 0, 0.99, 0 });

			MetricUtils::CalculateMeasureRank(scores, MetricUtils::rankTime);

			Assert::AreEqual(0.99, scores[0].time);
			Assert::AreEqual(1.0, scores[0].score);

			Assert::AreEqual(1.0, scores[1].time);
			Assert::AreEqual(2.0, scores[1].score);

			Assert::AreEqual(1.2, scores[2].time);
			Assert::AreEqual(3.0, scores[2].score);
		}

		TEST_METHOD(MetricUtilsCalculateTopRank)
		{
			MetricUtils::Scores scores;

			scores.push_back(MetricUtils::Score{ "2nd", 0, 0, 1.0, 2.0, 3.0, 3.0, 1.0, 1234.56 });
			scores.push_back(MetricUtils::Score{ "3rd", 0, 0, 2.0, 1.0, 1.0, 2.0, 3.0, 1234.56 });
			scores.push_back(MetricUtils::Score{ "1st", 0, 0, 3.0, 3.0, 2.0, 1.0, 2.0, 1234.56 });

			MetricUtils::CalculateTopRank(scores);

			Assert::AreEqual("1st", scores[0].ID.c_str());
			Assert::AreEqual((double)1 + 1 + 2 + 1, scores[0].score);

			Assert::AreEqual("2nd", scores[1].ID.c_str());
			Assert::AreEqual((double)3 + 2 + 1 + 3, scores[1].score);

			Assert::AreEqual("3rd", scores[2].ID.c_str());
			Assert::AreEqual((double)2 + 3 + 3 + 2, scores[2].score);
		}

		TEST_METHOD(MetricUtilsDeathBy1000PaperCuts)
		{
			Pixel8 dataGT[] = {
				Palette::White,  Palette::Black
			};
			Image groundTruthImage(1, 2, dataGT);

			Pixel8 dataExp[] = {
				Palette::White,  Palette::Black
			};
			Image experimentImage(1, 2, dataExp);

			int callCounter = 0;

			MetricUtils::Scores scores;
			MetricUtils::DeathBy1000PaperCuts(scores, groundTruthImage, experimentImage, 1, 3, 0.01, 0.03,
				[&](Image& binaryImage, const Image& inputImage, const int ws, const double k) {
				
				binaryImage.data[0] = groundTruthImage.data[0];
				binaryImage.data[1] = groundTruthImage.data[1];

				++callCounter;
			});

			Assert::AreEqual(9, callCounter);

			Assert::IsTrue(std::all_of(scores.begin(), scores.end(), [](auto& score) { return score.accuracy == 100; }));
		}
	};
}
