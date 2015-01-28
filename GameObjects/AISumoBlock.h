#pragma once

#include "SumoBlock.h"
#include "GameConstants.h"

ref class PowerUpManager;

ref class AISumoBlock : public SumoBlock
{
internal:
	AISumoBlock();
	AISumoBlock(DirectX::XMFLOAT3 position,	SumoBlock^ target,	GameConstants::Behavior aiBehavior, float speed = 1.0f);

	void Behavior(GameConstants::Behavior newBehavior);
	void DetermineAIAction(float deltaTime, PowerUpManager^ manager);

	bool PushingLeft() { return m_pushLeft; }
	bool PushingRight() { return m_pushRight; }
	void ResetPushing();

private:
	void EdgeCheck();

	GameConstants::Behavior m_behavior;
	GameConstants::ManeuverState m_choice;
	float m_delay;
	bool m_pushLeft;
	bool m_pushRight;
	
};

__forceinline void AISumoBlock::Behavior(GameConstants::Behavior newBehavior)
{
	m_behavior = newBehavior;
}

__forceinline void AISumoBlock::ResetPushing()
{
	m_pushLeft = false;
	m_pushRight = false;
}


