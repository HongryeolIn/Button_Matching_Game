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
	COORD Pos; //x, y�� ������ �ִ� ����ü
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//�Ķ���� false : �����, true : ���̱�
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
	cout << "������������������������������������������������������������������������������������������";
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
	cout << "������������������������������������������������������������������������������������������";
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
}

void GameInfo() {
	DrawGameInfo();
	gotoxy(7, 15);
	cout << "�����̽��ٸ� ���� ���� ȭ������.";
	while (true) {
		if (_getch() == SPACE_BAR) {
			return;
		}
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
				return GAMESTART;
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

void setQuestion(vector<int>& questionVector, int& level) {
	//questionVector << ���⿡ ����Ű�� ���� �־��ش�.
	//1 -> 1, 2->2 .........10->10   <-???����
	//����Ű ���� �����Ű�
	if (level > MAX_LEVEL) {
		level = MAX_LEVEL;
	}

	srand((unsigned int)time(NULL));
	for (int a = 0; a < level; a++) {
		int num = rand() % 4;
		switch (num) {
		case 0: //��
			questionVector.push_back(UP);
			break;
		case 1: //��
			questionVector.push_back(DOWN);
			break;
		case 2: //��
			questionVector.push_back(LEFT);
			break;
		case 3: //��
			questionVector.push_back(RIGHT);
			break;
		default:
			break;
		}
	}
}

void VectorToString(vector<int>& questionVector, string& string) {
	//questionVector�� ���� ���� string�� ����鸦 �־��ش�.
	//���� enum Arrow << ���⿡ �������ϱ� �װ� ���� string << ����١�����̰� �������

	for (vector<int>::iterator iter = questionVector.begin(); iter != questionVector.end(); iter++) {
		switch (*iter)
		{
		case UP:
			string += "��";
			break;
		case DOWN:
			string += "��";
			break;
		case RIGHT:
			string += "��";
			break;
		case LEFT:
			string += "��";
			break;
		default:
			break;
		}
	}
}

void drawGameOver(int playTime, int score) {
	system("cls");
	gotoxy(6, 5);
	cout << "������������������������������������������";
	gotoxy(6, 6);
	cout << " G A M E  0 V E R    ";
	gotoxy(6, 8);
	cout << " SCORE : " << score << "��";
	gotoxy(6, 10);
	cout << " PLAY TIME : " << playTime/1000 << "��";
	gotoxy(6, 11);
	cout << "������������������������������������������";
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
	//���� : life score level ���� �Է�
	//�Լ� : �������� ��������, �Է¹޴� �Լ�, ������ �˻�, ������ ���
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
		//�������� �������� �Ҵ�
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
			if (first_input == MAGIC_KEY) //�޾Ҵµ� 224��?
			{
				second_input = _getch();
				answerVector.push_back(second_input);
				switch (second_input) //�׷� �ѹ��� �޾ƺ��� �����¿� �ϼ� ������.
				{
				case UP: //��
					answer += "��";
					break;
				case DOWN: //�Ʒ�
					answer += "��";
					break;
				case RIGHT: //������
					answer += "��";
					break;
				case LEFT: //����
					answer += "��";
					break;
				default:
					break;
				}
			}
			else if (first_input == SPACE_BAR) {
				//����
				if (checkAnswer(questionVector, answerVector)) {
					//����
					//���� ����
					score += 10;
				}
				else {
					//����
					//��� ����, ���ھ� �ҷ� ����
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