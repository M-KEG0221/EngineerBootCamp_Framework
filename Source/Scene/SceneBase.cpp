#include "SceneBase.h"
#include <iostream>
#include "DxLib.h"

SceneBase::SceneBase()
	: screen_offset(Vector2D())
{
}

SceneBase::~SceneBase()
{
	//Finalize();
}

void SceneBase::Initialize()
{
}

SceneType SceneBase::Update(float delta_seconds)
{
	for (auto iterator = objects.begin(); iterator != objects.end(); ++iterator)// auto�͎����^���_
	{
		(*iterator)->Update(delta_seconds);
	}

	for (auto iterator = objects.begin(); iterator != objects.end(); ++iterator)
	{
		bool isHit;
		//�I�u�W�F�N�g�ƃX�e�[�W�̂Ԃ���m�F
		if (stage != nullptr)
		{
			for (BoxCollisionParams* ground_collision : stage->GetGroundCollisions())
			{
				isHit = CheckBoxCollision((*iterator), *(*iterator)->GetBodyCollision(), *ground_collision);
				if (isHit)
				{
					(*iterator)->OnHitBoxCollision(stage, *ground_collision);
				}
			}
		}

		//auto iterator2 = iterator;
		//iterator2++;
		//�I�u�W�F�N�g�Ԃ̂Ԃ���m�F
		for (auto iterator2 = objects.begin(); iterator2 != objects.end(); ++iterator2)
		{
			if (*iterator != *iterator2)
			{
				isHit = CheckBoxCollision((*iterator), *(*iterator)->GetBodyCollision(), *(*iterator2)->GetBodyCollision());
				if (isHit)
				{
					(*iterator)->OnHitBoxCollision(*iterator2, *(*iterator2)->GetBodyCollision());
				}
			}
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

	//for (auto iterator = objects.begin(); iterator != objects.end(); ++iterator)
	//{
	//	bool isHit;
	//	//�I�u�W�F�N�g�ƃX�e�[�W�̂Ԃ���m�F
	//	if (stage != nullptr)
	//	{
	//		for (BoxCollisionParams* ground_collision : stage->GetGroundCollisions())
	//		{
	//			isHit = CheckBoxCollision((*iterator), *(*iterator)->GetBodyCollision(), *ground_collision);
	//			if (isHit)
	//			{
	//				(*iterator)->OnHitBoxCollision(stage, *ground_collision);
	//			}
	//		}
	//	}

	//	auto iterator2 = iterator;
	//	iterator2++;
	//	//�I�u�W�F�N�g�Ԃ̂Ԃ���m�F
	//	for (; iterator2 != objects.end(); ++iterator2)
	//	{
	//		isHit = CheckBoxCollision((*iterator), *(*iterator)->GetBodyCollision(), *(*iterator2)->GetBodyCollision());
	//		if (isHit)
	//		{
	//			//printfDx("object ");
	//			(*iterator)->OnHitBoxCollision(*iterator2, *(*iterator2)->GetBodyCollision());
	//		}
	//	}
	//}
}

void SceneBase::Finalize()
{
	// �S�ẴI�u�W�F�N�g��j��
	DestroyAllObjects();
}

void SceneBase::DestroyObject(GameObject* object)
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

bool SceneBase::CheckBoxCollision(GameObject* target, const BoxCollisionParams& collision_params, BoxCollisionParams& hit_collision_params)
{
	return collision_params.IsHitCheckTarget(hit_collision_params);
}
