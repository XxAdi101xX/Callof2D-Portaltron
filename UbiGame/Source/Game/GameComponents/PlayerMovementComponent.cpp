#include "PlayerMovementComponent.h"

#include "GameEngine\GameEngineMain.h"
#include "GameEngine\EntitySystem\Components\SoundComponent.h"

#include "GameEngine\Util\TextureManager.h"
#include "GameEngine\Util\AnimationManager.h"

#include "Game\GameComponents\PlayerSoundComponent.h"

#include <SFML/Window/Keyboard.hpp>
#include "Game\GameEntities\PlayerEntity.h"

using namespace Game;

PlayerMovementComponent::PlayerMovementComponent()
	: m_flyTimerDt(0.f)
	, m_flyTimerMaxTime(2.f)
	, m_animComponent(nullptr)
	, m_playerSoundComponent(nullptr)
{

}


PlayerMovementComponent::~PlayerMovementComponent()
{

}

void PlayerMovementComponent::OnAddToWorld()
{
	m_animComponent = GetEntity()->GetComponent<GameEngine::AnimationComponent>();
	m_playerSoundComponent = GetEntity()->GetComponent<PlayerSoundComponent>();
}


void PlayerMovementComponent::Update()
{
	__super::Update();

	if (GameEngine::GameEngineMain::GetInstance()->IsGameOver())
	{
		return;
	}

	float dt = GameEngine::GameEngineMain::GetTimeDelta();
	static bool  debugSounds = false;
	static float playerVel = 150.f; //Pixels/s

	sf::Vector2f wantedVel = sf::Vector2f(0.f, 0.f);
	bool wantsToFly = false;
	auto playerType = dynamic_cast<PlayerEntity*>(GetEntity())->player;

	bool leftMovement = 
		playerType == 1 ? 
		sf::Keyboard::isKeyPressed(sf::Keyboard::Left) : 
		sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	bool rightMovement = 
		playerType == 1 ? 
		sf::Keyboard::isKeyPressed(sf::Keyboard::Right) : 
		sf::Keyboard::isKeyPressed(sf::Keyboard::D);
	bool upMovement = 
		playerType == 1 ? 
		sf::Keyboard::isKeyPressed(sf::Keyboard::Up) : 
		sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	bool downMovement = 
		playerType == 1 ? 
		sf::Keyboard::isKeyPressed(sf::Keyboard::Down) : 
		sf::Keyboard::isKeyPressed(sf::Keyboard::S);

	if (leftMovement) {
		dynamic_cast<PlayerEntity*>(GetEntity())->m_direction = 3;
	}
	else if (rightMovement) {
		dynamic_cast<PlayerEntity*>(GetEntity())->m_direction = 1;

	}
	else if (upMovement) {
		dynamic_cast<PlayerEntity*>(GetEntity())->m_direction = 4;

	}
	else if (downMovement) {
		dynamic_cast<PlayerEntity*>(GetEntity())->m_direction = 2;
	}

	if (leftMovement)
	{
		wantedVel.x -= playerVel * dt;
	}
	if (rightMovement)
	{
		wantedVel.x += playerVel * dt;
	}
	if (upMovement)
	{
		wantedVel.y -= playerVel * dt;
		if (m_playerSoundComponent)
		{
			m_playerSoundComponent->RequestSound(true);
		}
	}
	if (downMovement)
	{
		wantedVel.y += playerVel * dt;
		if (m_playerSoundComponent)
		{
			m_playerSoundComponent->RequestSound(false);
		}
	}

	GetEntity()->SetPos(GetEntity()->GetPos() + wantedVel);

	sf::Vector2f tempVel = GetEntity()->GetPos();
	if (tempVel.x < 0) tempVel.x = 0;
	if (tempVel.y < 0) tempVel.y = 0;
	if (tempVel.x > 1500) tempVel.x = 1500;
	if (tempVel.y > 1500) tempVel.y = 1500;

	GetEntity()->SetPos(tempVel);

	if (wantedVel != sf::Vector2f(0.f, 0.f))
	{
		m_flyTimerDt = m_flyTimerMaxTime;
	}
	else
	{
		m_flyTimerDt -= dt;
	}

	if (m_animComponent)
	{
		if (m_flyTimerDt > 0.f)
		{
			if (m_animComponent->GetCurrentAnimation() != GameEngine::EAnimationId::BirdFly)
			{
				m_animComponent->PlayAnim(GameEngine::EAnimationId::BirdFly);
			}
		}
		else if(m_animComponent->GetCurrentAnimation() != GameEngine::EAnimationId::BirdIdle)
		{
			m_animComponent->PlayAnim(GameEngine::EAnimationId::BirdIdle);
		}
	}

	
	static float rotationVel = 50.f; //Deg/s
	static float maxRotation = 20.f; //Deg
	
	float currentRotation = GetEntity()->GetRot();
	float wantedRot = 0.f;
	bool  reseting = false;

	if (wantedVel.y > 0.f)
		wantedRot = rotationVel;
	else if (wantedVel.y < 0.f)
		wantedRot = -rotationVel;
	else
	{				
		if (currentRotation > 0.f)
			wantedRot = -rotationVel;
		else if (currentRotation < 0.f)
			wantedRot = rotationVel;
	}

	float frameRot = wantedRot * dt;
	float totalRot = currentRotation + frameRot;

	if (!reseting)
	{
		if (totalRot > maxRotation)
			totalRot = maxRotation;
		else if (totalRot < -maxRotation)
			totalRot = -maxRotation;
	}
	else
	{
		if (currentRotation > 0.f && totalRot < 0.f)
			totalRot = 0.f;
		if (currentRotation < 0.f && totalRot > 0.f)
			totalRot = 0.f;
	}

	GetEntity()->SetRotation(totalRot);
}