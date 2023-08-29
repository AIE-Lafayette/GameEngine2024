#include "RigidBodyComponent.h"
#include <TransformComponent.h>

void GamePhysics::RigidBodyComponent::setVelocity3D(float x, float y, float z)
{
	m_velocity.x = x;
	m_velocity.y = y;
	m_velocity.z = z;
}

void GamePhysics::RigidBodyComponent::setVelocity2D(GameMath::Vector2 velocity)
{
	m_velocity.x = velocity.x;
	m_velocity.y = velocity.y;
}

void GamePhysics::RigidBodyComponent::setVelocity2D(float x, float y)
{
	m_velocity.x = x;
	m_velocity.y = y;
}

void GamePhysics::RigidBodyComponent::applyForce(GameMath::Vector3 force)
{
	setVelocity3D(getVelocity3D() + force / getMass());
}

void GamePhysics::RigidBodyComponent::applyForce(GameMath::Vector2 force)
{
	setVelocity2D(getVelocity2D() + force / getMass());
}

void GamePhysics::RigidBodyComponent::applyForceToActor(RigidBodyComponent* other, GameMath::Vector3 force)
{
	applyForce(force * -1);
	other->applyForce(force);
}

void GamePhysics::RigidBodyComponent::applyForceToActor(RigidBodyComponent* other, GameMath::Vector2 force)
{
	applyForce(force * -1);
	other->applyForce(force);
}

void GamePhysics::RigidBodyComponent::update(double deltaTime)
{
	GameMath::Vector3 position = getOwner()->getTransform()->getLocalPosition();
	getOwner()->getTransform()->setLocalPosition(position + getVelocity3D() * deltaTime);

	GameMath::Vector3 gravity = { 0, getGravity(), 0 };

	applyForce(gravity * getMass());
}