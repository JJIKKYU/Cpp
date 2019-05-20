// Screen.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

void draw(char* loc, const char* face)
{
	strncpy(loc, face, strlen(face));
}

class Screen {
	int size;
	char* screen;

public:
	Screen(int sz) : size(sz), screen(new char[sz + 1])
	{
		printf("Screen constructor\n");
	}
	~Screen()
	{
		printf("Screen destructor\n");
		if (screen) {
			delete[] screen;
			screen = nullptr;
		}
	}

	void draw(int pos, const char* face)
	{
		if (face == nullptr) return;
		if (pos < 0 || pos >= size) return;
		strncpy(&screen[pos], face, strlen(face));
	}

	void render()
	{
		printf("%s\r", screen);
	}

	void clear()
	{
		memset(screen, ' ', size);
		screen[size] = '\0';
	}

	int length()
	{
		return size;
	}

};

class GameObject {
	int pos;
	char face[20];
	Screen* screen;

public:
	GameObject(int pos, const char* face, Screen* screen)
		: pos(pos), screen(screen)
	{
		printf("GameObject constructor\n");
		strcpy(this->face, face);
	}

	~GameObject()
	{
		printf("GameObject destructor\n");
	}


	int getPosition()
	{
		return pos;
	}
	void setPosition(int pos)
	{
		this->pos = pos;
	}
	void draw()
	{
		screen->draw(pos, face);
	}
};

class Player : public GameObject {

public:
	Player(int pos, const char* face, Screen* screen)
		: GameObject(pos, face, screen)
	{
		printf("Player constructor\n");
	}

	~Player()
	{
		printf("Player destructor\n");
	}


	void moveLeft()
	{
		setPosition(getPosition() - 1);
	}

	void moveRight()
	{
		setPosition(getPosition() + 1);
	}

	void update(GameObject** gameObjects, int nGameObjects)
	{

	}

};

class Enemy : public GameObject {

public:
	Enemy(int pos, const char* face, Screen* screen)
		: GameObject(pos, face, screen)
	{
		printf("Enemy constructor\n");
	}

	~Enemy()
	{
		printf("Enemy destructor\n");
	}

	void moveRandom()
	{
		setPosition(getPosition() + rand() % 3 - 1);
	}

	void update(GameObject** gameObjects, int nGameObjects)
	{
		int n_remaining_enemies = 0;
		for (int i = 0; i < 100; i++) {
			if (gameObjects[i] == nullptr) continue;
			// upcasting해서 본다. 폴리모피즘 (다형성)
			// 일관적으로 관리가 가능하다.
			// 일전에 과제 했던 것을 폴리모피즘을 사용했을 때의 솔루션을 한 번더 생각해볼 것.
			// 이렇게 하면 얼마나 쉽게 할 수 있었을까와 같은 문제들?
			Enemy* enemy = dynamic_cast<Enemy*>(gameObjects[i]);
			if (enemy == nullptr) continue;
			if (enemy->isAlive() == false) continue;
			if (pos < enemy->getPosition()) {
				n_remaining_enemies++;
			}
		}
	};

	class Bullet : public GameObject {
		bool isFiring;

	public:
		Bullet(int pos, const char* face, Screen* screen)
			: GameObject(pos, face, screen), isFiring(false)
		{
			printf("Bullet constructor\n");
		}
		~Bullet()
		{
			printf("Bullet destructor\n");
		}

		void moveLeft()
		{
			setPosition(getPosition() - 1);
		}

		void moveRight()
		{
			setPosition(getPosition() + 1);
		}

		void draw()
		{
			if (isFiring == false) return;
			GameObject::draw();
		}

		void fire(int player_pos)
		{
			isFiring = true;
			setPosition(player_pos);
		}

		void update(int enemy_pos)
		{
			if (isFiring == false) return;
			int pos = getPosition();
			if (pos < enemy_pos) {
				pos = pos + 1;
			}
			else if (pos > enemy_pos) {
				pos = pos - 1;
			}
			else {
				isFiring = false;
			}
			setPosition(pos);
		}
	};

#define NORMAL_PLAY 1

#if NORMAL_PLAY
	int main()
	{
		Screen screen{ 80 };
		Player player = { 30, "(^_^)", &screen };
		Enemy enemy[20]; { 60, "(*--*)", &screen };
		Bullet bullet[10];  (-1, "+", &screen);
		GameObject* gameObjects[100];
		for (int i = 0; i < 100; i++) gameObjects[i] == nullptr;

		// 플레이어의 주소정보를 배열에다가 집어넣는 것, Type casting을 이용해서
		// 자식객체를 부모객체로 upcasting해서 보는 것은 무조건 가능하다.
		// GameObject *p = &player; 가능
		// 작업을 하다가 원상복귀 시키고 싶을 경우가 dynamic_cast이다.
		// dynamic_cast<player*>(p);
		// 리턴 결과는 Player *another; 이런식으로 만들어진다.
		// 만약 dynamic_cast<Enemy*>(E); 라고 할 경우 리턴 결과는 null을 반환해준다.
		// 뻔한 자료형일때 바꿔주는 것은 static_cast;

		gameObjects[0] = (GameObject *)&player;
		gameObjects[1] = &enemy[0];
		gameObjects[20] = &enemy[19];
		gameObjects[21] = &bullet[0];
		...gameObejcts[30] = &bullet[9];
		nGameObjects = 31;

		while (true)
		{
			screen.clear();

			if (_kbhit())
			{
				int c = _getch();
				switch (c) {
				case 'a':
					player.moveLeft();
					break;
				case 'd':
					player.moveRight();
					break;
				case ' ':
					bullet.fire(player.getPosition());
					break;
				}
			}
			player.draw();
			enemy.draw();
			bullet.draw();

			player.update(gameObjects, nGameObjects);
			enemy.update(gameObjects, nGameObjects);
			bullet.update(gameObjects, nGameObjects);

			screen.render();
			Sleep(66);
		}

		return 0;
	}
#else

	void test()
	{
		Screen* screen = nullptr;

		screen = new Screen(80);
		/* 80 };
		Player player = { 30, "(^_^)", &screen };
		Enemy enemy{ 60, "(*--*)", &screen };
		Bullet bullet(-1, "+", &screen);
		*/

	}

	int main()
	{
		test();


		Screen* another = nullptr;
		int ch = _getch();
		return 0;
	}

#endif