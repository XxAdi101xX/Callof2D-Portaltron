#pragma once
#include "GameEngine\EntitySystem\Entity.h"
#include "GameEngine\EntitySystem\Components\AnimationComponent.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"
#include "Game\GameComponents\PlayerMovementComponent.h"

namespace Game
{			

	class PlayerEntity : public GameEngine::Entity
	{
	public:
		PlayerEntity(int playerType);
		~PlayerEntity();

		int player;
		int m_direction;
		int m_lives;
		int m_isleft;
		int m_isright;
		int m_isup;
		int m_isdown;
		
		virtual void OnAddToWorld() override;
		virtual void OnRemoveFromWorld() override;
		virtual void PlayerEntity::OnHit();
		virtual bool IsDead();

	protected:
		GameEngine::SpriteRenderComponent* m_renderComponent;		
		PlayerMovementComponent*	 m_playerMovementComponent;
		GameEngine::AnimationComponent* m_animComponent;
	};
}

