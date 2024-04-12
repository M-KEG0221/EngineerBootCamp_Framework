#include "SceneBase.h"
#include <iostream>
#include "DxLib.h"

SceneBase::SceneBase()
	: screen_offset(Vector2D())
{
}

SceneBase::~SceneBase()
{
	// Finalize();
}

void SceneBase::Initialize()
{
}

SceneType SceneBase::Update(float delta_seconds)
{
	// hack:�@������ӂ�GameScene�Ɉڂ��H
	for (auto iterator = objects.begin(); iterator != objects.end(); ++iterator) // auto�͎����^���_
	{
		(*iterator)->Update(delta_seconds);
	}

	for (auto iterator = objects.begin(); iterator != objects.end(); ++iterator)
	{
		(*iterator)->ResetHitResult();
		bool isHit = false;

		// �I�u�W�F�N�g�ƃX�e�[�W�̂Ԃ���m�F
		if (stage != nullptr)
		{
			for (BoxCollisionParams *ground_collision : stage->GetGroundCollisions())
			{
				if (CheckBoxCollision((*iterator), *(*iterator)->GetBodyCollision(), *ground_collision))
				{
					isHit = true;
					(*iterator)->OnHitBoxCollision(stage, *ground_collision);
				}
				// }
			}
		}

		// �I�u�W�F�N�g�Ԃ̂Ԃ���m�F
		for (auto iterator2 = objects.begin(); iterator2 != objects.end(); ++iterator2)
		{
			if (*iterator != *iterator2)
			{
				// todo: iterator��body�ƁAiterator�̑S�R���W�������r����悤�ɕύX����
				auto target_collisions = (*iterator2)->GetCollisions();

				for (auto collision_map = target_collisions.begin(); collision_map != target_collisions.end(); ++collision_map)
				{
					if (CheckBoxCollision((*iterator), *(*iterator)->GetBodyCollision(), *collision_map->second))
					{
						isHit = true;
						// todo: ��Lnote�̏����͎��������̂ŁA��������������
						// (*iterator)->OnHitBoxCollision(*iterator2, *(*iterator2)->GetBodyCollision());
						(*iterator)->OnHitBoxCollision(*iterator2, *collision_map->second);
					}
				}
			}
		}
		if (!isHit)
		{
			(*iterator)->OnNoHitBoxCollision();
		}
	}

	return GetSceneType();
}

void SceneBase::Draw()
{
	if (stage != nullptr)
	{
		stage->Draw(screen_offset);
	}
	for (auto iterator = objects.begin(); iterator != objects.end(); ++iterator)
	{
		(*iterator)->Draw(screen_offset);
	}
}

void SceneBase::Finalize()
{
	// �S�ẴI�u�W�F�N�g��j��
	DestroyAllObjects();
}

void SceneBase::DestroyObject(GameObject *object)
{
	if (object == nullptr)
	{
		return;
	}

	// �폜�Ώۂ̌���
	auto iterator = objects.begin();
	for (; iterator != objects.end(); ++iterator)
	{
		if ((*iterator) == object)
		{
			break;
		}
	}

	// ������Ȃ������ꍇ�͔�����
	if (iterator == objects.end())
	{
		return;
	}

	// �폜
	(*iterator)->Finalize();
	objects.erase(iterator);
	delete object;
}

void SceneBase::DestroyAllObjects()
{
	for (auto iterator = objects.begin(); iterator != objects.end(); ++iterator)
	{
		(*iterator)->Finalize();
		delete (*iterator);
	}
	objects.clear();
}

bool SceneBase::CheckBoxCollision(GameObject *target, const BoxCollisionParams &collision_params, BoxCollisionParams &hit_collision_params)
{
	// todo: collision_params��able�̎��̂ݏ�������
	return collision_params.IsHitCheckTarget(hit_collision_params);
}
