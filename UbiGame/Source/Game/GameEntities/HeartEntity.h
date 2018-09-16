#pragma once
#include "GameEngine\EntitySystem\Entity.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"
namespace Game
{
	class HeartEntity : public GameEngine::Entity
	{
	public:
		HeartEntity(int player);
		~HeartEntity();
		int m_player;
		virtual void OnAddToWorld() override;
		virtual void OnRemoveFromWorld() override;
	protected:
		GameEngine::SpriteRenderComponent* m_renderComponent;
	};
}
