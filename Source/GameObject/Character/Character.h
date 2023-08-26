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
	//~ Begin GameObject interface
	virtual void Initialize() override;
	void Update(float delta_seconds) override;
	void Draw(const Vector2D& screen_offset) override;
	void Finalize() override;
	playerState getState() const { return state; }
	//~ End GameObject interface

private:
	//Idle状態アニメーション情報
	const static int maxIdleFlame = 4;
	const static int idleFlameDelay = 120;// まばたきアニメーションに入るまでの時間
	const static int winkFlameDelay = 5;// まばたきアニメーション間の時間
	int idleFlameAdjust = 0;// delayかけてフレーム遷移するための値
	int graphicHandleIdle[maxIdleFlame];
	int graphicIdleFlame;

	const static int maxRunFlame = 8;
	const static int runFlameDelay = 3;// 次の走りフレームに入るまでの時間
	int runFlameAdjust = 0;// delayかけてフレーム遷移するための値
	int graphicHandleRun[maxRunFlame];
	int graphicRunFlame;

	int hp;
	playerState state;

	void onEnterPlayerState(playerState s)
	{
		ChangePlayerState(s);
	}

	void ChangePlayerState(playerState s)
	{
		playerState oldState = s;
		onLeavePlayerState(oldState);
		state = s;
	}

	void onLeavePlayerState(playerState s)
	{
		
	}
};

