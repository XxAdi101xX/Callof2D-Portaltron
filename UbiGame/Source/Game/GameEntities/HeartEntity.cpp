#include "HeartEntity.h"

#include "GameEngine/EntitySystem/Components/CollidableComponent.h"
#include <SFML/Graphics.hpp>

using namespace Game;

HeartEntity::HeartEntity(int player)
{
	m_player = player;
	m_renderComponent = static_cast<GameEngine::SpriteRenderComponent*>(AddComponent<GameEngine::SpriteRenderComponent>());
	m_renderComponent->SetFillColor(sf::Color::Red);
	if (m_player == 1) {
		m_renderComponent->SetTexture(GameEngine::eTexture::BlueHeart);
	} else {
		m_renderComponent->SetTexture(GameEngine::eTexture::RedHeart);
	}
	
	m_renderComponent->SetZLevel(2);
	m_renderComponent->SetTileIndex(0, 0);
}

HeartEntity::~HeartEntity()
{

}


void HeartEntity::OnAddToWorld()
{
	__super::OnAddToWorld();
}


void HeartEntity::OnRemoveFromWorld()
{
	__super::OnRemoveFromWorld();
}
