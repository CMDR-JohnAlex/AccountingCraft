//#include <ApplicationFramework.h>

#include "ApplicationFramework/Application.h"
#include "ApplicationFramework/EntryPoint.hpp"

#include <stbi/stb_image.h>

#include <iostream>
#include <filesystem>
#include <fstream>

class ListWindow : public ApplicationFramework::Layer
{
public:
	unsigned int texture;
	int width, height, nrChannels;

	virtual void OnAttach() override
	{
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load and generate the texture
		unsigned char* data = stbi_load("16x9.png", &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, width, height, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
	}

	virtual void OnDetach() override
	{
		glDeleteTextures(1, &texture);
	}

	virtual void OnUIRender() override
	{
		ImGui::Begin("ListWindow", (bool*)0, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar); // Note: These flags are not working?

		/*
			Useful Note: We are calculating the width of the ImGui window, so we
			can resize the image's width to the window width, then we are
			calculating the resized image's height.
		*/
		ImVec2 avail_size = ImGui::GetContentRegionAvail();
		ImGui::Image(
			(ImTextureID)((unsigned long)texture),
			ImVec2(avail_size.x, avail_size.x / ((float)width / (float)height))); // height = width / ratio

		ImGui::SetNextItemAllowOverlap();

		// https://stackoverflow.com/questions/64653747/how-to-center-align-text-horizontally
		ImVec2 textSize = ImGui::CalcTextSize(std::string("USERNAME HERE").c_str());

		ImVec2 originalPosition = ImGui::GetCursorPos();
		ImGui::SetCursorPosX((avail_size.x - textSize.x) / 2.0f);
		ImGui::SetCursorPosY(avail_size.x / ((float)width / (float)height) / 2.0f + ImGui::GetTextLineHeightWithSpacing()/*textSize.y*/);
		ImGui::Text("USERNAME HERE");
		ImGui::SetCursorPos(originalPosition);

		ImGui::Separator();

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(1, 0));
		ImVec2 size = ImVec2(32.0f, 32.0f);                         // Size of the image we want to make visible
		ImVec2 uv0 = ImVec2(0.0f, 0.0f);                            // UV coordinates for lower-left
		ImVec2 uv1 = ImVec2(1, 1);    // UV coordinates for (1,1) in our texture
		ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);             // Black background
		ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);           // No tint
		if (ImGui::ImageButton("##Button1", (ImTextureID)((unsigned long)texture), size, uv0, uv1, bg_col, tint_col))
			;

		ImGui::SameLine();

		const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK", "LLLLLLL", "MMMM", "OOOOOOO", "PPPP", "QQQQQQQQQQ", "RRR", "SSSS" };
		static const char* current_item = NULL;

		if (ImGui::BeginCombo("##combo", NULL, ImGuiComboFlags_NoPreview)) // The second parameter is the label previewed before opening the combo.
		{
			for (int n = 0; n < IM_ARRAYSIZE(items); n++)
			{
				bool is_selected = (current_item == items[n]); // You can store your selection however you want, outside or inside your objects
				if (ImGui::Selectable(items[n], is_selected))
					current_item = items[n];
				if (is_selected)
					ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
			}
			ImGui::EndCombo();
		}
		ImGui::PopStyleVar();

		ImGui::Separator();

		if (ImGui::BeginTable("table1", 5, ImGuiTableFlags_Borders | ImGuiTableFlags_ScrollY, ImVec2(0.0f, ImGui::GetContentRegionAvail().y)))
		{
			ImGui::TableSetupColumn("Zero", ImGuiTableColumnFlags_WidthStretch, 25.0f);
			ImGui::TableSetupColumn("One", ImGuiTableColumnFlags_WidthStretch, 25.0f);
			ImGui::TableSetupColumn("Two", ImGuiTableColumnFlags_WidthStretch, 200.0f);
			ImGui::TableSetupColumn("Three", ImGuiTableColumnFlags_WidthStretch, 100.0f);
			ImGui::TableSetupColumn("Four", ImGuiTableColumnFlags_WidthStretch, 25.0f);
			ImGui::TableHeadersRow();
			for (int row = 0; row < 30; row++)
			{
				ImGui::TableNextRow();
				for (int column = 0; column < 5; column++)
				{
					ImGui::TableSetColumnIndex(column);
					if (column == 0)
					{
						ImVec2 size = ImVec2(32.0f, 8.0f);                         // Size of the image we want to make visible
						ImVec2 uv0 = ImVec2(0.0f, 0.0f);                            // UV coordinates for lower-left
						ImVec2 uv1 = ImVec2(1, 1);    // UV coordinates for (1,1) in our texture
						ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);             // Black background
						ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);           // No tint
						if (ImGui::ImageButton("##Button1", (ImTextureID)((unsigned long)texture), size, uv0, uv1, bg_col, tint_col))
							;
						if (ImGui::ImageButton("##Button2", (ImTextureID)((unsigned long)texture), size, uv0, uv1, bg_col, tint_col))
							;
					}
					else if (column == 1)
					{
						ImGui::Image(
							(ImTextureID)((unsigned long)texture),
							size);
					}
					else if (column == 2 && row < IM_ARRAYSIZE(items))
					{
						ImGui::Text("%s", items[row]);
					}
					else if (column == 4)
					{
						ImVec2 size = ImVec2(32.0f, 32.0f);                         // Size of the image we want to make visible
						ImVec2 uv0 = ImVec2(0.0f, 0.0f);                            // UV coordinates for lower-left
						ImVec2 uv1 = ImVec2(1, 1);    // UV coordinates for (1,1) in our texture
						ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);             // Black background
						ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);           // No tint
						if (ImGui::ImageButton("##Button1", (ImTextureID)((unsigned long)texture), size, uv0, uv1, bg_col, tint_col))
							;
					}
					else
						ImGui::Text("Row %d Column %d", row, column);
				}
			}
			ImGui::EndTable();
		}

		ImGui::End();
	}
};

class DetailsWindow : public ApplicationFramework::Layer
{
public:
	unsigned int texture;
	int width, height, nrChannels;

	virtual void OnAttach() override
	{
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load and generate the texture
		unsigned char* data = stbi_load("16x9.png", &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, width, height, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
	}

	virtual void OnDetach() override
	{
		glDeleteTextures(1, &texture);
	}

	virtual void OnUIRender() override
	{
		ImGui::Begin("DetailsWindow");

		if (ImGui::BeginTable("table_nested1", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable))
		{
			//ImGui::TableSetupColumn("A0");
			//ImGui::TableSetupColumn("A1");
			//ImGui::TableHeadersRow();

			ImGui::TableNextColumn();

			ImVec2 avail_size = ImGui::GetContentRegionAvail();
			ImGui::Image(
				(ImTextureID)((unsigned long)texture),
				ImVec2(avail_size.x, avail_size.x));

			ImGui::TableNextColumn();
			{
				if (ImGui::BeginTable("table_nested2", 1, ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable))
				{
					//ImGui::TableSetupColumn("##");
					//ImGui::TableSetupColumn("##");
					//ImGui::TableHeadersRow();

					//ImVec2 avail_size = ImGui::GetContentRegionAvail();
					ImGui::TableNextRow(ImGuiTableRowFlags_None, avail_size.x - ImGui::GetTextLineHeight() * 8); // ImGui::GetTextLineHeight() * 8 is the size below...
					ImGui::TableNextColumn();

					// https://stackoverflow.com/questions/64653747/how-to-center-align-text-horizontally
					ImVec2 textSize = ImGui::CalcTextSize(std::string("Group Name Here").c_str());
					ImVec2 originalPosition = ImGui::GetCursorPos();
					ImGui::SetCursorPosY((avail_size.x / 2.0f) + (ImGui::GetTextLineHeightWithSpacing() * 1.25f/*textSize.y*/) - (ImGui::GetTextLineHeight() * 8.0f / 2.0f));
					ImVec2 avail_size = ImGui::GetContentRegionAvail();
					ImGui::SetCursorPosX((avail_size.x - textSize.x) / 2.0f + originalPosition.x);
					ImGui::Text("Group Name Here");
					ImGui::SetCursorPos(originalPosition);

					ImGui::TableNextRow();
					ImGui::TableNextColumn();
					{
						// Note: we are using a fixed-sized buffer for simplicity here. See ImGuiInputTextFlags_CallbackResize
						// and the code in misc/cpp/imgui_stdlib.h for how to setup InputText() for dynamically resizing strings.
						static char text[1024 * 8] =
							"/*\n"
							" The Pentium F00F bug, shorthand for F0 0F C7 C8,\n"
							" the hexadecimal encoding of one offending instruction,\n"
							" more formally, the invalid operand with locked CMPXCHG8B\n"
							" instruction bug, is a design flaw in the majority of\n"
							" Intel Pentium, Pentium MMX, and Pentium OverDrive\n"
							" processors (all in the P5 microarchitecture).\n"
							"*/\n\n"
							"label:\n"
							"\tlock cmpxchg8b eax\n";

						// Perhaps the user can toggle a flag in the settings to enable/disable read-only mode? (ImGuiInputTextFlags_ReadOnly)
						ImGui::InputTextMultiline("##source", text, IM_ARRAYSIZE(text), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 8), ImGuiInputTextFlags_AllowTabInput /*| ImGuiInputTextFlags_ReadOnly | ImGuiInputTextFlags_CtrlEnterForNewLine*/); // https://github.com/ocornut/imgui/issues/3237#issuecomment-1966083395
					}

					ImGui::EndTable();
				}
			}
			ImGui::EndTable();
		}

		if (ImGui::BeginTable("table1", 3, ImGuiTableFlags_Borders/*, ImVec2(0.0f, ImGui::GetContentRegionAvail().y)*/))
		{
			ImVec2 size = ImVec2(32.0f, 32.0f);
			ImGui::TableSetupColumn("##", ImGuiTableColumnFlags_WidthStretch, 25.0f);
			ImGui::TableSetupColumn("##", ImGuiTableColumnFlags_WidthStretch, 100.0f);
			ImGui::TableSetupColumn("##", ImGuiTableColumnFlags_WidthStretch, 200.0f);
			ImGui::TableHeadersRow();
			for (int row = 0; row < 3; row++)
			{
				ImGui::TableNextRow();
				for (int column = 0; column < 3; column++)
				{
					ImGui::TableSetColumnIndex(column);
					if (column == 0)
					{
						ImGui::Image(
							(ImTextureID)((unsigned long)texture),
							size);
					}
					else if (column == 1)
					{
						ImGui::Text("AAAAAAA");
					}
					else if (column == 2)
					{
						ImVec2 size = ImVec2(32.0f, 32.0f);                         // Size of the image we want to make visible
						ImVec2 uv0 = ImVec2(0.0f, 0.0f);                            // UV coordinates for lower-left
						ImVec2 uv1 = ImVec2(1, 1);    // UV coordinates for (1,1) in our texture
						ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);             // Black background
						ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);           // No tint
						if (ImGui::ImageButton("##Button1", (ImTextureID)((unsigned long)texture), size, uv0, uv1, bg_col, tint_col))
							;
						ImGui::SameLine();
						if (ImGui::ImageButton("##Button2", (ImTextureID)((unsigned long)texture), size, uv0, uv1, bg_col, tint_col))
							;
						ImGui::SameLine();
						if (ImGui::ImageButton("##Button3", (ImTextureID)((unsigned long)texture), size, uv0, uv1, bg_col, tint_col))
							;
						ImGui::SameLine();
						ImGui::PushItemWidth(32.0f);
						static char buf1[4] = "00"; ImGui::InputText("##", buf1, 4, ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_ReadOnly);
						ImGui::PopItemWidth();
						ImGui::SameLine();
						if (ImGui::ImageButton("##Button4", (ImTextureID)((unsigned long)texture), size, uv0, uv1, bg_col, tint_col))
							;
						ImGui::SameLine();
						if (ImGui::ImageButton("##Button5", (ImTextureID)((unsigned long)texture), size, uv0, uv1, bg_col, tint_col))
							;
						ImGui::SameLine();
						if (ImGui::ImageButton("##Button6", (ImTextureID)((unsigned long)texture), size, uv0, uv1, bg_col, tint_col))
							;
					}
				}
			}
			ImGui::EndTable();
		}

		{
			// Note: we are using a fixed-sized buffer for simplicity here. See ImGuiInputTextFlags_CallbackResize
			// and the code in misc/cpp/imgui_stdlib.h for how to setup InputText() for dynamically resizing strings.
			static char text[1024 * 8] =
				"/*\n"
				" The Pentium F00F bug, shorthand for F0 0F C7 C8,\n"
				" the hexadecimal encoding of one offending instruction,\n"
				" more formally, the invalid operand with locked CMPXCHG8B\n"
				" instruction bug, is a design flaw in the majority of\n"
				" Intel Pentium, Pentium MMX, and Pentium OverDrive\n"
				" processors (all in the P5 microarchitecture).\n"
				"*/\n\n"
				"label:\n"
				"\tlock cmpxchg8b eax\n";

			// Perhaps the user can toggle a flag in the settings to enable/disable read-only mode? (ImGuiInputTextFlags_ReadOnly)
			ImGui::InputTextMultiline("##source1", text, IM_ARRAYSIZE(text), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 16.0f), ImGuiInputTextFlags_AllowTabInput /*| ImGuiInputTextFlags_ReadOnly | ImGuiInputTextFlags_CtrlEnterForNewLine*/); // https://github.com/ocornut/imgui/issues/3237#issuecomment-1966083395
		}

		ImGui::End();
	}
};

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
		ShowWindow = false;
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