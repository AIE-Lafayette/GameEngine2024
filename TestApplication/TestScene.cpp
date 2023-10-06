#include "TestScene.h"
#include "GameEngine2024/Entity.h"
#include "GameGraphics/ShapeComponent.h"
#include "GamePhysics/RigidBodyComponent.h"
#include "GamePhysics/CircleColliderCompnent.h"
#include "GamePhysics/AABBColliderComponent.h"

void TestScene::onStart()
{
	//ball 1
	GameEngine::Entity* circle = new GameEngine::Entity();
	circle->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::CIRCLE);
	GamePhysics::RigidBodyComponent* rigidBody = circle->addComponent<GamePhysics::RigidBodyComponent>();

	circle->addComponent(new GamePhysics::CircleColliderComponent(30));

	circle->getTransform()->setLocalPosition(0,100);
	circle->getTransform()->setLocalScale(25, 25);
	rigidBody->setElasticity(1);

	//ball 2
	GameEngine::Entity* circle2 = new GameEngine::Entity();
	circle2->addComponent<GameGraphics::ShapeComponent>()->setShapeType(GameGraphics::BOX);
	GamePhysics::RigidBodyComponent* rigidBody2 = circle2->addComponent<GamePhysics::RigidBodyComponent>();

	circle2->addComponent(new GamePhysics::AABBColliderComponent(30,30));

	rigidBody2->setGravity(0);
	rigidBody2->setIsKinematic(true);
	circle2->getTransform()->setLocalPosition(0, 0);

	circle2->getTransform()->setLocalScale(25, 25);

	addEntity(circle);
	addEntity(circle2);
}