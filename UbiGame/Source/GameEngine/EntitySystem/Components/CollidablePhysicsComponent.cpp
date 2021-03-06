#include "CollidablePhysicsComponent.h"

#include "GameEngine/Util/CollisionManager.h"
#include "GameEngine/EntitySystem/Entity.h"
#include "Game\GameEntities\PlayerEntity.h"

#include <vector>
#include <iostream>
#include <random>

using namespace GameEngine;

CollidablePhysicsComponent::CollidablePhysicsComponent(): CollidableComponent(false)
{

}


CollidablePhysicsComponent::~CollidablePhysicsComponent()
{

}


void CollidablePhysicsComponent::OnAddToWorld()
{
	__super::OnAddToWorld();
}


void CollidablePhysicsComponent::OnRemoveFromWorld()
{
	__super::OnAddToWorld();
}


void CollidablePhysicsComponent::Update()
{
	//For the time being just a simple intersection check that moves the entity out of all potential intersect boxes
	std::vector<CollidableComponent*>& collidables = CollisionManager::GetInstance()->GetCollidables();

	for (int a = 0; a < collidables.size(); ++a)
	{
		CollidableComponent* colComponent = collidables[a];
		if (colComponent == this)
			continue;

		AABBRect intersection;
		AABBRect myBox = GetWorldAABB();
		AABBRect colideBox = colComponent->GetWorldAABB();

		int entityType = GetEntity()->GetEntityType(); // DO SOMETHING WITH THIS
		bool carHit = colideBox.height == 18 && colideBox.width == 18 && myBox.height == 46 && myBox.width == 100;

		if (myBox.intersects(colideBox, intersection))
		{
			std::cout << entityType << std::endl;
			sf::Vector2f pos = GetEntity()->GetPos();
			
			if (carHit) {
				dynamic_cast<Game::PlayerEntity*>(GetEntity())->OnHit();
				// std::cout << dynamic_cast<Game::PlayerEntity*>(GetEntity())->m_lives << std::endl;
				colComponent->OnRemoveFromWorld();
				// delete colComponent;
				
			}
			else {

				if (intersection.width < intersection.height)
				{
					if (myBox.left < colideBox.left)
						pos.x -= intersection.width;
					else
						pos.x += intersection.width;
				}
				else
				{
					if (myBox.top < colideBox.top)
						pos.y -= intersection.height;
					else
						pos.y += intersection.height;
				}
				if (colComponent->ShouldEnableTeleportation()) {
					int random = ((5 - 1) * ((float)rand() / RAND_MAX)) + 1;
					std::cout << random << "sdfsdfsd";

					switch (random) {
					case 1:
						pos.x = 50; // update this 
						pos.y = 750; // and thiss
						break;
					case 2:
						pos.x = 750; // update this 
						pos.y = 50; // and thiss
						break;
					case 3:
						pos.x = 1450; // update this 
						pos.y = 750; // and thiss
						break;
					case 4:
						pos.x = 750; // update this 
						pos.y = 1450; // and thiss
						break;
					}
				}
				GetEntity()->SetPos(pos);
			}
			
			std::cout << myBox.height << " " << colideBox.height << " " << myBox.width << " " << colideBox.width << " "<< entityType << std::endl;
			// std::cout << oldPos.x - pos.x << "  BBBBBBBBBBBBBBBBBBBB   " << oldPos.y - pos.y << std::endl;
			// std::cout << pos.x << GetEntity()->GetPos().x  << " sdfsdfsdf" << pos.y << GetEntity()->GetPos().y << std::endl;
		}
	}
}