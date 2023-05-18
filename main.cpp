#include "DxLib.h"
#include"Player.h"
#include"Camera.h"
#include "game.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    // windowモード設定
    ChangeWindowMode(Game::kWindowMode);

    // ウインドウ名設定
    SetMainWindowText("ゲーム名");

    // 画面サイズの設定
    SetGraphMode(Game::kScreenWindth, Game::kScreenHeight, Game::kColorDepth);
	SetWindowSizeChangeEnableFlag(true);//ウィンドウモードの拡大縮小（サイズ変更）
	SetAlwaysRunFlag(true);
    if (DxLib_Init() == -1)        // ＤＸライブラリ初期化処理
    {
        return -1;            // エラーが起きたら直ちに終了
    }
    // ダブルバッファモード
    SetDrawScreen(DX_SCREEN_BACK);


	// 画面モードのセット
	SetGraphMode(1600, 900, 16);

	// カメラを生成.
	Camera* camera = new Camera();
	// プレイヤーを生成.
	Player* player = new Player();

	
	// エスケープキーが押されるかウインドウが閉じられるまでループ
	LONGLONG frameTime = 0;
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		frameTime = GetNowHiPerformanceCount();
		// プレイヤー制御.
		player->Update();
		camera->Update(*player);

		// 画面を初期化する
		ClearDrawScreen();		

// デバッグ描画
#if _DEBUG
		//(仮決め)グリッドの表示
		for (float x = 100.0f; x <= 800.0f; x += 50.0f)
		{
			VECTOR start = VGet(x, 0.0f, -100.0f);		//線の始点
			VECTOR end = VGet(x, 0.0f, 1800.0f);		//線の終点
			DrawLine3D(start, end, 0x7fffd4);			//あお
		}
		for (float z = -100.0f; z <= 1800.0f; z += 50.0f)
		{
			VECTOR start = VGet(100.0f, 0.0f, z);		//線の始点
			VECTOR end = VGet(800.0f, 0.0f, z);			//線の終点
			DrawLine3D(start, end, 0xdc143c);			//あか
		}
		DrawString(0, 0, "Test",0x00ff00);

		//auto i = GetDrawCallCount();
		//DrawFormatString(800, 100, 0x0000ff, "%d", i);
#endif // kWindowMode

		// 描画
		player->Draw();

		// 裏画面の内容を表画面に反映させる
		ScreenFlip();

		// 雑に60fps固定
		while ((GetNowHiPerformanceCount() - frameTime) < 16667) {}

	}
    // 後始末
    delete(player);
    delete(camera);
    DxLib_End();                // ＤＸライブラリ使用の終了処理

    return 0;                // ソフトの終了
}