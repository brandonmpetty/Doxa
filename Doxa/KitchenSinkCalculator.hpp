// Δoxa Binarization Framework
// License: CC0 2017, "Freely you have received; freely give." - Matt 10:8
#ifndef KITCHENSINKCALCULATOR_HPP
#define KITCHENSINKCALCULATOR_HPP

#include "Types.hpp"
#include "MeanVarianceCalculator.hpp"
#include "MinMaxCalculator.hpp"


namespace Doxa
{
	/// <summary>
	/// The Kitchen Sink Calculator will allow you to perform any calculation available.
	/// While it offers the most options, it is also the most costly to initialize and use.
	/// </summary>
	class KitchenSinkCalculator : public MeanVarianceCalculator, public MinMaxCalculator
	{
	public:
		void Initialize(const Image& grayScaleImage)
		{
			MeanVarianceCalculator::Initialize(grayScaleImage);
			MinMaxCalculator::Initialize(grayScaleImage);
		}
	};
}


#endif //KITCHENSINKCALCULATOR_HPP
