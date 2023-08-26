#include "Character.h"

#include "DxLib.h"

Character::Character()
	:
	graphicHandleIdle{ 0,0,0,0 },
	graphicIdleFlame(0)
{
}

Character::~Character()
{
	Finalize();
}

void Character::Initialize()
{
	__super::Initialize();

	// 画像の読み込み
	LoadDivGraph(_T("Resources/Images/collon_wait_a.bmp"), maxIdleFlame, maxIdleFlame, 1, 128, 128, graphicHandleIdle);
	LoadDivGraph(_T("Resources/Images/collon_run8.bmp"), maxRunFlame, 4, 2, 128, 128, graphicHandleRun);
}

void Character::Update(float delta_seconds)
{
	__super::Update(delta_seconds);

	// 動かす
	Vector2D input_dir;
	if (CheckHitKey(KEY_INPUT_A) == 1)
	{
		input_dir.x = -1;
		onEnterPlayerState(playerState::RUN);
	}
	else if (CheckHitKey(KEY_INPUT_D) == 1)
	{
		input_dir.x = 1;
		onEnterPlayerState(playerState::RUN);
	}
	else
	{
		onEnterPlayerState(playerState::IDLE);
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
	boolean canMoveNextWinkFlame = (idleFlameAdjust - idleFlameDelay) % winkFlameDelay == 0;

	switch (getState()) 
	{
		case playerState::IDLE:

			if (idleFlameAdjust >= idleFlameDelay && canMoveNextWinkFlame)//120fたったら瞬きモーションに入る。5fごとにフレームを動かす
			{
				graphicIdleFlame++;
				printfDx("@@\n");
			}
			if (graphicIdleFlame == maxIdleFlame)//最後の瞬きモーションが終わったらリセットする
			{
				idleFlameAdjust = 0;
				graphicIdleFlame = 0;
				printfDx("リセット\n");
			}

			idleFlameAdjust++;
			//if(idleFlameAdjust - idleFlameDelay )//125, 130, 135
			DrawGraph(x, y, graphicHandleIdle[graphicIdleFlame], true);
			break;

		case playerState::RUN:
			if (runFlameAdjust == runFlameDelay)//10f立ったら次のモーションに移る
			{
				runFlameAdjust = 0;
				graphicRunFlame++;
			}
			if (graphicRunFlame == maxRunFlame)//最後の瞬きモーションが終わったらリセットする
			{
				graphicRunFlame = 0;
			}

			runFlameAdjust++;

			//左右反転処理。ただしこのままだとキーを反転しても途中のflameから描画されるため注意
			if(CheckHitKey(KEY_INPUT_A))
			{
				DrawTurnGraph(x, y, graphicHandleRun[graphicRunFlame], true);
			}
			else if(CheckHitKey(KEY_INPUT_D) == 1)
			{
				DrawGraph(x, y, graphicHandleRun[graphicRunFlame], true);
			}
			break;

	}

}

void Character::Finalize()
{
	__super::Finalize();

	for (int graphic : graphicHandleIdle)
	{
	 //画像の破棄
		DeleteGraph(graphic);
		graphic = 0;
	}
}