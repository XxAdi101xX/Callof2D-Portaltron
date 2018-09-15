#pragma once
#include "GameEngine\EntitySystem\Entity.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"

namespace Game
{

	class ObstacleEntity : public GameEngine::Entity
	{
	public:
		ObstacleEntity(bool isPortal);
		~ObstacleEntity();

		virtual int GetEntityType() override;
		virtual void OnAddToWorld() override;
		virtual void OnRemoveFromWorld() override;

	protected:
		GameEngine::SpriteRenderComponent* m_renderComponent;		
	};
}

