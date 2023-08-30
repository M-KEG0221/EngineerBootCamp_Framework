#pragma once
#include "DxLib.h"
#include "../Character.h"
#include "vector"

/**
 * キャラクター
 * サンプル用に簡易的に実装
 */
class Player : public Character
{
	enum class PlayerState
	{
		IDLE, RUN,
	};
	enum class DirectionState
	{
		LEFT, RIGHT,
	};

public:
	Player();
	virtual ~Player();

public:
	//~ Begin GameObject interface
	void Initialize() override;
	void Update(float delta_seconds) override;
	void Draw(const Vector2D& screen_offset) override;
	void Finalize() override;
	//~ End GameObject interface
	PlayerState getState() const { return currentPlayerState; }
	DirectionState getHorizontalDirectionState() const { return currentDirectionState; }

private:
	//IDLE状態アニメーション情報
	const static int maxIdleFlame = 4;
	const static int idleFlameDelay = 120;// まばたきアニメーションに入るまでの時間
	const static int winkFlameDelay = 5;// まばたきアニメーション間の時間
	int idleFlameAdjust = 0;// delayかけてフレーム遷移するための値
	int graphicHandleIdle[maxIdleFlame] = { 0,0,0,0 };
	int graphicIdleFlame = 0;

	//RUN状態アニメーション情報
	const static int maxRunFlame = 8;
	const static int runFlameDelay = 3;// 次の走りフレームに入るまでの時間
	int runFlameAdjust = 0;// delayかけてフレーム遷移するための値
	int graphicHandleRun[maxRunFlame] = { 0,0,0,0 };
	int graphicRunFlame = 0;

	//playerState関係
	PlayerState currentPlayerState;
	void ChangePlayerState(PlayerState s);
	void OnEnterPlayerState(PlayerState s);
	void OnLeavePlayerState(PlayerState s);

	//キャラの向き関係
	DirectionState currentDirectionState = DirectionState::RIGHT;
	void SetDirectionState(DirectionState hds) { currentDirectionState = hds; }
};

