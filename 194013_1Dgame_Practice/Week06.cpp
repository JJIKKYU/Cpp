// Week06.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>

int main()
{
	const int screen_size = 80; // 앞으로 상수는 define이 아닌 const를 사용.
	char screen[screen_size + 1];
	int player_pos = 60;
	int enemy_pos = 30;

	while (true) {
		for (int i = 0; i < screen_size; ++i) {
			screen[i] = ' ';
		}
		screen[screen_size] = '\0';
		strncpy(&screen[player_pos], "(+__+)", strlen("(+__+)"));
		strncpy(&screen[enemy_pos], "(@-@)", strlen("(@-@)"));
		player_pos = (player_pos + rand() % 7 -3) % screen_size; // 최종값 : -1, 0, 1
		printf("%s\r", screen); // \n과 \r의 기능을 잘 기억하자.
		Sleep(66); // ms 단위 0.066초를 30번 반복하면 1초 = 초당 30번 돈다.
	}

	return 0;
}

