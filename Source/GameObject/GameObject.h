#pragma once

#include "../Utility/Vector2D.h"
#include "../Utility/BoxCollisionParams.h"

/**
 * ゲーム内に表示されるオブジェクトの基底クラス
 */
class GameObject
{
public:
	GameObject();
	virtual ~GameObject() {}

public:
	/**
	 * 初期化
	 */
	virtual void Initialize() {}

	/**
	 * 更新
	 * @param	delta_seconds	前フレームとの差分時間(s)
	 */
	virtual void Update(float delta_seconds) {}

	/**
	 * 描画
	 */
	virtual void Draw(const Vector2D& screen_offset) {}

	/**
	 * 解放
	 */
	virtual void Finalize() {}

	/**
	 * シーンの取得
	 * @return owner_scene
	 */
	class SceneBase* GetOwnerScene() const { return owner_scene; }

	/**
	 * シーンのセット
	 * @param	new_owner_scene	セットするPosition
	 */
	void SetOwnerScene(class SceneBase* new_owner_scene);

	/**
	 * Positionの取得
	 * @return	position
	 */
	Vector2D GetPosition() const { return position; }

	/**
	 * Positionのセット
	 * @param	new_position	セットするPosition
	 */
	void SetPosition(const Vector2D& new_position);

	/**
	 * OldPositionの取得
	 * @return	old_position
	 */
	Vector2D GetOldPosition() const { return old_position; }

	/**
	 * OldPositionのセット
	 * @param	new_old_position	セットするPosition
	 */
	void SetOldPosition(const Vector2D& new_old_position);
	/**
	 * 描画順の取得
	 * @return	draw_sort_priority
	 */
	int GetDrawSortPriority() const { return draw_sort_priority; }

	/**
	 * 描画順のセット
	 * @param	new_priority	セットする描画順
	 */
	void SetDrawSortPriority(int new_priority);

	BoxCollisionParams* GetBodyCollision() { return body_collision; }

	virtual void OnHitBoxCollision(const GameObject* hit_object, const BoxCollisionParams& hit_collision_params) {};
	virtual void OnNoHitBoxCollision() {};
	void ResetHitResult() { hitResult = BoxHitResult(); }

protected:
	// 位置
	Vector2D position;

	// 1f前の位置
	Vector2D old_position;

	//コリジョン
	BoxCollisionParams* body_collision;
	BoxHitResult hitResult;

	//画像の描画位置とコリジョンの描画位置の差分
	Vector2D delta_position = Vector2D(0, 0);
	Vector2D GetDeltaPosition() { return delta_position; }
	void SetDeltaPosition(Vector2D new_delta_position) { delta_position = new_delta_position; };

private:
	// オーナーとなるシーン
	class SceneBase* owner_scene;

	// 描画順。数値が小さい順から描画を行う
	int draw_sort_priority;
};