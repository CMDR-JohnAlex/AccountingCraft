//#include <ApplicationFramework.h>

#include "ApplicationFramework/Application.h"
#include "ApplicationFramework/EntryPoint.hpp"

#include "ImGuiWindows/ListWindow.h"
#include "ImGuiWindows/DetailsWindow.h"
#include "ImGuiWindows/NewFileWindow.h"

#include <iostream>
#include <filesystem>
#include <fstream>

class ImGuiDemoWindow : public ApplicationFramework::Layer
{
public:
	virtual void OnUIRender() override
	{
		ImGui::ShowDemoWindow();
	}
};

class AboutWindow : public ApplicationFramework::Layer
{
public:
	static bool ShowWindow;

	virtual void OnAttach() override
	{
	}

	virtual void OnDetach() override
	{
	}

	virtual void OnUIRender() override
	{
		if (ShowWindow)
		{
			ImGui::Begin("AboutWindow", (bool*)true, ImGuiWindowFlags_AlwaysAutoResize /*| ImGuiWindowFlags_NoBackground*/ | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking /*| ImGuiWindowFlags_NoMove*/);
			ImGui::Text("Version: %s", std::string("Current Version").c_str());
			ApplicationFramework::Application::Get().GetTimeStep();
			ImGui::Text("Frame Time: %.2fms\n", ApplicationFramework::Application::Get().GetFrameTime() * 1000.0f);
			ImGui::Text("FPS: %.2f\n", 1000 / (ApplicationFramework::Application::Get().GetFrameTime() * 1000.0f));
			ImGui::End();
		}
	}
};
bool AboutWindow::ShowWindow = false;

class TestWindow : public ApplicationFramework::Layer
{
	virtual void OnAttach() override
	{
		std::string path = "test/";
		for (const auto& entry : std::filesystem::directory_iterator(path))
			std::cout << entry.path() << std::endl;

		std::cout << std::endl;

		for (const auto& entry : std::filesystem::directory_iterator(path))
			std::cout << entry.path().filename() << std::endl;

		std::cout << std::endl;

		for (const auto& entry : std::filesystem::directory_iterator(path))
			std::cout << entry.path().filename().string() << std::endl;

		std::cout << std::endl;

		for (const auto& entry : std::filesystem::directory_iterator(path))
			std::cout << entry.path().filename().string().substr(0, entry.path().filename().string().find_last_of('.')) << std::endl;
	}
};

ApplicationFramework::Application* ApplicationFramework::CreateApplication(int argc, char** argv)
{
	ApplicationProperties properties = { "Accounting Craft", "", 1280, 720, WindowModes::Windowed, true, true };

	Application* application = new Application(properties);

	application->PushLayer<ListWindow>();
	application->PushLayer<DetailsWindow>();

	application->PushLayer<AboutWindow>();
	application->PushLayer<NewFileWindow>();

#ifdef ACCOUNTING_CRAFT_BUILD_DEBUG
	application->PushLayer<ImGuiDemoWindow>();
#endif

	application->PushLayer<TestWindow>();

	std::vector<std::string> files;
	for (const auto& entry : std::filesystem::directory_iterator("test/"))
	{
		files.push_back(entry.path().filename().string().substr(0, entry.path().filename().string().find_last_of('.')));
	}

	application->SetMenubarCallback([application, files]()
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New"))
			{
				NewFileWindow::ShowWindow = true;
			}
			if (ImGui::BeginMenu("Data"))
			{
				for (const auto& file : files)
				{
					if (ImGui::MenuItem(file.c_str(), nullptr, true))
					{
						// Unload current data
						// Load new data
						std::fstream fileStream("test/" + file + ".txt", std::ios::in);
					}
				}
				ImGui::EndMenu();
			}
			if (ImGui::MenuItem("Exit"))
			{
				application->Close();
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Nothing"))
			{
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Settings"))
		{
			if (ImGui::MenuItem("Nothing"))
			{
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help/About"))
		{
			if (ImGui::MenuItem("Help"))
			{
			}
			if (ImGui::MenuItem("About"))
			{
				AboutWindow::ShowWindow = !AboutWindow::ShowWindow;
			}
			if (ImGui::MenuItem("..."))
			{
			}
			ImGui::EndMenu();
		}
	});

	return application;
}