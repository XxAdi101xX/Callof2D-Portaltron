#include "LazerEntity.h"
#include "GameEngine/EntitySystem/Components/CollidableComponent.h"
#include "SFML/Graphics.hpp"
using namespace Game;
LazerEntity::LazerEntity(int dir, int player)
{
	m_dir = dir;
	m_player = player;
	m_isleft = 0;
	m_isright = 0;
	m_isup = 0;
	m_isdown = 0;

	m_renderComponent = static_cast<GameEngine::SpriteRenderComponent*>(AddComponent<GameEngine::SpriteRenderComponent>());
	m_renderComponent->SetFillColor(sf::Color::Red);
	if (m_player == 1) {
		m_renderComponent->SetTexture(GameEngine::eTexture::Lazers);
	} else {
		m_renderComponent->SetTexture(GameEngine::eTexture::Lazers2);
	}
	m_renderComponent->SetZLevel(2);
	m_renderComponent->SetTileIndex(0, 0);
	//AddComponent<GameEngine::CollidableComponent>();
}
LazerEntity::~LazerEntity()
{
}
void LazerEntity::OnAddToWorld()
{
	__super::OnAddToWorld();
}
void LazerEntity::OnRemoveFromWorld()
{
	__super::OnRemoveFromWorld();
}