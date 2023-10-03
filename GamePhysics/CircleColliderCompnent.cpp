#include "CircleColliderCompnent.h"
#include <GameMath/Vector3.h>
#include "GameEngine2024/TransformComponent.h"
#include "AABBColliderComponent.h"

GamePhysics::Collision* GamePhysics::CircleColliderComponent::checkCollisionCircle(CircleColliderComponent* other)
{
	GameMath::Vector3 position = getOwner()->getTransform()->getGlobalPosition();
	GameMath::Vector3 otherPosition = other->getOwner()->getTransform()->getGlobalPosition();

	GameMath::Vector3 direction = otherPosition - position;
	float distance = direction.getMagnitude();
	direction.normalize();

	if (distance > other->getRadius() + getRadius())
		return nullptr;

	GamePhysics::Collision* collisionData = new GamePhysics::Collision();

	collisionData->collider = other;
	collisionData->normal = direction;
	collisionData->contactPoint = getOwner()->getTransform()->getGlobalPosition() + direction * getRadius();
	collisionData->penetrationDistance = other->getRadius() + getRadius() - distance;

	return collisionData;
}

GamePhysics::Collision* GamePhysics::CircleColliderComponent::checkCollisionAABB(AABBColliderComponent* other)
{
	GamePhysics::Collision* collisionData = other->checkCollisionCircle(this);
	if (collisionData)
	{
		collisionData->collider = other;
		collisionData->normal = collisionData->normal * -1;
	}
	return collisionData;
}

void GamePhysics::CircleColliderComponent::draw()
{
	GameMath::Vector3 position = getOwner()->getTransform()->getGlobalPosition();

	unsigned int colorCode = getColor();

	//RAYLIB_H::DrawCircleLines(position.x, position.y, getRadius(), GetColor(colorCode));
}
