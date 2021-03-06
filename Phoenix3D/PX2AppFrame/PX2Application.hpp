// PX2Application.hpp

#ifndef PX2WINDOWAPPLICATION_HPP
#define PX2WINDOWAPPLICATION_HPP

#include "PX2ApplicationBase.hpp"

#if defined(_WIN32) || defined(WIN32)
#include <windows.h>
#include <ShellAPI.h>
#endif

namespace PX2
{

#define PX2_DECLARE_APPLICATION(classname) \
	\
	static bool RegisterInitTerm (); \
	static bool AppInitialize (); \
	static bool AppTerminate ();

#define PX2_REGISTER_APPLICATION(classname) \
	static bool gsAppInitializeRegistered_##classname = \
	classname::RegisterInitTerm ();

#define PX2_IMPLEMENT_APPLICATION(classname) \
	\
	bool classname::RegisterInitTerm () \
	{ \
		ApplicationBase::msAppInitlizeFun = &classname::AppInitialize; \
		ApplicationBase::msAppTernamateFun = &classname::AppTerminate; \
		ApplicationBase::msEntry = &Application::Entry; \
		return true; \
	} \
	\
	bool classname::AppInitialize () \
	{ \
		msApplication = new classname(); \
		return true; \
	} \
	\
	bool classname::AppTerminate () \
	{ \
		delete (msApplication); \
		msApplication = 0; \
		return true; \
	}
	//----------------------------------------------------------------------------

	class PX2_APPFRAME_ITEM Application : public ApplicationBase
	{
	public:
		Application ();
		virtual ~Application ();

		static int Entry (int numArguments, char** arguments);
		virtual int Main (int numArguments, char** arguments);
		virtual bool OnIdle ();

		virtual bool Initlize();
		virtual bool Ternamate();

		virtual void SetTitle(const std::string &title);

#if defined(_WIN32) || defined(WIN32)
		// ����
		HWND mhWnd;
#endif
	};

}

#endif