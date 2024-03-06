//#include <ApplicationFramework.h>

#include "ApplicationFramework/Application.h"
#include "ApplicationFramework/EntryPoint.hpp"

class ExampleLayer : public ApplicationFramework::Layer
{
public:
	virtual void OnUIRender() override
	{
		ImGui::Begin("Hello");
		static bool toggle = false;
		if (ImGui::Button("Button"))
			toggle = !toggle;
		if (toggle)
			ImGui::Text("Kaboom");
		else
			ImGui::Text("");
		ImGui::End();

		ImGui::ShowDemoWindow();
	}
};

ApplicationFramework::Application* ApplicationFramework::CreateApplication()
{
	ApplicationProperties properties = { "Accounting Craft", "", 1280, 720, WindowModes::Windowed, true, true };

	Application* application = new Application(properties);

	application->PushLayer<ExampleLayer>();

	application->SetMenubarCallback([application]()
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				application->Close();
			}
			ImGui::EndMenu();
		}
	});

	return application;
}