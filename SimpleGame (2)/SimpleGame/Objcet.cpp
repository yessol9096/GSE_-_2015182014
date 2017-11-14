#include "stdafx.h"
#include "Renderer.h"
#include "Objcet.h"
#include "SceneMgr.h"

Objcet::Objcet(float x, float y, int type)
{
	SetPosition(x, y, 0);
	SetType(type);
	if(type == OBJECT_BULLET || type == OBJECT_ARROW)
	dir = rand() % 8;
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

void  Objcet::SetType(int t)
{
	type = t;
}

void Objcet::SetLife(int l)
{
	life = l;
}

void Objcet::Update(float time)
{
	float elapsedTime = time / 1000.f;

	last_bullet_time += elapsedTime;
	last_arrow_time += elapsedTime;

	if (type == OBJECT_CHARACTER)
	{
		position_x = position_x + m_vX * time;
		position_y = position_y + m_vY * time;
		
		if (position_x > 250)
			m_vX = -0.1;

		if (position_x < -250)                                                                                                                                                                                                                                                                       
			m_vX = 0.1;

		if (position_y > 250)
			m_vY = -0.1;

		if (position_y < -250)
			m_vY = 0.1;
	
		SetPosition(position_x, position_y, 0);
	}

	if (type == OBJECT_BULLET || type == OBJECT_ARROW)
	{
		position_x = position_x + m_vX *  elapsedTime;
		position_y = position_y + m_vY *  elapsedTime;

		if (position_x < -250 || position_x > 250 || position_y < -250 || position_y > 250)
		{
			life = -1;
		}
		if (dir == 0)// 위
		{
			m_vY = -30.0;
			m_vX = 0;
		}
		else if (dir == 1)	// 아래
		{
			m_vY = 30;
			m_vX = 0;
		}

		else if (dir == 2)	// 왼쪽
		{
			m_vX = -30;
			m_vY = 0;
		}
		else if (dir == 3)	// 오른쪽
		{
			m_vX = 30;
			m_vY = 0;
		}
		else if (dir == 4)	// 오른쪽 대각선
		{
			m_vY = 30;
			m_vX = 30;
		}
		else 
		{
			m_vY = -30;
			m_vX = -30;
		}
		SetPosition(position_x, position_y, 0);
	}
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


