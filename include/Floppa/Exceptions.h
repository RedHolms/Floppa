#pragma once

#include <exception>
#include <string>

namespace Floppa {
      
   class BaseException : public std::exception {
   public:
      BaseException(std::string information, std::string throwedFunc, const char* throwedFile, int throwedLine)
         : m_info(information), m_thrwFunc(throwedFunc), m_thrwFile(throwedFile), m_thrwLine(throwedLine),
         std::exception(information.c_str()) {}

      std::string GetInformation() { return m_info; }
      std::string GetThrowedFunction() { return m_thrwFunc; }
      const char* GetThrowedFile() { return m_thrwFile; }
      int GetThrowedLine() { return m_thrwLine; }

   private:
      std::string m_info;
      std::string m_thrwFunc;
      const char* m_thrwFile;
      int m_thrwLine;
   };

   // Engine.h
   class NoAvailableWindowImplimentationException;
   class NoAvailableRendererImplimentationException;

   // Window.h
   class WindowNotOpenException;

   // Renderer.h
   class RendererException;
   class ShaderCompilingException;
   class ShaderProgramLinkingException;

}