#pragma once
#include "../GameObject.h"

/**
 * キャラクター
 * サンプル用に簡易的に実装
 */
class Character : public GameObject
{
	enum class playerState
	{
		IDLE, RUN,
	};

public:
	Character();
	virtual ~Character();

public:
	//~ Begin Character interface
	virtual void Initialize() override;
	virtual void Update(float delta_seconds) override;
	virtual void Draw(const Vector2D& screen_offset) override;
	virtual void Finalize() override;
	//~ End Character interface

	void applyDamage(int damage) {};


protected:
	int hp;
	int graphic_handle;
private:
	virtual void onDamaged(int damage) {};
};

