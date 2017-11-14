#pragma once
#include "Renderer.h"
#include <ctime>
#include <cstdlib>
class Renderer;

class Objcet
{
public:
	Objcet(float x, float y , int type);
	virtual ~Objcet();

private:
	// 오브젝트 위치
	float position_x;
	float position_y;
	float position_z;
	// 오브젝트 크기
	

public:
	float fixel_size;
	float red;
	float green;
	float blue;
	float transparent;
	float speed;
	float life;
	float life_time;

	float m_vX = 0.1;
	float m_vY = 0.1;
	int type;
	int dir;
public:
	bool LbuttonDown;
public:
	//struct float3f GetPosition();

	void SetSize(float size);
	void SetPosition(float x, float y, float z);
	void SetType(int t);
	void SetLife(int l);
	void SetColor(float r, float g, float b, float a);

	float GetpositionX();
	float GetpositionY();
	float GetpositionZ();
	void SetSpeed(float s);
	void Update(float time);
	
	
	float last_bullet_time = 0.f;
	float last_arrow_time = 0.f;

	int parent_num;
};

