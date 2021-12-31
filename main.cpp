#include "time.h"
#include "BackScleen.h"

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

	//背景
	BackScleen* backScleen = new BackScleen();

	//プレイヤー
	Player player = {
		WIN_WIDTH / 2,		//x
		WIN_HEIGHT / 2,		//y
		16,					//r
		{					//speed
			0,					//x
			0					//y
		}
	};

	const int OLD_CONST = 50;
	OldPlayer oldPlayer[OLD_CONST];
	for (int i = 0; i < OLD_CONST; i++) {
		oldPlayer[i] = {
			player.x,
			player.y
		};
	}

	//gravity
	int gravityArrow = 0;

	//イージング描画
	int drawR = 0;
	int drawG = 1;
	int drawB = 2;

	//壁と当たっているか
	IsHit isHit = {
		0,		//UP
		0,		//DOWN
		0,		//RIGHT
		0		//LEFT
	};
	OldIsHit oldIsHit = {
		0,		//UP
		0,		//DOWN
		0,		//RIGHT
		0		//LEFT
	};

	//円のパーティクル
	const int CIRCLE_CONST = 100;
	Circle circle[CIRCLE_CONST];
	for (int i = 0; i < CIRCLE_CONST; i++) {
		circle[i] = {
			-100,	//x
			-100,	//y
			5,		//r
			0,		//show
			0,		//hitCount
		};
	}

	int isHitCount = 0;
	//パーティクル
	const int PAR_CONST = 1000;
	Par par[PAR_CONST];
	for (int i = 0; i < PAR_CONST; i++) {
		par[i] = {
			-100.0f,	//x
			-100.0f,	//y
			0,		//recoilX
			0,		//recoilY
			0,		//isShow
			0,		//time
			0		//color
		};
	}

	//乱数
	srand(time(NULL));

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

		//当たり判定のリセット
		oldIsHit.up = isHit.up;
		oldIsHit.down = isHit.down;
		oldIsHit.right = isHit.right;
		oldIsHit.left = isHit.left;

		isHit = {
			0,		//UP
			0,		//DOWN
			0,		//RIGHT
			0		//LEFT
		};

		//背景
		backScleen->BackColor();

		//重力の方向操作
		if (keys[KEY_INPUT_W] == 1 || keys[KEY_INPUT_UP] == 1) {
			gravityArrow = 1;
		}
		else if (keys[KEY_INPUT_D] == 1 || keys[KEY_INPUT_RIGHT] == 1) {
			gravityArrow = 2;
		}
		else if (keys[KEY_INPUT_S] == 1 || keys[KEY_INPUT_DOWN] == 1) {
			gravityArrow = 3;
		}
		else if (keys[KEY_INPUT_A] == 1 || keys[KEY_INPUT_LEFT] == 1) {
			gravityArrow = 4;
		}

		//リセット
		if (keys[KEY_INPUT_R] == 1) {
			//初期化
			player = {
				WIN_WIDTH / 2,		//x
				WIN_HEIGHT / 2,		//y
				16,					//r
				{					//speed
					0,					//x
					0					//y
				}
			};
			for (int i = 0; i < OLD_CONST; i++) {
				oldPlayer[i] = {
					player.x,
					player.y
				};
			}

			gravityArrow = 0;
			drawR = 0;
			drawG = 1;
			drawB = 2;

			for (int i = 0; i < CIRCLE_CONST; i++) {
				circle[i] = {
					-100,
					-100,
					5,
					0,
					0
				};
			}

			isHitCount = 0;

			Back back = {
				100,		//r
				1,		//isR
				0,		//g
				0,		//isG
				0,		//b
				0		//isB
			};
		}

		//イージング
		for (int i = OLD_CONST - 1; i > 0; i--) {
			oldPlayer[i].x = oldPlayer[i - 1].x;
			oldPlayer[i].y = oldPlayer[i - 1].y;
		}
		oldPlayer[0].x = player.x;
		oldPlayer[0].y = player.y;

		drawR++;
		drawG++;
		drawB++;
		if (drawR >= 3) {
			drawR = 0;
		}
		if (drawG >= 3) {
			drawG = 0;
		}
		if (drawB >= 3) {
			drawB = 0;
		}

		//プレイヤーの移動
		switch (gravityArrow) {
			case 1:
				if (player.speed.x > 0) {
					player.speed.x--;
				}
				else if (player.speed.x < 0) {
					player.speed.x++;
				}
				player.speed.y--;
				break;
			case 2:
				if (player.speed.y > 0) {
					player.speed.y--;
				}
				else if (player.speed.y < 0) {
					player.speed.y++;
				}
				player.speed.x++;
				break;
			case 3:
				if (player.speed.x > 0) {
					player.speed.x--;
				}
				else if (player.speed.x < 0) {
					player.speed.x++;
				}
				player.speed.y++;
				break;
			case 4:
				if (player.speed.y > 0) {
					player.speed.y--;
				}
				else if (player.speed.y < 0) {
					player.speed.y++;
				}
				player.speed.x--;
				break;
			default:
				break;
		}

		player.x += player.speed.x;
		player.y += player.speed.y;

		//プレイヤーが画面外に行かないようにする
		if (player.x <= 0 + player.r) {
			player.x = 0 + player.r;
			player.speed.x = 0;
			isHit.left = 1;
		}
		if (player.x >= WIN_WIDTH - player.r) {
			player.x = WIN_WIDTH - player.r;
			player.speed.x = 0;
			isHit.right = 1;
		}
		if (player.y <= 0 + player.r) {
			player.y = 0 + player.r;
			player.speed.y = 0;
			isHit.up = 1;
		}
		if (player.y >= WIN_HEIGHT - player.r) {
			player.y = WIN_HEIGHT - player.r;
			player.speed.y = 0;
			isHit.down = 1;
		}

		//円のパーティクル
		//上
		if (isHit.up == 1 && oldIsHit.up == 0) {
			isHitCount++;
			for (int i = 0; i < CIRCLE_CONST; i++) {
				if (circle[i].isShow == 0) {
					circle[i].x = player.x;
					circle[i].y = player.y - player.r;
					circle[i].isShow = 1;
					circle[i].hitCount = isHitCount;
					break;
				}
			}
		}
		//下
		if (isHit.down == 1 && oldIsHit.down == 0) {
			isHitCount++;
			for (int i = 0; i < CIRCLE_CONST; i++) {
				if (circle[i].isShow == 0) {
					circle[i].x = player.x;
					circle[i].y = player.y + player.r;
					circle[i].isShow = 1;
					circle[i].hitCount = isHitCount;
					break;
				}
			}
		}
		//右
		if (isHit.right == 1 && oldIsHit.right == 0) {
			isHitCount++;
			for (int i = 0; i < CIRCLE_CONST; i++) {
				if (circle[i].isShow == 0) {
					circle[i].x = player.x + player.r;
					circle[i].y = player.y;
					circle[i].isShow = 1;
					circle[i].hitCount = isHitCount;
					break;
				}
			}
		}
		//左
		if (isHit.left == 1 && oldIsHit.left == 0) {
			isHitCount++;
			for (int i = 0; i < CIRCLE_CONST; i++) {
				if (circle[i].isShow == 0) {
					circle[i].x = player.x - player.r;
					circle[i].y = player.y;
					circle[i].isShow = 1;
					circle[i].hitCount = isHitCount;
					break;
				}
			}
		}

		for (int i = 0; i < CIRCLE_CONST; i++) {
			if (circle[i].isShow == 1) {
				circle[i].r += 5;
				if (circle[i].r >= 2000) {
					circle[i] = {
					-100,
					-100,
					5,
					0,
					0
					};
				}
			}
		}

		//パーティクル
		if (player.speed.x != 0 || player.speed.y != 0) {
			for (int j = 0; j < 5; j++) {
				for (int i = 0; i < PAR_CONST; i++) {
					if (par[i].isShow == 0) {
						par[i].isShow = 1;
						par[i].x = player.x;
						par[i].y = player.y;
						par[i].recoilX = (player.speed.x * -1) + rand() % 13 - 6;
						par[i].recoilY = (player.speed.y * -1) + rand() % 13 - 6;
						par[i].color = rand() % 3;
						break;
					}
				}
			}
		}

		for (int i = 0; i < PAR_CONST; i++) {
			if (par[i].isShow == 1) {
				par[i].x += par[i].recoilX / 5;
				par[i].y += par[i].recoilY / 5;
				par[i].time++;
				if (par[i].time >= 100) {
					par[i] = {
						-100.0f,	//x
						-100.0f,	//y
						0,		//recoilX
						0,		//recoilY
						0,		//isShow
						0,		//time
						0		//color
					};

				}
			}
		}

		// 描画処理
		backScleen->ShowBackColor();

		//イージング
		for (int i = 0; i < OLD_CONST; i++) {
			SetDrawBlendMode(DX_BLENDMODE_ADD, 150 - (i * 5));
			if (i % 3 == drawR) {
				DrawBox(oldPlayer[i].x - player.r, oldPlayer[i].y - player.r, oldPlayer[i].x + player.r, oldPlayer[i].y + player.r, GetColor(200, 0, 0), true);
			}
			if (i % 3 == drawG) {
				DrawBox(oldPlayer[i].x - player.r, oldPlayer[i].y - player.r, oldPlayer[i].x + player.r, oldPlayer[i].y + player.r, GetColor(0, 200, 0), true);
			}
			if (i % 3 == drawB) {
				DrawBox(oldPlayer[i].x - player.r, oldPlayer[i].y - player.r, oldPlayer[i].x + player.r, oldPlayer[i].y + player.r, GetColor(0, 0, 200), true);
			}
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		//円のパーティクル
		for (int i = 0; i < CIRCLE_CONST; i++) {
			if (circle[i].isShow == 1) {
				SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
				if (circle[i].hitCount % 3 == 0) {
					for (int j = 0; j < 10; j++) {
						DrawCircle(circle[i].x, circle[i].y, circle[i].r - j, GetColor(255, 0, 0), false);
					}
				}
				else if (circle[i].hitCount % 3 == 1) {
					for (int j = 0; j < 10; j++) {
						DrawCircle(circle[i].x, circle[i].y, circle[i].r - j, GetColor(0, 255, 0), false);
					}
				}
				else if (circle[i].hitCount % 3 == 2) {
					for (int j = 0; j < 10; j++) {
						DrawCircle(circle[i].x, circle[i].y, circle[i].r - j, GetColor(0, 0, 255), false);
					}
				}
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}

		//パーティクル
		for (int i = 0; i < PAR_CONST; i++) {
			if (par[i].isShow == 1) {
				SetDrawBlendMode(DX_BLENDMODE_ADD, 200 - par[i].time * 2);
				switch (par[i].color) {
					case 0:
						DrawCircle(par[i].x, par[i].y, 5, GetColor(255, 0, 0), true);
						break;
					case 1:
						DrawCircle(par[i].x, par[i].y, 5, GetColor(0, 255, 0), true);
						break;
					case 2:
						DrawCircle(par[i].x, par[i].y, 5, GetColor(0, 0, 255), true);
						break;
				}
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}

		//プレイヤー
		DrawBox(player.x - player.r, player.y - player.r, player.x + player.r, player.y + player.r, GetColor(255, 255, 255), true);
		DrawBox(player.x - player.r, player.y - player.r, player.x + player.r, player.y + player.r, GetColor(255, 0, 0), false);

		//外枠
		DrawBox(-50, -50, WIN_WIDTH + 50, 0, GetColor(255, 255, 255), true);
		DrawBox(-50, -50, 0, WIN_HEIGHT + 50, GetColor(255, 255, 255), true);
		DrawBox(-50, WIN_HEIGHT + 50, WIN_WIDTH + 50, WIN_HEIGHT, GetColor(255, 255, 255), true);
		DrawBox(WIN_WIDTH + 50, -50, WIN_WIDTH, WIN_HEIGHT + 50, GetColor(255, 255, 255), true);
		//デバック
		DrawFormatString(0, 0, GetColor(255, 255, 255), "isHitCount:%d", isHitCount);


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
	delete backScleen;

	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}
