//Author: Yonah Elorza

#include "Yo.h"

int main()
{
	Board();
	Board game;
	string a;

	while(cin)
	{
		cout << endl;
		cout << "Welcome to Tetris!\n";
		cout << "If you want to start playing, type (Play).\n";
		cout << "If you want to see the instructions, type (Instructions)\n";
		cin >> a;
		sleep(2000);

		if(a=="Instructions")
		{
			if (system("CLS")) system("clear");
			cout << endl;
			cout << "To move, press A to go left and D to move right.\n";
			sleep(5000);
			cout << "Your goal is to eliminate the most blocks you can by matching them in a row\n";
			sleep(5000);
			cout << "To make this harder than regular tetris, we removed rotation (it totally wasn't because we had a bunch of diffuculty implementing it)\n";
			sleep(5000);
			cout << "We did feel bad, however, and to make it easier, we added rotation for the cube shape. To rotate it, press Q.\n";
			sleep(5000);
			cout << "You will now return to the main menu.\n";
			sleep(10000);
			if (system("CLS")) system("clear");
		}


		if(a=="Play")
		game.Game();
	}
}









