#include "NewFileWindow.h"

#include <stbi/stb_image.h>

#include <iostream>

bool NewFileWindow::ShowWindow = false;

void NewFileWindow::OnAttach()
{
}

void NewFileWindow::OnDetach()
{
}

void NewFileWindow::OnUIRender()
{
	if (ShowWindow)
	{
		ImGui::Begin("New File", &ShowWindow, ImGuiWindowFlags_AlwaysAutoResize /*| ImGuiWindowFlags_NoBackground*/ /*| ImGuiWindowFlags_NoDecoration*/ | ImGuiWindowFlags_NoDocking /*| ImGuiWindowFlags_NoMove*/);

		// TODO: Make a new file with user's filename input, then populate it with default data

		ImGui::End();
	}
}