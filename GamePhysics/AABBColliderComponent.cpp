#include "AABBColliderComponent.h"
#include "CircleColliderCompnent.h"
#include "GameEngine2024/TransformComponent.h"
#include <GameGraphics/Gizmos.h>

GamePhysics::AABBColliderComponent::AABBColliderComponent(float width, float height)
{
    m_width = width;
    m_height = height;
    setColliderType(ColliderType::AABB);
}

GamePhysics::Collision* GamePhysics::AABBColliderComponent::checkCollisionCircle(CircleColliderComponent* other)
{
    GameMath::Vector3 direction = other->getOwner()->getTransform()->getGlobalPosition() - getOwner()->getTransform()->getGlobalPosition();

    if (direction.x > m_width / 2)
        direction.x = m_width / 2;
    else if (direction.x < -m_width / 2)
        direction.x = -m_width / 2;

    if (direction.y > m_height / 2)
        direction.y = m_height / 2;
    else if (direction.y < -m_height / 2)
        direction.y = -m_height / 2;

    GameMath::Vector3 closestPoint = getOwner()->getTransform()->getGlobalPosition() + direction;

    direction = (other->getOwner()->getTransform()->getGlobalPosition() - closestPoint);

    float distanceToPoint = direction.getMagnitude();

    if (distanceToPoint >= other->getRadius())
        return nullptr;

    GamePhysics::Collision* collisionData = new GamePhysics::Collision();
    collisionData->collider = other;
    collisionData->normal = direction.getNormalized();
    collisionData->contactPoint = closestPoint;
    collisionData->penetrationDistance = other->getRadius() - distanceToPoint;

    return collisionData;
}

GamePhysics::Collision* GamePhysics::AABBColliderComponent::checkCollisionAABB(AABBColliderComponent* other)
{
    bool collisionDetected =
        getRight() > other->getLeft() &&
        getBottom() < other->getTop() &&
        getTop() > other->getBottom() &&
        getLeft() < other->getRight();

    if (!collisionDetected)
        return nullptr;

    GameMath::Vector3 otherToAABB = other->getOwner()->getTransform()->getGlobalPosition() - getOwner()->getTransform()->getGlobalPosition();

    if (otherToAABB.x > m_width / 2)
        otherToAABB.x = m_width / 2;
    else if (otherToAABB.x < -m_width / 2)
        otherToAABB.x = -m_width / 2;

    if (otherToAABB.y > m_height / 2)
        otherToAABB.y = m_height / 2;
    else if (otherToAABB.y < -m_height / 2)
        otherToAABB.y = -m_height / 2;



    GameMath::Vector3 closestPoint = getOwner()->getTransform()->getGlobalPosition() + otherToAABB;

    GamePhysics::Collision* collisionData = new GamePhysics::Collision();
    collisionData->collider = other;
    collisionData->normal = getPenetrationVector(other).getNormalized();
    collisionData->contactPoint = closestPoint;
    collisionData->penetrationDistance = getPenetrationVector(other).getMagnitude();

    return collisionData;
}

void GamePhysics::AABBColliderComponent::draw()
{
    GameMath::Vector3 position = getOwner()->getTransform()->getGlobalPosition();
    GameGraphics::Gizmos::drawBoxLines({ m_width, m_height }, { position.x, position.y }, getColor());
}

float GamePhysics::AABBColliderComponent::getLeft()
{
    return getOwner()->getTransform()->getGlobalPosition().x - m_width / 2;
}

float GamePhysics::AABBColliderComponent::getRight()
{
    return getOwner()->getTransform()->getGlobalPosition().x + m_width / 2;
}

float GamePhysics::AABBColliderComponent::getTop()
{
    return getOwner()->getTransform()->getGlobalPosition().y + m_height / 2;
}

float GamePhysics::AABBColliderComponent::getBottom()
{
    return getOwner()->getTransform()->getGlobalPosition().y - m_height / 2;
}

GameMath::Vector3 GamePhysics::AABBColliderComponent::getPenetrationVector(AABBColliderComponent* other)
{
    float smallestPenetration = abs(getRight() - other->getLeft());

    GameMath::Vector3 normalFace = { 1,0,0 };

    if (abs(getLeft() - other->getRight()) < smallestPenetration)
    {
        smallestPenetration = abs(getLeft() - other->getRight());
        normalFace = { -1, 0,0 };
    }
    if (abs(getTop() - other->getBottom()) < smallestPenetration)
    {
        smallestPenetration = abs(getTop() - other->getBottom());
        normalFace = { 0,1,0 };
    }
    if (abs(getBottom() - other->getTop()) < smallestPenetration)
    {
        smallestPenetration = abs(getBottom() - other->getTop());
        normalFace = { 0,-1,0 };
    }

    return normalFace * smallestPenetration;
}
