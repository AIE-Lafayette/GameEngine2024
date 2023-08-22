#include "Component.h"

void GameEngine::Component::setEnabled(bool value)
{
	if (!m_enabled && value == true)
		onEnable();
	else if (m_enabled && value == false)
		onDisable();

	m_enabled = value;
}
