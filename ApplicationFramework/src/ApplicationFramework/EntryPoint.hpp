#pragma once

extern ApplicationFramework::Application* ApplicationFramework::CreateApplication();

int main()
{
	ApplicationFramework::Application* application = ApplicationFramework::CreateApplication();
	application->Run();
	delete application;

	return 0;
}

/*
#include <Windows.h>

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	return main(__argc, __argv);
}
*/