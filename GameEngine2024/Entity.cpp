#include "Entity.h"
#include "Component.h"

GameEngine::Entity::Entity()
{
}

void GameEngine::Entity::start()
{
	m_started = true;

	for (Component* component : m_components)
	{
		if (component->getEnabled())
			component->start();
	}

	onStart();
}

void GameEngine::Entity::update(double deltaTime)
{
	for (Component* component : m_components)
	{
		if (component->getEnabled())
			component->update(deltaTime);
	}

	onUpdate(deltaTime);
}

void GameEngine::Entity::draw()
{
	for (Component* component : m_components)
	{
		if (component->getEnabled())
			component->draw();
	}

	onDraw();
}

void GameEngine::Entity::end()
{
	for (Component* component : m_components)
	{
		if (component->getEnabled())
			component->end();
	}

	onEnd();
}

void GameEngine::Entity::addComponent(Component* component)
{
	component->setOwner(this);
	m_components.add(component);
}

void GameEngine::Entity::setEnabled(bool value)
{
	if (!m_enabled && value == true)
		onEnable();
	else if (m_enabled && value == false)
		onDisable();

	m_enabled = value;
}
