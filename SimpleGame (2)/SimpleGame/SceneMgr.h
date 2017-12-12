#pragma once
#include "Object.h"
#include <iostream>

#define MAX_OBJECTS_COUNT 10000


#define	OBJECT_BUILDING	 0
#define	OBJECT_CHARACTER 1
#define	OBJECT_BULLET	 2
#define	OBJECT_ARROW	 3

#define TEAM_1			 1
#define TEAM_2			 2

#define LEVEL_GOD		 0
#define LEVEL_SKY		 0.1	
#define LEVEL_GROUND     0.2
#define LEVEL_UNDERGROUND 0.3	
#define LEVEL_BACKGROUND 0.4



class SceneMgr
{
	int m_num;
public:
	SceneMgr(int width, int height);
	~SceneMgr();

	
	int add(float x, float y, int type, int team);
	

	void draw();
	void update(float time);
	void release();
	void collision();

	bool BoxBoxCollisionTest(float minX, float minY, float maxX, float maxY, float minX1, float minY1, float maxX1, float maxY1);

	Renderer *m_renderer;
	Object* m_objects[MAX_OBJECTS_COUNT];
	int m_windowWidth;
	int m_windowHeight;
};

