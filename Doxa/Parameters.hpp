// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP

#include <map>
#include <variant>
#include <string>
#include "Types.hpp"


namespace Doxa
{
	typedef std::variant<int, double> ParameterValue;
	typedef std::map<std::string, ParameterValue> ParameterMap;

	/// <summary>
	/// Parameters can be passed into any algorithm, much like a key value pair.
	/// The Key is the name of the parameter, while the Value can be any Integer or Double.
	/// 
	/// Note: All window values should be ODD.  We are currently not enforcing this.
	/// </summary>
	class Parameters
	{
	public:
		template<typename Type>
		const Type Get(const std::string& name, const Type& defaultValue) const
		{
			ParameterMap::const_iterator pos = parameterMap.find(name);
			if (pos == parameterMap.end()) 
			{
				return defaultValue;
			}
			else
			{
				return std::get<Type>(pos->second);
			}
		}

		void Set(const std::string& name, const ParameterValue& value)
		{
			parameterMap[name] = value;
		}

		/// <summary>
		/// CTOR
		/// Example: Parameters param({ {"window", 75}, {"k", 0.1 } });
		/// </summary>
		Parameters(const ParameterMap& parameterMap)
		{
			this->parameterMap = parameterMap;
		}
		
		/// <summary>
		/// A very naive JSON object parser.  Useful for WebAssembly.
		/// Example: Parameters params(R"({"window": 75, "k": -0.01})");
		/// </summary>
		/// <param name="json">A simple JSON object</param>
		static Parameters FromJson(const std::string& json)
		{
			Parameters params;

			std::size_t keyStart = json.find('"');
			while (keyStart != std::string::npos)
			{
				// Get Coordinates
				std::size_t keyStop = json.find('"', ++keyStart);
				std::size_t valueStart = json.find(':', keyStop);
				std::size_t valueStop = json.find_first_of(",}", ++valueStart);

				// Get Key / Value
				std::string key = json.substr(keyStart, keyStop - keyStart);
				std::string value = json.substr(valueStart, valueStop - valueStart);

				// Value Type: String
				if (value.find('"') != std::string::npos)
				{
					// Filtered Out: We do not currently support string parameters.
				}
				// Value Type: Double
				else if (value.find('.') != std::string::npos)
				{
					params.parameterMap[key] = std::stod(value);
				}
				// Value Type: Integer
				else
				{
					params.parameterMap[key] = std::stoi(value);
				}

				keyStart = json.find('"', ++keyStop);
			}

			return params;
		}

		Parameters() {}

	protected:
		ParameterMap parameterMap;
	};
}

#endif //PARAMETERS_HPP