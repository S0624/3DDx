#pragma once

#include "DxLib.h"

/// <summary>
/// プレイヤークラス
/// </summary>
class Player
{
public:
	Player();				// コンストラクタ
	~Player();				// デストラクタ

	void Update();			// 更新
	void Draw();			// 描画

	void PlayerMoveUpdate();// プレイヤーの移動処理
	void PlayAnimation();	// アニメーションの処理
	void DetachAnimation(); // アニメーションを切り替える

	int GetModelHandle() const { return m_modelHandle; } // モデルハンドルの取得
	const VECTOR& GetPos() const { return m_pos; }		 //現在地を渡す
	const VECTOR& GetDir() const { return m_dir; }

private:
	int		m_modelHandle;	// モデルハンドル
	float	m_jumpAcc;		// ジャンプ力
	float   m_Gravity;		// 重力
	bool	m_jumpFlag;		// ジャンプ中かどうか調べる
	VECTOR	m_pos;			// ポジション
	VECTOR	m_velocity;		// 移動力
	VECTOR	m_dir;			// 回転方向

	int		m_attachIndex;	// 総時間取得するアニメーションのアタッチ番号
	int		m_totalTime;	// アニメーションの総再生時間
	float	m_animTime;		// 現在のアニメーションの再生時間
	int		m_attachAnimNum;// 再生したいアニメーションの番号

	// 静的定数
	static const float m_Speed;
	static const float m_Scale;

	
};
