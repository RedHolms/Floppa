#pragma once
#include "Base.h"

#include <string>

namespace Floppa {

   _FLOPPA_API std::wstring TransformStringFromUTF8ToWide(std::string str);
   _FLOPPA_API std::string TransformStringFromWideToUTF8(std::wstring str);

}