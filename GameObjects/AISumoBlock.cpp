#include "pch.h"
#include "AISumoBlock.h"
#include "PowerUpManager.h"

using namespace DirectX;

AISumoBlock::AISumoBlock()
{
	Initialize(XMFLOAT3(0, 0, 0), nullptr, SUMO_SPEED);
	Behavior(GameConstants::Easy);
	m_delay = 2;
	m_choice = GameConstants::Walk;
}

AISumoBlock::AISumoBlock(DirectX::XMFLOAT3 position,SumoBlock^ target,GameConstants::Behavior aiBehavior, float speed)
{
	Initialize(position, target, speed);
	Behavior(aiBehavior);
	m_delay = 2;
	m_choice = GameConstants::Walk;
}

void AISumoBlock::DetermineAIAction(float deltaTime, PowerUpManager^ powerUpManager)
{
	//count down towards next action
	m_delay -= deltaTime;

	if (m_delay <= 0)
	{
		m_choice = static_cast<GameConstants::ManeuverState>(rand() % GameConstants::NumOfStates);

		//reset delay until next action (1 to 3 seconds)
		m_delay = (rand() % 3) + 1.0f;
	}

	
	//apply current action
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
	XMVECTOR direction;
	
	switch (m_choice)
	{
	case GameConstants::Dodge:
		//dodge
		direction = XMVector3Cross(Target()->VectorPosition() - VectorPosition(), up);
		direction = XMVectorSetIntY(direction, 0);
		Position(VectorPosition() + XMVector3Normalize(direction) * deltaTime * (m_behavior - 1) * GetSpeedFactor());
		if (m_behavior != GameConstants::Angry)
		{
			break;
		}

	case GameConstants::Push:
		//push harder
		direction = ((Target()->VectorPosition() - VectorPosition()));
		direction = XMVectorSetIntY(direction, 0);
		Position(VectorPosition() + XMVector3Normalize(direction) * deltaTime * m_behavior * GetSpeedFactor());
		break;
	case GameConstants::EdgeCheck:
		//check for edge
		EdgeCheck();
		break;
	case GameConstants::PowerupCheck:
		//check for power-ups
		if (powerUpManager->IsPowerUpActive())
		{
			direction = ((powerUpManager->GetPowerUpPosition() - VectorPosition()));
			//check if it is close to the AISumo
			if (XMVectorGetX(XMVector3Length(direction)) <= 3.0f * GetSpeedFactor() && powerUpManager->GetPowerUpType() % 2 == 0)
			{
				//its close and helpful so run to it.
				direction = XMVectorSetIntY(direction, 0);
				Position(VectorPosition() + XMVector3Normalize(direction) * deltaTime * GetSpeedFactor());
				return;
			}
		}

		//not close or not active, so do something else.
		m_delay = 0;
		break;	
	case GameConstants::Slap:
		//pick a direction to slap
		if ((rand() % 2) > 0.0f)
		{
			m_pushLeft = true;
		}
		else
		{
			m_pushRight = true;
		}

		m_delay = 0;
		break;
	default:
		//move forward normally
		direction = ((Target()->VectorPosition() - VectorPosition()));
		direction = XMVectorSetIntY(direction, 0);
		Position(VectorPosition() + XMVector3Normalize(direction) * deltaTime * GetSpeedFactor());
		break;
	}
}

void AISumoBlock::EdgeCheck()
{
	XMFLOAT3 length;
	XMStoreFloat3(&length, XMVector3Length(VectorPosition()));
	if (abs(length.x) > 6)
	{
		//near an edge! But are we in trouble?
		XMFLOAT3 targetLength;
		XMStoreFloat3(&targetLength, XMVector3Length(Target()->VectorPosition()));
		if (abs(length.x) > (targetLength.x))
		{
			//we are closer to the edge, try to escape!
			if (m_behavior == GameConstants::Angry)
			{
				m_choice = GameConstants::Slap;
			}
			else
			{
				m_choice = GameConstants::Dodge;
			}
			
		}
		else
		{
			//our target is closer to the edge, keep pushing!
			m_choice = GameConstants::Walk;
		}
	}
	else
	{
		//not near an edge so choose something else!
		m_delay = 0;
	}
}