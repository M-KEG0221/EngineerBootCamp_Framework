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

	// �摜�̓ǂݍ���
	LoadDivGraph(_T("Resources/Images/collon_wait_a.bmp"), maxIdleFlame, maxIdleFlame, 1, 128, 128, graphicHandleIdle);
	LoadDivGraph(_T("Resources/Images/collon_run8.bmp"), maxRunFlame, 4, 2, 128, 128, graphicHandleRun);
}

void Character::Update(float delta_seconds)
{
	__super::Update(delta_seconds);

	// ������
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

	// �摜�̕`��
	int x, y;
	GetPosition().ToInt(x, y);
	boolean canMoveNextWinkFlame = (idleFlameAdjust - idleFlameDelay) % winkFlameDelay == 0;

	switch (getState()) 
	{
		case playerState::IDLE:

			if (idleFlameAdjust >= idleFlameDelay && canMoveNextWinkFlame)//120f��������u�����[�V�����ɓ���B5f���ƂɃt���[���𓮂���
			{
				graphicIdleFlame++;
				printfDx("@@\n");
			}
			if (graphicIdleFlame == maxIdleFlame)//�Ō�̏u�����[�V�������I������烊�Z�b�g����
			{
				idleFlameAdjust = 0;
				graphicIdleFlame = 0;
				printfDx("���Z�b�g\n");
			}

			idleFlameAdjust++;
			//if(idleFlameAdjust - idleFlameDelay )//125, 130, 135
			DrawGraph(x, y, graphicHandleIdle[graphicIdleFlame], true);
			break;

		case playerState::RUN:
			if (runFlameAdjust == runFlameDelay)//10f�������玟�̃��[�V�����Ɉڂ�
			{
				runFlameAdjust = 0;
				graphicRunFlame++;
			}
			if (graphicRunFlame == maxRunFlame)//�Ō�̏u�����[�V�������I������烊�Z�b�g����
			{
				graphicRunFlame = 0;
			}

			runFlameAdjust++;

			//���E���]�����B���������̂܂܂��ƃL�[�𔽓]���Ă��r����flame����`�悳��邽�ߒ���
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
	 //�摜�̔j��
		DeleteGraph(graphic);
		graphic = 0;
	}
}