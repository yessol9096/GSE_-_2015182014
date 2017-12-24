#pragma once
#include "Renderer.h"
#include <ctime>
#include <cstdlib>
class Renderer;


class Object
{
public:
	Object(float x, float y , int type, int team);
	virtual ~Object();

private:
	// 오브젝트 위치
	float position_x;
	float position_y;
	float position_z;
	// 오브젝트 크기
	float draw_level;

public:
	float fixel_size;
	float red;
	float green;
	float blue;
	float transparent;
	float speed;
	float life;
	float life_time;
	
	float p_time;
	bool p_time_plus = true;
	float m_vX = 0.1;
	float m_vY = 0.1;
	int melee;
	int type;
	int team;
	int dir;
public:
	bool LbuttonDown;
public:
	void SetSize(float size);
	void SetPosition(float x, float y, float z);
	void SetType(int t);
	void SetLife(int l);
	void SetColor(float r, float g, float b, float a);
	void SetLevel(float level);

	float GetpositionX();
	float GetpositionY();
	float GetpositionZ();
	float GetLevel();
	void SetSpeed(float s);
	void Update(float time);
	
	
	float last_bullet_time = 0.f;
	float last_arrow_time = 0.f;
	
	int parent_num;
};

