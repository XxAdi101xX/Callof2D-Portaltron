#pragma once
#include "GameEngine\EntitySystem\Entity.h"

#include "Game/GameEntities/HeartEntity.h"
#include "Game/GameEntities/LazerEntity.h"
#include <SFML/System/Vector2.hpp>
#include <vector>

namespace Game
{
	//Used for storing and controling all game related entities
	class PlayerEntity;	

	class GameBoard
	{
	public:
		GameBoard();
		virtual ~GameBoard();

		//Temp - for nice architecture this should be within some sort of IUpdatable interface that GameEngine handles (so that not only entities can be updated)
		void Update();
		void UpdateObstacles(float dt);
		void UpdateLazers(float dt);
		void UpdateHeart();
		void UpdatePlayerDying();
		void SpawnTwoPortals();
		void SpawnNewRandomObstacles();
		void SpawnLazer(int player);
		void SpawnNewRandomTiledObstacles();
		void SpawnNewObstacle(const sf::Vector2f& pos, const sf::Vector2f& size);
		void ClearAllObstacles();

		bool IsGameOver() const { return m_isGameOver; }		

	protected:
		//Placeholder temp - should go to helpers or smth.
		float RandomFloatRange(float a, float b)
		{
			return ((b - a) * ((float)rand() / RAND_MAX)) + a;
		}

		void CreateBackGround();
		void UpdateBackGround();

		PlayerEntity* m_player;
		PlayerEntity* m_player2;

		HeartEntity* m_heart_player1_1;
		HeartEntity* m_heart_player1_2;
		HeartEntity* m_heart_player1_3;

		HeartEntity* m_heart_player2_1;
		HeartEntity* m_heart_player2_2;
		HeartEntity* m_heart_player2_3;
		
		float m_p1_lastshot;
		float m_p2_lastshot;
		GameEngine::Entity* m_backGround;

		std::vector<GameEngine::Entity*> m_obstacles;
		std::vector<LazerEntity*> m_lazers;
		float m_lastObstacleSpawnTimer;
		bool  m_isGameOver;
	};
}

