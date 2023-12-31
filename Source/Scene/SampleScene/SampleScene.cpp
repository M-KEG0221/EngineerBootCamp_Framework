#include "SampleScene.h"
#include "../../SystemTypes.h"
#include "../../GameObject/Character/Player/Player.h"
#include "../../GameObject/Character/Enemy/Murasuke/Murasuke.h"
#include "../../GameObject/Ground/Ground.h"
#include "../../GameObject/SampleObject/SampleObject.h"


SampleScene::SampleScene()
{
}

void SampleScene::Initialize()
{
	// 親クラスのInitialize()
	__super::Initialize();

	// SampleObjectを生成
	//CreateObject<SampleObject>(Vector2D(SCREEN_RESOLUTION_X / 2.0f, SCREEN_RESOLUTION_Y / 2.0f));
	CreateObject<Player>(Vector2D(SCREEN_RESOLUTION_X / 2.0f, SCREEN_RESOLUTION_Y / 2.0f));
	CreateObject<Murasuke>(Vector2D(SCREEN_RESOLUTION_X / 2.0f, SCREEN_RESOLUTION_Y / 3.0f));
	/*CreateObject<Ground>(Vector2D(SCREEN_RESOLUTION_X / 3.0f, SCREEN_RESOLUTION_Y / 3.0f));*/
}

SceneType SampleScene::Update(float delta_seconds)
{
	// 親クラスのUpdate()
	return __super::Update(delta_seconds);
}

void SampleScene::Draw()
{
	// 親クラスのDraw()
	__super::Draw();
}

void SampleScene::Finalize()
{
	// 親クラスのFinalize()
	__super::Finalize();
}