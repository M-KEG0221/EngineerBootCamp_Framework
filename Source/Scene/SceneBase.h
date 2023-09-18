#pragma once

#include <vector>
#include <string>
#include "../Utility/Vector2D.h"
#include "../GameObject/GameObject.h"
#include "../Source/GameObject/Ground/Ground.h"

/**
 * �V�[���^�C�v
 */
enum class SceneType : unsigned short
{
	SAMPLE_SCENE,
	SAMPLE_MAP_SCENE,
	TITLE_SCENE,
	GAME_SCENE,
	RESULT_SCENE,
};

/**
 * �V�[���̊��N���X
 */
class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase();

public:
	/**
	 * ������
	 */
	virtual void Initialize();

	/**
	 * �X�V
	 * @param	delta_seconds	�O�t���[���Ƃ̍�������(s)
	 * @return	���ɑJ�ڂ���V�[���^�C�v
	 */
	virtual SceneType Update(float delta_seconds);

	/**
	 * �`��
	 */
	virtual void Draw();

	/**
	 * ���
	 */
	virtual void Finalize();

	/**
	 * �V�[���^�C�v�̎擾
	 * @return �V�[���^�C�v
	 */
	virtual SceneType GetSceneType() const = 0;

	/**
	 * GameObject�̐���
	 * Template�Ŏw�肵��GameObject�N���X��h�������N���X�̃C���X�^���X��������
	 * @param	Position	�����ʒu
	 * @return	��������GameObject
	 */
	template <class T>
	T* CreateObject(const Vector2D& position)
	{
		// GameObject�̐���
		T* new_instance = new T();
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		// GameObject��h�����Ă��Ȃ��ꍇ�́A�j�����ďI������
		if (new_object == nullptr)
		{
			//�h�����Ă��Ȃ��N���X�̂��߁A�������Ȃ�
			delete new_instance;
			return nullptr;
		}

		// GameObject�̏�����
		new_object->SetOwnerScene(this);
		new_object->SetPosition(position);
		new_object->Initialize();
		objects.push_back(new_object);//new object�𖖔��ɒǉ�

		return new_instance;
	}

	/**
	 * GameObject�̔j��
	 * GameObject��j�����A�z�񂩂�폜����
	 * @param	object	�j������I�u�W�F�N�g
	 */
	void DestroyObject(class GameObject* object);

	/**
	 * �S�Ă�GameObject�̔j��
	 * �V�[���ɐ�������Ă���S�ẴI�u�W�F�N�g��j������
	 */
	void DestroyAllObjects();

	bool CheckBoxCollision(GameObject* target, const BoxCollisionParams& collision_params, BoxCollisionParams& hit_collision_params);

protected:
	// �V�[���Ő��������I�u�W�F�N�g
	std::vector<class GameObject*> objects;//�|�C���^���󂯎��i�V�����[�R�s�[�j

	// �X�N���[���p�X�N���[���I�t�Z�b�g
	Vector2D screen_offset;

	//�X�e�[�W�f�[�^
	Ground* stage = nullptr;
};