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

	// SampleObjectを生成
	//CreateObject<SampleObject>(Vector2D(SCREEN_RESOLUTION_X / 2.0f, SCREEN_RESOLUTION_Y / 2.0f));

	vector<int> stage_data;
	LoadStageCSV("hoge", stage_data);

	int stage_width = SCREEN_RESOLUTION_X / 32;//20
	int stage_height = SCREEN_RESOLUTION_Y / 32;//15

	stage = new Ground(SCREEN_RESOLUTION_X / 32, SCREEN_RESOLUTION_Y / 32);
	stage->SetGroundData(stage_data);
	stage->SetOwnerScene(this);
	stage->SetPosition(Vector2D(0, 0));
	stage->Initialize();
	objects.push_back(stage);


	CreateObject<Player>(Vector2D(SCREEN_RESOLUTION_X / 2.0f, SCREEN_RESOLUTION_Y / 2.0f));
	CreateObject<Murasuke>(Vector2D(SCREEN_RESOLUTION_X / 2.0f, SCREEN_RESOLUTION_Y / 3.0f));

	/*for (int y = 0; y < MAP_SIZE_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_SIZE_WIDTH; x++)
		{
			int chip = stage_data[x];
			if (!chip)
			{
				continue;
			}
			float chip_pos_x = (float)(chip_id % width_chip_num) * MAPCHIP_WIDTH;
			float chip_pos_y = (float)(chip_id / height_chip_num) * MAPCHIP_HEIGHT;
			CreateObject<Ground>
		}
	}*/

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

void SampleMapScene::LoadStageCSV(const string& filename, vector<int>& stage_data)
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
		0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,

		0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
		0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
		0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
		1,0,0,0,0, 1,0,0,0,0, 1,0,0,0,0, 1,0,0,0,0,
		1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
	};

	stage_data = scv;
}

void SampleMapScene::Finalize()
{
	// 親クラスのFinalize()
	__super::Finalize();
}
