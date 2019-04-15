#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h> // sleep 함수 사용을 위해
#include <conio.h> // getch 함수 사용을 위해
using namespace std;

void draw(char* location, const char* face) {
	strncpy(location, face, strlen(face));
}

int main()
{
	const int screen_size = 80;
	char screen[screen_size + 1];
	char player_face[] = "(^o^)";
	int player_pos = 30;
	char enemy_face[] = "(#__#)";
	int enemy_pos = 60;
	char bullet_face[] = "+";
	const int max_bullets = 100;
	int bullet_pos[max_bullets]; // 안 보이는 공간에 놓기 위해서

	// 총알을 모두 초기화
	for (int i = 0; i < max_bullets; i++) {
		bullet_pos[i] = -1;
	}


	while (true) {

		for (int i = 0; i < screen_size; ++i) {
			screen[i] = ' ';
		}
		screen[screen_size] = '\0';

		if (_kbhit()) {
			int c = _getch();
			switch (c) {
			case 'a':
				player_pos = (player_pos - 1) % screen_size; // screen_size를 나눠주는 이유는 스크린 사이즈를 넘어가지 않게 하기 위해서
				break;
			case 'd':
				player_pos = (player_pos + 1) % screen_size;
				break;
			case ' ':
				int i = 0;
				for (; i < max_bullets; i++) {
					if (bullet_pos[i] == -1)
						break;
				}
				if (i == max_bullets) break;
				// i < max_bullets
				bullet_pos[i] = player_pos;
				break;
			}
		}

		//player_pos = (player_pos + rand() % 3 - 1) % screen_size;
		enemy_pos = (enemy_pos + rand() % 3 - 1) % screen_size;
		for (int i = 0; i < max_bullets; i++) {
			if (bullet_pos[i] != -1) {
				if (bullet_pos[i] < enemy_pos) {
					bullet_pos[i] = (bullet_pos[i] + 1) % screen_size;
				}
				else if (bullet_pos[i] > enemy_pos) {
					bullet_pos[i] = (bullet_pos[i] - 1) % screen_size;
				}
				else {
					bullet_pos[i] = -1;
				}
			}
		}

		draw(&screen[player_pos], player_face);
		draw(&screen[enemy_pos], enemy_face);

		for (int i = 0; i < max_bullets; i++) {
			if (bullet_pos[i] != -1) {
				draw(&screen[bullet_pos[i]], bullet_face);
			}
		}

		printf("%s\r", screen);

		//cout << screen << '\r';
		Sleep(66);
	}

	return 0;
}
