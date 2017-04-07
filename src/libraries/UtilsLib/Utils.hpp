#ifndef __RD_UTILS_HPP__
#define __RD_UTILS_HPP__

#include <string>
#include <sstream>

//-- Include all utils
#include "Vocabs.hpp"
#include "Macros.hpp"
#include "Vector2dBase.hpp"
#include "IniReader.hpp"

//-- Misc utils ----------------------------------------------//

//! @ingroup UtilsLib
template<typename T> std::string number2str(T number)
{
    std::stringstream sstream;
    sstream << number;
    return sstream.str();
}

#endif
