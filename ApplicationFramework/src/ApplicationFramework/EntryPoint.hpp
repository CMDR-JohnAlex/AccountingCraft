#pragma once

extern ApplicationFramework::Application* ApplicationFramework::CreateApplication(int argc, char** argv);

int main(int argc, char** argv)
{
	ApplicationFramework::Application* application = ApplicationFramework::CreateApplication(argc, argv);
	application->Run();
	delete application;

	return 0;
}

#ifdef APPLICATION_FRAMEWORK_PLATFORM_WINDOWS
/*
Other than our preprocessor definitions, most compilers define these depending on the platform:
	* _WIN32 = Windows32
	* _WIN64 = Windows64
	* __APPLE__ = MacOS
	* __linux__ = Linux
	* __ANDROID__ = Android

https://blog.kowalczyk.info/article/j/guide-to-predefined-macros-in-c-compilers-gcc-clang-msvc-etc..html
*/

#ifdef APPLICATION_FRAMEWORK_BUILD_DIST
#define nominmax
#include <Windows.h>
int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PSTR szCmdLine, _In_ int iCmdShow)
{
	main(__argc, __argv); // __argc, __argv, __wargv: https://docs.microsoft.com/en-us/cpp/c-runtime-library/argc-argv-wargv?view=msvc-170
	//MessageBox(NULL, TEXT("Body Text"), TEXT("Title"), 0);
	return 0;
}
#endif
#endif // Another option to hide window without WinMain but on Windows: https://stackoverflow.com/questions/18260508/c-how-do-i-hide-a-console-window-on-startup