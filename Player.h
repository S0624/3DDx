// 2023 Takeru Yui All Rights Reserved.
#pragma once

#include "DxLib.h"

/// <summary>
/// プレイヤークラス
/// </summary>
class Player final
{
public:
	Player();				// コンストラクタ.
	~Player();				// デストラクタ.

	void Update();			// 更新.
	void Draw();			// 描画.

	// モデルハンドルの取得.
	int GetModelHandle() const { return m_modelHandle; }

	const VECTOR& GetPos() const { return m_pos; }
	const VECTOR& GetDir() const { return m_dir; }

private:
	int		m_modelHandle;	// モデルハンドル.
	int		m_jumpAcc;
	int     m_Gravity;
	VECTOR	m_pos;			// ポジション.
	VECTOR	m_velocity;		// 移動力.
	VECTOR	m_dir;			// 回転方向.

	// 静的定数.
	static const float m_Speed;
	static const float m_Scale;
};
