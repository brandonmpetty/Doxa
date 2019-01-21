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

		Parameters(const ParameterMap& parameterMap)
		{
			this->parameterMap = parameterMap;
		}

		Parameters() {}

	protected:
		ParameterMap parameterMap;
	};
}

#endif //PARAMETERS_HPP