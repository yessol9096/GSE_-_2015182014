#pragma once
#include "SceneMgr.h"
#include "Objcet.h"
#include "Renderer.h"


#define MAX_OBJECTS_COUNT 100


class SceneMgr
{
	int m_num;
public:
	SceneMgr();
	~SceneMgr();

	void add(int num);
	

	void draw();
	void update(float time);
	void release();
	void collision();
};

