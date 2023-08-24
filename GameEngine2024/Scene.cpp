#include "Scene.h"

void GameEngine::Scene::start()
{
	for (Entity* entity : m_entities)
	{
		if (entity->getEnabled())
			entity->start();
	}

	onStart();
}

void GameEngine::Scene::update(double deltaTime)
{
	for (Entity* entity : m_entities)
	{
		if (!entity->getEnabled())
			continue;

		if (!entity->getStarted())
			entity->start();

		entity->update(deltaTime);
	}

	onUpdate(deltaTime);
}

void GameEngine::Scene::draw()
{
	for (Entity* entity : m_entities)
	{
		if (entity->getEnabled())
			entity->draw();
	}

	onDraw();
}

void GameEngine::Scene::end()
{
	for (Entity* entity : m_entities)
	{
		if (entity->getEnabled())
			entity->end();
	}

	onEnd();
}

void GameEngine::Scene::addEntity(Entity* entity)
{
	m_entities.add(entity);
}

void GameEngine::Scene::removeEntity(Entity* entity)
{
	m_entities.remove(entity);
}
