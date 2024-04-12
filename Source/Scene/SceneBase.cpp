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
	// hack:　ここら辺はGameSceneに移す？
	for (auto iterator = objects.begin(); iterator != objects.end(); ++iterator) // autoは自動型推論
	{
		(*iterator)->Update(delta_seconds);
	}

	for (auto iterator = objects.begin(); iterator != objects.end(); ++iterator)
	{
		(*iterator)->ResetHitResult();
		bool isHit = false;

		// オブジェクトとステージのぶつかり確認
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

		// オブジェクト間のぶつかり確認
		for (auto iterator2 = objects.begin(); iterator2 != objects.end(); ++iterator2)
		{
			if (*iterator != *iterator2)
			{
				// todo: iteratorのbodyと、iteratorの全コリジョンを比較するように変更する
				auto target_collisions = (*iterator2)->GetCollisions();

				for (auto collision_map = target_collisions.begin(); collision_map != target_collisions.end(); ++collision_map)
				{
					if (CheckBoxCollision((*iterator), *(*iterator)->GetBodyCollision(), *collision_map->second))
					{
						isHit = true;
						// todo: 上記noteの処理は実装したので、ここを実装する
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
	// 全てのオブジェクトを破棄
	DestroyAllObjects();
}

void SceneBase::DestroyObject(GameObject *object)
{
	if (object == nullptr)
	{
		return;
	}

	// 削除対象の検索
	auto iterator = objects.begin();
	for (; iterator != objects.end(); ++iterator)
	{
		if ((*iterator) == object)
		{
			break;
		}
	}

	// 見つからなかった場合は抜ける
	if (iterator == objects.end())
	{
		return;
	}

	// 削除
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
	// todo: collision_paramsがableの時のみ処理する
	return collision_params.IsHitCheckTarget(hit_collision_params);
}
