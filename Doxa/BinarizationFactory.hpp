// Δoxa Binarization Framework
// License: CC0 2022, "Freely you have received; freely give." - Matt 10:8
#ifndef BINARIZATIONFACTORY_HPP
#define BINARIZATIONFACTORY_HPP

// Note: Only include this header if you are prepared to pull in 95%+ of the entirety of this library.
#include "Otsu.hpp"
#include "Bernsen.hpp"
#include "Niblack.hpp"
#include "Sauvola.hpp"
#include "ISauvola.hpp"
#include "Nick.hpp"
#include "TRSingh.hpp"
#include "Bataineh.hpp"
#include "Wan.hpp"
#include "Wolf.hpp"
#include "Su.hpp"
#include "Gatos.hpp"
#include "AdOtsu.hpp"


namespace Doxa
{
	enum Algorithms
	{
		OTSU = 0,
		BERNSEN = 1,
		NIBLACK = 2,
		SAUVOLA = 3,
		WOLF = 4,
		NICK = 5,
		SU = 6,
		TRSINGH = 7,
		BATAINEH = 8,
		ISAUVOLA = 9,
		WAN = 10,
		GATOS = 11,
		ADOTSU = 12
	};


	/// <summary>
	/// A factory class for creating instances of binarization algorithms.
	/// </summary>
	class BinarizationFactory
	{
	public:
		static IAlgorithm* Algorithm(const Algorithms algorithm)
		{
			IAlgorithm* algorithmPtr = nullptr;

			switch (algorithm)
			{
			case OTSU:
				algorithmPtr = new Otsu();
				break;
			case BERNSEN:
				algorithmPtr = new Bernsen();
				break;
			case NIBLACK:
				algorithmPtr = new Niblack();
				break;
			case SAUVOLA:
				algorithmPtr = new Sauvola();
				break;
			case NICK:
				algorithmPtr = new Nick();
				break;
			case WOLF:
				algorithmPtr = new Wolf();
				break;
			case SU:
				algorithmPtr = new Su();
				break;
			case TRSINGH:
				algorithmPtr = new TRSingh();
				break;
			case BATAINEH:
				algorithmPtr = new Bataineh();
				break;
			case ISAUVOLA:
				algorithmPtr = new ISauvola();
				break;
			case WAN:
				algorithmPtr = new Wan();
				break;
			case GATOS:
				algorithmPtr = new Gatos();
				break;
			case ADOTSU:
				algorithmPtr = new AdOtsuMS();
				break;
			}

			return algorithmPtr;
		}
	};
}


#endif // #BINARIZATIONFACTORY_HPP
