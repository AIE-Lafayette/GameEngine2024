#include "GameEngine2024/Component.h"

class RotationComponent : public GameEngine::Component
{
public:
	void update(double deltaTime) override;

private:
	float _radians;
};