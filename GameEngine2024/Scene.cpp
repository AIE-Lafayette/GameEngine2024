#include "Scene.h"
#include "Entity.h"
#include "GamePhysics/ColliderComponent.h"
#include "GamePhysics/RigidBodyComponent.h"

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


void GameEngine::Scene::fixedUpdate(double fixedDeltaTime)
{
	for (Entity* entity : m_entities)
	{
		entity->fixedUpdate(fixedDeltaTime);
	}

	onFixedUpdate(fixedDeltaTime);

	for (auto row = m_activeColliders.begin(); row != m_activeColliders.end(); row++)
	{
		for (auto column = row; column != m_activeColliders.end(); column++)
		{
			if (row == column)
				continue;

			GamePhysics::Collision* collisionData1 = nullptr;
			GamePhysics::Collision* collisionData2 = new GamePhysics::Collision();
			GamePhysics::ColliderComponent* collider1 = *row;
			GamePhysics::ColliderComponent* collider2 = *column;

			if (collisionData1 = collider1->checkCollision(collider2))
			{
				collider1->getRigidBody()->resolveCollision(collisionData1);
				collider1->getOwner()->onCollisionEnter(collisionData1);

				collisionData2->normal = collisionData1->normal * -1;
				collisionData2->collider = collider1;
				collider2->getOwner()->onCollisionEnter(collisionData2);
			}
		}

	}

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
