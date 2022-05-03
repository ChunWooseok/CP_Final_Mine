#include "MineSweeper.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <random>
#include <fstream>
#include <conio.h> //_getch사용
int _x = 10;
int _y = 5;
using namespace std;

//생성자
MineSweeper::MineSweeper()
{
}

//복사생성자
MineSweeper::MineSweeper(const MineSweeper& arr)
	:MineSweeper()
{
	for (int i = 0; i < N + 2; i++) {
		for (int j = 0; j < N + 2; j++) {
			mine[i][j] = arr.mine[i][j];
			input[i][j] = arr.input[i][j];
		}
	}
}

//이동 생성자
MineSweeper::MineSweeper(MineSweeper&& arr) noexcept
	:N(arr.N), mine(move(arr.mine)), input(move(arr.input))
{
}

//소멸자
MineSweeper::~MineSweeper()
{
}

//대입연산자
MineSweeper& MineSweeper::operator=(const MineSweeper& arr)
{
	if (this == &arr) {
		return *this;
	}
	this->N = arr.N;
	for (int i = 0; i < N + 2; i++) {
		mine[i].reset(new int[N]);
		input[i].reset(new int[N]);
	}
	for (int i = 0; i < N + 2; i++) {
		for (int j = 0; j < N + 2; j++) {
			mine[i][j] = arr.mine[i][j];
			input[i][j] = arr.input[i][j];
		}
	}
	return *this;
}

//이동대입연산자
MineSweeper& MineSweeper::operator=(MineSweeper&& arr) noexcept
{
	this->N = arr.N;
	mine = move(arr.mine);
	input = move(arr.input);
	return *this;
}

void MineSweeper::initData()
{
	int n;

	_getch();
	//system("");

	system("mode con:cols=50 lines=13");
	try {
		int k;
		set_color(100, 0);
		gotoxy(10, 5);
		cout << "N x N 지뢰찾기를 시작합니다." << endl;
		set_color(7, 0);
		gotoxy(10, 7);
		cout << "N (4이상 20이하) : ";
		cin >> k;
		system("cls");
		if (k < 4 || k > 20)
			throw k;
		n = k;
	}
	catch (int nExp) {
		gotoxy(10, 5);
		cout << "ERROR - Program Exit!!" << endl;
		exit(0);
	}
	N = n;

	//실제보다 row와 col이 1씩 큰 배열 생성.
	shared_ptr<shared_ptr<int[]>[]> mine2(new shared_ptr<int[]>[n + 2]);
	shared_ptr<shared_ptr<int[]>[]> input2(new shared_ptr<int[]>[n + 2]);

	mine = mine2;
	input = input2;

	for (int i = 0; i < n + 2; i++) {
		mine[i] = shared_ptr<int[]>(new int[n + 2]);
		input[i] = shared_ptr<int[]>(new int[n + 2]);
	}

	//둘 다 일단 0으로 초기화
	for (int i = 0; i < n + 2; i++) {
		for (int j = 0; j < n + 2; j++) {
			mine[i][j] = 0;
			input[i][j] = 0;
		}
	}
}

void MineSweeper::startScreen()
{
	system("mode con:cols=142 lines=30");

	gotoxy(10, 3);
	cout << "■      ■  ■  ■■■■■  ■■■■■  ■■■■■  ■  ■  ■  ■■■■■  ■■■■■  ■■■■■  ■■■■■  ■■■■■" << endl;
	gotoxy(10, 4);
	cout << "■■  ■■  ■  ■      ■  ■          ■          ■  ■  ■  ■          ■          ■      ■  ■          ■      ■" << endl;
	gotoxy(10, 5);
	cout << "■  ■  ■  ■  ■      ■  ■■■      ■■■■■  ■  ■  ■  ■■■      ■■■      ■■■■■  ■■■      ■■■■■" << endl;
	gotoxy(10, 6);
	cout << "■      ■  ■  ■      ■  ■                  ■  ■  ■  ■  ■          ■          ■          ■          ■    ■ " << endl;
	gotoxy(10, 7);
	cout << "■      ■  ■  ■      ■  ■■■■■  ■■■■■  ■■■■■  ■■■■■  ■■■■■  ■          ■■■■■  ■      ■" << endl;
	gotoxy(10, 9);
	cout << "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□" << endl;

	gotoxy(65, 16);
	cout << "♡ 시작하기" << endl;
	gotoxy(65, 18);
	cout << "♡ 이어하기" << endl;
	gotoxy(65, 20);
	cout << "♡ 종료" << endl;
	gotoxy(60, 23);
	cout << "press SPACE to select." << endl;

	gotoxy(116, 28);
	cout << "made by. 전우석_201510595" << endl;

	for (int i = 0; i < 17; i++) {
		gotoxy(54 + 2 * i, 14);
		cout << "●" << endl;
	}
	for (int i = 0; i < 17; i++) {
		gotoxy(54 + 2 * i, 25);
		cout << "●" << endl;
	}
	for (int i = 1; i < 11; i++) {
		gotoxy(54, 14 + i);
		cout << "●" << endl;
	}
	for (int i = 1; i < 11; i++) {
		gotoxy(86, 14 + i);
		cout << "●" << endl;
	}

}

int MineSweeper::selectMenu()
{
	int x = 65;
	int y = 16;

	startScreen();

	while (1) {
		//&0x8000
		if (GetAsyncKeyState(VK_UP) & 0x0001) {
			y -= 2;
			if (y < 16) y = 20;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x0001) {
			y += 2;
			if (y > 20) y = 16;
		}

		gotoxy(x, y);

		if (GetAsyncKeyState(VK_SPACE) & 0x0001) {
			break;
		}
		Sleep(100);
	}

	system("cls");
	return (y - 14) / 2;
}

//지뢰 심는 함수 
void MineSweeper::setMine(const int& level)
{
	random_device rd;
	mt19937 engine(rd()); //난수 발생
	uniform_int_distribution<int> value(1, this->N); //1~N의 정수 난수 생성

	int mineN = (N * N * (level * 10) / 100);
	int i, j;
	int cnt = 0;

	cout << mineN << endl;
	while (cnt < mineN) {
		i = value(engine);
		j = value(engine);
		if (mine[i][j] != 9) { //지뢰는 9로
			mine[i][j] = 9;
			cnt++;
		}
	}
}

void MineSweeper::contGame()
{
	int n;

	ifstream fin("save_mine_file.txt");
	if (!fin.is_open()) {
		cerr << "이어하기 데이터 없음." << endl;
		exit(0);
	}
	fin >> n;
	N = n;
	shared_ptr<shared_ptr<int[]>[]> map(new shared_ptr<int[]>[N + 2]);
	mine = map;
	for (int i = 0; i < N + 2; i++) {
		mine[i] = shared_ptr<int[]>(new int[N + 2]);
	}
	while (!fin.eof()) {
		for (int i = 0; i < N + 2; i++) {
			for (int j = 0; j < N + 2; j++) {
				fin >> mine[i][j];
			}
		}
	}
	int m;

	ifstream fin2("save_input_file.txt");
	if (!fin2.is_open()) {
		cerr << "이어하기 데이터 없음." << endl;
		exit(0);
	}
	fin2 >> m;
	shared_ptr<shared_ptr<int[]>[]> map2(new shared_ptr<int[]>[N + 2]);
	input = map2;
	for (int i = 0; i < N + 2; i++) {
		input[i] = shared_ptr<int[]>(new int[N + 2]);
	}
	while (!fin2.eof()) {
		for (int i = 0; i < N + 2; i++) {
			for (int j = 0; j < N + 2; j++) {
				fin2 >> input[i][j];
			}
		}
	}
}

//주변 지뢰갯수에 따라 숫자 올리는 함수.
void MineSweeper::initMap()
{
	for (int i = 1; i < N + 1; i++) {
		for (int j = 1; j < N + 1; j++) {
			if (mine[i][j] != 9) {
				for (int k = -1; k < 2; k++) {
					for (int t = -1; t < 2; t++) {
						if (mine[i + k][j + t] == 9) {
							mine[i][j]++;
						}
					}
				}
			}
		}
	}
}

//지뢰심기
void MineSweeper::setLevel()
{
	int level;
	try {
		system("mode con:cols=60 lines=13");
		set_color(14, 0);
		gotoxy(21, 4);
		cout << " *** 난이도 ***" << endl;
		gotoxy(10, 6);
		set_color(50, 0);
		cout << "1.하(10%) \t 2.중(20%) \t 3.상(30%)" << endl;
		gotoxy(12, 8);
		set_color(7, 0);
		cout << "선택 : ";
		cin >> level;
		if (level != 1 && level != 2 && level != 3) {
			throw level;
		}
	}
	catch (int nExp) {
		system("cls");
		gotoxy(10, 5);
		cout << "Error!" << endl;
		exit(0);
	}
	setMine(level);
	system("cls");
}

void MineSweeper::printMap() {

	gotoxy(10 + N - 8, 1);
	set_color(50, 0);
	cout << "MINE SWEEPER <<<<<" << endl;
	set_color(100, 0);
	gotoxy(10 + N - 7, 3);
	cout << N << " x " << N << " 지뢰찾기" << endl;

	set_color(7, 0);
	for (int i = 1; i < N + 1; i++) {
		gotoxy(_x, _y);
		for (int j = 1; j < N + 1; j++) {
			if (input[i][j] == 0) { //사용자가 클릭X 상태
				cout << "□";
			}
			else if (input[i][j] == 1) { //사용자가 클릭 O
				if (mine[i][j] == 9) {
					cout << "♨";
				}
				else {
					cout << " " << mine[i][j];
				}
			}
			else if (input[i][j] == 2) { //깃발 상태
				cout << "★";
			}
		}
		cout << endl;
		_y++;
	}
	_y = 5;
	set_color(14, 0);
	gotoxy(10 + N - 8, _y + N + 1);
	cout << "지뢰 개수 : " << countMine() << "개" << endl;
	gotoxy(10 + N - 8, _y + N + 3);
	cout << "남은 깃발 : " << countMine() - countFlag() << "개" << endl;
	howPlay();
}

int MineSweeper::countMine()
{
	int count = 0;

	for (int i = 1; i < N + 1; i++) {
		for (int j = 1; j < N + 1; j++) {
			if (mine[i][j] == 9) {
				count++;
			}
		}
	}

	return count;
}

int MineSweeper::countFlag()
{
	int flagCount = 0;

	for (int i = 1; i < N + 1; i++) {
		for (int j = 1; j < N + 1; j++) {
			if (input[i][j] == 2) {
				flagCount++;
			}
		}
	}

	return flagCount;
}

void MineSweeper::howPlay()
{
	set_color(7, 0);
	gotoxy(10 + N - 10, _y + N + 5);
	cout << "조작키 : ↑  → ↓ ←" << endl;
	gotoxy(10 + N - 9, _y + N + 7);
	cout << "확인 : D, 깃발 : F" << endl;
}

//D를 눌렀을때, 해당 칸을 여는 함수
void MineSweeper::openMine(const int& x, const int& y)
{
	if (input[y][x] == 0)
	{
		input[y][x] = 1;
		if (mine[y][x] == 0) {
			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {
					//생성된 Mine 배열을 넘어가지 않는다면 재귀함수 ! => 자동 펼침 구현.
					if ((x + i > 0 && x + i <= N) && (y + j > 0 && y + j <= N)) {
						openMine(x + i, y + j);
					}
				}
			}
		}
	}
}

//D버튼을 눌렀을때
void MineSweeper::pressD(const int& x, const int& y)
{
	int ix = (x - 10 + 2) / 2;
	int iy = y - 5 + 1;
	//배열이 출력되는 순서는 반대.
	openMine(ix, iy);
	if (mine[iy][ix] == 9) {
		for (int i = 1; i < N + 1; i++) {
			for (int j = 1; j < N + 1; j++) {
				if (mine[i][j] == 9 && input[i][j] == 0) {
					input[i][j] = 1;
				}
			}
		}
	}
}

void MineSweeper::pressF(const int& x, const int& y)
{
	int ix = (x - 10 + 2) / 2;
	int iy = y - 5 + 1;

	if (input[iy][ix] == 0 && countFlag() < countMine()) {
		input[iy][ix] = 2;
	}
	else if (input[iy][ix] == 2) {
		input[iy][ix] = 0;
	}
}

void MineSweeper::saveBackM()
{
	ofstream fout("save_mine_file.txt");
	if (!fout.is_open()) {
		cerr << "이어하기 실패!";
		exit(0);
	}
	fout << N << endl;
	for (int i = 0; i < N + 2; i++) {
		for (int j = 0; j < N + 2; j++) {
			fout << mine[i][j] << " ";
		}
		fout << endl;
	}
}

void MineSweeper::saveBackI()
{
	ofstream fout("save_input_file.txt");
	if (!fout.is_open()) {
		cerr << "이어하기 실패!";
		exit(0);
	}
	fout << N << endl;
	for (int i = 0; i < N + 2; i++) {
		for (int j = 0; j < N + 2; j++) {
			fout << input[i][j] << " ";
		}
		fout << endl;
	}
}

void MineSweeper::saveReplay()
{
	shared_ptr<shared_ptr<int[]>[]> replayF(new shared_ptr<int[]>[N + 2]);

	for (int i = 0; i < N + 2; i++) {
		replayF[i] = shared_ptr<int[]>(new int[N + 2]);
	}

	for (int i = 0; i < N + 2; i++) {
		for (int j = 0; j < N + 2; j++) {
			replayF[i][j] = input[i][j];
		}
	}

	replay.push_back(replayF);
}

void MineSweeper::printReplay(shared_ptr<shared_ptr<int[]>[]>& rp)
{
	setCursorView(FALSE); //커서 안보이게!

	gotoxy(10 + N - 5, 1);
	set_color(50, 0);
	cout << "REPLAY <<<<<" << endl;
	set_color(7, 0);

	for (int i = 1; i < N + 1; i++) {
		gotoxy(_x, _y);
		for (int j = 1; j < N + 1; j++) {
			if (rp[i][j] == 0) { //사용자가 클릭X 상태
				cout << "□";
			}
			else if (rp[i][j] == 1) { //사용자가 클릭 O
				if (mine[i][j] == 9) {
					cout << "♨";
				}
				else {
					cout << " " << mine[i][j];
				}
			}
			else if (rp[i][j] == 2) { //깃발 상태
				cout << "★";
			}
		}
		cout << endl;
		_y++;
	}
	_y = 5;

	gotoxy(5, _y + N + 3);
	cout << "←" << endl;
	gotoxy(5, _y + N + 4);
	cout << "이전" << endl;
	gotoxy(10 + N * 2 + 3, _y + N + 3);
	cout << "→" << endl;
	gotoxy(10 + N * 2 + 1, _y + N + 4);
	cout << "다음" << endl;

	gotoxy(10 + N - 13, _y + N + 9);
	cout << "press space to exit replay." << endl;
}

//리플레이 보여주기.
void MineSweeper::showReplay()
{
	int end = 0;
	auto it = replay.begin();

	while (1) {
		printReplay(*it);
		while (1) {
			//&0x8000
			if (GetAsyncKeyState(VK_LEFT) & 0x0001) {
				if (it == replay.begin()) break;
				else {
					--it;
					break;
				}
			}
			if (GetAsyncKeyState(VK_RIGHT) & 0x0001) {
				++it;
				if (it == replay.end()) --it;
				break;

			}
			/*gotoxy(0, 0);
			cout << x << ", " << y << endl;*/


			if (GetAsyncKeyState(VK_SPACE) & 0x0001) {
				end = 1;
				break;
			}
			Sleep(100);
		}
		if (end == 1) break;
	}
}

//게임이 끝나는 조건.
int MineSweeper::endGame()
{
	int count = 0;
	for (int i = 1; i < N + 1; i++) {
		for (int j = 1; j < N + 1; j++) {
			if (mine[i][j] == 9 && input[i][j] == 2) {
				count++;
			}
		}
	}

	if (countMine() == count) {
		return 1;
	}
	for (int i = 1; i < N + 1; i++) {
		for (int j = 1; j < N + 1; j++) {
			if (mine[i][j] == 9 && input[i][j] == 1) {
				return 2;
			}
		}
	}
	return 0;
}

//이겼을때 화면.
void MineSweeper::win()
{
	setCursorView(FALSE);
	Sleep(900);
	system("cls");

	system("mode con:cols=88 lines=11");
	gotoxy(10, 3);
	cout << "■      ■  ■■■■■  ■      ■    ■          ■  ■  ■      ■" << endl;
	gotoxy(10, 4);
	cout << "  ■  ■    ■      ■  ■      ■    ■          ■  ■  ■■    ■" << endl;
	gotoxy(10, 5);
	cout << "    ■      ■      ■  ■      ■    ■    ■    ■  ■  ■  ■  ■" << endl;
	gotoxy(10, 6);
	cout << "    ■      ■      ■  ■      ■    ■    ■    ■  ■  ■    ■■" << endl;
	gotoxy(10, 7);
	cout << "    ■      ■■■■■  ■■■■■    ■■■■■■■  ■  ■      ■" << endl;

	Sleep(1500);
}

//졌을때 화면.
void MineSweeper::lose()
{
	setCursorView(FALSE);
	Sleep(900);
	system("cls");

	system("mode con:cols=102 lines=11");
	gotoxy(10, 3);
	cout << "■      ■  ■■■■■  ■      ■    ■          ■■■■■  ■■■■■  ■■■■" << endl;
	gotoxy(10, 4);
	cout << "  ■  ■    ■      ■  ■      ■    ■          ■      ■  ■          ■      " << endl;
	gotoxy(10, 5);
	cout << "    ■      ■      ■  ■      ■    ■          ■      ■  ■■■■■  ■■■  " << endl;
	gotoxy(10, 6);
	cout << "    ■      ■      ■  ■      ■    ■          ■      ■          ■  ■       " << endl;
	gotoxy(10, 7);
	cout << "    ■      ■■■■■  ■■■■■    ■■■■■  ■■■■■  ■■■■■  ■■■■" << endl;

	Sleep(1500);
}

void MineSweeper::play() {
	char con[100];
	string tem;

	//커서 사이즈와 visible여부
	static HANDLE hOut;
	CONSOLE_CURSOR_INFO cInfo;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cInfo.dwSize = 100;
	cInfo.bVisible = TRUE;
	SetConsoleCursorInfo(hOut, &cInfo);

	int menu;
	menu = selectMenu();

	if (menu == 1) {
		initData();
		setLevel();
		initMap();
		saveBackM(); // mine 맵은 한번만 저장!
	}
	else if (menu == 2) {
		contGame();
	}
	else if (menu == 3) {
		exit(0);
	}

	//콘솔창 조절
	tem = "mode con:cols=" + to_string(N * 2 + 20) + " lines=" + to_string(N + 20);
	strcpy_s(con, tem.c_str());

	system(con);
	//showArray();
	//system("pause");
	system("cls");

	int x = 10;
	int y = 5;

	//cInfo.bVisible = TRUE;
	while (1) {
		saveReplay();
		printMap();
		if (endGame() == 1) {
			win();
			break;
		}
		else if (endGame() == 2) {
			lose();
			break;
		}

		while (1) {
			//&0x8000
			if (GetAsyncKeyState(VK_LEFT) & 0x0001) {
				x -= 2;
				if (x < 10) x = 10;
			}
			if (GetAsyncKeyState(VK_RIGHT) & 0x0001) {
				x += 2;
				if (x > 10 + N * 2 - 2) x = 10 + N * 2 - 2;
			}
			if (GetAsyncKeyState(VK_UP) & 0x0001) {
				y -= 1;
				if (y < 5) y = 5;
			}
			if (GetAsyncKeyState(VK_DOWN) & 0x0001) {
				y += 1;
				if (y > 5 + N - 1) y = 5 + N - 1;
			}

			gotoxy(x, y);

			if (GetAsyncKeyState(0x44) & 0x0001) {
				pressD(x, y);
				break;
			}
			if (GetAsyncKeyState(0x46) & 0x0001) {
				pressF(x, y);
				break;
			}

			Sleep(100);
		}
		//input 데이터 버튼 누를때마다 저장.
		saveBackI();
		system("cls");
	}
	system("cls");

	setCursorView(TRUE);
	system("mode con:cols=60 lines=11");
	int sel = 0;
	gotoxy(30 - 12, 3);
	cout << "리플레이를 보시겠습니까?" << endl;
	gotoxy(13, 5);
	cout << "♡ 예" << endl;
	gotoxy(40, 5);
	cout << "♡ 아니오" << endl;
	gotoxy(30 - 6, 7);
	cout << "PRESS SPACE." << endl;
	gotoxy(30 - 6, 9);
	cout << "※유의사항※" << endl;
	gotoxy(30 - 12, 10);
	cout << "이어하기시 리플레이 제약" << endl;
	x = 13;
	y = 4;
	while (1) {
		if (GetAsyncKeyState(VK_LEFT) & 0x0001) {
			x -= 27;
			if (x < 13) x = 13;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x0001) {
			x += 27;
			if (x > 40) x = 40;
		}

		gotoxy(x, y);

		if (GetAsyncKeyState(VK_SPACE) & 0x0001) {
			if (x == 13) sel = 1;
			break;
		}
		Sleep(100);
	}
	if (sel == 1) {
		system(con);
		showReplay();
	}

	Sleep(200);
	system("cls");

	system("mode con:cols=60 lines=12");
	gotoxy(30 - 12, 4);
	cout << "THANK YOU FOR PLAYING!!!" << endl;
	/*mine = nullptr;
	input = nullptr;*/
}

void gotoxy(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void setCursorView(bool visible) {
	CONSOLE_CURSOR_INFO cursor = { 1, visible };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

void set_color(int color, int bgcolor) {
	color &= 0xf;
	bgcolor &= 0xf;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgcolor << 4) | color);
}
