#include "Yo.h"

void sleep(unsigned int mseconds)
{
	clock_t goal = mseconds + clock();
	while (goal > clock());
}

int random(int a)
{
	srand((unsigned)time(NULL));
	return rand() % a;
}


Board::Board()
{
	int x;                                                    //Tetris board is 10 spaces long and 18 tall. Center is at y=39
	int y;
	for (x = 0; x<20; x++)
	{
		y = 0;
		for (y = 0; y<80; y++)
		{
			board[x][y] = ' ';                                //This defines the entire terminal as a board space
		}
	}

	for (x = 0; x <= 18; x++)
	{
		board[x][34] = '|';
		board[x][45] = '|';                                   //This defines the actual board on said board space
		if (x == 18)
		{
			for (y = 35; y<45; y++)
			{
				board[x][y] = '_';
			}
		}
	}

	board[9][60] = 'S';
	board[9][61] = 'c';
	board[9][62] = 'o';										//Prints the score section
	board[9][63] = 'r';
	board[9][64] = 'e';
	board[9][65] = ':';

	board[10][61] = '0';
	board[10][62] = '0';
	board[10][63] = '0';
	board[10][64] = '0';
}

void Board::Game()
{
	bool notLose = true;
	score = 0;
	printBoard();                                          //Prints the board for the first time-clean
	sleep(1000);
	if (system("CLS")) system("clear");                    //Clears the board                                       

	user = thread(&Board::userInput, this);					//Defines user input thread
	clear = thread(&Board::clearRow, this);					//Defines the row clear thread


	user;
	clear;

	while (notLose)
	{
		Movement();											//Creates a loop for when Movement ends
		notLose = false;
	}

	sleep(1000);
	if (system("CLS")) system("clear");						//Ends game by clearing screen
	cout << "The game has ended\n";
	sleep(5000);
}

void Board::printBoard()
{
	int x;
	int y;
	for (x = 0; x<20; x++)
	{
		y = 0;
		for (y = 0; y<80; y++)
		{
			cout << board[x][y];
		}															  //This prints the board

	}
	cout << endl;
}



void Board::Tshape()
{

	board[0][38] = '*';
	board[0][39] = '*';
	board[0][40] = '*';
	board[1][39] = '*';

	printBoard();
}

void Board::Ishape()
{
	board[0][38] = '*';
	board[0][39] = '*';
	board[0][40] = '*';
	board[0][41] = '*';

	printBoard();
}

void Board::L1shape()
{
	board[0][38] = '*';
	board[1][38] = '*';
	board[1][39] = '*';
	board[1][40] = '*';
	board[1][41] = '*';

	printBoard();
}                                                             //Use these as extended functions to board.

void Board::L2shape()
{
	board[0][41] = '*';
	board[1][38] = '*';
	board[1][39] = '*';
	board[1][40] = '*';
	board[1][41] = '*';

	printBoard();
}

void Board::Cubeshape()
{
	board[0][39] = '*';
	board[0][40] = '*';
	board[1][39] = '*';
	board[1][40] = '*';

	printBoard();
}

void Board::S1shape()
{
	board[1][38] = '*';
	board[1][39] = '*';
	board[0][39] = '*';
	board[0][40] = '*';

	printBoard();
}

void Board::S2shape()
{
	board[0][38] = '*';
	board[0][39] = '*';
	board[1][39] = '*';
	board[1][40] = '*';

	printBoard();
}



void Board::Score(int x)
{
	score += x;
	int temp = score;
	int i = 0;
	while (score > 0)
	{
		score /= 10;
		i++;
	}
	score = temp;

	char a[5];		
	_itoa(x, a, 10);

	if (i == 2)
	{
		board[10][63] = a[0];
	}
	
	else if (i == 3)
	{
		board[10][62] = a[0];
		board[10][63] = a[1];
	}

	else if (i == 4)
	{
		board[10][61] = a[0];
		board[10][62] = a[1];
		board[10][62] = a[2];
	}
}

void Board::clearRow()
{
	while (true)
	{
		for (int x = 17; x >= 0; x--)
		{
			if (board[x][35] == '*' && board[x][36] == '*' && board[x][37] == '*' && board[x][38] == '*' && board[x][39] == '*' && board[x][40] == '*' && board[x][41] == '*' && board[x][42] == '*' && board[x][43] == '*' && board[x][44] == '*')
			{
				for (int y = 35; y < 45; y++)
				{
					board[x][y] = ' ';															//Erases a row that's been completed
				}

				for (int b = 44; b > 33; b--)
				{
					for (int a = 16; a >= 0; a--)
					{
						if (board[a][b] == '*' && board[a + 1][b] == ' ')
						{
							board[a + 1][b] = '*';
							board[a][b] = ' ';

						}
					}
				}
				Score(100);
			}
		}
	}
}

void Board::userInput()
{
	while (true)
	{


		if (_getch() == 'a')
		{
			bool breaker = false;
			int a = 0, b = 0;
			for (int i = 0; i < 18; i++)
			{
				for (int j = 34; j < 45; j++)
				{
					if (board[i][j] == '*' && board[i + 1][j] == ' ')												//Looks for the shape
					{
						a = i;
						b = j;
						breaker = true;
						break;
					}
				}
				if (breaker)
					break;
			}


			if (board[a + 1][b] == ' ' && board[a + 1][b + 2] == ' ' && board[a + 2][b + 1] == ' ' && board[a][b] == '*' && board[a + 1][b + 1] == '*' && board[a][b + 2] == '*')			//Checks for the shape
				Tuser(a, b, 0);

			if (board[a + 1][b] == ' ' && board[a + 1][b + 1] == ' ' && board[a + 1][b + 2] == ' ' && board[a + 1][b + 3] == ' ' && board[a][b] == '*' && board[a][b + 1] == '*' && board[a][b + 2] == '*' && board[a][b + 3] == '*' && board[a - 1][b] == ' ' && board[a - 1][b + 3] == ' ')
				Iuser(a, b, 0);

			if (board[a + 1][b] == ' ' && board[a + 1][b + 1] == ' ' && board[a + 1][b + 2] == ' ' && board[a + 1][b + 3] == ' ' && board[a][b] == '*' && board[a][b + 1] == '*' && board[a][b + 2] == '*' && board[a][b + 3] == '*' && board[a - 1][b] == '*')
				L1user(a, b, 0);

			if (board[a + 1][b] == ' ' && board[a + 1][b + 1] == ' ' && board[a + 1][b + 2] == ' ' && board[a + 1][b + 3] == ' ' && board[a][b] == '*' && board[a][b + 1] == '*' && board[a][b + 2] == '*' && board[a][b + 3] == '*' && board[a - 1][b + 3] == '*')
				L2user(a, b, 0);

			if (board[a + 1][b] == ' ' && board[a + 1][b + 1] == ' ' && board[a][b] == '*' && board[a][b + 1] == '*' && board[a - 1][b] == '*' && board[a - 1][b + 1] == '*')
				Cubeuser(a, b, 0);

			if (board[a + 2][b - 1] == ' ' && board[a + 2][b - 2] == ' ' && board[a + 1][b - 1] == '*' && board[a + 1][b - 2] == '*')
				S1user(a, b, 0);

			if (board[a + 2][b + 1] == ' ' && board[a + 2][b + 2] == ' ' && board[a + 1][b + 1] == '*' && board[a + 1][b + 2] == '*')
				S2user(a, b, 0);
		}



		if (_getch() == 'd')
		{
			bool breaker = false;
			int a = 0, b = 0;
			for (int i = 0; i < 18; i++)
			{
				for (int j = 34; j < 45; j++)
				{
					if (board[i][j] == '*' && board[i + 1][j] == ' ')												//Looks for the shape
					{
						a = i;
						b = j;
						breaker = true;
						break;
					}
				}
				if (breaker)
					break;
			}


			if (board[a + 1][b] == ' ' && board[a + 1][b + 2] == ' ' && board[a + 2][b + 1] == ' ' && board[a][b] == '*' && board[a + 1][b + 1] == '*' && board[a][b + 2] == '*')			//Checks for the shape
				Tuser(a, b, 1);

			if (board[a + 1][b] == ' ' && board[a + 1][b + 1] == ' ' && board[a + 1][b + 2] == ' ' && board[a + 1][b + 3] == ' ' && board[a][b] == '*' && board[a][b + 1] == '*' && board[a][b + 2] == '*' && board[a][b + 3] == '*' && board[a - 1][b] == ' ' && board[a - 1][b + 3] == ' ')
				Iuser(a, b, 1);

			if (board[a + 1][b] == ' ' && board[a + 1][b + 1] == ' ' && board[a + 1][b + 2] == ' ' && board[a + 1][b + 3] == ' ' && board[a][b] == '*' && board[a][b + 1] == '*' && board[a][b + 2] == '*' && board[a][b + 3] == '*' && board[a - 1][b] == '*')
				L1user(a, b, 1);

			if (board[a + 1][b] == ' ' && board[a + 1][b + 1] == ' ' && board[a + 1][b + 2] == ' ' && board[a + 1][b + 3] == ' ' && board[a][b] == '*' && board[a][b + 1] == '*' && board[a][b + 2] == '*' && board[a][b + 3] == '*' && board[a - 1][b + 3] == '*')
				L2user(a, b, 1);

			if (board[a + 1][b] == ' ' && board[a + 1][b + 1] == ' ' && board[a][b] == '*' && board[a][b + 1] == '*' && board[a - 1][b] == '*' && board[a - 1][b + 1] == '*')
				Cubeuser(a, b, 1);

			if (board[a + 2][b - 1] == ' ' && board[a + 2][b - 2] == ' ' && board[a + 1][b - 1] == '*' && board[a + 1][b - 2] == '*')
				S1user(a, b, 1);

			if (board[a + 2][b + 1] == ' ' && board[a + 2][b + 2] == ' ' && board[a + 1][b + 1] == '*' && board[a + 1][b + 2] == '*')
				S2user(a, b, 1);
		}
	}
}

void Board::Movement()
{
	int time = 1000;
	while (true)
	{
		sleep(time);
		time -= 10;
		for (int i = 0; i < 45; i++)
		{
			if (board[2][i] == '*')
				return;
		}
		Score(10);
		if (system("CLS")) system("clear");
		Selector();
	}
}

void Board::Selector()
{
	int x;
	x = random(7);
	switch (x)
	{
	case 0:
		Tshape();
		Tmove();
		break;
	case 1:
		Ishape();
		Imove();
		break;
	case 2:
		L1shape();
		L1move();
		break;
	case 3:
		L2shape();
		L2move();											//Used to select the next shape to come down the board. Uses randomizer in header.
		break;
	case 4:
		Cubeshape();
		Cubemove();
		break;
	case 5:
		S1shape();
		S1move();
		break;
	case 6:
		S2shape();
		S2move();
		break;
	default:
		NULL;
		break;
	}
}



void Board::Tmove()
{
	bool canMove = true;
	while (canMove)
	{
		sleep(500);
		bool breaker = false;
		int a = 0, b = 0;
		for (int i = 0; i < 18; i++)
		{
			for (int j = 34; j < 45; j++)
			{
				if (board[i][j] == '*' && board[i + 1][j] == ' ')																																//Looks for the tshape
				{
					a = i;
					b = j;
					breaker = true;
					break;
				}
			}
			if (breaker)
				break;
		}

		if (board[a + 1][b] != ' ' || board[a + 1][b + 2] != ' ' || board[a + 2][b + 1] != ' ' || board[a][b] != '*' || board[a + 1][b + 1] != '*' || board[a][b + 2] != '*')					//Makes sure the tshape can move
			canMove = false;

		if (canMove)
		{
			board[a + 1][b] = '*';
			board[a + 1][b + 2] = '*';
			board[a + 2][b + 1] = '*';																																							//Moves the tshape
			board[a][b] = ' ';
			board[a][b + 1] = ' ';
			board[a][b + 2] = ' ';
		}


		sleep(1000);
		if (system("CLS")) system("clear");
		printBoard();


	}
}

void Board::Tuser(int a, int b, bool x)
{

		bool canLeft = true;
		bool canRight = true;

		if (x == 0)
		{
			if (board[a][b] != '*' || board[a + 1][b] != ' ' || board[a][b - 1] == '|' || board[a][b - 1] == '*') 					//Makes sure the tshape can move left
				canLeft = false;

			if (canLeft)
			{
				board[a][b - 1] = '*';
				board[a + 1][b] = '*';
				board[a][b + 2] = ' ';																								//Moves tshape left
				board[a + 1][b + 1] = ' ';
			}
		}

		if (x == 1)
		{
			if (board[a][b] != '*' || board[a + 1][b] != ' ' || board[a][b + 3] == '|' || board[a][b + 3] == '*')					//Makes sure the tshape can move right
				canRight = false;

			if (canRight)
			{
				board[a][b + 3] = '*';
				board[a + 1][b + 2] = '*';																							//Moves tshape right
				board[a][b] = ' ';
				board[a + 1][b + 1] = ' ';
			}

		}

}

void Board::Imove()
{
	bool canMove = true;
	while (canMove)
	{
		sleep(500);
		bool breaker = false;
		int a = 0, b = 0;
		for (int i = 0; i < 18; i++)
		{
			for (int j = 34; j < 45; j++)
			{
				if (board[i][j] == '*' && board[i + 1][j] == ' ')												//Looks for the ishape
				{
					a = i;
					b = j;
					breaker = true;
					break;
				}
			}
			if (breaker)
				break;
		}

		if (board[a + 1][b] != ' ' || board[a + 1][b + 1] != ' ' || board[a + 1][b + 2] != ' ' || board[a + 1][b + 3] != ' ' || board[a][b] != '*' || board[a][b + 1] != '*' || board[a][b + 2] != '*' || board[a][b + 3] != '*')					//Makes sure the tishape can move
			canMove = false;

		if (canMove)
		{
			board[a + 1][b] = '*';
			board[a + 1][b + 1] = '*';
			board[a + 1][b + 2] = '*';
			board[a + 1][b + 3] = '*';
			board[a][b] = ' ';
			board[a][b + 1] = ' ';
			board[a][b + 2] = ' ';																				//Moves the ishape
			board[a][b + 3] = ' ';
		}

		sleep(1000);
		if (system("CLS")) system("clear");
		printBoard();
	}
}

void Board::Iuser(int a, int b, bool x)
{

		bool canLeft = true;
		bool canRight = true;

		if (x == 0)
		{
			if (board[a][b] != '*' || board[a + 1][b] != ' ' || board[a][b - 1] == '|' || board[a][b - 1] == '*') 					//Makes sure the ishape can move left
				canLeft = false;

			if (canLeft)
			{
				board[a][b - 1] = '*';
				board[a][b + 3] = ' ';																								//Moves ishape left
			}
		}

		if (x == 1)
		{
			if (board[a][b] != '*' || board[a + 1][b] != ' ' || board[a][b + 4] == '|' || board[a][b + 4] == '*')					//Makes sure the ishape can move right
				canRight = false;

			if (canRight)
			{
				board[a][b + 4] = '*';
				board[a][b] = ' ';
			}
		}

}

void Board::L1move()
{
	bool canMove = true;
	while (canMove)
	{
		sleep(500);
		bool breaker = false;
		int a = 0, b = 0;
		for (int i = 0; i < 18; i++)
		{
			for (int j = 34; j < 45; j++)
			{
				if (board[i][j] == '*' && board[i + 1][j] == ' ')												//Looks for the l1shape
				{
					a = i;
					b = j;
					breaker = true;
					break;
				}
			}
			if (breaker)
				break;
		}

		if (board[a + 1][b] != ' ' || board[a + 1][b + 1] != ' ' || board[a + 1][b + 2] != ' ' || board[a + 1][b + 3] != ' ' || board[a][b] != '*' || board[a][b + 1] != '*' || board[a][b + 2] != '*' || board[a][b + 3] != '*')					//Makes sure the l1shape can move
			canMove = false;

		if (canMove)
		{
			board[a + 1][b] = '*';
			board[a + 1][b + 1] = '*';
			board[a + 1][b + 2] = '*';																			//Moves the l1shape
			board[a + 1][b + 3] = '*';
			board[a - 1][b] = ' ';
			board[a][b + 1] = ' ';
			board[a][b + 2] = ' ';
			board[a][b + 3] = ' ';
		}

		sleep(1000);
		if (system("CLS")) system("clear");
		printBoard();
	}
}

void Board::L1user(int a, int b, bool x)
{
	bool canLeft = true;
	bool canRight = true;

	if (x == 0)
	{
		if (board[a - 1][b - 1] != ' ' || board[a][b - 1] != ' ') 																//Makes sure the l1shape can move left
			canLeft = false;

		if (canLeft)
		{
			board[a][b - 1] = '*';
			board[a - 1][b - 1] = '*';
			board[a - 1][b] = ' ';
			board[a][b + 3] = ' ';																								//Moves l1shape left
			board[a - 1][b] = ' ';
		}
	}

	if (x == 1)
	{
		if (board[a - 1][b + 1] != ' ' || board[a][b + 4] != ' ')																//Makes sure the l1shape can move right
			canRight = false;

		if (canRight)
		{
			board[a][b + 4] = '*';
			board[a - 1][b + 1] = '*';
			board[a - 1][b] = ' ';																								//Moves l1shape right
			board[a][b] = ' ';
			board[a - 1][b] = ' ';
		}
	}


	
}

void Board::L2move()
{
	bool canMove = true;
	while (canMove)
	{
		sleep(500);
		bool breaker = false;
		int a = 0, b = 0;
		for (int i = 0; i < 18; i++)
		{
			for (int j = 34; j < 45; j++)
			{
				if (board[i][j] == '*' && board[i + 1][j] == ' ')												//Looks for the l2shape
				{
					a = i;
					b = j;
					breaker = true;
					break;
				}
			}
			if (breaker)
				break;
		}

		if (board[a + 1][b] != ' ' || board[a + 1][b + 1] != ' ' || board[a + 1][b + 2] != ' ' || board[a + 1][b + 3] != ' ' || board[a][b] != '*' || board[a][b + 1] != '*' || board[a][b + 2] != '*' || board[a][b + 3] != '*')					//Makes sure the l2shape can move
			canMove = false;

		if (canMove)
		{
			board[a + 1][b] = '*';
			board[a + 1][b + 1] = '*';
			board[a + 1][b + 2] = '*';																			//Moves the l2shape
			board[a + 1][b + 3] = '*';
			board[a][b] = ' ';
			board[a][b + 1] = ' ';
			board[a][b + 2] = ' ';
			board[a - 1][b + 3] = ' ';
		}

		sleep(1000);
		if (system("CLS")) system("clear");
		printBoard();
	}
}

void Board::L2user(int a, int b, bool x)
{
	bool canLeft = true;
	bool canRight = true;

	if (x == 0)
	{
		if (board[a][b - 1] != ' ' || board[a - 1][b + 2] != ' ') 																//Makes sure the l2shape can move left
			canLeft = false;

		if (canLeft)
		{
			board[a][b - 1] = '*';
			board[a - 1][b + 2] = '*';
			board[a - 1][b + 3] = ' ';
			board[a][b + 3] = ' ';																								//Moves l2shape left
			board[a - 1][b + 3] = ' ';
		}
	}

	if (x == 1)
	{
		if (board[a - 1][b + 4] != ' ' || board[a][b + 4] != ' ')																//Makes sure the l2shape can move right
			canRight = false;

		if (canRight)
		{
			board[a][b + 4] = '*';
			board[a - 1][b + 4] = '*';	
			board[a - 1][b + 3] = ' ';																							//Moves l2shape right
			board[a][b] = ' ';
			board[a - 1][b + 3] = ' ';
		}
	}

}

void Board::Cubemove()
{
	bool canMove = true;
	while (canMove)
	{
		sleep(500);
		bool breaker = false;
		int a = 0, b = 0;
		for (int i = 0; i < 18; i++)
		{
			for (int j = 34; j < 45; j++)
			{
				if (board[i][j] == '*' && board[i + 1][j] == ' ')																							//Looks for the cubeshape
				{
					a = i;
					b = j;
					breaker = true;
					break;
				}
			}
			if (breaker)
				break;
		}

		if (board[a + 1][b] != ' ' || board[a + 1][b + 1] != ' ' || board[a][b] != '*' || board[a][b + 1] != '*')											//Makes sure the cubeshape can move
			canMove = false;

		if (canMove)
		{
			board[a + 1][b] = '*';
			board[a + 1][b + 1] = '*';																														//Moves the cubeshape
			board[a - 1][b] = ' ';
			board[a - 1][b + 1] = ' ';
		}

		sleep(1000);
		if (system("CLS")) system("clear");
		printBoard();
	}
}

void Board::Cubeuser(int a, int b, bool x)
{

		bool canLeft = true;
		bool canRight = true;

		if (x == 0)
		{
			if (board[a][b] != '*' || board[a + 1][b] != ' ' || board[a][b - 1] == '|' || board[a][b - 1] == '*') 					//Makes sure the cubeshape can move left
				canLeft = false;

			if (canLeft)
			{
				board[a][b - 1] = '*';
				board[a - 1][b - 1] = '*';
				board[a][b + 1] = ' ';																								//Moves cubeshape left
				board[a - 1][b + 1] = ' ';
			}
		}


		if (x == 1)
		{
			if (board[a][b] != '*' || board[a + 1][b] != ' ' || board[a][b + 2] == '|' || board[a][b + 2] == '*')					//Makes sure the cubeshape can move right
				canRight = false;

			if (canRight)
			{
				board[a][b + 2] = '*';
				board[a - 1][b + 2] = '*';																							//Moves cubeshape right
				board[a][b] = ' ';
				board[a - 1][b] = ' ';
			}
		}

}

void Board::S1move()
{
	bool canMove = true;
	while (canMove)
	{
		sleep(500);
		bool breaker = false;
		int a = 0, b = 0;
		for (int i = 0; i < 18; i++)
		{
			for (int j = 34; j < 45; j++)
			{
				if (board[i][j] == '*' && board[i + 1][j] == ' ')																										//Looks for the s1shape
				{
					a = i;
					b = j;
					breaker = true;
					break;
				}
			}
			if (breaker)
				break;
		}

		if (board[a + 2][b - 1] != ' ' || board[a + 2][b - 2] != ' ' || board[a + 1][b - 1] != '*' || board[a + 1][b - 2] != '*')											//Makes sure the s1shape can move
			canMove = false;

		if (canMove)
		{
			board[a + 1][b] = '*';
			board[a + 2][b - 1] = '*';
			board[a + 2][b - 2] = '*';																																	//Moves the s1shape
			board[a][b] = ' ';
			board[a][b - 1] = ' ';
			board[a + 1][b - 2] = ' ';
		}

		sleep(1000);
		if (system("CLS")) system("clear");
		printBoard();
	}
}

void Board::S1user(int a, int b, bool x)
{

		bool canLeft = true;
		bool canRight = true;

		if (x == 0)
		{
			if (board[a][b - 2] != ' ' || board[a + 1][b - 3] != ' ') 																//Makes sure the s1shape can move left
				canLeft = false;

			if (canLeft)
			{
				board[a][b - 2] = '*';
				board[a + 1][b - 3] = '*';
				board[a][b] = ' ';																									//Moves s1shape left
				board[a + 1][b - 1] = ' ';
			}
		}

		if (x == 1)
		{
			if (board[a][b + 1] != ' ' || board[a + 1][b] != ' ' )																//Makes sure the s1shape can move right
				canRight = false;

			if (canRight)
			{
				board[a][b + 1] = '*';
				board[a + 1][b] = '*';																								//Moves s1shape right
				board[a + 1][b - 2] = ' ';
				board[a][b - 1] = ' ';
			}
		}

}

void Board::S2move()
{
	bool canMove = true;
	while (canMove)
	{
		sleep(500);
		bool breaker = false;
		int a = 0, b = 0;
		for (int i = 0; i < 18; i++)
		{
			for (int j = 34; j < 45; j++)
			{
				if (board[i][j] == '*' && board[i + 1][j] == ' ')																									//Looks for the s2shape
				{
					a = i;
					b = j;
					breaker = true;
					break;
				}
			}
			if (breaker)
				break;
		}

		if (board[a + 2][b + 1] != ' ' || board[a + 2][b + 2] != ' ' || board[a + 1][b + 1] != '*' || board[a + 1][b + 2] != '*')											//Makes sure the s2shape can move
			canMove = false;

		if (canMove)
		{
			board[a + 1][b] = '*';
			board[a + 2][b + 1] = '*';
			board[a + 2][b + 2] = '*';																																//Moves the s2shape
			board[a][b] = ' ';
			board[a][b + 1] = ' ';
			board[a + 1][b + 2] = ' ';
		}

		sleep(1000);
		if (system("CLS")) system("clear");
		printBoard();
	}
}

void Board::S2user(int a, int b, bool x)
{

		bool canLeft = true;
		bool canRight = true;

		if (x == 0)
		{
			if (board[a][b - 1] != ' ' || board[a + 1][b] != ' ') 																	//Makes sure the s2shape can move left
				canLeft = false;

			if (canLeft)
			{
				board[a][b - 1] = '*';
				board[a + 1][b] = '*';
				board[a][b + 1] = ' ';																								//Moves s2shape left
				board[a + 1][b + 2] = ' ';
			}
		}

		if (x == 1)
		{
			if (board[a][b] != '*' || board[a + 1][b + 3] != ' ' || board[a][b + 2] != ' ')												//Makes sure the s2shape can move right
				canRight = false;

			if (canRight)
			{
				board[a][b + 2] = '*';
				board[a + 1][b + 3] = '*';																							//Moves s2shape right
				board[a + 1][b + 1] = ' ';
				board[a][b] = ' ';
			}
		}

}