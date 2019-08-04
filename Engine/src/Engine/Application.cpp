#include "engine_pch.h"

#include "Application.h"

#include <Glad/glad.h>

namespace Engine {

#define BIND_EVENT_FUNCTION(x) std::bind(&x, this, std::placeholders::_1)

	Application::Application()
	{
		m_Running = true;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FUNCTION(Application::OnEvent));
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher eventDispatcher(event);
		eventDispatcher.Dispatch<WindowClosedEvent>(BIND_EVENT_FUNCTION(Application::OnWindowClosed));
		
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(event);
			if (event.Handled)
			{
				break;
			}
		}

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	bool Application::OnWindowClosed(WindowClosedEvent& event)
	{
		m_Running = false;
		return true;
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
			
			m_Window->OnUpdate();
		}
	}
}