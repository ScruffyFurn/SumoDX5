#include "pch.h"
#include "PowerUpManager.h"
#include "SumoBlock.h"


using namespace DirectX;

PowerUpManager::PowerUpManager() : m_timeUntilSpawn(SPAWN_TIME), m_timeUntilDespawn(0)
{
	m_powerUp = ref new PowerUp();
}

void PowerUpManager::Update(float deltaTime)
{
	m_timeUntilSpawn -= deltaTime;

	if (m_timeUntilSpawn <= 0)
	{
		//spawn a power-up somwehere on the map
		XMFLOAT3 location = XMFLOAT3((rand() % 15) - 7.5f, 0.75f, (rand() % 15) - 7.5f);
		m_powerUp->Position(location);

		//Determine what type of power-up to spawn
		int choice = rand() % PowerUps::numberOfPowers;
		switch (choice)
		{
		case PowerUps::speed:
			m_powerUp->Activate(PowerUps::speed);
			m_powerUp->NormalMaterial()->SetColor(XMFLOAT4(1.0f,0.0f,0.0f,1.0f));
			break;
		case PowerUps::knockback:
			m_powerUp->Activate(PowerUps::knockback);
			m_powerUp->NormalMaterial()->SetColor(XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));
			break;
		case PowerUps::stun:
			m_powerUp->Activate(PowerUps::stun);
			m_powerUp->NormalMaterial()->SetColor(XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
			break;
		case PowerUps::slow:
			m_powerUp->Activate(PowerUps::slow);
			m_powerUp->NormalMaterial()->SetColor(XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f));
			break;
		case PowerUps::blastback:
			m_powerUp->Activate(PowerUps::blastback);
			m_powerUp->NormalMaterial()->SetColor(XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f));
			break;
		case PowerUps::sticky:
			m_powerUp->Activate(PowerUps::sticky);
			m_powerUp->NormalMaterial()->SetColor(XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f));
			break;
		}

		//set the despawn time
		m_timeUntilDespawn = LIFE_TIME;

		//reset the spawn timer
		m_timeUntilSpawn = SPAWN_TIME;
	}

	if (m_timeUntilDespawn > 0)
	{
		m_timeUntilDespawn -= deltaTime;

		if (m_timeUntilDespawn <= 0)
		{
			//despawn power-up
			m_powerUp->Deactivate();
		}
	}
}

bool PowerUpManager::CheckIfTouchingPowerUp(XMVECTOR position)
{
	if (m_powerUp->isActive())
	{
		XMFLOAT3 answer;
		XMStoreFloat3(&answer, XMVector3Length(position - m_powerUp->VectorPosition()));
		if (answer.x < 1.0f)
		{
			return true;
		}
	}

	return false;
}

void PowerUpManager::PowerUpTaken(_In_ SumoBlock^ owner, _In_ SumoBlock^ target)
{

	switch (m_powerUp->isType())
	{
	case PowerUps::speed: 
		owner->SetSpeedFactor(owner->GetSpeedFactor() + 0.5f);
		m_powerUp->Deactivate();
		break;
	case PowerUps::knockback:
		target->Position( target->VectorPosition() + ( XMVector3Normalize( target->VectorPosition() - owner->VectorPosition() ) *3.0f ) );
		m_powerUp->Deactivate();
		break;
	case PowerUps::stun:
		target->SetStunDelay(3.0f);
		m_powerUp->Deactivate();
		break;
	case PowerUps::slow:
		owner->SetSpeedFactor(owner->GetSpeedFactor() - 0.5f);
		m_powerUp->Deactivate();
		break;
	case PowerUps::blastback:
		owner->Position(owner->VectorPosition() + (XMVector3Normalize(owner->VectorPosition() - target->VectorPosition()) *3.0f));
		m_powerUp->Deactivate();
		break;
	case PowerUps::sticky:
		owner->SetStunDelay(3.0f);
		m_powerUp->Deactivate();
		break;
	}
}

void PowerUpManager::RenderPowerUp(_In_ ID3D11DeviceContext *context, _In_ ID3D11Buffer *primitiveConstantBuffer)
{
	if (m_powerUp->isActive())
	{
		m_powerUp->Render(context, primitiveConstantBuffer);
	}
}

__forceinline void PowerUpManager::PowerUpMaterial(_In_ Material^ material)
{
	m_powerUp->NormalMaterial( material);
}

__forceinline void PowerUpManager::PowerUpMesh(_In_ MeshObject^ mesh)
{
	m_powerUp->Mesh(mesh);
}