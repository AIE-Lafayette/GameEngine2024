#pragma once
#include "List.h"

namespace GameEngine
{
	class Component;

	class Entity
	{
	public:
		Entity();

		void start();
		void update(double deltaTime);
		void draw();
		void end();

		virtual void onStart() {}
		virtual void onUpdate(double deltaTime) {}
		virtual void onDraw() {}
		virtual void onEnd() {}
		virtual void onEnable() {}
		virtual void onDisable() {}

		/// <summary>
		/// Returns nullptr if the variable can't be cast as the type. 
		/// Otherwise, returns a pointer to the variable of the desired cast type.
		/// dynamic_cast<type*>(pointer name)
		/// </summary>
		
		/// <summary>
		/// for (type variableName : listName)
		/// {
		/// 
		/// }
		/// </summary>
		/// <param name="component"></param>

		void addComponent(Component* component);

		template<typename T>
		T* addComponent();

		template<typename T>
		T* getComponent();

		bool getStarted() { return m_started; }

		bool getEnabled() { return m_enabled; }
		void setEnabled(bool value) { m_enabled = value; }

	private:
		bool m_enabled;
		bool m_started;
		List<Component*> m_components;
	};
}