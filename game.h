#pragma once
namespace Game
{
#ifdef  _DEBUG
    // ウインドウモード設定
    constexpr bool kWindowMode = true;
#else
    constexpr bool kWindowMode = false;
#endif
    // ウインドウ名
    const char* const kTitleText = "ゲーム名";

    // ウインドウサイズ
    constexpr int kScreenWindth = 1600;
    constexpr int kScreenHeight = 900;


    // カラーモード
    constexpr int kColorDepth = 32;        // 32 or 16
};