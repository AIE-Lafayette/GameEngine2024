#include "TestScene.h"
#include "GameEngine2024/Entity.h"
#include "GameGraphics/ShapeComponent.h"
#include "GamePhysics/RigidBodyComponent.h"
#include "GamePhysics/CircleColliderCompnent.h"
#include "GamePhysics/AABBColliderComponent.h"
#include "GameGraphics/SpriteComponent.h"
#include "RotationComponent.h"

void TestScene::onStart()
{
	GameEngine::Entity* spaceShip = new GameEngine::Entity();

	spaceShip->addComponent<GameGraphics::SpriteComponent>()->setTexture("spaceship.png");
	spaceShip->addComponent<RotationComponent>();

	spaceShip->getTransform()->setLocalScale(50, 50);

	addEntity(spaceShip);
}