// Δoxa Binarization Framework
// License: CC0 2025, "Freely you have received; freely give." - Matt 10:8
#ifndef DIBCOUTILS_HPP
#define DIBCOUTILS_HPP

#include <fstream>
#include <iomanip>
#include <istream>
#include <limits>
#include <ostream>
#include <vector>


namespace Doxa
{
	class DIBCOUtils
	{
	public:

		/// <summary>
		/// Read DIBCO Weighted .dat files.
		/// </summary>
		/// <remarks>"Performance Evaluation Methodology for Historical Document Image Binarization", 2013.</remarks>
		static std::vector<double> ReadWeightsFile(const std::string& fileLocation, size_t allocatedSize = 0)
		{
			std::ifstream file;
			file.open(fileLocation.c_str(), std::ios::binary);

			const auto weights = DIBCOUtils::ReadWeights(file, allocatedSize);

			file.clear();
			file.close(); // Automatically closes, but done explicitly for posterity.

			return weights;
		}

		/// <summary>
		/// Read DIBCO Weighted content from either a file or string stream.
		/// </summary>
		static std::vector<double> ReadWeights(std::istream& stream, size_t allocatedSize = 0)
		{
			std::vector<double> values;
			values.reserve(allocatedSize);

			double value;
			while (stream >> value)
			{
				values.push_back(value);
			}

			return values;
		}

		/// <summary>
		/// Write weights to a stream in the DIBCO whitespace-separated format.
		/// The inverse of ReadWeights; full double precision keeps the round-trip lossless.
		/// </summary>
		static void WriteWeights(std::ostream& stream, const std::vector<double>& weights)
		{
			stream << std::setprecision(std::numeric_limits<double>::max_digits10);

			for (size_t i = 0; i < weights.size(); ++i)
			{
				if (i) stream << ' ';
				stream << weights[i];
			}
		}
	};
}


#endif //DIBCOUTILS_HPP
