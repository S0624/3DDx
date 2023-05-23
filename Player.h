﻿#pragma once

#include "DxLib.h"

/// <summary>
/// プレイヤークラス
/// </summary>
class Player
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


	void Test();
	void TestAnimDelete();
private:
	int		m_modelHandle;	// モデルハンドル.
	float	m_jumpAcc;
	float   m_Gravity;
	bool	m_jumpFlag;
	VECTOR	m_pos;			// ポジション.
	VECTOR	m_velocity;		// 移動力.
	VECTOR	m_dir;			// 回転方向.

	// 静的定数.
	static const float m_Speed;
	static const float m_Scale;






	//テスト用の関数ちゃん
	int AttachIndex = 0;
	int TotalTime = 0;
	float PlayTime = 0.0f;
	int testAnimNum = 10;
};
