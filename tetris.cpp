#include "tetris.h"
#include "Computer.h"


void tetris::ChooseGame() // צריך להוסיף אופציה של תפריט כאן ולא רק במשחקים עצמים
{
	char key_char = 0;
	TheGame* game = nullptr;
	Computer* c = nullptr;
	Menu m;
	while (1)
	{
		if (_kbhit())
		{
			key_char = _getch();
			if (game == nullptr && key_char == INSTRUCTIO_KEYS)
			{
				game->getMenuInstructions();
			}
			if (key_char == STARTHvsH)
			{
				game = new HumanVsHuman();

			}
			else if (key_char == STARTHvsC)
			{
				c->ChooseComputerLevel();
				game = new HumanVsComputer();

			}
			else if (key_char == STARTCvsC)
			{
				c->ChooseComputerLevel();
				game = new ComputerVsComputer();

			}
			game->RunGame();
			delete game;

		}
	}
}



