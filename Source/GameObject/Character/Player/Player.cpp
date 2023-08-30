#include "Player.h"

#include "DxLib.h"

Player::Player()
	:graphicIdleFlame(0)
	//graphicHandleIdle(maxIdleFlame)
{
}

Player::~Player()
{
	//Finalize();
}

void Player::Initialize()
{
	__super::Initialize();

	// �摜�̓ǂݍ���
	// HACK: �O���t�B�b�N�}�l�[�W���[��������璼��
	LoadDivGraph(_T("Resources/Images/collon_wait_a.bmp"), maxIdleFlame, maxIdleFlame, 1, 128, 128, graphicHandleIdle);
	LoadDivGraph(_T("Resources/Images/collon_run8.bmp"), maxRunFlame, 4, 2, 128, 128, graphicHandleRun);
}

void Player::Update(float delta_seconds)
{
	__super::Update(delta_seconds);

	// ������
	Vector2D input_dir;
	if (CheckHitKey(KEY_INPUT_A) == 1)
	{
		input_dir.x = -1;
		ChangePlayerState(PlayerState::RUN);
		SetDirectionState(DirectionState::LEFT);
	}
	else if (CheckHitKey(KEY_INPUT_D) == 1)
	{
		input_dir.x = 1;
		ChangePlayerState(PlayerState::RUN);
		SetDirectionState(DirectionState::RIGHT);
	}
	else
	{
		ChangePlayerState(PlayerState::IDLE);
		hp--;
	}

	/*if (CheckHitKey(KEY_INPUT_W) == 1)
	{
		//TODO: jump
		input_dir.y = -1; 
	}
	else if (CheckHitKey(KEY_INPUT_S) == 1)
	{
		// NOTE: ���Ⴊ�݁H���蔲�����Ŏg�p
		input_dir.y = 1; 
	}*/

	const float MOVEMENT_SPEED = 300.0f;
	Vector2D delta_position = input_dir.Normalize() * MOVEMENT_SPEED * delta_seconds;
	SetPosition(GetPosition() + delta_position);
}

void Player::Draw(const Vector2D& screen_offset)
{
	__super::Draw(screen_offset);

	// �摜�̕`��
	int x, y;
	GetPosition().ToInt(x, y);
	boolean canMoveNextWinkFlame = (idleFlameAdjust - idleFlameDelay) % winkFlameDelay == 0;

	switch (getState())
	{
	case PlayerState::IDLE:

		if (idleFlameAdjust >= idleFlameDelay && canMoveNextWinkFlame)//120f��������u�����[�V�����ɓ���B5f���ƂɃt���[���𓮂���
		{
			graphicIdleFlame++;
			//printfDx("@@\n");
		}
		if (graphicIdleFlame == maxIdleFlame)//�Ō�̏u�����[�V�������I������烊�Z�b�g����
		{
			idleFlameAdjust = 0;
			graphicIdleFlame = 0;
			//printfDx("���Z�b�g\n");
		}

		idleFlameAdjust++;
		//DrawGraph(x, y, graphicHandleIdle[graphicIdleFlame], true);
		if (getHorizontalDirectionState() == DirectionState::LEFT)
		{
			DrawTurnGraph(x, y, graphicHandleIdle[graphicIdleFlame], true);
		}
		else if (getHorizontalDirectionState() == DirectionState::RIGHT)
		{
			DrawGraph(x, y, graphicHandleIdle[graphicIdleFlame], true);
		}
		break;

	case PlayerState::RUN:
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

		//���E���]�����B
		// NOTE: ���������̂܂܂��ƃL�[�𔽓]���Ă��r����flame����`�悳��邽�ߒ���
		if (CheckHitKey(KEY_INPUT_A))
		{
			DrawTurnGraph(x, y, graphicHandleRun[graphicRunFlame], true);
		}
		else if (CheckHitKey(KEY_INPUT_D) == 1)
		{
			DrawGraph(x, y, graphicHandleRun[graphicRunFlame], true);
		}
		break;

	}

}

void Player::Finalize()
{
	__super::Finalize();

	for (int graphic : graphicHandleIdle)
	{
		//�摜�̔j��
		DeleteGraph(graphic);
		graphic = 0;
	}
}

void Player::ChangePlayerState(PlayerState s)
{
	//OnLeavePlayerState(currentPlayerState);
	currentPlayerState = s;
	OnEnterPlayerState(s);
}

void Player::OnEnterPlayerState(PlayerState s)
{
}

void Player::OnLeavePlayerState(PlayerState s)
{

}