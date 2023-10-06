#pragma once
#include "GameEngine2024/Component.h"
#include <GameMath/Vector3.h>
#include <GameMath/Vector4.h>

namespace GamePhysics
{
    class CircleColliderComponent;
    class AABBColliderComponent;
    class RigidBodyComponent;

    class ColliderComponent : public GameEngine::Component
    {
    public:
        enum ColliderType
        {
            CIRCLE,
            AABB
        };

    public:
        void start() override;
        Collision* checkCollision(ColliderComponent* other);

        virtual Collision* checkCollisionCircle(CircleColliderComponent* other) = 0;
        virtual Collision* checkCollisionAABB(AABBColliderComponent* other) = 0;

        void onCollision(GamePhysics::Collision* other) override;

        void update(double deltaTime) override;

        ColliderType getColliderType() { return m_colliderType; }
        void setColliderType(ColliderType type) { m_colliderType = type; }

        bool getIsTrigger() { return m_isTrigger; }
        void setIsTrigger(bool value) { m_isTrigger = value; }

        GameMath::Vector4 getColor() { return m_color; }
        void setColor(GameMath::Vector4 color) { m_color = color; }

        RigidBodyComponent* getRigidBody() { return m_rigidBody; }

    private:
        bool m_isTrigger;
        ColliderType m_colliderType;
        GameMath::Vector4 m_color = {1,1,1,1};
        RigidBodyComponent* m_rigidBody;
    };

    struct Collision
    {
    public:
        GameMath::Vector3 normal;
        ColliderComponent* collider;
        GameMath::Vector3 contactPoint;
        float penetrationDistance;
    };
}