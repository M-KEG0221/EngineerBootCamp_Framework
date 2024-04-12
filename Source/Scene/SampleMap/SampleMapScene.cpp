#include "SampleMapScene.h"
#include "../../SystemTypes.h"
#include "../../GameObject/Character/Player/Player.h"
#include "../../GameObject/Character/Enemy/Murasuke/Murasuke.h"
#include "../../GameObject/SampleObject/SampleObject.h"
#include "../../GameObject/Ground/Ground.h"

SampleMapScene::SampleMapScene()
{
}

void SampleMapScene::Initialize()
{
	// 親クラスのInitialize()
	__super::Initialize();

	// ステージ読み込み
	vector<int> stage_data;
	LoadStageCSV("hoge", stage_data);

	// 横に置けるブロックの個数
	int stage_width_num = SCREEN_RESOLUTION_X / 32; // 20個
	// 縦に置けるブロックの個数
	int stage_height_num = SCREEN_RESOLUTION_Y / 32; // 15個

	stage = new Ground(stage_data, SCREEN_RESOLUTION_X / 32, SCREEN_RESOLUTION_Y / 32, this);
	// stage->SetGroundData(stage_data);
	stage->Initialize();
	stage->SetOwnerScene(this);
	stage->SetPosition(Vector2D(0, 0));
	// ステージ読み込みここまで

	CreateObject<Player>(Vector2D(SCREEN_RESOLUTION_X / 2.0f, SCREEN_RESOLUTION_Y / 2.0f));
	CreateObject<Murasuke>(Vector2D(SCREEN_RESOLUTION_X / 2.0f, SCREEN_RESOLUTION_Y / 2.25f));
}

SceneType SampleMapScene::Update(float delta_seconds)
{
	// 親クラスのUpdate()
	return __super::Update(delta_seconds);
}

void SampleMapScene::Draw()
{
	// 親クラスのDraw()
	__super::Draw();
}

void SampleMapScene::LoadStageCSV(const string &filename, vector<int> &stage_data)
{
	vector<int> scv = {
		1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
		0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
		0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
		0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
		0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,

		0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
		0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
		0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
		0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
		0,0,0,0,0, 0,0,1,0,0, 0,0,0,0,0, 0,0,0,0,0,

		0,0,0,0,0, 0,0,1,0,0, 0,0,0,0,0, 0,0,0,0,0,
		0,0,0,0,0, 0,0,1,0,0, 0,0,0,0,0, 0,0,0,0,0,
		0,0,0,0,0, 0,0,1,0,0, 0,0,0,0,0, 0,0,0,0,0,
		1,0,0,0,0, 1,0,1,0,1, 1,0,0,0,0, 1,0,0,0,0,
		1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
	};

	stage_data = scv;
}

void SampleMapScene::Finalize()
{
	// 親クラスのFinalize()
	__super::Finalize();
}
