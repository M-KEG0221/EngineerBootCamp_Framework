#include "Player.h"
#include "../Character.h"

#include "DxLib.h"

enum class Player::PlayerState
{
	IDLE, RUN,
};

Player::Player()
{
	current_direction_state = DirectionState::RIGHT;
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
	LoadDivGraph(_T("Resources/Images/collon_wait_a.bmp"), max_idle_flame, max_idle_flame, 1, 128, 128, graphic_handle_idle);
	LoadDivGraph(_T("Resources/Images/collon_run8.bmp"), max_run_flame, 4, 2, 128, 128, graphic_handle_run);
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
		SetCurrentDirectionState(DirectionState::LEFT);
	}
	else if (CheckHitKey(KEY_INPUT_D) == 1)
	{
		input_dir.x = 1;
		ChangePlayerState(PlayerState::RUN);
		SetCurrentDirectionState(DirectionState::RIGHT);
	}
	else
	{
		ChangePlayerState(PlayerState::IDLE);
		//hp--;
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

	UpdateAnimation();

	const float MOVEMENT_SPEED = 300.0f;
	Vector2D delta_position = input_dir.Normalize() * MOVEMENT_SPEED * delta_seconds;
	SetPosition(GetPosition() + delta_position);
}

void Player::UpdateAnimation()
{
	// NOTE: ���̂܂܂��ƃL�[�𔽓]���Ă��r����flame����`�悳��邽�ߒ���

	// �摜�̕`��
	boolean canMoveNextWinkFlame = (idle_flame_adjust - idle_flame_delay) % wink_flame_delay == 0;

	switch (GetCuurentPlayerState())
	{
	case PlayerState::IDLE:

		if (idle_flame_adjust >= idle_flame_delay && canMoveNextWinkFlame)//120f��������u�����[�V�����ɓ���B5f���ƂɃt���[���𓮂���
		{
			graphic_idle_flame++;
			//printfDx("@@\n");
		}
		if (graphic_idle_flame == max_idle_flame)//�Ō�̏u�����[�V�������I������烊�Z�b�g����
		{
			idle_flame_adjust = 0;
			graphic_idle_flame = 0;
			//printfDx("���Z�b�g\n");
		}

		idle_flame_adjust++;

		graphic_handle = graphic_handle_idle[graphic_idle_flame];

		break;

	case PlayerState::RUN:
		if (run_flame_adjust == run_flame_delay)//���f�������玟�̃��[�V�����Ɉڂ�
		{
			run_flame_adjust = 0;
			graphic_run_flame++;
		}
		if (graphic_run_flame == max_run_flame)//�Ō�̃��[�V�������I������烊�Z�b�g����
		{
			graphic_run_flame = 0;
		}

		run_flame_adjust++;

		graphic_handle = graphic_handle_run[graphic_run_flame];

		break;
	}
}

void Player::Draw(const Vector2D& screen_offset)
{
	__super::Draw(screen_offset);

	// �摜�̕`��
	int x, y;
	GetPosition().ToInt(x, y);

	//���E���]����
	if (GetCurrentDirectionState() == DirectionState::LEFT)
	{
		DrawTurnGraph(x, y, graphic_handle, true);
	}
	else if (GetCurrentDirectionState() == DirectionState::RIGHT)
	{
		DrawGraph(x, y, graphic_handle, true);
	}

}

void Player::Finalize()
{
	__super::Finalize();

	for (int graphic : graphic_handle_idle)
	{
		//�摜�̔j��
		DeleteGraph(graphic);
		graphic = 0;
	}

	for (int graphic : graphic_handle_run)
	{
		//�摜�̔j��
		DeleteGraph(graphic);
		graphic = 0;
	}
}

void Player::ChangePlayerState(PlayerState s)
{
	OnLeavePlayerState(current_player_state);
	current_player_state = s;
	OnEnterPlayerState(current_player_state);
}

void Player::OnEnterPlayerState(PlayerState s)
{
}

void Player::OnLeavePlayerState(PlayerState s)
{

}