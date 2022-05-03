#pragma once
#include <memory>
#include <vector>
using namespace std;
//using std::shared_ptr;
class MineSweeper
{
private:
	int N = 0; // N x N �� ����ã��
	shared_ptr<shared_ptr<int[]>[]> mine = nullptr; //���� ��ġ ����
	shared_ptr<shared_ptr<int[]>[]> input = nullptr; //����� �Է� ����
	vector<shared_ptr<shared_ptr<int[]>[]>> replay; //���÷��̿� ���
public:
	MineSweeper(); //������
	MineSweeper(const MineSweeper& arr); //���� ������
	MineSweeper(MineSweeper&& arr) noexcept; //�̵� ������
	~MineSweeper(); //�Ҹ���
	MineSweeper& operator=(const MineSweeper& arr); //���Կ�����
	MineSweeper& operator=(MineSweeper&& arr) noexcept; //�̵����Կ�����

	void initData(); //����ڰ� �Է��� data��� Ŭ���� �ʱ�ȭ
	void startScreen(); //����ȭ���� �ٹ̴� �Լ�
	int selectMenu(); //���� �޴��� ���� �Լ�
	void setMine(const int& level); //�Է� ���� level�� ���� ���ڸ� �ɴ� �Լ�
	void contGame(); //�̾��ϱ�
	void initMap();  //�ֺ� ���� ������ ���� ���� ĭ�� ����ϴ� �Լ�
	void setLevel(); //���� ����
	void printMap(); //mine ���� input�ʰ� ������ ������ִ� �Լ�
	int countMine(); //�� ���� ���� ����
	int countFlag(); //��� ���� ����
	void howPlay();  //���ӹ�� ����ִ� �Լ�.
	void openMine(const int& x, const int& y); //ĭ�� �����ִ� �Լ�(�ڵ���ħ ����)
	void pressD(const int& x, const int& y); //openmine�� ȣ���ϴ� ĭ ���� �Լ�
	void pressF(const int& x, const int& y); //����� �����ִ� �Լ�
	void saveBackM(); //�̾��ϱ�� Mine ������� ����.
	void saveBackI(); //�̾��ϱ�� Input ������� ����.
	void saveReplay(); //���÷��� ���Ϳ� ���÷��� ������ ���ʷ� ����!
	void printReplay(shared_ptr<shared_ptr<int[]>[]>& rp); //���÷��� ������ ���!
	void showReplay(); //���÷��� �� ���ʴ�� �����ִ� �޼���
	int endGame(); //���� ���� �Լ�
	void win();  //�¸� ȭ��
	void lose();  //�й� ȭ��
	void play(); //���� �÷��� �Լ�
};

void gotoxy(int x, int y);
void setCursorView(bool visible);
void set_color(int color, int bgcolor);
