// 2023 Takeru Yui All Rights Reserved.
#include "Player.h"
#include"Pad.h"

// 静的定数
// 速度（1=1m、60fps固定として、時速10km）
// 10000m ÷ 時間 ÷ 分 ÷ 秒 ÷ フレーム
const float Player::m_Speed = 5.0f;
//const float Player::Speed = static_cast<float>(10000.0 / 60.0 / 60.0 / 60.0);
const float Player::m_Scale = 0.25f;		// スケール

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
	: m_modelHandle(-1)
{
	//// ３Ｄモデルの読み込み
	m_modelHandle = MV1LoadModel("Data/Model/Robot.mv1");
	m_pos = VGet(450, 0, 0);
	m_velocity = VGet(0, 0, 0);
	m_dir = VGet(0, 0, 1);
	MV1SetUseZBuffer(m_modelHandle, true);
	m_Gravity = -5;
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
	// モデルのアンロード.
	MV1DeleteModel(m_modelHandle);
}

/// <summary>
/// 更新
/// </summary>
void Player::Update()
{
	Pad::update();
	//m_pos.y += m_Gravity;
	m_pos.y += m_jumpAcc;
	if (m_pos.y > 50.0f)
	{
		m_jumpAcc = -5.0f;
	}
	if (m_pos.y < 0.0f)
	{
		m_pos.y = 0.0f;
		m_jumpFlag = false;
	}
	// キー入力取得
	int Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	// 単純に方向転換
	m_dir = VGet(0, 0, 0);
	if (Pad::isPress(PAD_INPUT_UP))
	{
		m_dir = VAdd(m_dir, VGet(0, 0, 1));
	}
	else if (Pad::isPress(PAD_INPUT_DOWN))
	{
		m_dir = VAdd(m_dir, VGet(0, 0, -1));
	}
	if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		m_dir = VAdd(m_dir, VGet(1, 0, 0));
	}
	else if (Pad::isPress(PAD_INPUT_LEFT))
	{
		m_dir = VAdd(m_dir, VGet(-1, 0, 0));
	}
	
	if (Pad::isPress(PAD_INPUT_1) && !m_jumpFlag)
	{
		//m_dir = VAdd(m_dir, VGet(0, 1, 0));
		m_jumpAcc = 3;
		m_jumpFlag = true;
	}


	// ゼロ除算避け
	if (VSquareSize(m_dir) > 0)
	{
		// 正規化
		m_dir = VNorm(m_dir);
	}

	// ポジションを更新.
	m_velocity = VScale(m_dir, m_Speed);
	m_pos = VAdd(m_pos, m_velocity);
	
	// 力をかけ終わったベロシティの方向にディレクションを調整.
	if (VSize(m_velocity) != 0)
	{
		m_dir = VNorm(m_velocity);
	}

	// 3Dモデルのスケール決定
	MV1SetScale(m_modelHandle, VGet(m_Scale, m_Scale, m_Scale));
	// ３Dモデルのポジション設定
	MV1SetPosition(m_modelHandle, m_pos);
	// 回転
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, 91.0f, 0.0f));

	//アニメーション関連の何か（できなかったんで放置）
	//MV1AttachAnim(modelHandle, 1, -1, false);
	
	//printfDx("%f %f %f\n", dir.x, dir.y, dir.z);
	printfDx("%f %f %f\n", m_pos.x, m_pos.y, m_pos.z);
}

/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
	// ３Ｄモデルの描画
	MV1DrawModel(m_modelHandle);
}
