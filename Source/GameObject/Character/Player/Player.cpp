#include "Player.h"
#include "../Enemy/Enemy.h"
#include "../Character.h"

#include "DxLib.h"

Player::Player()
// Player::Player(SceneBase* owner_scene)
// :Character(owner_scene)
{
	current_direction_state = DirectionState::RIGHT;
	// body_collision = new BoxCollisionParams(
	// 	BoxCollisionParams::CollisionObjectType::PLAYER,
	// 	BoxCollisionParams::CollisionType::BLOCK,
	// 	Vector2D(30.0f, 50.0f));
	collisions["body"] = new BoxCollisionParams(
		BoxCollisionParams::CollisionObjectType::PLAYER,
		BoxCollisionParams::CollisionType::BLOCK,
		Vector2D(30.0f, 50.0f));
	collisions["attack"] = new BoxCollisionParams(
		BoxCollisionParams::CollisionObjectType::PLAYER,
		BoxCollisionParams::CollisionType::OVERLAP,
		Vector2D(30.0f, 50.0f),
		false);

	// �p�ɂɎg��body�͎��񂵂��₷������
	body_collision = collisions["body"];

	// attack_collision = new BoxCollisionParams(
	// 	BoxCollisionParams::CollisionObjectType::PLAYER,
	// 	BoxCollisionParams::CollisionType::OVERLAP,
	// 	Vector2D(30.0f, 50.0f));

	SetDeltaPosition(Vector2D(50, 60));
}

Player::~Player()
{
	// Finalize();
}

void Player::Initialize()
{
	__super::Initialize();

	// �摜�̓ǂݍ���
	// HACK: �O���t�B�b�N�}�l�[�W���[��������璼��
	LoadDivGraph(_T("Resources/Images/collon_wait_a.bmp"), max_idle_flame, max_idle_flame, 1, 128, 128, graphic_handle_idle);
	LoadDivGraph(_T("Resources/Images/collon_run8.bmp"), max_run_flame, 4, 2, 128, 128, graphic_handle_run);
	LoadDivGraph(_T("Resources/Images/collon_jump.bmp"), max_jump_flame, 4, 2, 128, 128, graphic_handle_jump);
	LoadDivGraph(_T("Resources/Images/collon_attack.bmp"), max_attack_flame, max_attack_flame, 2, 128, 128, graphic_handle_attack);
}

void Player::Update(float delta_seconds)
{
	__super::Update(delta_seconds);

	// ������
	Vector2D input_dir;
	if (!is_ground)
	{
		ChangePlayerState(PlayerState::JUMP);
		input_dir.y = 1;
	}

	if (CheckHitKey(KEY_INPUT_A) == 1)
	{
		input_dir.x = -1;
		if (is_ground)
		{
			ChangePlayerState(PlayerState::RUN);
		}
		SetCurrentDirectionState(DirectionState::LEFT);
	}
	else if (CheckHitKey(KEY_INPUT_D) == 1)
	{
		input_dir.x = 1;
		if (is_ground)
		{
			ChangePlayerState(PlayerState::RUN);
		}
		SetCurrentDirectionState(DirectionState::RIGHT);
	}
	/**
	 * �U��
	 */
	else if (CheckHitKey(KEY_INPUT_SPACE) == 1)
	{
		Attack();
	}
	else // todo: �����s�v�ɂ������i�U���L�����Z���̌����ɂȂ��Ă�j
	{
		if (is_ground)
		{
			ChangePlayerState(PlayerState::IDLE);
		}
	}

	if (CheckHitKey(KEY_INPUT_W) == 1)
	{
		// �󒆂Ɉڍs
		if (is_ground)
		{
			is_ground = false;
			is_jumping = true;
			ChangePlayerState(PlayerState::JUMP);
			speed_y = jump_inital_speed;
		}

		// TODO: w�L�[�����������Ԃ����|���Z����B�iinital�����킹�ďC������j
		if (is_jumping && !is_ground && jumping_seconds < 0.01 /* && speed_y > -500.0f*/)
		{
			jumping_seconds += delta_seconds;
			speed_y -= GRAVITY * delta_seconds;
			// printfDx("�����Ă��`�I�I\n");
		}
	}
	else if (is_jumping && speed_y < -500.0f)
	{
		// printfDx("STOP�I�I\n");
		jumping_seconds = 1.0f;
		speed_y = -500.0f;
	}

	if (CheckHitKey(KEY_INPUT_S) == 1)
	{
		// TODO: ���Ⴊ�݁H���蔲�����Ŏg�p
	}

	Vector2D delta_position = input_dir.Normalize() * MOVEMENT_SPEED * delta_seconds;

	// ChangePlayerState(PlayerState::JUMP);

	if (!is_ground)
	{
		delta_position.y = delta_position.y + speed_y * delta_seconds;
		speed_y += GRAVITY * delta_seconds;
		if (speed_y > MAX_FALL_SPEED)
		{
			speed_y = MAX_FALL_SPEED;
		}
		else if (speed_y <= MAX_FALL_SPEED * -1)
		{
			speed_y = MAX_FALL_SPEED * -1;
		}
	}

	SetOldPosition(GetPosition());
	SetPosition(GetPosition() + delta_position);

	// �R���W�����A�b�v�f�[�g
	UpdateCollisions(delta_seconds);
	// body_collision->Update(delta_seconds, GetPosition() + GetDeltaPosition());

	UpdateAnimation();
}

void Player::UpdateCollisions(float delta_seconds)
{
	body_collision->Update(delta_seconds, GetPosition() + Vector2D(50, 60));

	float attack_delta_x = 50.0f; // deltaP.x
	float attack_delta_y = 60.0f; // deltaP.y

	switch (GetCurrentDirectionState())
	{
	case DirectionState::LEFT:
		attack_delta_x -= 30.0f;
		break;
	case DirectionState::RIGHT:
		attack_delta_x += 30.0f;
	}

	collisions["attack"]->Update(delta_seconds, GetPosition() + Vector2D(attack_delta_x, attack_delta_y));
}

// �摜�̕`��ݒ�
void Player::UpdateAnimation()
{
	// NOTE: ���̂܂܂��ƃL�[�𔽓]���Ă��r����flame����`�悳��邽�ߒ���
	boolean canMoveNextWinkFlame = (idle_flame_adjust - idle_flame_delay) % wink_flame_delay == 0;

	switch (GetCuurentPlayerState())
	{
	case PlayerState::IDLE:

		if (idle_flame_adjust >= idle_flame_delay && canMoveNextWinkFlame) // 120f��������u�����[�V�����ɓ���B5f���ƂɃt���[���𓮂���
		{
			graphic_idle_flame++;
		}
		if (graphic_idle_flame == max_idle_flame) // �Ō�̏u�����[�V�������I������烊�Z�b�g����
		{
			idle_flame_adjust = 0;
			graphic_idle_flame = 0;
		}

		idle_flame_adjust++;

		graphic_handle = graphic_handle_idle[graphic_idle_flame];

		break;

	case PlayerState::RUN:
		if (run_flame_adjust == run_flame_delay) // ���f�������玟�̃��[�V�����Ɉڂ�
		{
			run_flame_adjust = 0;
			graphic_run_flame++;
		}
		if (graphic_run_flame == max_run_flame) // �Ō�̃��[�V�������I������烊�Z�b�g����
		{
			graphic_run_flame = 0;
		}

		run_flame_adjust++;

		graphic_handle = graphic_handle_run[graphic_run_flame];

		break;
	case PlayerState::JUMP:
		if (speed_y < -jump_flame_branch_speed)
		{
			jump_flame_point = 0;
		}
		else if (-jump_flame_branch_speed <= speed_y && speed_y < jump_flame_branch_speed)
		{
			jump_flame_point = 2;
		}
		else if (speed_y >= jump_flame_branch_speed)
		{
			jump_flame_point = 4;
		}

		if (jump_flame_adjust == jump_flame_delay)
		{
			toggle_jump_image = !toggle_jump_image;
			jump_flame_adjust = 0;
		}

		jump_flame_adjust++;

		graphic_jump_flame = jump_flame_point + toggle_jump_image;

		graphic_handle = graphic_handle_jump[graphic_jump_flame];
		break;
	case PlayerState::ATTACK:
		// �@�U�����[�V����
		if (attack_flame_adjust >= attack_flame_delay) // ���f�������玟�̃��[�V�����Ɉڂ�
		{
			attack_flame_adjust = 0;
			graphic_attack_flame++;
		}
		if (graphic_attack_flame == max_attack_flame) // �Ō�̃��[�V�������I������烊�Z�b�g����
		{
			// attack_flame_adjust = 0;
			graphic_attack_flame = 0;
		}

		// hack: �A�j���[�V�����Ɋւ���Ă��邪�A�L�����N�^�[�̏����Ɋւ��邱�ƂȂ̂�uppdate�Ɉڂ��ׂ��H
		graphic_attack_flame > 0
			? collisions["attack"]->SetCanHit(true)
			: collisions["attack"]->SetCanHit(false);

		attack_flame_adjust++;

		if (graphic_attack_flame < max_attack_flame)
		{
			graphic_handle = graphic_handle_attack[graphic_attack_flame];
		}
		else
		{
			ChangePlayerState(PlayerState::IDLE);
		}

		break;
	}
}

void Player::Draw(const Vector2D &screen_offset)
{
	__super::Draw(screen_offset);

	// �摜�̕`��
	int x, y;
	GetPosition().ToInt(x, y);

	// ���E���]����
	if (GetCurrentDirectionState() == DirectionState::LEFT)
	{
		DrawTurnGraph(x, y, graphic_handle, true);
	}
	else if (GetCurrentDirectionState() == DirectionState::RIGHT)
	{
		DrawGraph(x, y, graphic_handle, true);
	}

	// body_collision->center_position = Vector2D(x + 48, y + 60);

	// hack: DrawCollitions�ł܂Ƃ߂�H�i�ǂ����f�o�b�O�������`�悷�邽�߁j
	DrawCollisions(screen_offset);

	body_collision->GetCenterPosition().ToInt(x, y);
	char str[256];
	sprintf_s(str, sizeof(str), "x: %d, y: %d", x, y);
	DrawString(0, 0, (const TCHAR *)str, GetColor(255, 255, 255));

	sprintf_s(str, sizeof(str), "speed: %f", speed_y);
	DrawString(200, 0, (const TCHAR *)str, GetColor(0, 0, 255));
	// printfDx("%f\n", speed_y);
}

void Player::DrawCollisions(Vector2D const screen_offset)
{
	for (auto collision_map = collisions.begin(); collision_map != collisions.end(); ++collision_map)
	{
		collision_map->second->Draw(screen_offset);
	}
}

void Player::Finalize()
{
	__super::Finalize();

	for (int graphic : graphic_handle_idle)
	{
		// �摜�̔j��
		DeleteGraph(graphic);
		graphic = 0;
	}

	for (int graphic : graphic_handle_run)
	{
		// �摜�̔j��
		DeleteGraph(graphic);
		graphic = 0;
	}
}

void Player::Attack()
{
	is_attacking = true;
	ChangePlayerState(PlayerState::ATTACK);
}

void Player::ApplyDamage(int damage)
{
}

void Player::ChangePlayerState(PlayerState s)
{
	if (current_player_state != s)
	{
		OnLeavePlayerState(current_player_state);
		current_player_state = s;
		OnEnterPlayerState(current_player_state);
	}
}

void Player::OnEnterPlayerState(PlayerState s)
{
	// switch (s)
	// {
	// 	case PlayerState::RUN:
	// }
}

void Player::OnLeavePlayerState(PlayerState s)
{
	switch (s)
	{
	case PlayerState::IDLE:
		idle_flame_adjust = 0;
		graphic_idle_flame = 0;
		break;
	case PlayerState::RUN:
		run_flame_adjust = 0;
		graphic_run_flame = 0;
		break;
	case PlayerState::JUMP:
		jump_flame_adjust = 0;
		graphic_jump_flame = 0;
		toggle_jump_image = 0;
		break;
	case PlayerState::ATTACK:
		attack_flame_adjust = 0;
		graphic_attack_flame = 0;
		collisions["attack"]->SetCanHit(false);
		break;
	}
}

void Player::OnHitBoxCollision(const GameObject *hit_object, const BoxCollisionParams &hit_collision_params)
{
	// todo[]:�e�R���W�����ibody, attack�j���Ƃɓ������Ă��邩�ǂ�������������
	switch (hit_collision_params.GetCollisionObjectType())
	{
	case BoxCollisionParams::CollisionObjectType::GROUND:
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

		// ���������ɑΏۂƐڂ��Ă���Ƃ��͉����o���������s��Ȃ��悤�ɂ���(�΂ߐڐG�΍�)
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

			speed_y = 0.0f;
		}
		if (my_result.is_hit_under_side && !is_touch_horizontal_side)
		{
			HandleLanding();
			new_position.y = hit_y - height;
		}

		if (my_result.is_touch_under_side)
		{
			HandleLanding();
		}

		body_collision->SetCenterPosition(new_position);
		my_result = GetBodyCollision()->HitCheckTarget(hit_collision_params);

		if (!hitResult.is_touch_under_side && my_result.is_touch_under_side && my_result.IsTouchHorizontalSide())
		{
			is_ground = false;
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

		/*printfDx("Y<%f,", new_position.y + height);
		printfDx("%f>\n", hit_y);*/

		/*if (result.is_hit_left_side)
		{
			printfDx("left\n");
		}
		if (result.is_hit_right_side)
		{
			printfDx("right\n");
		}
		if (result.is_hit_top_side)
		{
			printfDx("top\n");
		}
		if (result.is_hit_under_side)
		{
			printfDx("under\n");
		}

		if (result.is_touch_left_side)
		{
			printfDx("touch left\n");
		}
		if (result.is_touch_right_side)
		{
			printfDx("touch right\n");
		}
		if (result.is_touch_top_side)
		{
			printfDx("touch top\n");
		}
		if (result.is_touch_under_side)
		{
			printfDx("touch under\n");
		}
		printfDx("------\n\n");*/

		body_collision->SetCenterPosition(new_position);
		SetPosition(new_position - GetDeltaPosition());
		break;
	}

	case BoxCollisionParams::CollisionObjectType::ENEMY:
	{

		// todo: �����炭�_���[�W�����́A�_���[�W���󂯂鑤�ł��ׂĔ��f����
		// todo: �G����player�̍U���ɓ��������Ɣ��f�����玩���Ƀ_���[�W��^����H
		// boolean isEnemy = typeid(*hit_object) == typeid(const Enemy);
		// if (GetCollisions()["attack"]->HitCheckTarget(hit_collision_params).IsHit() && isEnemy)
		// {
		// 	printfDx("attack");
		// }
	}
	}
}

/*
 * �v���C���[�����n�����ۂ̏������܂Ƃ߂Ď��s����
 */
void Player::HandleLanding()
{
	is_ground = true;
	is_jumping = false;
	jumping_seconds = 0.0f;
	speed_y = 0.0f;
}

void Player::OnNoHitBoxCollision()
{
	is_ground = false;
	ChangePlayerState(PlayerState::JUMP);

	// printfDx("NO\n");
}
