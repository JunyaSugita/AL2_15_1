#include "BackScleen.h"
#include "Player.h"
#include "Particle.h"
#include "Gravity.h"
#include "After.h"
#include "Scene.h"
#include "Title.h"
#include "Easing.h"
#include "Info.h"
#include "Reset.h"
#include "Bgm.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0, 0, 0);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み


	// ゲームループで使う変数の宣言
	//シーン管理
	Scene* scene = new Scene();

	//背景
	BackScleen* backScleen = new BackScleen();

	//bgm
	Bgm* bgm = new Bgm();

	//タイトル
	Title* title = new Title();

	//プレイヤー
	Player* player = new Player();

	//gravity
	Gravity* gravity = new Gravity();

	//残像
	After* after = new After();

	//パーティクル
	Particle* particle = new Particle();

	//イージング
	Easing* easing = new Easing();

	//リセット
	Reset* reset = new Reset();

	//その他
	Info* info = new Info();

	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

	// ゲームループ
	while (true) {
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		for (int i = 0; i < 256; ++i)
		{
			oldkeys[i] = keys[i];
		}
		//配列なのでoldkey - keys;のようにできない。要素を１つずつコピー

		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理

		//背景
		backScleen->BackColor();

		//イージング
		easing->easeOutSine();

		//シーン管理
		scene->SceneChange(easing->frame);

		//bgm
		bgm->PlayBgm();

		switch (scene->scene) {
			case 0:
				title->TitleMove();
				title->SceneTrans(keys, scene->isSceneChange);
				break;
			case 1:
				//当たり判定のリセット
				particle->ResetHit();

				//重力の方向操作
				gravity->GravityOpe(keys);

				//リセット
				reset->ResetKey(keys, scene->isSceneChange);

				if (easing->frame == 50) {
					delete player;
					player = new Player();
					delete gravity;
					gravity = new Gravity();
					delete after;
					after = new After();
					delete particle;
					particle = new Particle();
				}

				//イージング
				after->UpdatePlayer(player->player);

				//プレイヤーの移動
				player->PlayerMove(gravity->gravityArrow, particle->isHit);

				//壁のパーティクル
				particle->HitParticle(player->player);

				//パーティクル
				particle->PlayerParticle(player->player);

				break;
		}
		// 描画処理
		//背景
		backScleen->ShowBackColor();

		switch (scene->scene) {
			case 0:
				title->DrawTitle(easing->easingNum);
				title->DrawPress(easing->easingNum);
				break;
			case 1:
				//操作説明
				info->DrawInfo(easing->easingNum);
				//残像
				after->DrawEasing(player->player, easing->easingNum);
				//壁のパーティクル
				particle->DrawHitParticle(easing->easingNum);
				//パーティクル
				particle->DrawPlayerParticle(easing->easingNum);
				//プレイヤー
				player->DrawPlayer(easing->easingNum);
				//リセット
				reset->ShowReset(easing->easingNum);
				break;
		}
		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1) {
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	//デストラクタ
	delete scene;
	delete backScleen;
	delete player;
	delete gravity;
	delete particle;
	delete after;
	delete title;
	delete easing;
	delete info;
	delete reset;

	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}
