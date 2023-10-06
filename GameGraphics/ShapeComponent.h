#pragma once
#include "GameEngine2024/TransformComponent.h"
#include "Gizmos.h"

namespace GameGraphics
{
    enum ShapeType
    {
        CIRCLE,
        BOX
    };

    class ShapeComponent : public GameEngine::Component
    {
    public:
        ShapeComponent() {};
        ShapeComponent(ShapeType shapeType) : Component() { m_shapeType = shapeType; }

        void setColor(GameMath::Vector4 color) { m_color = color; }
        GameMath::Vector4 getColor() { return m_color; }

        void setShapeType(ShapeType shapeType) { m_shapeType = shapeType; }
        ShapeType getShapeType() { return m_shapeType; }

        void draw() override;

    private:
        ShapeType m_shapeType;
        GameMath::Vector4 m_color = { 1,1,1,1 };
    };
}
