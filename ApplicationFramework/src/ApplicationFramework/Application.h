#pragma once

#include "Layer.h"

#include <imgui.h>

#include <string>
#include <functional>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace ApplicationFramework
{
	enum class WindowModes
	{
		Windowed,
		Boarderless,
		Fullscreen
	};

	// TODO: Reorganize and maybe refractor this?
	struct ApplicationProperties
	{
		std::string Name;
		std::string IconPath;
		uint32_t WindowWidth, WindowHeight;
		WindowModes WindowMode;
		bool Maximized;
		bool VSync;
	};

	class Application
	{
	public:
		Application(const ApplicationProperties& properties = { "Application Framework", "", 1280, 720, WindowModes::Windowed, true, true });
		virtual ~Application();

		void Run();
		void SetMenubarCallback(const std::function<void()>& menubarCallback) { m_MenubarCallback = menubarCallback; }
		void Close();

		template<typename T>
		void PushLayer()
		{
			static_assert(std::is_base_of<Layer, T>::value, "Pushed type is not subclass of Layer!");
			m_LayerStack.emplace_back(std::make_shared<T>())->OnAttach();
		}

		void PushLayer(const std::shared_ptr<Layer>& layer) { m_LayerStack.emplace_back(layer); layer->OnAttach(); }

		float GetTime();
		inline GLFWwindow* GetWindowHandle() const { return m_WindowHandle; }

		float GetTimeStep();
		float GetFrameTime();
		float GetLastFrameTime();

		static inline Application& Get() { return *s_Instance; }

	private:
		void Init();
		void Shutdown();

		void LoadIcon(const std::string& iconPath);

	private:
		ApplicationProperties m_Properties;
		GLFWwindow* m_WindowHandle = nullptr;
		GLFWimage Icon[1];
		bool m_Running = true;
		bool m_Minimized = false;

		float m_TimeStep = 0.0f;
		float m_FrameTime = 0.0f;
		float m_LastFrameTime = 0.0f;

		std::vector<std::shared_ptr<Layer>> m_LayerStack;
		std::function<void()> m_MenubarCallback;

		static Application* s_Instance;
	};

	Application* CreateApplication(int argc, char** argv);
}