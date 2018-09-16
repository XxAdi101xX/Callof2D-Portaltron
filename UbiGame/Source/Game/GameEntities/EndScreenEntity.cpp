#include "EndScreenEntity.h"

#include "Game/GameComponents/PlayerSoundComponent.h"
#include "Game/GameComponents/PlayerCameraComponent.h"

#include "GameEngine/EntitySystem/Components/CollidablePhysicsComponent.h"
#include "GameEngine/EntitySystem/Components/ParticleEmitterComponent.h"
#include "GameEngine/EntitySystem/Components/SoundComponent.h"
#include "GameEngine/Util/AnimationManager.h"

using namespace Game;

EndScreenEntity::EndScreenEntity(int winner)
{
	//Render
	m_renderComponent = static_cast<GameEngine::SpriteRenderComponent*>(AddComponent<GameEngine::SpriteRenderComponent>());
	if (winner == 1) {
		m_renderComponent->SetTexture(GameEngine::eTexture::EndW1);
	} else {
		m_renderComponent->SetTexture(GameEngine::eTexture::EndW2);
	}
}


EndScreenEntity::~EndScreenEntity()
{

}

void EndScreenEntity::OnAddToWorld()
{
	__super::OnAddToWorld();
}


void EndScreenEntity::OnRemoveFromWorld()
{
	__super::OnRemoveFromWorld();
}
