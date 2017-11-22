#include "stdafx.h"
#include "Renderer.h"
#include "Object.h"
#include "SceneMgr.h"

Object::Object(float x, float y, int type, int Team)
{
	SetPosition(x, y, 0);
	SetType(type);
	team = Team;
	if (type == OBJECT_BUILDING)
	{
		SetSize(100);
		SetSpeed(0);
		SetLife(500);
		SetLevel(LEVEL_GOD);
		
		m_vX = 0;
		m_vY = 0;
		
		SetColor(1, 1, 1, 1);
	}
	else if (type == OBJECT_CHARACTER)
	{
		SetSize(30);
		SetSpeed(300);
		SetLife(100);
		SetLevel(LEVEL_SKY);
		
		if (team == TEAM_1)
			SetColor(1, 0, 0, 1);
		else if (team == TEAM_2)
			SetColor(0, 0, 1, 1);
	}
	else if (type == OBJECT_BULLET)
	{
		SetSize(4);
		SetSpeed(600);
		SetLife(15);
		SetLevel(LEVEL_GROUND);

		if (team == TEAM_1)
			SetColor(1, 0, 0, 1);
		else if (team == TEAM_2)
			SetColor(0, 0, 1, 1);
	}
	else if (type == OBJECT_ARROW)
	{
		SetSize(4);
		SetSpeed(100);
		SetLife(10);
		SetLevel(LEVEL_UNDERGROUND);

		if (team == TEAM_1)
			SetColor(0.5, 0.2, 0.7, 1);
		else if (team == TEAM_2)
			SetColor(1, 1, 0, 1);
	}
	if(type == OBJECT_BULLET || type == OBJECT_ARROW)
	dir = rand() % 8;
}


Object::~Object()
{
	
}

void Object::SetSize(float size)
{
	fixel_size = size;
}

void Object::SetPosition(float x, float y, float z)
{
	position_x = x;
	position_y = y;
	position_z = z;
}

void Object::SetColor(float r, float g, float b, float a)
{
	red = r;
	green = g;
	blue = b;
	transparent = a;
}

void Object::SetSpeed(float s)
{
	speed = s;
}

void  Object::SetType(int t)
{
	type = t;
}

void Object::SetLife(int l)
{
	life = l;
}

void Object::Update(float time)
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

		if (position_y > 400)
			m_vY = -0.1;

		if (position_y < -400)
			m_vY = 0.1;
	
		SetPosition(position_x, position_y, 0);
	}

	if (type == OBJECT_BULLET || type == OBJECT_ARROW)
	{
		position_x = position_x + m_vX *  elapsedTime;
		position_y = position_y + m_vY *  elapsedTime;

		if (position_x < -250 || position_x > 250 || position_y < -400 || position_y > 400)
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

void Object::SetLevel(float level)
{
	draw_level = level;
};

float Object::GetpositionX()
{
	return position_x;
}

float Object::GetpositionY()
{
	return position_y;
}


float Object::GetpositionZ()
{
	return position_z;
}

float Object::GetLevel()
{
	return draw_level;
}


