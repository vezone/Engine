#pragma once

#include "Core.h"
#include "Window.h"
#include "Engine/LayerStack.h"
#include "Engine/Events/Event.h"
#include "Engine/Events/ApplicationEvent.h"

namespace Engine {
	
	class ENGINE_API Application
	{
	private:
		bool m_Running;
		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;

		bool OnWindowClosed(WindowClosedEvent& event);

	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	};

	Application* CreateApplication();

}