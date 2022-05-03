#include <iostream>
#include "MineSweeper.h"

using namespace std;

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	cout << "전우석, 학번 : 201510595\n" << endl;

	MineSweeper ms;
	ms.play();
}