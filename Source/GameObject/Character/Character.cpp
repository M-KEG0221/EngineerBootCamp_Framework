#include "Character.h"

#include "DxLib.h"

Character::Character()
	:
	graphic_handle_idle{ 0,0,0,0 },
	graphic_idle_flame(0)
{
}

Character::~Character()
{
	Finalize();
}

void Character::Initialize()
{
	__super::Initialize();

	// 画像の読み込みsad
	LoadDivGraph(_T("Resources/Images/collon_wait_a.bmp"), idleMaxFlame, idleMaxFlame, 1, 128, 128, graphic_handle_idle);
}

void Character::Update(float delta_seconds)
{
	__super::Update(delta_seconds);

	// 動かす
	Vector2D input_dir;
	if (CheckHitKey(KEY_INPUT_A) == 1)
	{
		input_dir.x = -1;
	}
	else if (CheckHitKey(KEY_INPUT_D) == 1)
	{
		input_dir.x = 1;
	}

	/*if (CheckHitKey(KEY_INPUT_W) == 1)
	{
		input_dir.y = -1;
	}
	else if (CheckHitKey(KEY_INPUT_S) == 1)
	{
		input_dir.y = 1;
	}*/

	const float MOVEMENT_SPEED = 300.0f;
	Vector2D delta_position = input_dir.Normalize() * MOVEMENT_SPEED * delta_seconds;
	SetPosition(GetPosition() + delta_position);
}

void Character::Draw(const Vector2D& screen_offset)
{
	__super::Draw(screen_offset);

	// 画像の描画
	int x, y;
	GetPosition().ToInt(x, y);

	if (flame_adjust >= idleFlameDelay)//60f立ったら瞬きモーションに入る
	{
		graphic_idle_flame++;
		printfDx("@@\n");
	}
	if (graphic_idle_flame == idleMaxFlame)//最後の瞬きモーションが終わったらリセットする
	{
		flame_adjust = 0;
		graphic_idle_flame = 0;
		printfDx("リセット\n");
	}

	flame_adjust++;
	printfDx("%d\n",flame_adjust);
	DrawGraph(x, y, graphic_handle_idle[graphic_idle_flame], true);
}

void Character::Finalize()
{
	__super::Finalize();

	for (int graphic : graphic_handle_idle)
	{
	 //画像の破棄
		DeleteGraph(graphic);
		graphic = 0;
	}
}