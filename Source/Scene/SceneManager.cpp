#include "SceneManager.h"

#include <cassert>
#include "DxLib.h"

#include "SceneBase.h"
#include "SampleScene/SampleScene.h"
#include "SampleMap/SampleMapScene.h"

SceneManager::SceneManager()
	: current_scene(nullptr)
{
}

SceneManager::~SceneManager()
{
	//Finalize();
}

void SceneManager::Initialize()
{
	// 開始シーンをSAMPLE_SCENEに設定
	//ChangeScene(SceneType::SAMPLE_SCENE);
	ChangeScene(SceneType::SAMPLE_MAP_SCENE);
	// 今後はここをTitleSceneに置き換える
}

void SceneManager::Update(float DeltaSeconds)
{
	// シーンの更新
	SceneType result_scene_type = current_scene->Update(DeltaSeconds);

	// 現在とUpdateから受け取ったシーンが別の場合、シーンの遷移を行う
	if (result_scene_type != current_scene->GetSceneType())
	{
		ChangeScene(result_scene_type);
	}

	// 描画
	Draw();
}

void SceneManager::Finalize()
{
	// CurrentSceneの解放
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
		current_scene = nullptr;
	}
}

void SceneManager::Draw()
{
	// 裏画面に描画
	SetDrawScreen(DX_SCREEN_BACK);

	// 画面をクリア
	ClearDrawScreen();

	// シーンの描画
	current_scene->Draw();

	// 画面を更新
	ScreenFlip();
}

void SceneManager::ChangeScene(SceneType new_scene_type)
{
	// シーンの生成
	SceneBase* new_scene = CreateScene(new_scene_type);
	assert(new_scene != nullptr);

	// 現在のシーンの解放
	// 最初のシーン生成時のみCurrentSceneがnullptr
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
	}

	// 新しいシーンの開始
	new_scene->Initialize();
	current_scene = new_scene;
}

SceneBase* SceneManager::CreateScene(SceneType new_scene_type)
{
	switch (new_scene_type)
	{
	case SceneType::SAMPLE_SCENE:		return new SampleScene();
	case SceneType::SAMPLE_MAP_SCENE:	return new SampleMapScene();
		//case SceneType::TITLE_SCENE:		return new TitleScene();
		//case SceneType::GAME_SCENE:			return new GameScene();
		//case SceneType::RESULT_SCENE:		return new ResultScene();
	default:					return nullptr;
	}
}