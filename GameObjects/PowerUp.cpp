#include "pch.h"
#include "PowerUp.h"

using namespace DirectX;


PowerUp::PowerUp() : m_active(false), m_type(PowerUps::speed)
{

}

void PowerUp::Activate(PowerUps type)
{
	m_type = type;
	m_active = true;
}

void PowerUp::Deactivate()
{
	m_active = false;
}