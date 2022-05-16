#include<iostream>
#include<windows.h>
#include<conio.h>
using namespace std;

#define CONSOL_COLS 150
#define CONSOL_LINES 50
#define MAGIC_KEY 0 //224
#define SPACE_BAR 32

//Cursor Move Function
void gotoxy(int x, int y) {
	COORD Pos; //x, y�� ������ �ִ� ����ü
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//�Ķ���� 0 : �����, 1 : ���̱�
void CursorView(char show) {
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

enum Menu {
	GAMESTART = 0,
	GAMEINFO,
	QUIT
};

enum Arrow {
	UP = 72,
	LEFT = 75,
	RIGHT = 77,
	DOWN = 80
};

//Set up Function
void SetUp() {
	system("title Button Matching Game");
	system("mode con:cols=50 lines=20");
	CursorView(0);
}

void MainMenu() {
	system("cls");
	gotoxy(3, 2);
	cout << "��������������������������������������������������������������������������";
	gotoxy(3, 3);
	cout << "��        BUTTON MATCHING GAME       ��";
	gotoxy(3, 4);
	cout << "��������������������������������������������������������������������������";
	gotoxy(12, 7);
	cout << "GAME START";
	gotoxy(12, 9);
	cout << "GAME INFO";
	gotoxy(12, 11);
	cout << "QUIT";
}

void drawCursor(int& y) {
	if (y <= 0) {
		y = 0;
	}
	else if (y >= 2) {
		y = 2;
	}
	gotoxy(10, 7 + y*2);
	cout << ">";
}

void DrawGameInfo() {
	system("cls");
	//������, �����̸�, ���ӹ��, ���۱Ⱓ, ����Ѿ��
	gotoxy(3, 2);
	cout << "��������������������������������������������������������������������������";
	gotoxy(3, 3);
	cout << "��  ������ : ��ȫ��, �����, ����ȭ  ��";
	gotoxy(3, 4);
	cout << "��������������������������������������������������������������������������";
	gotoxy(3, 5);
	cout << "��  �����̸� : BUTTON MATCHING GAME  ��";
	gotoxy(3, 6);
	cout << "��������������������������������������������������������������������������";
	gotoxy(3, 7);
	cout << "��  ����Ѿ�� : C++                 ��";
	gotoxy(3, 8);
	cout << "��������������������������������������������������������������������������";
	gotoxy(3, 9);
	cout << "��  ���۱Ⱓ : ����                  ��";
	gotoxy(3, 10);
	cout << "��������������������������������������������������������������������������";
	gotoxy(7, 15);
}

void GameInfo() {
	DrawGameInfo();
	cout << "�����̽��ٸ� ���� ���� ȭ������.";
	if (_getch() == SPACE_BAR) {
		return;
	}
}

int ReadyGame() {
	int y = 0; //���Ʒ��� ������ ��ǥ
	int input = 0; //Ű���� �Է��� ���� ����
	while (true) //���� ����
	{
		MainMenu();
		drawCursor(y);
		input = _getch(); //Ű���� �Է��� �޾Ҵ�. //�����

		if (input == MAGIC_KEY) //�޾Ҵµ� 224��?
		{
			switch (_getch()) //�׷� �ѹ��� �޾ƺ��� �����¿� �ϼ� ������.
			{
			case UP: //��
				--y;
				break;
			case DOWN: //�Ʒ�
				++y;
				break;
			default:
				break;
			}
		}
		
		else if (input == SPACE_BAR) {
			if (y == 0) {
				//���ӽ���
			}
			else if (y == 1) {
				//��������
				//���� ������ ����ϰ� �����̽��ٸ� ������ ����ȭ������ ������
				return GAMEINFO;
			}
			else {
				return QUIT;
			}
		}
		
	}
}

int main(void) {
	SetUp();
	while (true) {
		switch (ReadyGame()) {
		case GAMESTART:
			break;
		case GAMEINFO:
			GameInfo();
			break;
		case QUIT:
			return 0;
		}
	}
	return 0;
}
