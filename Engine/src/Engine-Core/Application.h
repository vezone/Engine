#pragma once

#include "Core.h"
#include "Events\Event.h"
#include "Window.h"

namespace Engine {
	
	class ENGINE_API Application
	{
	private:
		bool m_Running;
		std::unique_ptr<Window> m_Window;
	public:
		Application();
		virtual ~Application();

		void Run();

	};

	Application* CreateApplication();

}