#include "RotationComponent.h"
#include "GameEngine2024/TransformComponent.h"

void RotationComponent::update(double deltaTime)
{
	getOwner()->getTransform()->setLocalRotation({ 0,0,_radians += deltaTime });
}