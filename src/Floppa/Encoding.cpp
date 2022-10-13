#include <Floppa/Encoding.h>

#include <codecvt>

namespace Floppa {

   std::wstring TransformStringFromUTF8ToWide(std::string str) {
      std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> convert;
      return convert.from_bytes(str);
   }

   std::string TransformStringFromWideToUTF8(std::wstring str) {
      std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> convert;
      return convert.to_bytes(str);
   }

}