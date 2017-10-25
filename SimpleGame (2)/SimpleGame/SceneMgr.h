#pragma once
#include "SceneMgr.h"
#include "Objcet.h"
#include "Renderer.h"
#include <cstdlib>
#include <iostream>

#define MAX_OBJECTS_COUNT 100

class SceneMgr
{
	int m_num;
public:
	SceneMgr(int width, int height);
	~SceneMgr();

	void add(int x, int y);
	

	void draw();
	void update(DWORD time);
	void release();
	void collision();
	bool BoxBoxCollisionTest(float minX, float minY, float maxX, float maxY, float minX1, float minY1, float maxX1, float maxY1);

	Renderer *m_renderer;
	Objcet *m_objects[MAX_OBJECTS_COUNT];
	int m_windowWidth;
	int m_windowHeight;
};

