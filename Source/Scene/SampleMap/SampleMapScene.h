#pragma once

#include<iostream>
#include<string>
#include "../SceneBase.h"
#include "../Source/GameObject/Ground/Ground.h"

using namespace std;

/**
 * �T���v���V�[��
 * �T���v���p�ɊȈՓI�Ɏ���
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
	//todo: �K�����ꏊ�ɕۑ��������˂�
	const int STAGE_WIDTH = 320;					// �X�e�[�W�̉���
	const int STAGE_HEIGHT = 320;					// �X�e�[�W�̏c��
	const int MAPCHIP_WIDTH = 64;					// �}�b�v�`�b�v�̉���
	const int MAPCHIP_HEIGHT = 64;					// �}�b�v�`�b�v�̏c��
	const int MAP_SIZE_WIDTH = STAGE_WIDTH / MAPCHIP_WIDTH;		// MAP�̉���(�l�̓`�b�v��)
	const int MAP_SIZE_HEIGHT = STAGE_HEIGHT / MAPCHIP_HEIGHT;		// MAP�̏c��(�l�̓`�b�v��)

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
	* @param filename csv�t�@�C���̃p�X�H
	* @param stage_data csv�t�@�C������ϊ������}�b�v�`�b�v��
	*/
	void LoadStageCSV(const string& filename, vector<int>& stage_data);
};