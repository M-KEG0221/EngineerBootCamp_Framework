#include "SceneManager.h"

#include <cassert>
#include "DxLib.h"

#include "SceneBase.h"
#include "SampleScene/SampleScene.h"

SceneManager::SceneManager()
	: current_scene(nullptr)
{
}

SceneManager::~SceneManager()
{
	Finalize();
}

void SceneManager::Initialize()
{
	// �J�n�V�[����SAMPLE_SCENE�ɐݒ�
	ChangeScene(SceneType::SAMPLE_SCENE);
}

void SceneManager::Update(float DeltaSeconds)
{
	// �V�[���̍X�V
	SceneType result_scene_type = current_scene->Update(DeltaSeconds);

	// ���݂�Update����󂯎�����V�[�����ʂ̏ꍇ�A�V�[���̑J�ڂ��s��
	if (result_scene_type != current_scene->GetSceneType())
	{
		ChangeScene(result_scene_type);
	}

	// �`��
	Draw();
}

void SceneManager::Finalize()
{
	// CurrentScene�̉��
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
		current_scene = nullptr;
	}
}

void SceneManager::Draw()
{
	// ����ʂɕ`��
	SetDrawScreen(DX_SCREEN_BACK);

	// ��ʂ��N���A
	ClearDrawScreen();

	// �V�[���̕`��
	current_scene->Draw();

	// ��ʂ��X�V
	ScreenFlip();
}

void SceneManager::ChangeScene(SceneType new_scene_type)
{
	// �V�[���̐���
	SceneBase* new_scene = CreateScene(new_scene_type);
	assert(new_scene != nullptr);

	// ���݂̃V�[���̉��
	// �ŏ��̃V�[���������̂�CurrentScene��nullptr
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
	}

	// �V�����V�[���̊J�n
	new_scene->Initialize();
	current_scene = new_scene;
}

SceneBase* SceneManager::CreateScene(SceneType new_scene_type)
{
	switch (new_scene_type)
	{
	case SceneType::SAMPLE_SCENE:	return new SampleScene();
	default:					return nullptr;
	}
}