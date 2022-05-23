#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <cstdlib>
#include <time.h>
using namespace std;

#define CONSOL_COLS 150
#define CONSOL_LINES 50
#define MAGIC_KEY 0 //224
#define SPACE_BAR 32
#define MAX_LEVEL 10

//Cursor Move Function
void gotoxy(int x, int y) {
	COORD Pos; //x, y를 가지고 있는 구조체
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//파라미터 false : 숨기기, true : 보이기
void CursorView(boolean show) {
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

enum Menu {
	GAMESTART = 0,
	GAMEINFO,         //1
	QUIT			  //2
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
	CursorView(false);
}

void drawGame(const int& life, const int& score, const string& question, const string& answer) {
	system("cls");
	gotoxy(2, 1);
	cout << "┌───────────────────────────────────────────┐";
	gotoxy(4, 3);
	cout << "Life : " << life;
	gotoxy(4, 4);
	cout << "Score : " << score;
	gotoxy(4, 8);
	cout << "Q : " << question;
	gotoxy(4, 10);
	cout << "A : " << answer;
	gotoxy(4, 12);
	cout << "press SPACE! after input done.";
	gotoxy(2, 18);
	cout << "└───────────────────────────────────────────┘";
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
}

void GameInfo() {
	DrawGameInfo();
	gotoxy(7, 15);
	cout << "스페이스바를 눌러 이전 화면으로.";
	while (true) {
		if (_getch() == SPACE_BAR) {
			return;
		}
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
				return GAMESTART;
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

void setQuestion(vector<int>& questionVector, int& level) {
	//questionVector << 여기에 방향키의 값을 넣어준다.
	//1 -> 1, 2->2 .........10->10   <-???뭐임
	//방향키 값을 넣을거고
	if (level > MAX_LEVEL) {
		level = MAX_LEVEL;
	}

	srand((unsigned int)time(NULL));
	for (int a = 0; a < level; a++) {
		int num = rand() % 4;
		switch (num) {
		case 0: //상
			questionVector.push_back(UP);
			break;
		case 1: //하
			questionVector.push_back(DOWN);
			break;
		case 2: //좌
			questionVector.push_back(LEFT);
			break;
		case 3: //우
			questionVector.push_back(RIGHT);
			break;
		default:
			break;
		}
	}
}

void VectorToString(vector<int>& questionVector, string& string) {
	//questionVector의 값에 따라서 string에 →←↑↓를 넣어준다.
	//위에 enum Arrow << 여기에 값있으니까 그거 따라서 string << 여기다→←↑↓이거 넣으면댐

	for (vector<int>::iterator iter = questionVector.begin(); iter != questionVector.end(); iter++) {
		switch (*iter)
		{
		case UP:
			string += "↑";
			break;
		case DOWN:
			string += "↓";
			break;
		case RIGHT:
			string += "→";
			break;
		case LEFT:
			string += "←";
			break;
		default:
			break;
		}
	}
}

void drawGameOver(int playTime, int score) {
	system("cls");
	gotoxy(6, 5);
	cout << "─────────────────────";
	gotoxy(6, 6);
	cout << " G A M E  0 V E R    ";
	gotoxy(6, 8);
	cout << " SCORE : " << score << "점";
	gotoxy(6, 10);
	cout << " PLAY TIME : " << playTime/1000 << "초";
	gotoxy(6, 11);
	cout << "─────────────────────";
	gotoxy(9, 15);
	cout << " PRESS SPACEBAR TO MAIN ";
	while (true) {
		if (_getch() == SPACE_BAR) {
			return;
		}
	}
}

boolean checkAnswer(vector<int>& questionVector, vector<int>& answerVector) {
	if (questionVector == answerVector) {
		return true;
	}
	return false;
}

void InGame() {
	//변수 : life score level 문제 입력
	//함수 : 문제에다 랜덤으로, 입력받는 함수, 답인지 검사, 문제를 출력
	int life = 1;
	int score = 0;
	int level;

	clock_t startTime, endTime;
	startTime = clock();

	vector<int> questionVector;
	string question;

	vector<int> answerVector;
	string answer;

	int first_input;
	int second_input;
	while (true) {
		//문제에다 랜덤으로 할당
		level = (score / 10) + 1;
		setQuestion(questionVector, level);
		VectorToString(questionVector, question);
		while (true) {
			drawGame(life, score, question ,answer);
			if (life <= 0) {
				endTime = clock();
				int playTime = (int)((endTime - startTime));
				drawGameOver(playTime, score);
				return;
			}
			first_input = _getch();
			if (first_input == MAGIC_KEY) //받았는데 224네?
			{
				second_input = _getch();
				answerVector.push_back(second_input);
				switch (second_input) //그럼 한번더 받아보자 상하좌우 일수 있으니.
				{
				case UP: //위
					answer += "↑";
					break;
				case DOWN: //아래
					answer += "↓";
					break;
				case RIGHT: //오른쪽
					answer += "→";
					break;
				case LEFT: //왼쪽
					answer += "←";
					break;
				default:
					break;
				}
			}
			else if (first_input == SPACE_BAR) {
				//제출
				if (checkAnswer(questionVector, answerVector)) {
					//정답
					//점수 증가
					score += 10;
				}
				else {
					//오답
					//목숨 감소, 스코어 소량 감소
					life--;
				}
				questionVector.clear();
				question = "";
				answerVector.clear();
				answer = "";
				break;
			}
		}
	}
}

int main(void) {
	SetUp();
	while (true) {
		switch (ReadyGame()) {
		case GAMESTART:
			InGame();
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