#pragma once

#include<iostream>
#include<string>
#include "../SceneBase.h"
#include "../Source/GameObject/Ground/Ground.h"

using namespace std;

/**
 * サンプルシーン
 * サンプル用に簡易的に実装
 */
class SampleMapScene : public SceneBase
{
public:
	SampleMapScene();
	virtual ~SampleMapScene() {}

public:
	//~ Begin CSceneBase interface
	virtual void Initialize() override;
	virtual SceneType Update(float delta_seconds) override;
	virtual void Draw() override;
	virtual void Finalize() override;
	virtual SceneType GetSceneType() const override { return SceneType::SAMPLE_SCENE; }
	//~ End SceneBase interface
protected:
	//todo: 適した場所に保存したいねぇ
	const int STAGE_WIDTH = 320;					// ステージの横幅
	const int STAGE_HEIGHT = 320;					// ステージの縦幅
	const int MAPCHIP_WIDTH = 64;					// マップチップの横幅
	const int MAPCHIP_HEIGHT = 64;					// マップチップの縦幅
	const int MAP_SIZE_WIDTH = STAGE_WIDTH / MAPCHIP_WIDTH;		// MAPの横幅(値はチップ数)
	const int MAP_SIZE_HEIGHT = STAGE_HEIGHT / MAPCHIP_HEIGHT;		// MAPの縦幅(値はチップ数)

	const int MAPCHIP_NUM_HEIGHT = 5;
	const int MAPCHIP_NUM_WIDTH = 5;

	vector<int> scv = {
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		1,1,1,1,1,
	};
private:
	//Ground* stage = nullptr;

	/**
	* @param filename csvファイルのパス？
	* @param stage_data csvファイルから変換したマップチップの
	*/
	void LoadStageCSV(const string& filename, vector<int>& stage_data);
};