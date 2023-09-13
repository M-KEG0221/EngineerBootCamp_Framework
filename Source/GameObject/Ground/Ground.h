#pragma once
#include "../GameObject.h"
#include <iostream>
#include <vector>

using namespace std;

class Ground :
	public GameObject
{
public:
	Ground();
	Ground(int width, int height);
	~Ground();

	//~ Begin GameObject interface
	void Initialize() override;
	void Update(float delta_seconds) override;
	void Draw(const Vector2D& screen_offset) override;
	void Finalize() override;
	//~ End GameObject interface

	void SetGroundData(const vector<int>& new_ground_data) { ground_data = new_ground_data; };
protected:
private:
	vector<int> ground_data;
	int stage_width;
	int stage_height;
	const int GROUND_SIDE_PX_LENGTH = 32;//�n�ʉ摜�̈�ӂ̃T�C�Y
	const int TOP_GROUND_PX_HEIGHT = 48;//��Ӓn�ʉ摜�̏c�T�C�Y
	int ground_graphics[9] = { 0,0,0,0,0,0,0,0,0, };
	// 
};