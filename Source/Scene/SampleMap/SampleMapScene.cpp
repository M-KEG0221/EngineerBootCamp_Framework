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
	// �e�N���X��Initialize()
	__super::Initialize();

	// �X�e�[�W�ǂݍ���
	vector<int> stage_data;
	LoadStageCSV("hoge", stage_data);

	// ���ɒu����u���b�N�̌�
	int stage_width_num = SCREEN_RESOLUTION_X / 32; // 20��
	// �c�ɒu����u���b�N�̌�
	int stage_height_num = SCREEN_RESOLUTION_Y / 32; // 15��

	stage = new Ground(stage_data, SCREEN_RESOLUTION_X / 32, SCREEN_RESOLUTION_Y / 32, this);
	// stage->SetGroundData(stage_data);
	stage->Initialize();
	stage->SetOwnerScene(this);
	stage->SetPosition(Vector2D(0, 0));
	// �X�e�[�W�ǂݍ��݂����܂�

	CreateObject<Player>(Vector2D(SCREEN_RESOLUTION_X / 2.0f, SCREEN_RESOLUTION_Y / 2.0f));
	CreateObject<Murasuke>(Vector2D(SCREEN_RESOLUTION_X / 2.0f, SCREEN_RESOLUTION_Y / 2.25f));
}

SceneType SampleMapScene::Update(float delta_seconds)
{
	// �e�N���X��Update()
	return __super::Update(delta_seconds);
}

void SampleMapScene::Draw()
{
	// �e�N���X��Draw()
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
	// �e�N���X��Finalize()
	__super::Finalize();
}
