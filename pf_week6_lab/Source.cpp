#include<stdio.h>
#include<windows.h>
#include<conio.h>
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}

void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void draw_ship(int x, int y)
{
	setcolor(2, 4);
	gotoxy(x, y); printf(" <-0-> ");
}

void erase_ship(int x, int y)
{
	setcolor(2, 0);
	gotoxy(x, y);	printf("       ");

}

void draw_bullet(int x, int y)
{
	setcolor(1, 0);
	gotoxy(x, y);	printf("|");
}

void erase_bullet(int x, int y)
{
	setcolor(1, 0);
	gotoxy(x, y);	printf(" ");
}


int main()
{
	char ch = '.';
	int x = 38, y = 20;
	int dx = 0, dy = 0;

	//int for bullet
	int ammo = 5;
	int dbx[5] = { 0,0,0,0,0 };
	int dby[5] = { 19,19,19,19,19 };
	setcursor(0);
	draw_ship(x, y);

	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a') { dy = 0; dx=1; }
			if (ch == 'd') { dx = 0; dy=1; }
			if (ch == 's') { dx = 0; dy = 0; draw_ship(x, y); }
			if (ch == ' ') { if ( ammo > 0)
			{ 
				for (int i = 0; i < 5; i++)
				{
					if (dbx[i] == 0)
					{
						dbx[i] = x + 3;
						dby[i] = 19;
						break;
					}
				}
			} }
			fflush(stdin);
		}

		//for ship
		if (dx != 0 || dy != 0)
		{
			erase_ship(x, y);
			if (dx == 1)
			{
				draw_ship(--x, y);
			}
			if (dy==1)
			{
				draw_ship(++x, y);
			}
			if (x == 0 || x == 80-7)
			{
				dx = 0; dy = 0;
				draw_ship(x, y);
			}
		}

		//for bullet
		for (int i = 0; i < 5; i++)
		{
			if (dbx[i] != 0)
			{
				erase_bullet(dbx[i], dby[i]);
				if (dby[i] == 0)
				{
					dby[i] = 19;
					dbx[i] = 0;
				}
				else
				{
					draw_bullet(dbx[i], --dby[i]);
				}
			}
		}

		Sleep(100);
	}while (ch != 'x');
	
	return 0;
}