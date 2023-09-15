#ifndef IMAGEFIXTURE_HPP
#define IMAGEFIXTURE_HPP

#include "pch.h"
#include "TestUtilities.hpp"


namespace Doxa::UnitTests
{
	class ImageFixture : public ::testing::Test
	{
	protected:
		void SetUp() override {
			projFolder = TestUtilities::ProjectFolder();

			// Load Color Image
			const std::string filePath = projFolder + "2JohnC1V3.ppm";
			image = PNM::Read(filePath, ParameterMap{ {"grayscale", PNM::GrayscaleConversion::Qt} });
		}

		Image image;
		std::string projFolder;
	};
}

#endif // IMAGEFIXTURE_HPP
