#pragma once
#include "Renderer.h"

class Renderer;



class Objcet
{
public:
	Objcet();
	virtual ~Objcet();

private:
	// ������Ʈ ��ġ
	float position_x;
	float position_y;
	float position_z;
	// ������Ʈ ũ��
	float fixel_size;
	

	float red;
	float green;
	float blue;
	float transparent;

public:
	//struct float3f GetPosition();
	
	void SetSize(float size);
	void SetPosition(float x, float y, float z);
	void SetColor(float r, float g, float b, float a);

	virtual void DrawObject();
	
};

