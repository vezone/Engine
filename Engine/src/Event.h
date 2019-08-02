#pragma once

#include <string>
#include <functional>

#include "src/Engine-Core/Core.h"

namespace Engine
{
	enum class EventType
	{
		None = 0,
		/*Window events*/
		WindowCloseed, WindowFocused, WindowUnfocused, WindowResized, WindowMoved,
		/*App events*/
		AppTick, AppUpdate, AppRender, 
		/*Key events*/
		KeyPressed, KeyReleased,
		/*Mouse events*/
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput		 = BIT(1),
		EventCategoryKeyboard	 = BIT(2),
		EventCategoryMouse		 = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};


#define EVENT_CLASS_TYPE(event_type) static EventType GetStaticType() { return Event::##event_type; }\
									 virtual EventType GetEventType() const override { return GetStaticType(); }\
									 virtual const char* GetName() const override { return #event_type; }

#define EVENT_CLASS_CATEGORY(event_category) virtual int GetCategoryFlags() const override { return event_category; }

	class ENGINE_API Event
	{
	public:
		virtual EventType GetEventType() const = 0;
		/*Debug mode only*/
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		/*Debug mode only*/
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory eventCategory)
		{
			return GetCategoryFlags() & eventCategory;
		}

	protected:
		bool m_Handled = false;

	private:
		friend class EventDispatcher;

	};

	class EventDispatcher
	{
	private:
		template <typename T>
		using EventFn = std::function<bool(T&)>;
		Event& m_Event;
	public:
		EventDispatcher(Event& event)
			: m_Event(event) {}

		template <typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)& m_Event);
				return true;
			}
			return false;
		}
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

}