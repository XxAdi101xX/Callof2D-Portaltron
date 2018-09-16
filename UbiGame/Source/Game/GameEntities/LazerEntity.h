#pragma once
#include "GameEngine\EntitySystem\Entity.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"
namespace Game
{
	class LazerEntity : public GameEngine::Entity
	{
	public:
		LazerEntity(int dir);
		~LazerEntity();
		int m_dir;
		int m_isleft;
		int m_isright;
		int m_isup;
		int m_isdown;
		virtual void OnAddToWorld() override;
		virtual void OnRemoveFromWorld() override;
	protected:
		GameEngine::SpriteRenderComponent* m_renderComponent;
	};
}
