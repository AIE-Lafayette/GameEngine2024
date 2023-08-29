#include <Component.h>
#include <GameMath/Vector3.h>
#include <GameMath/Vector2.h>

namespace GamePhysics
{
	class RigidBodyComponent : public GameEngine::Component
	{
	public:
		GameMath::Vector3 getVelocity3D() { return m_velocity; }
		void setVelocity3D(GameMath::Vector3 velocity) { m_velocity = velocity; }
		void setVelocity3D(float x, float y, float z);

		GameMath::Vector2 getVelocity2D() { return { m_velocity.x, m_velocity.y }; }
		void setVelocity2D(GameMath::Vector2 velocity);
		void setVelocity2D(float x, float y);

		float getGravity() { return m_gravity; }
		void setGravity(float gravity) { m_gravity = gravity; }

		float getMass() { return m_mass; }
		void setMass(float mass) {}

		void applyForce(GameMath::Vector3 force);
		void applyForce(GameMath::Vector2 force);

		void applyForceToActor(RigidBodyComponent* other, GameMath::Vector3 force);
		void applyForceToActor(RigidBodyComponent* other, GameMath::Vector2 force);

		void update(double deltaTime) override;

	private:
		float m_mass = 1;
		float m_gravity = 9.81f;
		GameMath::Vector3 m_velocity = GameMath::Vector3();
	};
}