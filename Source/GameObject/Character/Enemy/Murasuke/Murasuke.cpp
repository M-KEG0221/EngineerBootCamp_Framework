#include "Murasuke.h"
#include "../../../../SystemTypes.h"
#include "DxLib.h"

Murasuke::Murasuke()
// Murasuke::Murasuke(SceneBase* owner_scene)
// :Enemy(owner_scene)
{
	hp = 2;
	current_direction_state = DirectionState::LEFT;
	current_enemy_state = EnemyState::IDLE;
	collisions["body"] = new BoxCollisionParams(
		BoxCollisionParams::CollisionObjectType::ENEMY,
		BoxCollisionParams::CollisionType::BLOCK,
		Vector2D(32.0f, 50.0f));
	body_collision = collisions["body"];
	SetDeltaPosition(Vector2D(0, 0));
	SetCurrentDirectionState(DirectionState::LEFT);
}

Murasuke::~Murasuke()
{
	// Finalize();
}

void Murasuke::Initialize()
{
	__super::Initialize();

	// �摜�̓ǂݍ���
	// HACK: �O���t�B�b�N�}�l�[�W���[��������璼��
	LoadDivGraph(_T("Resources/Images/murasuke_pp_wait.bmp"), max_idle_flame, max_idle_flame, 1, 40, 48, graphic_handle_idle);
	LoadDivGraph(_T("Resources/Images/murasuke_pp_walk.bmp"), max_run_flame, max_run_flame, 1, 40, 48, graphic_handle_run);
	LoadDivGraph(_T("Resources/Images/murasuke_pp_damage.bmp"), max_damage_flame, max_damage_flame, 1, 40, 48, graphic_handle_damage);
}

void Murasuke::Update(float delta_seconds)
{
	__super::Update(delta_seconds);
	SetOldPosition(GetPosition());

	// ������
	Vector2D input_dir;

	// �e�X�g�p�ŊȒP�ȓ����ɂȂ��Ă���
	if (GetCurrentEnemyState() == EnemyState::RUN)
	{
		if (GetCurrentDirectionState() == DirectionState::LEFT)
		{
			input_dir.x = -1;
		}
		else
		{
			input_dir.x = 1;
		}
	}
	else if (GetCurrentEnemyState() == EnemyState::DEAD)
	{
		input_dir.x = 3;
		input_dir.y = -10;
	}
	ChangeEnemyState(EnemyState::RUN);

	UpdateAnimation();

	const float MOVEMENT_SPEED = 30.0f;
	Vector2D delta_position = input_dir.Normalize() * MOVEMENT_SPEED * delta_seconds;
	if (GetCurrentEnemyState() == EnemyState::DEAD)
	{
		delta_position *= 25;
	}
	SetPosition(GetPosition() + delta_position);

	body_collision->Update(delta_seconds, GetPosition());

	// TODO: dead���A�J�����͈�+NNN���ꂽ�玩�����폜
}

void Murasuke::UpdateAnimation()
{
	switch (GetCurrentEnemyState())
	{
	case EnemyState::IDLE:
	{
		graphic_handle = graphic_handle_idle[graphic_idle_flame];

		break;
	}
	case EnemyState::RUN:
	{
		if (run_flame_adjust == run_flame_delay)
		{
			run_flame_adjust = 0;
			graphic_run_flame++;
		}
		if (graphic_run_flame == max_run_flame)
		{
			graphic_run_flame = 0;
		}

		run_flame_adjust++;

		graphic_handle = graphic_handle_run[graphic_run_flame];

		break;
	}
	case EnemyState::DEAD:
	{
		graphic_handle = graphic_handle_damage[graphic_damage_flame];
	}
	}
}

void Murasuke::Draw(const Vector2D &screen_offset)
{
	__super::Draw(screen_offset);

	// ????`??
	int x, y;
	GetPosition().ToInt(x, y);

	//???E???]????
	if (GetCurrentDirectionState() == DirectionState::RIGHT)
	{
		DrawTurnGraph(x, y, graphic_handle, true);
	}
	else if (GetCurrentDirectionState() == DirectionState::LEFT)
	{
		DrawGraph(x, y, graphic_handle, true);
	}

	if (x < -50)
	{
		Vector2D new_position = Vector2D(SCREEN_RESOLUTION_X, y);
		SetPosition(new_position);
	}

	body_collision->Draw(screen_offset);

	body_collision->GetCenterPosition().ToInt(x, y);
	char str[256];
	sprintf_s(str, sizeof(str), "x: %d, y: %d", x, y);
	DrawString(0, 20, (const TCHAR *)str, GetColor(255, 255, 255));
}

void Murasuke::Finalize()
{
	__super::Finalize();

	for (int graphic : graphic_handle_idle)
	{
		//????j??
		DeleteGraph(graphic);
		graphic = 0;
	}

	for (int graphic : graphic_handle_run)
	{
		//????j??
		DeleteGraph(graphic);
		graphic = 0;
	}
}

void Murasuke::OnHitBoxCollision(const GameObject *hit_object, const BoxCollisionParams &hit_collision_params)
{
	// todo[]:�e�R���W�����ibody, attack�j���Ƃɓ������Ă��邩�ǂ�������������
	switch (hit_collision_params.GetCollisionObjectType())
	{
	case BoxCollisionParams::CollisionObjectType::GROUND:
	{
		if (GetCurrentEnemyState() != EnemyState::DEAD)
		{

			float x = body_collision->center_position.x;
			float y = body_collision->center_position.y;
			float width = body_collision->box_size.x;
			float height = body_collision->box_size.y;
			float old_x = body_collision->old_center_position.x;
			float old_y = body_collision->old_center_position.y;

			float hit_x = hit_collision_params.GetCenterPosition().x;
			float hit_y = hit_collision_params.GetCenterPosition().y;
			float hit_width = hit_collision_params.GetBoxSize().x;
			float hit_height = hit_collision_params.GetBoxSize().y;

			Vector2D new_position = body_collision->GetCenterPosition();

			BoxHitResult my_result = GetBodyCollision()->HitCheckTarget(hit_collision_params);

			// NOTE:��������

			// NOTE: �����܂Łu���ɂ߂荞��ł�I�u�W�F�N�g�v�ɑ΂��Ă̏����Ȃ̂ŁA����ȊO�̃I�u�W�F�N�g�Ƃ̊֌W�͋C�ɂ��ĂȂ�
			bool is_touch_vertical_side = my_result.IsTouchVerticalSide();

			if (my_result.is_hit_left_side && !is_touch_vertical_side)
			{
				new_position.x = hit_x + hit_width;
			}
			if (my_result.is_hit_right_side && !is_touch_vertical_side)
			{
				new_position.x = hit_x - width;
			}

			// ��ɐ����������C�����āA�΂߃W�����v�ȂǂŕǂɈ���������Ȃ��悤�ɂ���
			body_collision->SetCenterPosition(new_position);
			my_result = GetBodyCollision()->HitCheckTarget(hit_collision_params);
			// printfDx("X<%f,", new_position.x);
			// printfDx("%f>\n", hit_x + hit_width);

			// ��������

			// ���������ɑΏۂƐڂ��Ă���Ƃ��͉����o���������s��Ȃ��悤�ɂ���(�΂ߐڐG�΍�)
			bool is_touch_horizontal_side = my_result.IsTouchHorizontalSide();

			if (my_result.is_hit_top_side && !is_touch_horizontal_side)
			{
				new_position.y = hit_y + hit_height;

				// speed_y = 0.0f;
			}
			if (my_result.is_hit_under_side && !is_touch_horizontal_side)
			{
				// HandleLanding();
				new_position.y = hit_y - height;
			}

			if (my_result.is_touch_under_side)
			{
				// HandleLanding();
			}

			body_collision->SetCenterPosition(new_position);
			my_result = GetBodyCollision()->HitCheckTarget(hit_collision_params);

			if (!hitResult.is_touch_under_side && my_result.is_touch_under_side && my_result.IsTouchHorizontalSide())
			{
				// is_ground = false;
			}

			// �����蔻��̌��ʍX�V
			if (!hitResult.is_touch_left_side)
			{
				hitResult.is_touch_left_side = my_result.is_hit_left_side || my_result.is_touch_left_side;
			};
			if (!hitResult.is_touch_left_side)
			{
				hitResult.is_touch_right_side = my_result.is_hit_right_side || my_result.is_touch_right_side;
			};
			if (!hitResult.is_touch_left_side)
			{
				hitResult.is_touch_top_side = my_result.is_hit_top_side || my_result.is_touch_top_side;
			};
			if (!hitResult.is_touch_left_side)
			{
				hitResult.is_touch_under_side = my_result.is_hit_under_side || my_result.is_touch_under_side;
			};

			body_collision->SetCenterPosition(new_position);
			SetPosition(new_position - GetDeltaPosition());
			break;
		}
	}

	case BoxCollisionParams::CollisionObjectType::PLAYER:
	{
		if (hit_collision_params.GetCollisionType() == BoxCollisionParams::CollisionType::OVERLAP) // �U��
		{

			// todo: �����炭�_���[�W�����́A�_���[�W���󂯂鑤�ł��ׂĔ��f����
			// todo: �G����player�̍U���ɓ��������Ɣ��f�����玩���Ƀ_���[�W��^����H
			OnDamaged(1);
		}
	}
	}
}

void Murasuke::OnDamaged(int damage)
{
	ApplyDamage(damage);
}

void Murasuke::ApplyDamage(int damage)
{
	// printfDx("ApplyDamage: %d - %d\n", hp, damage);

	if (hp - damage < 0)
	{
		hp = 0;
	}
	else
	{
		hp = hp - damage;
	}

	if (hp <= 0)
	{
		ChangeEnemyState(EnemyState::DEAD);
	}
	// printfDx(_T("%d\n"), hp);
}