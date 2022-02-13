#include "NewGameMenu.h"
#include "Heading.h"

#include <time.h>
#include <iostream>

uint16_t NewGameMenu::GetWinCount(Heading& hd)
{
	return hd.GetWinCount();
}

void NewGameMenu::NewGameMenuView(Heading& hd)
{
	system("clear");
	// system("cls");
	hd.updateHeading();
	std::cout << m_defaultOutput << std::endl;
}

bool NewGameMenu::PlayGame(Heading& hd)
{
	if (hd.GetCredit() < hd.GetBet())
	{
		return false;
	}

	srand(static_cast<uint32_t>(time(0)));
	if (rand() % 2 == 1)
	{
		hd.UpdateWinCount();
	}
	return true;
}