#include "stdafx.h"
#include "SceneMgr.h"
#include "Renderer.h"


Objcet *m_objects[MAX_OBJECTS_COUNT];
int object_num;
Renderer *m_pRender;

SceneMgr::SceneMgr()
{
}


SceneMgr::~SceneMgr()
{
}

void SceneMgr::add(int num)
{
	object_num += num;
	for (int i = 0; i < num; ++i)
	{
		m_objects[i] = new Objcet;
		m_objects[i]->SetColor(1, 1, 1, 0);
		m_objects[i]->SetSize(50);
		if(i < 10)m_objects[i]->SetPosition(-1*rand()%250, -1*rand()%250, 0);
		else if(i > 10 &&i < 20)m_objects[i]->SetPosition(rand() % 250, -1 * rand() % 250, 0);
		else if (i > 20 && i < 30)m_objects[i]->SetPosition(rand() % 250, -1 * rand() % 250, 0);
		else if (i > 30 && i < 40)m_objects[i]->SetPosition(-1*rand() % 250, rand() % 250, 0);
		else m_objects[i]->SetPosition(rand() % 250, rand() % 250, 0);
		m_objects[i]->SetSpeed(2);
	}
}

void SceneMgr::draw()
{
	m_pRender = new Renderer(500, 500);
	for (int i = 0; i < object_num; ++i)
	{
		{
			m_pRender->DrawSolidRect(m_objects[i]->GetpositionX(), m_objects[i]->GetpositionY(), m_objects[i]->GetpositionZ(), m_objects[i]->fixel_size, m_objects[i]->red, m_objects[i]->green, m_objects[i]->blue, m_objects[i]->transparent);
		}
	}
}

void SceneMgr::update(float time)
{
	for (int i = 0; i < object_num; ++i)
	{
		m_objects[i]->Update(time);
	}
}

void SceneMgr::release()
{
	delete[] m_objects;
}

void SceneMgr::collision()
{
	for (int i = 0; i < object_num; ++i)
	{
		for (int j = i; i < object_num; ++j)
		{
			float x1 = m_objects[i]->GetpositionX();
			float left1 = x1 - m_objects[i]->fixel_size/2;
			float right1 = x1 + m_objects[i]->fixel_size / 2;

			float y1 = m_objects[i]->GetpositionY();
			float top1 = y1 + m_objects[i]->fixel_size / 2;
			float bottom1 = y1 - m_objects[i]->fixel_size / 2; 
			float x2 = m_objects[j]->GetpositionX();
			float left2 = x2 - m_objects[i]->fixel_size / 2;
			float right2 = x2 + m_objects[i]->fixel_size / 2;

			float y2 = m_objects[j]->GetpositionY();
			float top2 = y2 + m_objects[i]->fixel_size / 2;
			float bottom2 = y2 - m_objects[i]->fixel_size / 2;

			if (left1 < right2 && top1 < bottom2 && right1 > left2 && bottom1 > top2)
			{
				m_objects[i]->SetColor(1, 0, 0, 0);
				m_objects[j]->SetColor(1, 0, 0, 0);
			}
		}
	}
}
