#include "ColliderComponent.h"
#include "RigidBodyComponent.h"
#include "GameEngine2024/Engine.h"
#include "GameEngine2024/Scene.h"

void GamePhysics::ColliderComponent::start()
{
	GameEngine::Engine::getCurrentScene()->addActiveCollider(this);
	m_rigidBody = getOwner()->getComponent<RigidBodyComponent>();
}

GamePhysics::Collision* GamePhysics::ColliderComponent::checkCollision(ColliderComponent* other)
{
	switch (other->getColliderType())
	{
	case CIRCLE:
		return checkCollisionCircle((CircleColliderComponent*)other);
	case AABB:
		return checkCollisionAABB((AABBColliderComponent*)other);
	}

	return nullptr;
}

void GamePhysics::ColliderComponent::onCollision(GamePhysics::Collision* other)
{
	setColor({ 1,0,0,1 });
}

void GamePhysics::ColliderComponent::update(double deltaTime)
{
	setColor({ 0,1,0,1 });
}

