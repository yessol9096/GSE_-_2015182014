#pragma once
#include "SceneMgr.h"
#include "Objcet.h"

#define MAX_OBJECTS_COUNT 100


class SceneMgr
{
	int m_num;
public:
	SceneMgr();
	~SceneMgr();

	void add(int num);
	void draw();
	void update();
	void release();
	void collision();
};

