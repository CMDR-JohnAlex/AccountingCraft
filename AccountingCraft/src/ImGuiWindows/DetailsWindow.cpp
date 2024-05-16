#include "DetailsWindow.h"

#include <stbi/stb_image.h>

#include <iostream>

void DetailsWindow::OnAttach()
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

void DetailsWindow::OnDetach()
{
	glDeleteTextures(1, &texture);
}

void DetailsWindow::OnUIRender()
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
