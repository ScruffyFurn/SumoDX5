#pragma once

#include "GameObject.h"

#define SUMO_SPEED 1.0f

ref class SumoBlock : public GameObject
{
internal:
	SumoBlock();
	SumoBlock(DirectX::XMFLOAT3 position, SumoBlock^ target, float speed=1.0f);
	void Initialize(DirectX::XMFLOAT3 position, SumoBlock^ target, float speed);
	void Update(float deltaTime);
	void Target(SumoBlock^ target);
	SumoBlock^ Target();
	
	void ResetSumo();
	float GetSpeedFactor() { return m_speed; };
	void SetSpeedFactor(float newFactor) { m_speed = newFactor; };
	void SetStunDelay(float delay){ m_stunDelay = delay; };
	bool IsNotStunned(){ return m_stunDelay <= 0; };


protected:
	void UpdatePosition() override;



private:
	DirectX::XMFLOAT4X4 m_rotationMatrix;
	float m_angle;
	float m_speed;
	float m_stunDelay;
	SumoBlock^ m_target;
};


