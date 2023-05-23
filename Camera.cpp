// 2016 Takeru Yui All Rights Reserved.
#include "Player.h"
#include "Camera.h"

/// <summary>
/// コンストラクタ
/// </summary>
Camera::Camera()
{
	//奥行0.1～1000までをカメラの描画範囲とする
	SetCameraNearFar(0.1f, 1500.0f);
	SetCameraPositionAndTarget_UpVecY(VGet(550, 10, 0), VGet(550.0f, 10.0f, 0.0f));

	m_pos = VGet(0, 0, 0);

	// Zバッファを使用する
	SetUseZBuffer3D(true);
	// Zバッファへの書き込みを行う
	SetWriteZBuffer3D(true);

	// ポリゴンの裏面を描画しない
	SetUseBackCulling(true);
}

/// <summary>
/// デストラクタ
/// </summary>
Camera::~Camera()
{
	// 処理なし.
}

/// <summary>
/// 更新
/// </summary>
void Camera::Update(const Player& player)
{
	//SetCameraPositionAndTarget_UpVecY(VGet(650, 400, -700), VGet(650.0f, 300.0f, 0.0f));

	//カメラの設定
	// near,far
	SetCameraNearFar(5.0f, 2800.0f);
	// カメラの視野角を設定（ラジアン）
	SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);
	// カメラの位置、どこを見ているかを設定する
	SetCameraPositionAndTarget_UpVecY(VGet(550, 10, 0), VGet(550.0f, 10.0f, 0.0f));
	//VECTOR pos = VAdd(player.GetPos(), VGet(0, 200, -300.0f));
	//VECTOR lookPos = VAdd(player.GetPos(), VGet(0, 80.0f, 750.f));

	VECTOR pos = VAdd(VGet(player.GetPos().x, 0, player.GetPos().z), VGet(0, 200, -300.0f));
	VECTOR lookPos = VAdd(VGet(player.GetPos().x, 0, player.GetPos().z), VGet(0, 80.0f, 750.f));

	// カメラに位置を反映.
	SetCameraPositionAndTarget_UpVecY(pos, lookPos);
}