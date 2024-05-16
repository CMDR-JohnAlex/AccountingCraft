#include "ListWindow.h"

#include <stbi/stb_image.h>

#include <iostream>

void ListWindow::OnAttach()
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

void ListWindow::OnDetach()
{
	glDeleteTextures(1, &texture);
}

void ListWindow::OnUIRender()
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