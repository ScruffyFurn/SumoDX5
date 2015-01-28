#pragma once
#include "Sphere.h"
enum PowerUps
{
	speed,
	slow,
	stun,
	sticky,
	knockback,
	blastback,
	numberOfPowers
};

ref class PowerUp: public Sphere
{
internal:
	PowerUp();
	void Activate( PowerUps type );
	void Deactivate();
	bool isActive() { return m_active; }
	PowerUps isType() { return m_type; }

private:
	PowerUps m_type;
	bool m_active;
};