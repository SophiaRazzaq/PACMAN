#include<iostream>
using namespace std;
#include"myconsole.h"
#include"mygraphics.h"

#include <windows.h>
#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#define _WIN32_WINNT 1537
#endif
#include <WinCon.h>
#include <conio.h> 

//// there are 48 columns and 26 rows

const int col = 48;
const int row = 26;


class special_been
{
	bool activate;
public:
	special_been()
	{
		activate = 0;
	}

	void place_candY(char**& arr)
	{
		arr[3][3] = 'b';
		arr[23][45] = 'b';
	}

	bool isactivated()
	{
		if (activate == 1)
			return true;
		else
		{
			return false;
		}
	}

	void setactivate()
	{
		activate = 1;
	}

	void setactivate_OFF()
	{
		activate = 0;
	}

	~special_been()
	{

	}
};

special_been seeds;

class board
{
private:
	char** arr;


public:
	board()
	{
		arr = new char* [row];
		for (int i = 0; i < 26; i++)
		{
			arr[i] = new char[col];
		}

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				arr[i][j] = 0;
			}
		}

	}

	bool seed_activate()
	{
		return seeds.isactivated();
	}

	board(char arri[][100])
	{
		arr = new char* [row];
		for (int i = 0; i < 26; i++)
		{
			arr[i] = new char[col];
		}

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				arr[i][j] = arri[i][j];
			}
		}
       
		seeds.place_candY(arr);

	}

	char** getboard()
	{
		return arr;
	}

	void setboard(char arri[][100])
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				arr[i][j] = arri[i][j];
			}
		}
		seeds.place_candY(arr);
	}

	bool endgame()
	{
		int flag = 0;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (arr[i][j] == ' ')
				{
					return false;
				}
				else
				{
					flag = true;
				}
			}
		}
		if (flag == true)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	~board()
	{

	}
};

class pacman : public board
{
private:
	int score;
	int lives;
	bool killable;
public:
	pacman()
	{
		score = 0;
		lives = 3;
		killable = 1;
	}

	bool getlag()
	{
		return seeds.isactivated();
	}

	void movel(char** arr, int& i, int& j, int& m, int& n, int& v, int& x, int code)
	{
		if (code == 1)
		{
			if (j - 1 >= 0 && arr[i][j - 1] != '#' && arr[i][j - 1] != '8')
			{
				arr[i][j] = '0';
				j--;
				if (arr[i][j] == ' ')
				{
					score = score + 1;
				}
				if (arr[i][j] == 'b')
				{
					seeds.setactivate();
				}
				if ((arr[i][j] == '2' || arr[i][j] == '3') && getlag() == 1)
				{
				

					score = score + 200;
					seeds.setactivate_OFF();
					arr[m][n] = '0';
					arr[v][x] = '0';
					m = 9, n = 23;
					x = 28;
					v = 9;
					arr[9][23] = '2';
					arr[9][28] = '3';
					return;
				}
				else if ((arr[i][j] == '2' || arr[i][j] == '3') && getlag() == 0)
				{
					seeds.setactivate_OFF();
					lives--;
					j++;
					arr[i][j] = '0';
					arr[m][n] = '0';
					arr[v][x] = '0';
					i = 1, j = 1;
					m = 9, n = 23;
					x = 28;
					v = 9;
					arr[1][1] = '1';
					arr[9][23] = '2';
					arr[9][28] = '3';
					return;
				}
				arr[i][j] = '1';
			}
		}
		else if (code == 2)
		{
			if (n - 1 >= 0 && arr[m][n - 1] != '#' && arr[m][n - 1] != '8' && arr[m][n - 1] != '3')
			{
				if (arr[m][n] == '2')
				{
					if (arr[m][n - 1] == ' ')
					{
						arr[m][n] = ' ';
					}

					else if (arr[m][n - 1] == '0')
					{
						arr[m][n] = '0';
					}
				}
				
				n--;
				if (arr[m][n] == '1')
				{
					seeds.setactivate_OFF();
					lives--;
					n++;
					arr[i][j] = '0';
					arr[m][n] = '0';
					arr[v][x] = '0';
					i = 1, j = 1;
					m = 9, n = 23;
					x = 28;
					v = 9;
					arr[1][1] = '1';
					arr[9][23] = '2';
					arr[9][28] = '3';
					return;
				}
				arr[m][n] = '2';
			}
		}
		else if (code == 3)
		{
			if (x - 1 >= 0 && arr[v][x - 1] != '#' && arr[v][x - 1] != '8' && arr[v][x - 1] != '2')
			{
				if (arr[v][x] == '3')
				{
					if (arr[v][x - 1] == ' ')
					{
						arr[v][x] = ' ';
					}

					else if (arr[v][x - 1] == '0')
					{
						arr[v][x] = '0';
					}
				}

				x--;
				if (arr[v][x] == '1')
				{
					seeds.setactivate_OFF();
					lives--;
					x++;
					arr[i][j] = '0';
					arr[m][n] = '0';
					arr[v][x] = '0';
					i = 1, j = 1;
					m = 9, n = 23;
					x = 28;
					v = 9;
					arr[1][1] = '1';
					arr[9][23] = '2';
					arr[9][28] = '3';
					return;
				}
				arr[v][x] = '3';
			}
		}

	}

	void mover(char** arr, int& i, int& j, int& m, int& n, int& v, int& x, int code)
	{
		if (code == 1)
		{
			if (j + 1 <= col && arr[i][j + 1] != '#' && arr[i][j + 1] != '8')
			{
				arr[i][j] = '0';
				j++;
				if (arr[i][j] == ' ')
				{
					score = score + 1;
				}
				if (arr[i][j] == 'b')
				{

					seeds.setactivate();
				}
				if ((arr[i][j] == '2' || arr[i][j] == '3') && getlag() == 1)
				{
					score = score + 200;
					seeds.setactivate_OFF();
					arr[m][n] = '0';
					arr[v][x] = '0';
					m = 9, n = 23;
					x = 28;
					v = 9;
					arr[9][23] = '2';
					arr[9][28] = '3';
					return;
				}
				else if ((arr[i][j] == '2' || arr[i][j] == '3') && getlag() == 0)
				{
					seeds.setactivate_OFF();
					lives--;
					j++;
					arr[i][j] = '0';
					arr[m][n] = '0';
					arr[v][x] = '0';
					i = 1, j = 1;
					m = 9, n = 23;
					x = 28;
					v = 9;
					arr[1][1] = '1';
					arr[9][23] = '2';
					arr[9][28] = '3';
					return;
				}
				arr[i][j] = '1';
			}
		}
		else if (code == 2)
		{
			if (n + 1 <= col && arr[m][n + 1] != '#' && arr[m][n + 1] != '8' && arr[m][n + 1] != '3')
			{
				if (arr[m][n] == '2')
				{
					if (arr[m][n + 1] == ' ')
					{
						arr[m][n] = ' ';
					}

					else if (arr[m][n + 1] == '0')
					{
						arr[m][n] = '0';
					}
				}

				n++;
				if (arr[m][n] == '1')
				{
					seeds.setactivate_OFF();
					lives--;
					n--;
					arr[i][j] = '0';
					arr[m][n] = '0';
					arr[v][x] = '0';
					i = 1, j = 1;
					m = 9, n = 23;
					x = 9;
					v = 28;
					arr[1][1] = '1';
					arr[9][23] = '2';
					arr[9][28] = '3';
					return;
				}
				arr[m][n] = '2';
			}
		}
		else if (code == 3)
		{
			if (x + 1 <= col && arr[v][x + 1] != '#' && arr[v][x + 1] != '8' && arr[v][x + 1] != '2')
			{

				if (arr[v][x] == '3')
				{
					if (arr[v][x + 1] == ' ')
					{
						arr[v][x] = ' ';
					}

					else if (arr[v][x + 1] == '0')
					{
						arr[v][x] = '0';
					}
				}

				x++;
				if (arr[v][x] == '1')
				{
					seeds.setactivate_OFF();
					x--;
					lives--;
					arr[i][j] = '0';
					arr[m][n] = '0';
					arr[v][x] = '0';
					i = 1, j = 1;
					m = 9, n = 23;
					x = 28;
					v = 9;
					arr[1][1] = '1';
					arr[9][23] = '2';
					arr[9][28] = '3';
					return;
				}
				arr[v][x] = '3';
			}
		}
	}

	void moved(char** arr, int& i, int& j, int& m, int& n, int& v, int& x, int code)
	{
		if (code == 1)
		{
			if (i + 1 <= row && arr[i + 1][j] != '#' && arr[i + 1][j] != '8')
			{
				arr[i][j] = '0';
				i++;
				if (arr[i][j] == ' ')
				{

					score = score + 1;
				}
				if (arr[i][j] == 'b')
				{

					seeds.setactivate();
				}
				if ((arr[i][j] == '2' || arr[i][j] == '3') && getlag() == 1)
				{
					score = score + 200;
					seeds.setactivate_OFF();
					arr[m][n] = '0';
					arr[v][x] = '0';
					m = 9, n = 23;
					x = 28;
					v = 9;
					arr[9][23] = '2';
					arr[9][28] = '3';
					return;
				}
				else if ((arr[i][j] == '2' || arr[i][j] == '3') && getlag() == 0)
				{
					seeds.setactivate_OFF();
					lives--;
					j++;
					arr[i][j] = '0';
					arr[m][n] = '0';
					arr[v][x] = '0';
					i = 1, j = 1;
					m = 9, n = 23;
					x = 28;
					v = 9;
					arr[1][1] = '1';
					arr[9][23] = '2';
					arr[9][28] = '3';
					return;
				}
				arr[i][j] = '1';
			}
		}
		else if (code == 2)
		{
			if (m + 1 <= col && arr[m + 1][n] != '#' && arr[m + 1][n] != '8' && arr[m + 1][n] != '3')
			{

				if (arr[m][n] == '2')
				{
					if (arr[m + 1][n] == ' ')
					{
						arr[m][n] = ' ';
					}

					else if (arr[m + 1][n] == '0')
					{
						arr[m][n] = '0';
					}
				}

				m++;
				if (arr[m][n] == '1')
				{
					seeds.setactivate_OFF();
					lives--;
					m--;
					arr[i][j] = '0';
					arr[m][n] = '0';
					arr[v][x] = '0';
					i = 1, j = 1;
					m = 9, n = 23;
					x = 28;
					v = 9;
					arr[1][1] = '1';
					arr[9][23] = '2';
					arr[9][28] = '3';
					return;
				}
				arr[m][n] = '2';
			}
             
		}
		else if (code == 3)
		{
			if (v + 1 <= col && arr[v + 1][x] != '#' && arr[v + 1][x] != '8' && arr[v + 1][x] != '2')
			{

				if (arr[v][x] == '3')
				{
					if (arr[v + 1][x] == ' ')
					{
						arr[v][x] = ' ';
					}

					else if (arr[v + 1][x] == '0')
					{
						arr[v][x] = '0';
					}
				}

				v++;
				if (arr[v][x] == '1')
				{
					seeds.setactivate_OFF();
					lives--;
					v--;
					arr[i][j] = '0';
					arr[m][n] = '0';
					arr[v][x] = '0';
					i = 1, j = 1;
					m = 9, n = 23;
					x = 28;
					v = 9;
					arr[1][1] = '1';
					arr[9][23] = '2';
					arr[9][28] = '3';
					return;
				}
				arr[v][x] = '3';
			}
		}
	}

	void moveu(char** arr, int& i, int& j, int& m, int& n, int& v, int& x, int code)
	{
		static int temp = 0;
		if (code == 1)
		{
			if (i - 1 >= 0 && arr[i - 1][j] != '#' && arr[i - 1][j] != '8')
			{
				arr[i][j] = '0';
				i--;
				if (arr[i][j] == ' ')
				{
					score = score + 1;
				}
				if (arr[i][j] == 'b')
				{
					seeds.setactivate();
				}
				if ((arr[i][j] == '2' || arr[i][j] == '3') && getlag() == 1)
				{
					score = score + 200;
					seeds.setactivate_OFF();
					arr[m][n] = '0';
					arr[v][x] = '0';
					m = 9, n = 23;
					x = 28;
					v = 9;
					arr[9][23] = '2';
					arr[9][28] = '3';
					return;
				}
				else if ((arr[i][j] == '2' || arr[i][j] == '3') && getlag() == 0)
				{
					seeds.setactivate_OFF();
					lives--;
					j++;
					arr[i][j] = '0';
					arr[m][n] = '0';
					arr[v][x] = '0';
					i = 1, j = 1;
					m = 9, n = 23;
					x = 28;
					v = 9;
					arr[1][1] = '1';
					arr[9][23] = '2';
					arr[9][28] = '3';
					return;
				}
				arr[i][j] = '1';
			}
		}
		else if (code == 2)
		{
			if (m - 1 <= col && arr[m - 1][n] != '#' && arr[m - 1][n] != '8' && arr[m - 1][n] != '3')
			{

				if (arr[m][n] == '2')
				{
					if (arr[m - 1][n] == ' ')
					{
						arr[m][n] = ' ';
					}

					else if (arr[m - 1][n] == '0')
					{
						arr[m][n] = '0';
					}
				}

				m--;
				if (arr[m][n] == '1')
				{
					seeds.setactivate_OFF();
					lives--;
					m++;
					arr[i][j] = '0';
					arr[m][n] = '0';
					arr[v][x] = '0';
					i = 1, j = 1;
					m = 9, n = 23;
					x = 28;
					v = 9;
					arr[1][1] = '1';
					arr[9][23] = '2';
					arr[9][28] = '3';
					return;
				}
				arr[m][n] = '2';
			}
		}
		else if (code == 3)
		{
			if (v - 1 <= col && arr[v - 1][x] != '#' && arr[v - 1][x] != '8' && arr[v - 1][x] != '2')
			{

				if (arr[v][x] == '3')
				{
					if (arr[v - 1][x] == ' ')
					{
						arr[v][x] = ' ';
					}

					else if (arr[v - 1][x] == '0')
					{
						arr[v][x] = '0';
					}
				}

				v--;
				if (arr[v][x] == '1')
				{
					seeds.setactivate_OFF();
					lives--;
					v++;
					arr[i][j] = '0';
					arr[m][n] = '0';
					arr[v][x] = '0';
					i = 1, j = 1;
					m = 9, n = 23;
					x = 28;
					v = 9;
					arr[1][1] = '1';
					arr[9][23] = '2';
					arr[9][28] = '3';
					return;
				}
				arr[v][x] = '3';
			}
		}
	}

	int getscore()
	{
		return score;
	}

	int getlives()
	{
		return lives;
	}


	//polymorphism

	// void setloc() = 0;

	~pacman()
	{

	}

};

class enemY : public pacman
{
private:
	bool killable;
public:
	enemY()
	{
		killable = 0;
	}

	void random_movement(char** arr, int& i, int& j)
	{
		static char temp;
		//temp = arr[i][j];
		if (arr[i][j + 1] == ' ' || arr[i][j + 1] == '0')
		{
			arr[i][j] = ' ';
			j++;
			arr[i][j] = '3';
		}
		else if (arr[i + 1][j] == ' ' || arr[i + 1][j] == '0')
		{
			arr[i][j] = ' ';
			i++;
			arr[i][j] = '3';

		}
		else if (arr[i][j - 1] == ' ' || arr[i][j - 1] == '0')
		{
			arr[i][j] = ' ';
			j--;
			arr[i][j] = '3';
			temp = arr[i][j];
		}
		else if (arr[i - 1][j] == ' ' || arr[i - 1][j] == '0')
		{
			arr[i][j] = ' ';
			i--;
			arr[i][j] = '3';
			temp = arr[i][j];
		}
	}

	~enemY()
	{

	}
};


void convert_static_To_dYnamic(char arr[row][col], char** arri)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			arri[i][j] = arri[i][j];
		}
	}
}

int main()
{
	/*pacman* obj ;
	board* b1;*/
	char arr[100][100] =						   ////// to create board of the game
	{
	 "################################################",
	 "#                                              #",
	 "#     ####################################     #",
	 "#                                              #",
	 "#     ####    #               #         ####   #",
	 "#             #               #                #",
	 "#          #######         #######             #",
	 "#             #               #                #",
	 "#             #               #                #",
	 "#                                              #",
	 "#      #          ##888##        #             #",
	 "#      #          #88888#        #             #",
	 "#      #          #######        #             #",
	 "#      #                         #             #",
	 "#                  #####                       #",
	 "#        #######     #      #######            #",
	 "#                                              #",
	 "#  #####           ###########        #####    #",
	 "#  #####                              #####    #",
	 "#     ##                              ##       #",
	 "#     ##            #####             ##       #",
	 "#                    #                         #",
	 "#                                              #",
	 "#     #####################################    #",
	 "#                                              #",
	 "################################################"
	};

	board b(arr);		// to set board  on console
	pacman p;					 // to create enemy related to pacman class 
	enemY ei;					 /// to create enemies 
	enemY eii;

	// Initialising
	int w = 0, h = 0;
	getWindowDimensions(w, h);
	cls();
	//showConsoleCursor(false);
	arr[1][1] = '1';	 //// spawn location of pacman
	arr[9][23] = '2';	  ///spawn location of enemy
	arr[9][28] = '3';	   /// spawn location of enemy	  if you change location these will change accordinly

	b.setboard(arr);  // to set locations on board	 if you remove it they will dis-appear
	drawboard(b.getboard(), 48, 26);
	// main event loop
	int i = 1, j = 1;
	int m = 9, n = 23;
	int v = 9;
	int x = 28;
	while (!b.endgame() && p.getlives() != 0)	 // untill when game is played life condition and end game condition
	{

		delay(1);
		char c = getKey();	 /// function to check key for respectective 
		if (c == 'w')
		{
			while (!b.endgame() && p.getlives() != 0)
			{
			l:
				p.moveu(b.getboard(), i, j, m, n, v, x, 1);	 // too move pacman
				ei.moveu(b.getboard(), i, j, m, n, v, x, 2);  // to move aliens according to key movements
				eii.mover(b.getboard(), i, j, m, n, v, x, 3);
				if (seeds.isactivated() == 1)
				{
					p.moveu(b.getboard(), i, j, m, n, v, x, 1);
				}
				char c = getKey();		 /// all key movements 
				if (c == 's')
				{
					goto li;
				}
				else if (c == 'a')  //check all the keys pressed
				{
					goto lii;
				}
			
				else if (c == 'd')
				{
					goto liii;
				}
				PlaceCursor(0, 0);
				cout << "LIVES ARE : " << p.getlives();		 //// maintaining and displaying the lives of pacman
				cout << endl;
				PlaceCursor(0, 1);                             //to place the cursor on the screen
				cout << "SCORE IS : " << p.getscore();	  // maintaining and displaying the score of pacman
				drawboard(b.getboard(), 48, 26);
				PlaceCursor(0, 2);
				if (seeds.isactivated() == 1)              //put seeds on the map
				{ 
				
					//cout << "ABILITY : ON";
				}											   // ability turns on
				else
				{
					//cout << "ABILITY : OFF";
				}
			}
		}
		if (c == 's')
		{													/// is key s movements accordiing S will be done
			while (!b.endgame() && p.getlives() != 0)
			{
			li:
				p.moved(b.getboard(), i, j, m, n, v, x, 1);          //for the board places and put on the board
				ei.moved(b.getboard(), i, j, m, n, v, x, 2);    
				eii.moveu(b.getboard(), i, j, m, n, v, x, 3);
				if (seeds.isactivated() == 1)
				{
					p.moved(b.getboard(), i, j, m, n, v, x, 1);

				}
				//char array used for the board
				char c = getKey();
				if (c == 'w')
				{
					goto l;     //go to the function 
				}
				else if (c == 'a')  
				{
					goto lii;
				}
				else if (c == 'd')    
				{
					goto liii;
				}
				PlaceCursor(0, 0);
				cout << "LIVES ARE : " << p.getlives();			// same as above displaying and mainting score and lives 
				cout << endl;
				PlaceCursor(0, 1);
				cout << "SCORE IS : " << p.getscore();
				drawboard(b.getboard(), 48, 26);
				PlaceCursor(0, 2);
				if (seeds.isactivated() == 1)
				{
				//	cout << "ABILITY : ON";
				}
				else
				{
					//cout << "ABILITY : OFF";
				}
			}
		}

		if (c == 'a')
		{
			while (!b.endgame() && p.getlives() != 0)
			{
			lii:
				p.movel(b.getboard(), i, j, m, n, v, x, 1);
				ei.movel(b.getboard(), i, j, m, n, v, x, 2);
				eii.movel(b.getboard(), i, j, m, n, v, x, 3);
				if (seeds.isactivated() == 1)
				{
					p.movel(b.getboard(), i, j, m, n, v, x, 1);
					//p.movel(b.getboard(), i, j, m, n, v, x, 1);
					//p.movel(b.getboard(), i, j, m, n, v, x, 1);
				}
				char c = getKey();
				if (c == 'w')
				{
					goto l;
				}
				else if (c == 's')
				{
					goto li;
				}
				else if (c == 'd')
				{
					goto liii;
				}
				PlaceCursor(0, 0);
				cout << "LIVES ARE : " << p.getlives();
				cout << endl;
				PlaceCursor(0, 1);
				cout << "SCORE IS : " << p.getscore();     //check the score if its met with the enemy or not
				PlaceCursor(0, 2);
				if (seeds.isactivated() == 1)
				{
					//cout << "ABILITY : ON";
				}
				else
				{
					//cout << "ABILITY : OFF";
				}
				drawboard(b.getboard(), 48, 26);
			}
		}

		if (c == 'd')
		{
			while (!b.endgame() && p.getlives() != 0)
			{
			liii:
				p.mover(b.getboard(), i, j, m, n, v, x, 1);
				ei.mover(b.getboard(), i, j, m, n, v, x, 2);
				eii.moved(b.getboard(), i, j, m, n, v, x, 3);
				if (seeds.isactivated() == 1)
				{
					p.mover(b.getboard(), i, j, m, n, v, x, 1);
					//p.mover(b.getboard(), i, j, m, n, v, x, 1);
					//p.mover(b.getboard(), i, j, m, n, v, x, 1);
				}
				char c = getKey();
				if (c == 'w')
				{
					goto l;
				}
				else if (c == 's')
				{
					goto li;
				}
				else if (c == 'a')
				{
					goto lii;
				}
				PlaceCursor(0, 0);
				cout << "LIVES ARE : " << p.getlives();
				cout << endl;
				PlaceCursor(0, 1);
				cout << "SCORE IS : " << p.getscore();
				PlaceCursor(0, 2);
				if (seeds.isactivated() == 1)
				{
				//	cout << "ABILITY : ON";   //ability of the pacman
				}
				else
				{
				//	cout << "ABILITY : OFF";
				}
				drawboard(b.getboard(), 48, 26);
			}
		}
		//eii.random_movement(b.getboard(), x, v);
		PlaceCursor(0, 0);
		cout << "LIVES ARE : " << p.getlives();
		cout << endl;
		PlaceCursor(0, 1);
		cout << "SCORE IS : " << p.getscore();
		PlaceCursor(0, 2);
		if (seeds.isactivated() == 1)
		{
			//cout << "ABILITY : ON";
		}
		else
		{
			//cout << "ABILITY : OFF";
		}
		drawboard(b.getboard(), 48, 26);
	}

}