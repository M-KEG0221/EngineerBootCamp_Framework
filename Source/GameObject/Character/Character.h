#pragma once
#include "../GameObject.h"

/**
 * �T���v���I�u�W�F�N�g
 * �T���v���p�ɊȈՓI�Ɏ���
 */
class Character : public GameObject
{
public:
	Character();
	virtual ~Character();

public:
	//~ Begin GameObject interface
	virtual void Initialize() override;
	void Update(float delta_seconds) override;
	void Draw(const Vector2D& screen_offset) override;
	void Finalize() override;
	//~ End GameObject interface

private:
	const static int idleMaxFlame = 4;
	const static int idleFlameDelay = 120;// �܂΂����A�j���[�V�����ɓ���܂ł̎���
	int flame_adjust = 0;// delay�����ăt���[���J�ڂ��邽�߂̒l
	int graphic_handle_idle[idleMaxFlame];
	int graphic_idle_flame;

	int hp;
};

