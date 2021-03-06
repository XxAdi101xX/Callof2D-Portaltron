#include "GameBoard.h"

#include "Game\GameEntities\HeartEntity.h"
#include "Game\GameEntities\LazerEntity.h"
#include <SFML/Window/Keyboard.hpp>
#include "GameEngine\GameEngineMain.h"
#include "GameEngine\EntitySystem\Components\CollidableComponent.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"
#include "GameEngine\Util\CameraManager.h"
#include "Game\GameEntities\PlayerEntity.h"
#include "Game\GameEntities\ObstacleEntity.h"
#include "Game/GameEntities/EndScreenEntity.h"

#include <iostream>

using namespace Game;

GameBoard::GameBoard()
	: m_lastObstacleSpawnTimer(0.f)
	, m_isGameOver(false)
	, m_player(nullptr)
	, m_backGround(nullptr)
{
	m_player = new PlayerEntity(1);
	m_player2 = new PlayerEntity(2);
	m_heart_player1_1 = new HeartEntity(1);
	m_heart_player1_2 = new HeartEntity(1);
	m_heart_player1_3 = new HeartEntity(1);
	m_heart_player2_1 = new HeartEntity(2);
	m_heart_player2_2 = new HeartEntity(2);
	m_heart_player2_3 = new HeartEntity(2);
	m_p1_lastshot = GameEngine::GameEngineMain::GetInstance()->GetGameTime();
	m_p2_lastshot = GameEngine::GameEngineMain::GetInstance()->GetGameTime();

	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_player);
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_player2);
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_heart_player1_1);
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_heart_player1_2);
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_heart_player1_3);
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_heart_player2_1);
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_heart_player2_2);
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_heart_player2_3);

	m_player->SetPos(sf::Vector2f(100.f, 750.f));
	m_player->SetSize(sf::Vector2f(100.f, 46.f));

	m_player2->SetPos(sf::Vector2f(1400.f, 750.f));
	m_player2->SetSize(sf::Vector2f(100.f, 46.f));

	m_heart_player1_1->SetPos(sf::Vector2f(300.f, 50.f));
	m_heart_player1_1->SetSize(sf::Vector2f(100.f, 100.f));

	m_heart_player1_2->SetPos(sf::Vector2f(200.f, 50.f));
	m_heart_player1_2->SetSize(sf::Vector2f(100.f, 100.f));

	m_heart_player1_3->SetPos(sf::Vector2f(100.f, 50.f));
	m_heart_player1_3->SetSize(sf::Vector2f(100.f, 100.f));

	m_heart_player2_1->SetPos(sf::Vector2f(1400.f, 50.f));
	m_heart_player2_1->SetSize(sf::Vector2f(100.f, 100.f));

	m_heart_player2_2->SetPos(sf::Vector2f(1300.f, 50.f));
	m_heart_player2_2->SetSize(sf::Vector2f(100.f, 100.f));

	m_heart_player2_3->SetPos(sf::Vector2f(1200.f, 50.f));
	m_heart_player2_3->SetSize(sf::Vector2f(100.f, 100.f));

	CreateBackGround();
	//Debug
	for (int a = 0; a < 3; ++a)
	{
		//SpawnNewRandomObstacles();
	}
}


GameBoard::~GameBoard()
{

}


void GameBoard::Update()
{	
	float dt = GameEngine::GameEngineMain::GetInstance()->GetTimeDelta();
	float gt = GameEngine::GameEngineMain::GetInstance()->GetGameTime();
	if (!m_isGameOver)
	{
		m_lastObstacleSpawnTimer -= dt;
		if (m_lastObstacleSpawnTimer <= 0.f)
		{
			// SpawnNewRandomObstacles();
			// SpawnNewRandomTiledObstacles();
			SpawnTwoPortals();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
			&& gt - m_p1_lastshot > 0.5) {
			m_p1_lastshot = gt;
			SpawnLazer(1);

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)
			&& gt - m_p2_lastshot > 0.5) {
			m_p2_lastshot = gt;
			SpawnLazer(2);
		}

		UpdateObstacles(dt);
		UpdateBackGround();
		UpdateLazers(dt);
		UpdateHearts();
		UpdatePlayerDying();
	}		
}

void GameBoard::UpdateHearts() {
	if (m_player->lostLife) {
		switch (m_player->m_lives) {
		case 2:
			GameEngine::GameEngineMain::GetInstance()->RemoveEntity(m_heart_player1_1);
			break;
		case 1:
			GameEngine::GameEngineMain::GetInstance()->RemoveEntity(m_heart_player1_2);
			break;
		case 0:
			GameEngine::GameEngineMain::GetInstance()->RemoveEntity(m_heart_player1_3);
			break;
		}
		m_player->lostLife = false;
	}

	if (m_player2->lostLife) {
		switch (m_player2->m_lives) {
		case 2:
			GameEngine::GameEngineMain::GetInstance()->RemoveEntity(m_heart_player2_3);
			break;
		case 1:
			GameEngine::GameEngineMain::GetInstance()->RemoveEntity(m_heart_player2_2);
			break;
		case 0:
			GameEngine::GameEngineMain::GetInstance()->RemoveEntity(m_heart_player2_1);
			break;
		}
		m_player2->lostLife = false;
	}
}

void GameBoard::UpdateLazers(float dt) {
	static float lazerSpeed = 520.f;
	for (std::vector<LazerEntity*>::iterator it = m_lazers.begin(); it != m_lazers.end();)
	{
		LazerEntity* lazer = (*it);
		sf::Vector2f currPos = lazer->GetPos();
		float dx = 0;
		float dy = 0;

		if (lazer->m_isleft) dx = lazerSpeed * dt * -1;
		if (lazer->m_isright) dx = lazerSpeed * dt;
		if (lazer->m_isdown) dy = lazerSpeed * dt;
		if (lazer->m_isup) dy = lazerSpeed * dt * -1;

		if (dy == 0 && dx == 0) {
			if (lazer->m_dir == 1) {
				dx = lazerSpeed * dt;
			}
			else if (lazer->m_dir == 2) {
				dy = lazerSpeed * dt;
			}
			else if (lazer->m_dir == 3) {
				dx = lazerSpeed * dt * -1;
			}
			else {
				dy = lazerSpeed * dt * -1;
			}
		}

		currPos.x += dx;
		currPos.y += dy;
		lazer->SetPos(currPos);
		//If we are to remove ourselves

		if (currPos.x < -50.f || currPos.x > 1500.f || currPos.y < -50.f || currPos.y > 1500.f)
		{
			/*GameEngine::GameEngineMain::GetInstance()->RemoveEntity(lazer);
			it = m_lazers.erase(it);*/
			it++;
		}
		else
		{
			it++;
		}
	}
}


void GameBoard::UpdateObstacles(float dt)
{
	// static float obstacleSpeed = 100.f;
	
	for (std::vector<GameEngine::Entity*>::iterator it = m_obstacles.begin(); it != m_obstacles.end();)
	{
		GameEngine::Entity* obstacle = (*it);
		sf::Vector2f currPos = obstacle->GetPos();
		// currPos.x -= obstacleSpeed * dt;
		obstacle->SetPos(currPos);
		//If we are to remove ourselves
		if (currPos.x < -50.f)
		{
			GameEngine::GameEngineMain::GetInstance()->RemoveEntity(obstacle);
			it = m_obstacles.erase(it);
		}
		else
		{
			it++;
		}
	}
}


void GameBoard::UpdatePlayerDying()
{	
	bool noGameOver = GameEngine::CameraManager::IsFollowCameraEnabled();

	if (noGameOver || (!m_player->IsDead() && !m_player2->IsDead()))
		return;

	int winr;
	if (m_player->IsDead()) winr = 2;
	else winr = 1;

	EndScreenEntity* e = new EndScreenEntity(winr);
	GameEngine::GameEngineMain::GetInstance()->AddEntity(e);
	e->SetPos(sf::Vector2f(750.f, 750.f));
	e->SetSize(sf::Vector2f(600.f, 600.f));
	m_isGameOver = true;
}

void GameBoard::SpawnLazer(int player) {
	sf::Vector2f pos;
	int playerDirection;
	PlayerEntity* pe;
	if (player == 1) {
		pos = m_player->GetPos();
		playerDirection = m_player->m_direction;
		pe = m_player;
	} else {
		pos = m_player2->GetPos();
		playerDirection = m_player2->m_direction;
		pe = m_player2;
	}

	int xOffset = 60;
	int yOffset = 50;

	if (playerDirection == 1)
		pos.x += xOffset;
	else if (playerDirection == 2)
		pos.y += yOffset;
	else if (playerDirection == 3)
		pos.x -= xOffset;
	else pos.y -= yOffset;

	LazerEntity* lazer = new LazerEntity(playerDirection, player);
	lazer->m_isdown = pe->m_isdown;
	lazer->m_isup = pe->m_isup;
	lazer->m_isright = pe->m_isright;
	lazer->m_isleft = pe->m_isleft;

	GameEngine::GameEngineMain::GetInstance()->AddEntity(lazer);
	lazer->SetPos(pos);
	lazer->SetSize(sf::Vector2f(18, 18));
	m_lazers.push_back(lazer);
}


void GameBoard::SpawnNewRandomObstacles()
{
	static float minNextSpawnTime = 0.3f;
	static float maxNextSpawnTime = 0.7f;

	static float minObstacleXPos = 50.f;
	static float maxObstacleXPos = 450.f;
	static float minObstacleYPos = 20.f;
	static float maxObstacleYPos = 450.f;
	
	static float minObstacleHeight = 50.f;
	static float maxObstacleHeight = 170.f;
	static float minObstacleWidth = 20.f;
	static float maxObstacleWidth = 40.f;

	sf::Vector2f pos = sf::Vector2f(RandomFloatRange(minObstacleXPos, maxObstacleXPos), RandomFloatRange(minObstacleYPos, maxObstacleYPos));
	sf::Vector2f size = sf::Vector2f(RandomFloatRange(minObstacleWidth, maxObstacleWidth), RandomFloatRange(minObstacleHeight, maxObstacleHeight));

	SpawnNewObstacle(pos, size);

	m_lastObstacleSpawnTimer = RandomFloatRange(minNextSpawnTime, maxNextSpawnTime);
}

void GameBoard::SpawnNewRandomTiledObstacles() {
	static int minObstacleCount = 2;
	static int maxObstacleCount = 7;

	static float minNextSpawnTime = 0.3f;
	static float maxNextSpawnTime = 0.7f;

	static float minObstacleXPos = 350.f;
	static float maxObstacleXPos = 450.f;
	static float minObstacleYPos = 20.f;
	static float maxObstacleYPos = 450.f;

	sf::Vector2f pos = sf::Vector2f(RandomFloatRange(minObstacleXPos, maxObstacleXPos), RandomFloatRange(minObstacleYPos, maxObstacleYPos));
	sf::Vector2f size = sf::Vector2f(32.f, 32.f);

	int obstacleCount = (int)RandomFloatRange((float)minObstacleCount, (float)maxObstacleCount);
	for (int a = 0; a < obstacleCount; ++a)
	{
		SpawnNewObstacle(pos, size);
		pos.y += size.y;
	}

	m_lastObstacleSpawnTimer = RandomFloatRange(minNextSpawnTime, maxNextSpawnTime);
}

void GameBoard::SpawnTwoPortals()
{
	ClearAllObstacles();

	static float minNextSpawnTime = 4.0f;
	static float maxNextSpawnTime = 7.0f;

	static float min = 100.f;
	static float submin = 700.f;
	static float submax = 900.f;
	static float max = 1400.f;

	sf::Vector2f pos1 = sf::Vector2f(RandomFloatRange(min, submin), RandomFloatRange(min, submin));
	sf::Vector2f pos2 = sf::Vector2f(RandomFloatRange(min, submin), RandomFloatRange(submax, max));
	sf::Vector2f pos3 = sf::Vector2f(RandomFloatRange(submax, max), RandomFloatRange(min, submin));
	sf::Vector2f pos4 = sf::Vector2f(RandomFloatRange(submax, max), RandomFloatRange(submax, max));
	sf::Vector2f size = sf::Vector2f(32.f, 134.f);


	SpawnNewObstacle(pos1, size);
	pos1.y += size.y;

	SpawnNewObstacle(pos2, size);
	pos2.y += size.y;

	SpawnNewObstacle(pos3, size);
	pos3.y += size.y;

	SpawnNewObstacle(pos4, size);
	pos4.y += size.y;

	m_lastObstacleSpawnTimer = RandomFloatRange(minNextSpawnTime, maxNextSpawnTime);
}


void GameBoard::SpawnNewObstacle(const sf::Vector2f& pos, const sf::Vector2f& size)
{
	ObstacleEntity* obstacle = new ObstacleEntity(true);
	GameEngine::GameEngineMain::GetInstance()->AddEntity(obstacle);
	obstacle->SetPos(pos);
	obstacle->SetSize(sf::Vector2f(size.x, size.y));

	m_obstacles.push_back(obstacle);
}


void GameBoard::CreateBackGround()
{
	GameEngine::Entity* bgEntity = new GameEngine::Entity();
	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(bgEntity->AddComponent<GameEngine::SpriteRenderComponent>());
	render->SetTexture(GameEngine::eTexture::BG);
	render->SetZLevel(0);
	bgEntity->SetPos(sf::Vector2f(750.f, 750.f));
	bgEntity->SetSize(sf::Vector2f(1500.f, 1500.f));

	GameEngine::GameEngineMain::GetInstance()->AddEntity(bgEntity);

	m_backGround = bgEntity;
}


void GameBoard::UpdateBackGround()
{
	if (!m_backGround || !m_player)
		return;

	if (!GameEngine::CameraManager::IsFollowCameraEnabled())
		return;

	m_backGround->SetPos(m_player->GetPos());
}

void GameBoard::ClearAllObstacles() {
	for (std::vector<GameEngine::Entity*>::iterator it = m_obstacles.begin(); it != m_obstacles.end();) {
		GameEngine::Entity* obstacle = (*it);
		GameEngine::GameEngineMain::GetInstance()->RemoveEntity(obstacle);
		it = m_obstacles.erase(it);
	}
}
