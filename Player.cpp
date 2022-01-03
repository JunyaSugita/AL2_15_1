#include "Player.h"

Player::Player() {
	player = {
		WIN_WIDTH / 2,		//x
		WIN_HEIGHT / 2,		//y
		16,					//r
		{					//speed
			0,					//x
			0					//y
		}
	};
}

Player::~Player(){}

void Player::PlayerMove(int gravityArrow,ISHIT &isHit) {
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
}

void Player::DrawPlayer() {
	DrawBox(player.x - player.r, player.y - player.r, player.x + player.r, player.y + player.r, GetColor(255, 255, 255), true);
	DrawBox(player.x - player.r, player.y - player.r, player.x + player.r, player.y + player.r, GetColor(255, 0, 0), false);
}