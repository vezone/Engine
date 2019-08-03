#include "engine_pch.h"

#include "Application.h"
#include "Engine-Core/Events/ApplicationEvent.h"
#include "Engine-Core/Log.h"

namespace Engine {

	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizedEvent event(1280, 720);
		if (event.IsInCategory(EventCategoryApplication))
		ENGINE_TRACE(event.ToString());

		while (true) /*doing nothing*/ ;
	}
}