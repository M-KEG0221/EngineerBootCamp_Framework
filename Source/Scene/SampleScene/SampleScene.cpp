#include "SampleScene.h"
#include "../../SystemTypes.h"
#include "../../GameObject/SampleObject/SampleObject.h"

SampleScene::SampleScene()
{
}

void SampleScene::Initialize()
{
	// �e�N���X��Initialize()
	__super::Initialize();

	// SampleObject�𐶐�
	CreateObject<SampleObject>(Vector2D(SCREEN_RESOLUTION_X / 2.0f, SCREEN_RESOLUTION_Y / 2.0f));
}

SceneType SampleScene::Update(float delta_seconds)
{
	// �e�N���X��Update()
	return __super::Update(delta_seconds);
}

void SampleScene::Draw()
{
	// �e�N���X��Draw()
	__super::Draw();
}

void SampleScene::Finalize()
{
	// �e�N���X��Finalize()
	__super::Finalize();
}