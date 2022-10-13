#pragma once
#include "Base.h"

#include <functional>
#include <string>

#include "Exceptions.h"
#include "WindowEvents.h"

namespace Floppa {

	using WindowEventHandler = std::function<void(WindowEvent&)>;

	union WindowSystemHandle {
		void* win32Handle;
	};

	class Window {
		friend _FLOPPA_ENGINE_CLASS;

	public:
		_FLOPPA_API static DynamicAllocated<Window> New(const char* title, int sx, int sy);

		virtual ~Window();

	public:
		virtual std::string GetTitle() = 0;
		virtual void SetTitle(const char* title) = 0;
		virtual bool IsVisible() = 0;
		virtual void SetVisibility(bool vis) = 0;
		virtual bool IsOpen() = 0;
		virtual int GetClosingCode() = 0;
		virtual WindowSystemHandle GetSystemHandle() = 0;

	private:
		virtual void Update() = 0;
		virtual void SetCoreEventHandler(WindowEventHandler const& handler) = 0;
	};

}

namespace Floppa {

	class WindowNotOpenException : BaseException {
	public:
		WindowNotOpenException(std::string calledMethod, const char* file, int line)
			: BaseException("Trying to call window method when window not open", calledMethod, file, line) {}
	};

}