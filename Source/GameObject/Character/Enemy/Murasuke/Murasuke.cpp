#include "Murasuke.h"
//#include "../Character.h"

#include "DxLib.h"

//enum class Murasuke::MurasukeState
//{
//	IDLE, RUN,
//};

Murasuke::Murasuke()
{
	current_direction_state = DirectionState::LEFT;
	current_enemy_state = EnemyState::IDLE;
}

Murasuke::~Murasuke()
{
	//Finalize();
}

void Murasuke::Initialize()
{
	__super::Initialize();

	// �摜�̓ǂݍ���
	// HACK: �O���t�B�b�N�}�l�[�W���[��������璼��
	LoadDivGraph(_T("Resources/Images/murasuke_pp_wait.bmp"), max_idle_flame, max_idle_flame, 1, 40, 48, graphic_handle_idle);
	LoadDivGraph(_T("Resources/Images/murasuke_pp_walk.bmp"), max_run_flame, max_run_flame, 1, 40, 48, graphic_handle_run);
}

void Murasuke::Update(float delta_seconds)
{
	__super::Update(delta_seconds);

	// ������
	Vector2D input_dir;
	if (CheckHitKey(KEY_INPUT_A) == 1)
	{
		input_dir.x = -1;
		ChangeEnemyState(EnemyState::RUN);
		SetCurrentDirectionState(DirectionState::LEFT);
	}
	else if (CheckHitKey(KEY_INPUT_D) == 1)
	{
		input_dir.x = 1;
		ChangeEnemyState(EnemyState::RUN);
		SetCurrentDirectionState(DirectionState::RIGHT);
	}
	else
	{
		//ChangeEnemyState(EnemyState::IDLE);
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

void Murasuke::UpdateAnimation()
{
	// �摜�̕`��
	switch (GetCurrentEnemyState())
	{
	case EnemyState::IDLE:

		graphic_handle = graphic_handle_idle[graphic_idle_flame];

		break;

	case EnemyState::RUN:
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

void Murasuke::Draw(const Vector2D& screen_offset)
{
	__super::Draw(screen_offset);

	// �摜�̕`��
	int x, y;
	GetPosition().ToInt(x, y);

	//���E���]����
	if (GetCurrentDirectionState() == DirectionState::RIGHT)
	{
		DrawTurnGraph(x, y, graphic_handle, true);
	}
	else if (GetCurrentDirectionState() == DirectionState::LEFT)
	{
		DrawGraph(x, y, graphic_handle, true);
	}
}

void Murasuke::Finalize()
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