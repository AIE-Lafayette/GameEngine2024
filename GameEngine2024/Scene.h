#pragma once
#include "Entity.h"

namespace GameEngine
{
	class Scene
	{
	public:
		Scene() { m_entities = List<Entity*>(); }

		void start();
		void update(double deltaTime);
		void draw();
		void end();

		virtual void onStart() {}
		virtual void onUpdate(double deltaTime) {}
		virtual void onDraw() {}
		virtual void onEnd() {}

		void addEntity(Entity* entity);

		void removeEntity(Entity* entity);

	private:
		List<Entity*> m_entities;
	};

}