#include "stdafx.h"
#include "Renderer.h"
#include "Objcet.h"


Objcet::Objcet()
{
	m_vX = 200.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
	m_vY = 200.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
}


Objcet::~Objcet()
{
}

void Objcet::SetSize(float size)
{
	fixel_size = size;
}

void Objcet::SetPosition(float x, float y, float z)
{
	position_x = x;
	position_y = y;
	position_z = z;
}

void Objcet::SetColor(float r, float g, float b, float a)
{
	red = r;
	green = g;
	blue = b;
	transparent = a;
}

void Objcet::SetSpeed(float s)
{
	speed = s;
}

void Objcet::Update(float time)
{
	float elapsedTime = (int)time % 10;

	position_x = position_x + m_vX * elapsedTime;
	position_y = position_y + m_vY * elapsedTime;

	if (position_x > 250)
		m_vX = -1;

	if (position_x < -250)
		m_vX = 1;
	
	if (position_y > 250)
	{
		m_vY = -1;
	}

	if (position_y < -250)
	{
		m_vY = 1;
	}
	SetPosition(position_x, position_y, 0);
}

float Objcet::GetpositionX()
{
	return position_x;
}

float Objcet::GetpositionY()
{
	return position_y;
}


float Objcet::GetpositionZ()
{
	return position_z;
}


