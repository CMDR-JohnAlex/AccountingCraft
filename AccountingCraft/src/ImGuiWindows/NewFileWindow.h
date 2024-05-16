#pragma once

#include "ApplicationFramework/Application.h"

class NewFileWindow : public ApplicationFramework::Layer
{
public:
	static bool ShowWindow;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUIRender() override;
};