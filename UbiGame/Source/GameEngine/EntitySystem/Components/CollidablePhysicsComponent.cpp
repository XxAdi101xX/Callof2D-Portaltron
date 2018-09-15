#include "CollidablePhysicsComponent.h"

#include "GameEngine/Util/CollisionManager.h"
#include "GameEngine/EntitySystem/Entity.h"

#include <vector>
#include <iostream>

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

		if (myBox.intersects(colideBox, intersection))
		{
			sf::Vector2f pos = GetEntity()->GetPos();
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
				pos.x = 5; // update this 
				pos.y = 4; // and thiss
			}

			GetEntity()->SetPos(pos);
		}
	}
}