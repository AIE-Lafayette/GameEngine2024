#include "TestScene.h"
#include <Entity.h>
#include <ShapeComponent.h>

void TestScene::onStart()
{
	GameEngine::Entity* circle = new GameEngine::Entity();
	circle->addComponent(new GameGraphics::ShapeComponent(GameGraphics::CIRCLE));

	circle->getTransform()->setLocalPosition(100,100);
}