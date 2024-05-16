#pragma once

#include "ApplicationFramework/Application.h"

class ListWindow : public ApplicationFramework::Layer
{
public:
	unsigned int texture;
	int width, height, nrChannels;

	virtual void OnAttach() override;

	virtual void OnDetach() override;

	virtual void OnUIRender() override;
};