#include "ShapeComponent.h"

void GameGraphics::ShapeComponent::draw()
{
	GameMath::Vector3 position = getOwner()->getTransform()->getGlobalPosition();

	GameMath::Vector4 color = m_color;

	GameMath::Vector3 scale = getOwner()->getTransform()->getGlobalScale();

	if (m_shapeType == CIRCLE)
		GameGraphics::Gizmos::drawCircle({ position.x, position.y }, scale.x, 50, m_color);
	else if (m_shapeType == BOX)
		GameGraphics::Gizmos::drawBox({ scale.x, scale.y }, { position.x, position.y }, m_color);
}
