#include "stdafx.h"
#include "Renderer.h"
#include "Objcet.h"


Objcet::Objcet()
{
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

void Objcet::DrawObject()
{
	
}

void Objcet::SetSpeed(float s)
{
	speed = s;
}

void Objcet::Update(float time)
{
	float elapsedTime = time;
	position_x = position_x+ m_vX + speed * elapsedTime;
	position_y = position_y+ m_vY + speed * elapsedTime;

	if (position_x > 250)
		m_vX = -m_vX;

	if (position_x < -250)
		m_vX = -m_vX;

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


