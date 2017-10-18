#include "stdafx.h"
#include "SceneMgr.h"

Objcet *m_objects[MAX_OBJECTS_COUNT];
int object_num;
SceneMgr::SceneMgr()
{
}


SceneMgr::~SceneMgr()
{
}

void SceneMgr::add(int num)
{
	object_num = num;
	for (int i = 0; i < num; ++i)
	{
		m_objects[i] = new Objcet;
		m_objects[i]->SetColor(1, 1, 1, 0);
		m_objects[i]->SetSize(10);
		if(i < 10)m_objects[i]->SetPosition(-1*rand()%250, -1*rand()%250, 0);
		else if(i > 10 &&i < 20)m_objects[i]->SetPosition(rand() % 250, -1 * rand() % 250, 0);
		else if (i > 20 && i < 30)m_objects[i]->SetPosition(rand() % 250, -1 * rand() % 250, 0);
		else if (i > 30 && i < 40)m_objects[i]->SetPosition(-1*rand() % 250, rand() % 250, 0);
		else m_objects[i]->SetPosition(rand() % 250, rand() % 250, 0);
		m_objects[i]->SetSpeed(1);
	}
}

void SceneMgr::draw()
{
	for (int i = 0; i < object_num; ++i)
	{
		m_objects[i]->DrawObject();
	}
}

void SceneMgr::update()
{
	for (int i = 0; i < object_num; ++i)
	{
		m_objects[i]->Update();
	}
}

void SceneMgr::release()
{
	delete m_objects;
}

void SceneMgr::collision()
{

}