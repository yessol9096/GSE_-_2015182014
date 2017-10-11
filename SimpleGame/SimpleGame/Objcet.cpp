#include "stdafx.h"
#include "Renderer.h"
#include "Objcet.h"

Renderer *m_pRender;

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
	m_pRender = new Renderer(500, 500);
	m_pRender->DrawSolidRect(position_x, position_y, position_z, fixel_size, red, green, blue, transparent);
}

void Objcet::SetSpeed(float s)
{
	speed = s;
}

void Objcet::Update()
{


	float update_position_x = position_x + speed * 1;
	float update_position_y = position_y + speed * 1;

	SetPosition(update_position_x, update_position_y, 0);
}


