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
	COORD Pos; //x, y를 가지고 있는 구조체
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//파라미터 0 : 숨기기, 1 : 보이기
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
	cout << "┌───────────────────────────────────┐";
	gotoxy(3, 3);
	cout << "│        BUTTON MATCHING GAME       │";
	gotoxy(3, 4);
	cout << "└───────────────────────────────────┘";
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
	//개발자, 게임이름, 게임방법, 제작기간, 사용한언어
	gotoxy(3, 2);
	cout << "┌───────────────────────────────────┐";
	gotoxy(3, 3);
	cout << "│  개발자 : 인홍렬, 노범래, 고종화  │";
	gotoxy(3, 4);
	cout << "├───────────────────────────────────┤";
	gotoxy(3, 5);
	cout << "│  게임이름 : BUTTON MATCHING GAME  │";
	gotoxy(3, 6);
	cout << "├───────────────────────────────────┤";
	gotoxy(3, 7);
	cout << "│  사용한언어 : C++                 │";
	gotoxy(3, 8);
	cout << "├───────────────────────────────────┤";
	gotoxy(3, 9);
	cout << "│  제작기간 : 미정                  │";
	gotoxy(3, 10);
	cout << "└───────────────────────────────────┘";
	gotoxy(7, 15);
}

void GameInfo() {
	DrawGameInfo();
	cout << "스페이스바를 눌러 이전 화면으로.";
	if (_getch() == SPACE_BAR) {
		return;
	}
}

int ReadyGame() {
	int y = 0; //위아래로 움직일 좌표
	int input = 0; //키보드 입력을 받을 변수
	while (true) //게임 루프
	{
		MainMenu();
		drawCursor(y);
		input = _getch(); //키보드 입력을 받았다. //→←↑↓

		if (input == MAGIC_KEY) //받았는데 224네?
		{
			switch (_getch()) //그럼 한번더 받아보자 상하좌우 일수 있으니.
			{
			case UP: //위
				--y;
				break;
			case DOWN: //아래
				++y;
				break;
			default:
				break;
			}
		}
		
		else if (input == SPACE_BAR) {
			if (y == 0) {
				//게임시작
			}
			else if (y == 1) {
				//게임정보
				//게임 정보를 출력하고 스페이스바를 누르면 메인화면으로 나가기
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
