#pragma once
#include "ColliderComponent.h"

namespace GamePhysics
{
    class AABBColliderComponent :
        public ColliderComponent
    {
    public:
        AABBColliderComponent(float width, float height);

        GamePhysics::Collision* checkCollisionCircle(CircleColliderComponent* other);
        GamePhysics::Collision* checkCollisionAABB(AABBColliderComponent* other);

        void draw() override;

        /// <summary>
        /// Gets the x value that represents how far the box extends to the left.
        /// </summary>
        float getLeft();

        /// <summary>
        /// Gets the x value that represents how far the box extends to the right.
        /// </summary>
        float getRight();

        /// <summary>
        /// Gets the y value that represents how far the box extends to its top.
        /// </summary>
        float getTop();


        /// <summary>
        /// Gets the y value that represents how far the box extends to its bottom.
        /// </summary>
        float getBottom();

        GameMath::Vector3 getPenetrationVector(AABBColliderComponent* other);
    private:
        float m_width;
        float m_height;
    };

}