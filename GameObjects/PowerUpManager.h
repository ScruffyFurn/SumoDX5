
#pragma once

#include "PowerUp.h"
#include "SumoBlock.h"

#define LIFE_TIME 4
#define SPAWN_TIME 5

ref class PowerUpManager
{
internal:
	PowerUpManager();

	void Update(float deltaTime);
	void RenderPowerUp(_In_ ID3D11DeviceContext *context, _In_ ID3D11Buffer *primitiveConstantBuffer);

	void PowerUpMesh(_In_ MeshObject^ mesh);
	void PowerUpMaterial(_In_ Material^ material);
	PowerUps GetPowerUpType() { return m_powerUp->isType(); };
	DirectX::XMVECTOR GetPowerUpPosition() { return m_powerUp->VectorPosition(); };
	void PowerUpTaken(_In_ SumoBlock^ owner, _In_ SumoBlock^ target);
	bool CheckIfTouchingPowerUp(DirectX::XMVECTOR position);
	bool IsPowerUpActive() { return m_powerUp->isActive(); };

private:
	float m_timeUntilSpawn;
	float m_timeUntilDespawn;
	PowerUp^ m_powerUp;
};

