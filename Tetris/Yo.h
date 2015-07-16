#ifndef  YO_H
#define  YO_H
#include <time.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <ctime>
#include <thread>
#include <conio.h>

using namespace std;

void sleep(unsigned int);
int random(int);

class Board
{
public:
	Board();
	void Game();
private:
	int score;
	bool *notLose;
	char board[100][100];
	thread user;
	thread mov;
	thread clear;
	void clearRow();
	void Score(int x);
	void printBoard();
	void Tshape();
	void Tmove();
	void Tuser(int a, int b, bool x);
	void Ishape();
	void Imove();
	void Iuser(int a, int b, bool x);
	void L1shape();
	void L1move();
	void L1user(int a, int b, bool x);
	void L2shape();
	void L2move();
	void L2user(int a, int b, bool x);
	void Cubeshape();
	void Cubemove();
	void Cubeuser(int a, int b, bool x);
	void S1shape();
	void S1move();
	void S1user(int a, int b, bool x);
	void S2shape();
	void S2move();
	void S2user(int a, int b, bool x);
	void Movement();
	void userInput();
	void Selector();
};

#endif //  YO_H
