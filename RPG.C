/*
	Author: Gašper Rajšek
	E-mail & bugs report: https://github.com/grajsek

	Created: 8.12.2002 at 11.50 AM
	Finished: 8.12.2002 at 15.00 PM

	This code generates random password.
*/
# include <windows.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include "colors.h" // my header


// constant for the maximum number of characters
# define MAX_NOOF_CHARS 10

// constants for the starting point of the frame - if you change this, everything in the frame will be changed too (x and y coordinates)
# define START_X 15
# define START_Y 5

// constants for the ASCII boundaries
# define START_UPPERCASE_LETTERS 65
# define END_UPPERCASE_LETTERS   90
# define START_LOWERCASE_LETTERS 97
# define END_LOWERCASE_LETTERS   122
# define START_NUMBERS           48
# define END_NUMBERS             57
# define START_SYMBOLS           33
# define END_SYMBOLS             47

// constants for the password options
# define NO_OF_OPTIONS     4
# define LOWERCASE_LETTERS 0
# define UPPERCASE_LETTERS 1
# define NUMBERS           2
# define SYMBOLS           3

// ASCII constants for the frame
# define RIGHT_DOWN	218
# define RIGHT_UP	192
# define LEFT_DOWN	191
# define LEFT_UP	217
# define HORIZONTAL	196
# define VERTICAL	179

// ASCII constants for the arrow up and down
# define ARROW_UP   24
# define ARROW_DOWN 25

// function prototypes
void gotoxy	(short x, short	y); // with this function you can change a cursor's coordinates - very useful
void clrscr	(short x, short	y, short EraseLength, short	NoOfLines); // with this function you can clear a specified region on the screen - very useful
BOOL SetColor (WORD Color); // with this function you can change a background or foreground color in a console mode

int main ()
{
	HANDLE hInput;
	INPUT_RECORD ir;
	DWORD dwRead;
	short Loop = 1, i = 0, j = 0, x = 0, OptionLowerCaseLetters = 0, OptionUpperCaseLetters = 0, OptionNumbers = 0, OptionSymbols = 0, MaxNoOfChars = 10;
	int Generator[NO_OF_OPTIONS] = {0}, Choice[NO_OF_OPTIONS] = {0};
	char Password[11] = {0};
	time_t Seed = 0;

	// clear the whole screen
	SetColor (FRONT_GREY);
	clrscr (0, 0, 79, 24);
	// initialize input variable
	hInput = GetStdHandle (STD_INPUT_HANDLE);
	// drawing a frame
	SetColor (FRONT_DARKTURQUIOSE);
	gotoxy (START_X-1, START_Y+1);
	printf ("%c", RIGHT_DOWN);
	gotoxy (START_X+44, START_Y+1);
	printf ("%c", LEFT_DOWN);
	gotoxy (START_X-1, START_Y+10);
	printf ("%c", RIGHT_UP);
	gotoxy (START_X+44, START_Y+10);
	printf ("%c", LEFT_UP);
	for (i = 0; i < 44; i++)
	{
		gotoxy (START_X+i, START_Y+1);
		printf ("%c", HORIZONTAL);
		gotoxy (START_X+i, START_Y+10);
		printf ("%c", HORIZONTAL);
	}
	for (i = 0; i < 8; i++)
	{
		gotoxy (START_X-1, START_Y+2+i);
		printf ("%c", VERTICAL);
		gotoxy (START_X+44, START_Y+2+i);
		printf ("%c", VERTICAL);
	}
	// exit button
	SetColor (FRONT_WHITE | BACK_DARKTURQUIOSE);
	gotoxy (START_X+40, START_Y+2);
	printf ("EXIT");
	// about button
	gotoxy (START_X+39, START_Y+9);
	printf ("ABOUT");
	// generate password button
	gotoxy (START_X+27, START_Y+3);
	printf ("GENERATE");
	// options
	SetColor (FRONT_GREY);
	gotoxy (START_X+27, START_Y+6);
	printf ("Length:    %c", ARROW_UP);
	gotoxy (START_X+38, START_Y+7);
	printf ("%c", ARROW_DOWN);
	SetColor (BACK_WHITE);
	gotoxy (START_X+35, START_Y+6);
	printf ("%02d", MaxNoOfChars);
	SetColor (FRONT_GREY);
	gotoxy (START_X, START_Y+6);
	printf ("[ ] lower case letters");
	gotoxy (START_X, START_Y+7);
	printf ("[ ] upper case letters");
	gotoxy (START_X, START_Y+8);
	printf ("[ ] numbers");
	gotoxy (START_X, START_Y+9);
	printf ("[ ] symbols");
	// other text
	SetColor (FRONT_LIGHTGREEN);
	gotoxy (START_X+1, START_Y+1);
	printf (" Random password ");
	SetColor (FRONT_GREY);
	gotoxy (START_X, START_Y+5);
	printf ("Password options:");
	gotoxy (START_X, START_Y+3);
	printf ("Gen. password: ");
	SetColor (BACK_WHITE);
	gotoxy (START_X+15, START_Y+3);
	printf ("          ");
	// start random generator
	srand ((unsigned) time (&Seed));
	// main loop
	while (Loop)
	{
		// reading mouse and keyboard inputs
		if (ReadConsoleInput (hInput, &ir,	1, &dwRead))
		{
			//	mouse
			if	(ir.EventType == MOUSE_EVENT)
			{
				switch	(ir.Event.MouseEvent.dwEventFlags)
				{
					case MOUSE_MOVED:
						// exit button
						if ( (ir.Event.MouseEvent.dwMousePosition.X >= START_X+40) &&
							 (ir.Event.MouseEvent.dwMousePosition.X <= START_X+43) &&
							 (ir.Event.MouseEvent.dwMousePosition.Y == START_Y+2) )
						{
							SetColor (BACK_LIGHTTURQUIOSE);
							gotoxy (START_X+40, START_Y+2);
							printf ("EXIT");
						}
						else
						{
							SetColor (FRONT_WHITE | BACK_DARKTURQUIOSE);
							gotoxy (START_X+40, START_Y+2);
							printf ("EXIT");
						}
						// about button
						if ( (ir.Event.MouseEvent.dwMousePosition.X >= START_X+39) &&
							 (ir.Event.MouseEvent.dwMousePosition.X <= START_X+43) &&
							 (ir.Event.MouseEvent.dwMousePosition.Y == START_Y+9) )
						{
							SetColor (BACK_LIGHTTURQUIOSE);
							gotoxy (START_X+39, START_Y+9);
							printf ("ABOUT");
						}
						else
						{
							SetColor (FRONT_WHITE | BACK_DARKTURQUIOSE);
							gotoxy (START_X+39, START_Y+9);
							printf ("ABOUT");
						}
						// generate password button
						if ( (ir.Event.MouseEvent.dwMousePosition.X >= START_X+27) &&
							 (ir.Event.MouseEvent.dwMousePosition.X <= START_X+34) &&
							 (ir.Event.MouseEvent.dwMousePosition.Y == START_Y+3) )
						{
							SetColor (BACK_LIGHTTURQUIOSE);
							gotoxy (START_X+27, START_Y+3);
							printf ("GENERATE");
						}
						else
						{
							SetColor (FRONT_WHITE | BACK_DARKTURQUIOSE);
							gotoxy (START_X+27, START_Y+3);
							printf ("GENERATE");
						}
						/// password length option - arrow up
						if ( (ir.Event.MouseEvent.dwMousePosition.X == START_X+38) &&
							 (ir.Event.MouseEvent.dwMousePosition.Y == START_Y+6) )
						{
							SetColor (BACK_GREY);
							gotoxy (START_X+38, START_Y+6);
							printf ("%c", ARROW_UP);
						}
						else
						{
							SetColor (FRONT_GREY);
							gotoxy (START_X+38, START_Y+6);
							printf ("%c", ARROW_UP);
						}
						// password length option - arrow down
						if ( (ir.Event.MouseEvent.dwMousePosition.X == START_X+38) &&
							 (ir.Event.MouseEvent.dwMousePosition.Y == START_Y+7) )
						{
							SetColor (BACK_GREY);
							gotoxy (START_X+38, START_Y+7);
							printf ("%c", ARROW_DOWN);
						}
						else
						{
							SetColor (FRONT_GREY);
							gotoxy (START_X+38, START_Y+7);
							printf ("%c", ARROW_DOWN);
						}
						// lower case letters option
						if ( (ir.Event.MouseEvent.dwMousePosition.X >= START_X) &&
							 (ir.Event.MouseEvent.dwMousePosition.X <= START_X+21) &&
							 (ir.Event.MouseEvent.dwMousePosition.Y == START_Y+6) )
						{
							SetColor (FRONT_GREY | BACK_DARKGREEN);
							gotoxy (START_X, START_Y+6);
							printf ("[ ] lower case letters");
							if (OptionLowerCaseLetters)
							{
								gotoxy (START_X+1, START_Y+6);
								printf ("x");
							}
							else
							{
								gotoxy (START_X+1, START_Y+6);
								printf (" ");
							}
						}
						else
						{
							SetColor (FRONT_GREY);
							gotoxy (START_X, START_Y+6);
							printf ("[ ] lower case letters");
							if (OptionLowerCaseLetters)
							{
								gotoxy (START_X+1, START_Y+6);
								printf ("x");
							}
							else
							{
								gotoxy (START_X+1, START_Y+6);
								printf (" ");
							}
						}
						// upper case letters option
						if ( (ir.Event.MouseEvent.dwMousePosition.X >= START_X) &&
							 (ir.Event.MouseEvent.dwMousePosition.X <= START_X+21) &&
							 (ir.Event.MouseEvent.dwMousePosition.Y == START_Y+7) )
						{
							SetColor (FRONT_GREY | BACK_DARKGREEN);
							gotoxy (START_X, START_Y+7);
							printf ("[ ] upper case letters");
							if (OptionUpperCaseLetters)
							{
								gotoxy (START_X+1, START_Y+7);
								printf ("x");
							}
							else
							{
								gotoxy (START_X+1, START_Y+7);
								printf (" ");
							}
						}
						else
						{
							SetColor (FRONT_GREY);
							gotoxy (START_X, START_Y+7);
							printf ("[ ] upper case letters");
							if (OptionUpperCaseLetters)
							{
								gotoxy (START_X+1, START_Y+7);
								printf ("x");
							}
							else
							{
								gotoxy (START_X+1, START_Y+7);
								printf (" ");
							}
						}
						// numbers option
						if ( (ir.Event.MouseEvent.dwMousePosition.X >= START_X) &&
							 (ir.Event.MouseEvent.dwMousePosition.X <= START_X+10) &&
							 (ir.Event.MouseEvent.dwMousePosition.Y == START_Y+8) )
						{
							SetColor (FRONT_GREY | BACK_DARKGREEN);
							gotoxy (START_X, START_Y+8);
							printf ("[ ] numbers");
							if (OptionNumbers)
							{
								gotoxy (START_X+1, START_Y+8);
								printf ("x");
							}
							else
							{
								gotoxy (START_X+1, START_Y+8);
								printf (" ");
							}
						}
						else
						{
							SetColor (FRONT_GREY);
							gotoxy (START_X, START_Y+8);
							printf ("[ ] numbers");
							if (OptionNumbers)
							{
								gotoxy (START_X+1, START_Y+8);
								printf ("x");
							}
							else
							{
								gotoxy (START_X+1, START_Y+8);
								printf (" ");
							}
						}
						// symbols option
						if ( (ir.Event.MouseEvent.dwMousePosition.X >= START_X) &&
							 (ir.Event.MouseEvent.dwMousePosition.X <= START_X+10) &&
							 (ir.Event.MouseEvent.dwMousePosition.Y == START_Y+9) )
						{
							SetColor (FRONT_GREY | BACK_DARKGREEN);
							gotoxy (START_X, START_Y+9);
							printf ("[ ] symbols");
							if (OptionSymbols)
							{
								gotoxy (START_X+1, START_Y+9);
								printf ("x");
							}
							else
							{
								gotoxy (START_X+1, START_Y+9);
								printf (" ");
							}
						}
						else
						{
							SetColor (FRONT_GREY);
							gotoxy (START_X, START_Y+9);
							printf ("[ ] symbols");
							if (OptionSymbols)
							{
								gotoxy (START_X+1, START_Y+9);
								printf ("x");
							}
							else
							{
								gotoxy (START_X+1, START_Y+9);
								printf (" ");
							}
						}
						break;
				}
				switch	(ir.Event.MouseEvent.dwButtonState)
				{
					case FROM_LEFT_1ST_BUTTON_PRESSED:
						// izhod
						if ( (ir.Event.MouseEvent.dwMousePosition.X >= START_X+40) &&
							 (ir.Event.MouseEvent.dwMousePosition.X <= START_X+43) &&
							 (ir.Event.MouseEvent.dwMousePosition.Y == START_Y+2) )
						{
							// simulation of a pressed key ESCAPE
							keybd_event	(VK_ESCAPE,	0x01, 0, 0);
							keybd_event	(VK_ESCAPE,	0x01, KEYEVENTF_KEYUP, 0);
						}
						// about button
						if ( (ir.Event.MouseEvent.dwMousePosition.X >= START_X+39) &&
							 (ir.Event.MouseEvent.dwMousePosition.X <= START_X+43) &&
							 (ir.Event.MouseEvent.dwMousePosition.Y == START_Y+9) )
						{
							// deleting the warning text
							SetColor (FRONT_GREY);
							clrscr (START_X-2, START_Y+11, 47, 0);
							// about text
							SetColor (FRONT_WHITE);
							gotoxy (START_X+12, START_Y+11);
							printf ("Author: Gaçper Rajçek");
							gotoxy (START_X+9, START_Y+12);
							printf ("Github: https://github.com/grajsek");
						}
						// generate password button
						if ( (ir.Event.MouseEvent.dwMousePosition.X >= START_X+27) &&
							 (ir.Event.MouseEvent.dwMousePosition.X <= START_X+34) &&
							 (ir.Event.MouseEvent.dwMousePosition.Y == START_Y+3) )
						{
							if ( (!OptionLowerCaseLetters) && (!OptionUpperCaseLetters) && (!OptionNumbers) && (!OptionSymbols) )
							{
								// deleting the about text
								SetColor (FRONT_GREY);
								clrscr (START_X+9, START_Y+11, 26, 1);
								// warning text
								SetColor (FRONT_LIGHTRED);
								gotoxy (START_X-2, START_Y+11);
								printf ("You have to enable at least one password option!");
							}
							else
							{
								// deleting the previous text
								SetColor (FRONT_GREY);
								clrscr (START_X+9, START_Y+11, 26, 1);
								SetColor (FRONT_GREY);
								clrscr (START_X-2, START_Y+11, 47, 0);
								// loop for generating a random password
								for (i = 0; i < MAX_NOOF_CHARS; i++)
								{
									if (i < MaxNoOfChars)
									{
										Generator[LOWERCASE_LETTERS] = START_LOWERCASE_LETTERS + (rand () % (END_LOWERCASE_LETTERS+1 - START_LOWERCASE_LETTERS)); // izbere številko med START_LOWERCASE_LETTERS in END_LOWERCASE_LETTERS+1-1
										Generator[UPPERCASE_LETTERS] = START_UPPERCASE_LETTERS + (rand () % (END_UPPERCASE_LETTERS+1 - START_UPPERCASE_LETTERS)); // izbere številko med START_UPPERCASE_LETTERS in END_UPPERCASE_LETTERS+1-1
										Generator[NUMBERS] = START_NUMBERS + (rand () % (END_NUMBERS+1 - START_NUMBERS)); // izbere številko med START_NUMBERS in END_NUMBERS+1-1
										Generator[SYMBOLS] = START_SYMBOLS + (rand () % (END_SYMBOLS+1 - START_SYMBOLS)); // izbere številko med START_SYMBOLS in END_SYMBOLS+1-1
										if (OptionLowerCaseLetters) Password[i]   = (char) Generator[LOWERCASE_LETTERS];
										if (OptionUpperCaseLetters) Password[i] = (char) Generator[UPPERCASE_LETTERS];
										if (OptionNumbers) Password[i]   = (char) Generator[NUMBERS];
										if (OptionSymbols) Password[i]    = (char) Generator[SYMBOLS];
										if ( (OptionLowerCaseLetters) && (OptionUpperCaseLetters) )
										{
											Choice[LOWERCASE_LETTERS] = rand () % 2;
											Choice[UPPERCASE_LETTERS] = rand () % 2;
											if (Choice[LOWERCASE_LETTERS])
											{
												Password[i] = (char) Generator[LOWERCASE_LETTERS];
											}
											else if (Choice[UPPERCASE_LETTERS])
											{
												Password[i] = (char) Generator[UPPERCASE_LETTERS];
											}
										}
										if ( (OptionLowerCaseLetters) && (OptionNumbers) )
										{
											Choice[LOWERCASE_LETTERS] = rand () % 2;
											Choice[NUMBERS] = rand () % 2;
											if (Choice[LOWERCASE_LETTERS])
											{
												Password[i] = (char) Generator[LOWERCASE_LETTERS];
											}
											else if (Choice[NUMBERS])
											{
												Password[i] = (char) Generator[NUMBERS];
											}
										}
										if ( (OptionLowerCaseLetters) && (OptionSymbols) )
										{
											Choice[LOWERCASE_LETTERS] = rand () % 2;
											Choice[SYMBOLS] = rand () % 2;
											if (Choice[LOWERCASE_LETTERS])
											{
												Password[i] = (char) Generator[LOWERCASE_LETTERS];
											}
											else if (Choice[SYMBOLS])
											{
												Password[i] = (char) Generator[SYMBOLS];
											}
										}
										if ( (OptionUpperCaseLetters) && (OptionNumbers) )
										{
											Choice[UPPERCASE_LETTERS] = rand () % 2;
											Choice[NUMBERS] = rand () % 2;
											if (Choice[UPPERCASE_LETTERS])
											{
												Password[i] = (char) Generator[UPPERCASE_LETTERS];
											}
											else if (Choice[NUMBERS])
											{
												Password[i] = (char) Generator[NUMBERS];
											}
										}
										if ( (OptionUpperCaseLetters) && (OptionSymbols) )
										{
											Choice[UPPERCASE_LETTERS] = rand () % 2;
											Choice[SYMBOLS] = rand () % 2;
											if (Choice[UPPERCASE_LETTERS])
											{
												Password[i] = (char) Generator[UPPERCASE_LETTERS];
											}
											else if (Choice[SYMBOLS])
											{
												Password[i] = (char) Generator[SYMBOLS];
											}
										}
										if ( (OptionNumbers) && (OptionSymbols) )
										{
											Choice[NUMBERS] = rand () % 2;
											Choice[SYMBOLS] = rand () % 2;
											if (Choice[NUMBERS])
											{
												Password[i] = (char) Generator[NUMBERS];
											}
											else if (Choice[SYMBOLS])
											{
												Password[i] = (char) Generator[SYMBOLS];
											}
										}
										if ( (OptionLowerCaseLetters) && (OptionUpperCaseLetters) && (OptionNumbers) )
										{
											Choice[LOWERCASE_LETTERS] = rand () % 2;
											Choice[UPPERCASE_LETTERS] = rand () % 2;
											Choice[NUMBERS] = rand () % 2;
											if (Choice[LOWERCASE_LETTERS])
											{
												Password[i] = (char) Generator[LOWERCASE_LETTERS];
											}
											else if (Choice[UPPERCASE_LETTERS])
											{
												Password[i] = (char) Generator[UPPERCASE_LETTERS];
											}
											else if (Choice[NUMBERS])
											{
												Password[i] = (char) Generator[NUMBERS];
											}
										}
										if ( (OptionLowerCaseLetters) && (OptionUpperCaseLetters) && (OptionSymbols) )
										{
											Choice[LOWERCASE_LETTERS] = rand () % 2;
											Choice[UPPERCASE_LETTERS] = rand () % 2;
											Choice[SYMBOLS] = rand () % 2;
											if (Choice[LOWERCASE_LETTERS])
											{
												Password[i] = (char) Generator[LOWERCASE_LETTERS];
											}
											else if (Choice[UPPERCASE_LETTERS])
											{
												Password[i] = (char) Generator[UPPERCASE_LETTERS];
											}
											else if (Choice[SYMBOLS])
											{
												Password[i] = (char) Generator[SYMBOLS];
											}
										}
										if ( (OptionLowerCaseLetters) && (OptionNumbers) && (OptionSymbols) )
										{
											Choice[LOWERCASE_LETTERS] = rand () % 2;
											Choice[NUMBERS] = rand () % 2;
											Choice[SYMBOLS] = rand () % 2;
											if (Choice[LOWERCASE_LETTERS])
											{
												Password[i] = (char) Generator[LOWERCASE_LETTERS];
											}
											else if (Choice[NUMBERS])
											{
												Password[i] = (char) Generator[NUMBERS];
											}
											else if (Choice[SYMBOLS])
											{
												Password[i] = (char) Generator[SYMBOLS];
											}
										}
										if ( (OptionUpperCaseLetters) && (OptionNumbers) && (OptionSymbols) )
										{
											Choice[UPPERCASE_LETTERS] = rand () % 2;
											Choice[NUMBERS] = rand () % 2;
											Choice[SYMBOLS] = rand () % 2;
											if (Choice[UPPERCASE_LETTERS])
											{
												Password[i] = (char) Generator[UPPERCASE_LETTERS];
											}
											else if (Choice[NUMBERS])
											{
												Password[i] = (char) Generator[NUMBERS];
											}
											else if (Choice[SYMBOLS])
											{
												Password[i] = (char) Generator[SYMBOLS];
											}
										}
										if ( (OptionLowerCaseLetters) && (OptionUpperCaseLetters) && (OptionNumbers) && (OptionSymbols) )
										{
											Choice[LOWERCASE_LETTERS] = rand () % 2;
											Choice[UPPERCASE_LETTERS] = rand () % 2;
											Choice[NUMBERS] = rand () % 2;
											Choice[SYMBOLS] = rand () % 2;
											if (Choice[LOWERCASE_LETTERS])
											{
												Password[i] = (char) Generator[LOWERCASE_LETTERS];
											}
											else if (Choice[UPPERCASE_LETTERS])
											{
												Password[i] = (char) Generator[UPPERCASE_LETTERS];
											}
											else if (Choice[NUMBERS])
											{
												Password[i] = (char) Generator[NUMBERS];
											}
											else if (Choice[SYMBOLS])
											{
												Password[i] = (char) Generator[SYMBOLS];
											}
										}
									}
									else Password[i] = ' ';
								}
								Password[i] = '\0';
								SetColor (BACK_WHITE);
								gotoxy (START_X+15, START_Y+3);
								printf ("%s", Password);
							}
						}
						// password length option - arrow up
						if ( (ir.Event.MouseEvent.dwMousePosition.X == START_X+38) &&
							 (ir.Event.MouseEvent.dwMousePosition.Y == START_Y+6) )
						{
							if (MaxNoOfChars < 10)
							{
								SetColor (BACK_WHITE);
								gotoxy (START_X+35, START_Y+6);
								printf ("%02d", ++MaxNoOfChars);
							}
						}
						// password length option - arrow down
						if ( (ir.Event.MouseEvent.dwMousePosition.X == START_X+38) &&
							 (ir.Event.MouseEvent.dwMousePosition.Y == START_Y+7) )
						{
							if (MaxNoOfChars > 1)
							{
								SetColor (BACK_WHITE);
								gotoxy (START_X+35, START_Y+6);
								printf ("%02d", --MaxNoOfChars);
							}
						}
						// lower case letters option
						if ( (ir.Event.MouseEvent.dwMousePosition.X >= START_X) &&
							 (ir.Event.MouseEvent.dwMousePosition.X <= START_X+21) &&
							 (ir.Event.MouseEvent.dwMousePosition.Y == START_Y+6) )
						{
							SetColor (FRONT_GREY | BACK_DARKGREEN);
							if (!OptionLowerCaseLetters)
							{
								gotoxy (START_X+1, START_Y+6);
								printf ("x");
								OptionLowerCaseLetters = 1;
							}
							else
							{
								gotoxy (START_X+1, START_Y+6);
								printf (" ");
								OptionLowerCaseLetters = 0;
							}
						}
						// upper case letters option
						if ( (ir.Event.MouseEvent.dwMousePosition.X >= START_X) &&
							 (ir.Event.MouseEvent.dwMousePosition.X <= START_X+21) &&
							 (ir.Event.MouseEvent.dwMousePosition.Y == START_Y+7) )
						{
							SetColor (FRONT_GREY | BACK_DARKGREEN);
							if (!OptionUpperCaseLetters)
							{
								gotoxy (START_X+1, START_Y+7);
								printf ("x");
								OptionUpperCaseLetters = 1;
							}
							else
							{
								gotoxy (START_X+1, START_Y+7);
								printf (" ");
								OptionUpperCaseLetters = 0;
							}
						}
						// numbers option
						if ( (ir.Event.MouseEvent.dwMousePosition.X >= START_X) &&
							 (ir.Event.MouseEvent.dwMousePosition.X <= START_X+10) &&
							 (ir.Event.MouseEvent.dwMousePosition.Y == START_Y+8) )
						{
							SetColor (FRONT_GREY | BACK_DARKGREEN);
							if (!OptionNumbers)
							{
								gotoxy (START_X+1, START_Y+8);
								printf ("x");
								OptionNumbers = 1;
							}
							else
							{
								gotoxy (START_X+1, START_Y+8);
								printf (" ");
								OptionNumbers = 0;
							}
						}
						// symbols option
						if ( (ir.Event.MouseEvent.dwMousePosition.X >= START_X) &&
							 (ir.Event.MouseEvent.dwMousePosition.X <= START_X+10) &&
							 (ir.Event.MouseEvent.dwMousePosition.Y == START_Y+9) )
						{
							SetColor (FRONT_GREY | BACK_DARKGREEN);
							if (!OptionSymbols)
							{
								gotoxy (START_X+1, START_Y+9);
								printf ("x");
								OptionSymbols = 1;
							}
							else
							{
								gotoxy (START_X+1, START_Y+9);
								printf (" ");
								OptionSymbols = 0;
							}
						}
						break;
				}
			}
			//	keyboard
			if ( (ir.EventType == KEY_EVENT) && (ir.Event.KeyEvent.bKeyDown) )
			{
				switch (ir.Event.KeyEvent.wVirtualKeyCode)
				{
					case VK_ESCAPE: // quit the application
						Loop = 0;
						break;
				}
			}
		}
	}
	// clear the whole screen and return 0 to the os
	SetColor (FRONT_GREY);
	clrscr (0, 0, 79, 24);
	return 0;
}
void gotoxy	(short x, short	y)
{
	COORD coord;

	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition (GetStdHandle (STD_OUTPUT_HANDLE), coord);
}
void clrscr	(short x, short	y, short EraseLength, short	NoOfLines)
{
	short i	= 0, j = 0, k = 0;
	char Erase[30][85];

	if (NoOfLines == 0)	k = 0;	else k = 1;
	for	(i = 0;	i <= NoOfLines+k; i++)
	{
		for	(j	= 0; j <= EraseLength; j++)
		{
			Erase[i][j] = ' ';
		}
		Erase[i][j]	= '\0';
		SetColor (FRONT_GREY);
		gotoxy (x,	y+i);
		printf ("%s", Erase);
	}
}
BOOL SetColor (WORD Color)
{
	HANDLE hOutput;

	hOutput	= GetStdHandle (STD_OUTPUT_HANDLE);	
	return SetConsoleTextAttribute (hOutput, Color);
}