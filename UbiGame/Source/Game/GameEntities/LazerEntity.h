#pragma once
#include "GameEngine\EntitySystem\Entity.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"
namespace Game
{
	class LazerEntity : public GameEngine::Entity
	{
	public:
		LazerEntity(int dir, int player);
		~LazerEntity();
		int m_dir;

		int m_player;
		int m_isleft;
		int m_isright;
		int m_isup;
		int m_isdown;

		virtual void OnAddToWorld() override;
		virtual void OnRemoveFromWorld() override;
		virtual int GetEntityType() override;
	protected:
		GameEngine::SpriteRenderComponent* m_renderComponent;
	};
}
