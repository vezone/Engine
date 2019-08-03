#include "engine_pch.h"

#include "Application.h"
#include "Engine-Core/Events/ApplicationEvent.h"

#include <GLFW/glfw3.h>

namespace Engine {

	Application::Application()
	{
		m_Running = true;
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}