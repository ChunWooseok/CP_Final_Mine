#pragma once
#include <memory>
#include <vector>
using namespace std;
//using std::shared_ptr;
class MineSweeper
{
private:
	int N = 0; // N x N 맵 지뢰찾기
	shared_ptr<shared_ptr<int[]>[]> mine = nullptr; //지뢰 위치 저장
	shared_ptr<shared_ptr<int[]>[]> input = nullptr; //사용자 입력 저장
	vector<shared_ptr<shared_ptr<int[]>[]>> replay; //리플레이용 백업
public:
	MineSweeper(); //생성자
	MineSweeper(const MineSweeper& arr); //복사 생성자
	MineSweeper(MineSweeper&& arr) noexcept; //이동 생성자
	~MineSweeper(); //소멸자
	MineSweeper& operator=(const MineSweeper& arr); //대입연산자
	MineSweeper& operator=(MineSweeper&& arr) noexcept; //이동대입연산자

	void initData(); //사용자가 입력한 data대로 클래스 초기화
	void startScreen(); //시작화면을 꾸미는 함수
	int selectMenu(); //시작 메뉴를 고르는 함수
	void setMine(const int& level); //입력 받은 level에 따라 지뢰를 심는 함수
	void contGame(); //이어하기
	void initMap();  //주변 지뢰 개수를 세서 본인 칸에 기록하는 함수
	void setLevel(); //레벨 선택
	void printMap(); //mine 맵을 input맵과 대조해 출력해주는 함수
	int countMine(); //총 지뢰 개수 세기
	int countFlag(); //깃발 갯수 세기
	void howPlay();  //게임방법 띄어주는 함수.
	void openMine(const int& x, const int& y); //칸을 열어주는 함수(자동펼침 구현)
	void pressD(const int& x, const int& y); //openmine을 호출하는 칸 선택 함수
	void pressF(const int& x, const int& y); //깃발을 세워주는 함수
	void saveBackM(); //이어하기용 Mine 백업파일 저장.
	void saveBackI(); //이어하기용 Input 백업파일 저장.
	void saveReplay(); //리플레이 백터에 리플레이 데이터 차례로 삽입!
	void printReplay(shared_ptr<shared_ptr<int[]>[]>& rp); //리플레이 데이터 출력!
	void showReplay(); //리플레이 를 차례대로 보여주는 메서드
	int endGame(); //종료 조건 함수
	void win();  //승리 화면
	void lose();  //패배 화면
	void play(); //게임 플레이 함수
};

void gotoxy(int x, int y);
void setCursorView(bool visible);
void set_color(int color, int bgcolor);
