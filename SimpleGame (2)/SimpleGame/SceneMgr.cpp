#include "stdafx.h"
#include "SceneMgr.h"
#include "Renderer.h"
#include "Sound.h"
#include <stdlib.h>

Renderer *m_pRender;
int object_num;
float ani_index;
float ch_index;
float weather_time = 0.f;
Sound *m_sound;
Sound *e_sound;
Sound *p_sound;
Sound *d_sound;
float background_ID;
float character_ID ;
float snow_ID ;
float castle1_ID;
float castle2_ID ;
float particle1_ID;
float particle2_ID;
float melee_ID;
float explosion;
float punch;
float soundBG;
float gameover;


int die_1 = 0;
int die_2 = 0;

SceneMgr::SceneMgr(int width, int height)
{
	m_renderer = new Renderer(width, height);

	if (!m_renderer->IsInitialized())
	{
		std::cout << "SceneMgr::Renderer could not be initialized.. \n";
	}

	m_sound = new Sound();
	soundBG = m_sound->CreateSound("bgm.mp3");
	
	e_sound = new Sound();
	explosion = e_sound->CreateSound("explosion.wav");

	p_sound = new Sound();
	punch = p_sound->CreateSound("PUNCH.wav");

	d_sound = new Sound();
	gameover = d_sound->CreateSound("died.wav");

	background_ID = m_renderer->CreatePngTexture("background.png");
	character_ID = m_renderer->CreatePngTexture("Character.png");
	snow_ID = m_renderer->CreatePngTexture("snow.png");
	castle1_ID = m_renderer->CreatePngTexture("TEAM_1CASTLE.png");
	castle2_ID = m_renderer->CreatePngTexture("TEAM_2CASTLE.png");
	particle1_ID = m_renderer->CreatePngTexture("particle_Team1.png");
	particle2_ID = m_renderer->CreatePngTexture("particle_Team2.png");
	melee_ID = m_renderer->CreatePngTexture("MELEE.png");

	m_sound->PlaySound(soundBG, true, 0.7f);


	m_windowWidth = width;
	m_windowHeight = height;
}


SceneMgr::~SceneMgr()
{
}

int SceneMgr::add(float x, float y, int type, int team)
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		if (m_objects[i] == NULL)
		{
			m_objects[i] = new Object(x, y, type, team);
			return i;
		}
	}
	return -1;
}
void SceneMgr::draw()
{
	std::cout << die_2 << std::endl;
	char array[10];
	weather_time += 0.001;
	ani_index += 0.03;
	if (ch_index == 12)
	{
		ch_index = 0;
	}
	else if (ani_index > 1)
	{
		ch_index += 1;
		ani_index = 0;
	}
	m_renderer->DrawTexturedRect(0, 0, 0, 800, 1, 1, 1, 1, background_ID, LEVEL_BACKGROUND);
	if (die_1 == 3)
	{
		m_sound->DeleteSound(soundBG);
		d_sound->PlaySound(gameover, false, 0.7f);
		m_renderer->DrawTextW(-10, 0, GLUT_BITMAP_HELVETICA_12, 1, 0, 0, "TEAM_2 WIN!");
		d_sound->DeleteSound(gameover);
	}
	else if (die_2 == 3)
	{
		m_sound->DeleteSound(soundBG);
		d_sound->PlaySound(gameover, false, 0.7f);
		m_renderer->DrawTextW(-10, 0, GLUT_BITMAP_HELVETICA_12, 1, 0, 0, "TEAM_1 WIN!");
		d_sound->DeleteSound(gameover);
	}
	
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
		{
			if ( m_objects[i]->type == OBJECT_CHARACTER)
			{
				m_renderer->DrawTexturedRectSeq(m_objects[i]->GetpositionX(), m_objects[i]->GetpositionY(), m_objects[i]->GetpositionZ(), 64, m_objects[i]->red, m_objects[i]->green, m_objects[i]->blue, m_objects[i]->transparent, character_ID, ch_index, 0, 12, 1, m_objects[i]->GetLevel());
				m_renderer->DrawParticle(m_objects[i]->GetpositionX(), m_objects[i]->GetpositionY()-10, m_objects[i]->GetpositionZ(), 5, 1, 1, 1, 1, 0, -1, snow_ID , m_objects[i]->p_time, m_objects[i]->GetLevel());
				{
					if (m_objects[i]->team == TEAM_1)
						m_renderer->DrawSolidRectGauge(m_objects[i]->GetpositionX(), m_objects[i]->GetpositionY() - 25, m_objects[i]->GetpositionZ(), 40, 5, 1, 0, 0, 1, (m_objects[i]->life) / 100.f, m_objects[i]->GetLevel());
					if (m_objects[i]->team == TEAM_2)
						m_renderer->DrawSolidRectGauge(m_objects[i]->GetpositionX(), m_objects[i]->GetpositionY() - 25, m_objects[i]->GetpositionZ(), 40, 5, 0, 0, 1, 1, (m_objects[i]->life) / 100.f, m_objects[i]->GetLevel());
				}
			}
			else if (m_objects[i]->type == OBJECT_MELEEATTACK)
			{
				m_renderer->DrawTexturedRectSeq(m_objects[i]->GetpositionX(), m_objects[i]->GetpositionY(), m_objects[i]->GetpositionZ(), 64, m_objects[i]->red, m_objects[i]->green, m_objects[i]->blue, m_objects[i]->transparent, melee_ID, ch_index, 0, 6, 1, m_objects[i]->GetLevel());
				m_renderer->DrawParticle(m_objects[i]->GetpositionX(), m_objects[i]->GetpositionY() - 10, m_objects[i]->GetpositionZ(), 5, 1, 1, 1, 1, 0, -1, snow_ID, m_objects[i]->p_time, m_objects[i]->GetLevel());
				{
					if (m_objects[i]->team == TEAM_1)
						m_renderer->DrawSolidRectGauge(m_objects[i]->GetpositionX(), m_objects[i]->GetpositionY() - 25, m_objects[i]->GetpositionZ(), 40, 5, 1, 0, 0, 1, (m_objects[i]->life) / 100.f, m_objects[i]->GetLevel());
					if (m_objects[i]->team == TEAM_2)
						m_renderer->DrawSolidRectGauge(m_objects[i]->GetpositionX(), m_objects[i]->GetpositionY() - 25, m_objects[i]->GetpositionZ(), 40, 5, 0, 0, 1, 1, (m_objects[i]->life) / 100.f, m_objects[i]->GetLevel());
				}
			}
			else if (m_objects[i]->type == OBJECT_BUILDING && m_objects[i]->team == TEAM_1)
			{
				m_renderer->DrawSolidRectGauge(m_objects[i]->GetpositionX(), m_objects[i]->GetpositionY() - 70, m_objects[i]->GetpositionZ(), 100, 10, 1, 0, 0, 1, (m_objects[i]->life) / 500.f, m_objects[i]->GetLevel());
				m_renderer->DrawTexturedRect(m_objects[i]->GetpositionX(), m_objects[i]->GetpositionY(), m_objects[i]->GetpositionZ(), m_objects[i]->fixel_size, m_objects[i]->red, m_objects[i]->green, m_objects[i]->blue, m_objects[i]->transparent, castle1_ID, m_objects[i]->GetLevel());
				snprintf(array, 10, "%d", (int)m_objects[i]->life);
				m_renderer->DrawTextW(m_objects[i]->GetpositionX()-5, m_objects[i]->GetpositionY() - 20, GLUT_BITMAP_HELVETICA_12, 0, 0, 0, array);
			}
			else if (m_objects[i]->type == OBJECT_BUILDING && m_objects[i]->team == TEAM_2)
			{
				m_renderer->DrawSolidRectGauge(m_objects[i]->GetpositionX(), m_objects[i]->GetpositionY() - 70, m_objects[i]->GetpositionZ(), 100, 10, 0, 0, 1, 1, (m_objects[i]->life) / 500.f, m_objects[i]->GetLevel());
				m_renderer->DrawTexturedRect(m_objects[i]->GetpositionX(), m_objects[i]->GetpositionY(), m_objects[i]->GetpositionZ(), m_objects[i]->fixel_size, m_objects[i]->red, m_objects[i]->green, m_objects[i]->blue, m_objects[i]->transparent, castle2_ID, m_objects[i]->GetLevel());
				snprintf(array, 10, "%d", (int)m_objects[i]->life);
				m_renderer->DrawTextW(m_objects[i]->GetpositionX()-5, m_objects[i]->GetpositionY() - 20, GLUT_BITMAP_HELVETICA_12, 0, 0, 0, array);
			}
			else if (m_objects[i]->type == OBJECT_BULLET && m_objects[i]->team == TEAM_1)
			{
				if (m_objects[i]->p_time_plus)m_objects[i]->p_time += 0.0003; else m_objects[i]->p_time -= 0.005;
				if (m_objects[i]->p_time > 1000)m_objects[i]->p_time_plus = false;
				m_renderer->DrawSolidRect(m_objects[i]->GetpositionX(), m_objects[i]->GetpositionY(), m_objects[i]->GetpositionZ(), m_objects[i]->fixel_size, m_objects[i]->red, m_objects[i]->green, m_objects[i]->blue, m_objects[i]->transparent, m_objects[i]->GetLevel());
				m_renderer->DrawParticle(m_objects[i]->GetpositionX(), m_objects[i]->GetpositionY(), m_objects[i]->GetpositionZ(), 17, 1, 1, 1, 1, -(m_objects[i]->m_vX), -(m_objects[i]->m_vY), particle1_ID, m_objects[i]->p_time, m_objects[i]->GetLevel());
			}
			else if (m_objects[i]->type == OBJECT_BULLET && m_objects[i]->team == TEAM_2)
			{
				if (m_objects[i]->p_time_plus)m_objects[i]->p_time += 0.0003; else m_objects[i]->p_time -= 0.005;
				if (m_objects[i]->p_time > 1000)m_objects[i]->p_time_plus = false;
				m_renderer->DrawSolidRect(m_objects[i]->GetpositionX(), m_objects[i]->GetpositionY(), m_objects[i]->GetpositionZ(), m_objects[i]->fixel_size, m_objects[i]->red, m_objects[i]->green, m_objects[i]->blue, m_objects[i]->transparent, m_objects[i]->GetLevel());
				m_renderer->DrawParticle(m_objects[i]->GetpositionX(), m_objects[i]->GetpositionY(), m_objects[i]->GetpositionZ(), 15, 1, 1, 1, 1, -(m_objects[i]->m_vX), -(m_objects[i]->m_vY), particle2_ID, m_objects[i]->p_time, m_objects[i]->GetLevel());
			}
			else 
			{
				m_renderer->DrawSolidRect(m_objects[i]->GetpositionX(), m_objects[i]->GetpositionY(), m_objects[i]->GetpositionZ(), m_objects[i]->fixel_size, m_objects[i]->red, m_objects[i]->green, m_objects[i]->blue, m_objects[i]->transparent, m_objects[i]->GetLevel());
			}
		}
	}
	m_renderer->DrawParticleClimate(0, 0, 0, 5, 1, 1, 1, 1, -0.1, -0.1, particle2_ID, weather_time, LEVEL_GOD);
}
float last_character_time = 0.f;
float last_melee_time = 0.f;

void SceneMgr::update(float time)
{
	if (die_1 != 3 && die_2 != 3)
	{
		if (last_character_time > 5.f)
		{
			add((-1)*rand() % 200, rand() % 400, OBJECT_CHARACTER, TEAM_1);
			last_character_time = 0.f;
		}
		else
			last_character_time += time / 1000.f;

		if (last_melee_time > 8.f)
		{
			add((-1)*rand() % 200, rand() % 400, OBJECT_MELEEATTACK, TEAM_1);
			last_melee_time = 0.f;
		}
		else
			last_melee_time += time / 1000.f;

		for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		{
			if (m_objects[i] != NULL && m_objects[i]->life > 0)
			{
				m_objects[i]->Update(time);
			}
			else
			{
				delete m_objects[i];
				m_objects[i] = NULL;
			}
			if (m_objects[i] != NULL && m_objects[i]->type == OBJECT_BUILDING && m_objects[i]->last_bullet_time > 5.f)
			{
				float x = m_objects[i]->GetpositionX();
				float y = m_objects[i]->GetpositionY();

				int team = m_objects[i]->team;
				int num = add(x, y, OBJECT_BULLET, team);
				m_objects[num]->p_time = 0.f;
				m_objects[num]->p_time_plus = true;
				if (num >= 0) m_objects[num]->parent_num = i;
				m_objects[i]->last_bullet_time = 0.f;
			}
			if (m_objects[i] != NULL && m_objects[i]->type == OBJECT_CHARACTER && m_objects[i]->last_arrow_time > 3.f)
			{
				float x = m_objects[i]->GetpositionX();
				float y = m_objects[i]->GetpositionY();
				int team = m_objects[i]->team;
				int num = add(x, y, OBJECT_ARROW, team);
				if (num >= 0) m_objects[num]->parent_num = i;
				m_objects[i]->last_arrow_time = 0.f;
			}
		}
		collision();
	}
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
					{	
						if (m_objects[i]->team != m_objects[j]->team)
						{
							if (m_objects[j]->type == OBJECT_BUILDING && m_objects[i]->type == OBJECT_CHARACTER)	// 빌딩 캐릭터간 충돌 
							{
								p_sound->PlaySound(punch, false, 1.f);
								m_objects[j]->SetLife(m_objects[j]->life - m_objects[i]->life);
								m_objects[i]->SetLife(-1);// 캐릭터삭제 
								if (m_objects[j]->life < 0 || m_objects[j]->life == 0)
								{
									e_sound->PlaySound(explosion, false, 1.f);
									if (m_objects[j]->team == TEAM_1)	die_1++;
									else if (m_objects[j]->team == TEAM_2)	die_2++;
								}
							}
							else if (m_objects[j]->type == OBJECT_BUILDING && m_objects[i]->type == OBJECT_MELEEATTACK)	// 빌딩 근접공격캐릭터 충돌
							{
								p_sound->PlaySound(punch, false, 1.f);
								m_objects[j]->SetLife(m_objects[j]->life - m_objects[i]->life);
								m_objects[i]->SetLife(-1);// 캐릭터삭제 
								if (m_objects[j]->life < 0 || m_objects[j]->life == 0)
								{
									e_sound->PlaySound(explosion, false, 1.f);
									if (m_objects[j]->team == TEAM_1)	die_1++;
									else if (m_objects[j]->team == TEAM_2)	die_2++;
								}
							}
							else if (m_objects[j]->type == OBJECT_BUILDING && m_objects[i]->type == OBJECT_BULLET)	// 빌딩 총알 충돌 
							{
							
								m_objects[j]->SetLife(m_objects[j]->life - m_objects[i]->life);
								m_objects[i]->SetLife(-1);// 총알삭제 
								if (m_objects[j]->life < 0 || m_objects[j]->life == 0)
								{
									e_sound->PlaySound(explosion, false, 1.f);
									if (m_objects[j]->team == TEAM_1)	die_1++;
									else if (m_objects[j]->team == TEAM_2)	die_2++;
								}
							}
							else if (m_objects[j]->type == OBJECT_CHARACTER && m_objects[i]->type == OBJECT_BULLET && m_objects[i]->parent_num != j)	// 캐릭터 총알 충돌
							{
								m_objects[j]->SetLife(m_objects[j]->life - m_objects[i]->life);
								m_objects[i]->SetLife(-1);	// 총알삭제 
							}
							else if (m_objects[j]->type == OBJECT_MELEEATTACK && m_objects[i]->type == OBJECT_BULLET && m_objects[i]->parent_num != j)		//  근접공격 총알 충돌
							{
								m_objects[j]->SetLife(m_objects[j]->life - m_objects[i]->life);
								m_objects[i]->SetLife(-1);	// 총알삭제 
							}

							else if (m_objects[j]->type == OBJECT_CHARACTER && m_objects[i]->type == OBJECT_ARROW && m_objects[i]->parent_num != j)	// 캐릭터 화살 충돌
							{
								m_objects[j]->SetLife(m_objects[j]->life - m_objects[i]->life);
								m_objects[i]->SetLife(-1);	// 화살삭제 
							}
							else if (m_objects[j]->type == OBJECT_MELEEATTACK  && m_objects[i]->type == OBJECT_ARROW && m_objects[i]->parent_num != j)	// 근접공격 화살 충돌
							{
								m_objects[j]->SetLife(m_objects[j]->life - m_objects[i]->life);
								m_objects[i]->SetLife(-1);	// 화살삭제 
							}
							else if (m_objects[j]->type == OBJECT_BUILDING && m_objects[i]->type == OBJECT_ARROW)	// 빌딩 화살 충돌
							{
							
								m_objects[j]->SetLife(m_objects[j]->life - m_objects[i]->life);
								m_objects[i]->SetLife(-1);	// 화살삭제 
								if (m_objects[j]->life < 0 || m_objects[j]->life == 0)
								{
									e_sound->PlaySound(explosion, false, 1.f);
									if (m_objects[j]->team == TEAM_1)	die_1++;
									else if (m_objects[j]->team == TEAM_2)	die_2++;
								}
							}
							else if (m_objects[j]->type == OBJECT_CHARACTER && m_objects[i]->type == OBJECT_MELEEATTACK)	// 캐릭터 근접공격캐릭터 충돌
							{
								p_sound->PlaySound(punch, false, 1.f);
								m_objects[j]->SetLife(-1);
								m_objects[i]->SetLife(-1);// 캐릭터삭제 
							}
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