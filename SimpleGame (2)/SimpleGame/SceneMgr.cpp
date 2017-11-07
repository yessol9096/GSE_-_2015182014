#include "stdafx.h"
#include "SceneMgr.h"
#include "Renderer.h"



Renderer *m_pRender;
int object_num;

SceneMgr::SceneMgr(int width, int height)
{
	// Initialize Renderer
	m_renderer = new Renderer(width, height);

	if (!m_renderer->IsInitialized())
	{
		std::cout << "SceneMgr::Renderer could not be initialized.. \n";
	}

	m_windowWidth = width;
	m_windowHeight = height;
}


SceneMgr::~SceneMgr()
{
}

void SceneMgr::add(float x, float y, int t)
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		if (m_objects[i] == NULL)
		{
			m_objects[i] = new Objcet(x,y,t);
	
			if (m_objects[i]->type == OBJECT_BUILDING)
			{
				m_objects[i]->SetSize(50);
				m_objects[i]->SetColor(1, 1, 0, 0);  
				m_objects[i]->SetSpeed(0);
				m_objects[i]->SetLife(500);
			}
			else if (m_objects[i]->type == OBJECT_CHARACTER)
			{
				m_objects[i]->SetSize(10);
				m_objects[i]->SetColor(1, 1, 1, 0);
				m_objects[i]->SetSpeed(100);
				m_objects[i]->SetLife(10);
			}
			else if (m_objects[i]->type == OBJECT_BULLET)
			{
				m_objects[i]->SetSize(2);
				m_objects[i]->SetColor(1, 0, 0, 0);
				m_objects[i]->SetSpeed(300);
				m_objects[i]->SetLife(20);
			}
			else if (m_objects[i]->type == OBJECT_ARROW)
			{
				m_objects[i]->SetSize(2);
				m_objects[i]->SetColor(0, 1, 0, 0);
				m_objects[i]->SetSpeed(100);
				m_objects[i]->SetLife(10);
			}
			break;
		}
	}
}

void SceneMgr::bulletmake(int x, int y)
{
	//add(x, y, OBJECT_BULLET);
}

void SceneMgr::draw()
{
	m_renderer->DrawSolidRect(0, 0, 0, m_windowWidth, 0, 0, 0, 0.4);

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
		m_renderer->DrawSolidRect(m_objects[i]->GetpositionX(), m_objects[i]->GetpositionY(), m_objects[i]->GetpositionZ(), m_objects[i]->fixel_size, m_objects[i]->red, m_objects[i]->green, m_objects[i]->blue, m_objects[i]->transparent);
	}
}

void SceneMgr::update(float time)
{
	int b_time = time;
	std::cout << b_time << std::endl;
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL && m_objects[i]->type == OBJECT_BUILDING && b_time % 5 == 0 )
		{
			float x = m_objects[i]->GetpositionX();
			float y = m_objects[i]->GetpositionY();
			add(x, y, OBJECT_BULLET);
		}


		if (m_objects[i] != NULL)
		{
			m_objects[i]->Update((float)time);
			//if (m_objects[i]->GetpositionX() > 250) || m_objects[i]->GetpositionX() < -250) //|| m_objects[i]->GetpositionY() > 250 || m_objects[i]->GetpositionY() < -250)
				//delete m_objects[i];
		}
		
	}
	collision();
}

void SceneMgr::release()
{
}

void SceneMgr::collision()
{
	int collisionCount = 0;

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		collisionCount = 0;
		if (m_objects[i] != NULL)
		{
			for (int j = 0; j < MAX_OBJECTS_COUNT; j++)
			{
				if (i == j)
					continue;

				if (m_objects[j] != NULL)
				{
					float minX, minY;
					float maxX, maxY;

					float minX1, minY1;
					float maxX1, maxY1;

					minX = m_objects[i]->GetpositionX() - m_objects[i]->fixel_size / 2.f;
					minY = m_objects[i]->GetpositionY() - m_objects[i]->fixel_size / 2.f;
					maxX = m_objects[i]->GetpositionX() + m_objects[i]->fixel_size / 2.f;
					maxY = m_objects[i]->GetpositionY() + m_objects[i]->fixel_size / 2.f;
					minX1 = m_objects[j]->GetpositionX() - m_objects[j]->fixel_size / 2.f;
					minY1 = m_objects[j]->GetpositionY() - m_objects[j]->fixel_size / 2.f;
					maxX1 = m_objects[j]->GetpositionX() + m_objects[j]->fixel_size / 2.f;
					maxY1 = m_objects[j]->GetpositionY() + m_objects[j]->fixel_size / 2.f;

					if (BoxBoxCollisionTest(minX, minY, maxX, maxY, minX1, minY1, maxX1, maxY1))
					{	// 빌딩 캐릭터간 충돌 
						if (m_objects[j]->type == OBJECT_BUILDING && m_objects[i]->type == OBJECT_CHARACTER)
							{
								m_objects[j]->SetLife(m_objects[j]->life - m_objects[i]->life);
								delete m_objects[i];	// 캐릭터삭제 
								if (m_objects[j]->life < 0) delete m_objects[j];	// 빌딩삭제
							}
						else if (m_objects[j]->type == OBJECT_CHARACTER && m_objects[i]->type == OBJECT_BULLET)	// 캐릭터 총알 충돌
						{
							m_objects[j]->SetLife(m_objects[j]->life - m_objects[i]->life);
							delete m_objects[i];	// 총알삭제 
							if (m_objects[j]->life < 0) delete m_objects[j];	// 빌딩삭제
						}
					}
				}
			}
		}
	}
}

bool SceneMgr::BoxBoxCollisionTest(float minX, float minY, float maxX, float maxY, float minX1, float minY1, float maxX1, float maxY1)
{
	if (minX > maxX1)
		return false;
	if (maxX < minX1)
		return false;

	if (minY > maxY1)
		return false;
	if (maxY < minY1)
		return false;

	return true;
}