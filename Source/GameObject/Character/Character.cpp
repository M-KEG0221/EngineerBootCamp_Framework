#include "Character.h"

#include "DxLib.h"

Character::Character()
	: graphic_handle(0)
// Character::Character(SceneBase* owner_scene)
// 	: graphic_handle(0),
// 	GameObject(owner_scene)
{
}

Character::~Character()
{
	Finalize();
}

void Character::Initialize()
{
	__super::Initialize();
}

void Character::Update(float delta_seconds)
{
	__super::Update(delta_seconds);
}

void Character::Draw(const Vector2D &screen_offset)
{
	__super::Draw(screen_offset);
}

void Character::Finalize()
{
	__super::Finalize();
	// ‰æ‘œ‚Ì”jŠü
	graphic_handle = 0;
}