// Built-in includes:
#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <cstdlib>

//Custom includes:
#include "NewGameMenu.h"
#include "CreditMenu.h"
#include "BetMenu.h"
#include "InfoMenu.h"

void MainMenuView(Heading& hd, const std::string& mainMenu);

int main() 
{
	int16_t mainMenuInput = 0;
	int16_t infoMenuInput = 0;
	int32_t creditMenuInput = 0;
	int16_t betMenuInput = 0;
	int16_t newGameMenuInput = 0;	

	InfoMenu infoMenu;
	CreditMenu creditMenu;
	BetMenu betMenu;
	NewGameMenu newGame;
	Heading hd;

	uint16_t currentWinCount = hd.GetWinCount();

	const std::string mainMenu = {	"Main Menu Options:\n"
									"1. Exit.\n"
									"2. Enter Info Menu.\n"
									"3. Enter Credit Menu.\n"
									"4. Enter Bet Menu.\n"
									"5. Start New Game.\n"  };

	MainMenuView(hd, mainMenu);

	std::cout << "User Input : ";
	std::cin >> mainMenuInput;

	while (mainMenuInput != 1) 
	{
		switch (mainMenuInput)
		{
		case 2:
			do 
			{
				infoMenu.InfoMenuView(hd);

				std::cout << "User Input : ";
				std::cin >> infoMenuInput;

				if (infoMenuInput == 2) {
					infoMenu.setNewPage();
				}
			} while (infoMenuInput != 1);

			MainMenuView(hd, mainMenu);
			break;
		case 3:
			creditMenu.CreditMenuView(hd);
			std::cin >> creditMenuInput;

			while (creditMenuInput != 1) 
			{
				if (creditMenuInput == 2) 
				{
					creditMenu.AddCreditView(hd);
					std::cin >> creditMenuInput;

					creditMenu.AddCredit(creditMenuInput, hd);
				}
				else if (creditMenuInput == 3) 
				{
					creditMenu.CashOut(hd);
				}
				creditMenu.CreditMenuView(hd);
				std::cin >> creditMenuInput;
			}

			MainMenuView(hd, mainMenu);
			break;
		case 4:
			do 
			{
				betMenu.BetMenuView(hd);

				std::cout << "User Input : ";
				std::cin >> mainMenuInput;

				if (mainMenuInput == 2) 
				{
					system("clear");
					// system("cls");
					hd.updateHeading();
					betMenu.GetBetsList();

					std::cout << "User Input : ";
					std::cin >> betMenuInput;

					while (!betMenu.SetBet(betMenuInput, hd)) 
					{
						system("clear");
						// system("cls");
						hd.updateHeading();
						betMenu.GetBetsList();

						std::cout << "Error! Please select bet from the list." << std::endl;
						std::cout << "\nUser Input : ";
						std::cin >> betMenuInput;
					}
				}
			} while (mainMenuInput != 1);
			
			MainMenuView(hd, mainMenu);
			break;
		case 5:
			newGame.NewGameMenuView(hd);

			std::cout << "User Input : ";
			std::cin >> newGameMenuInput;

			while (newGameMenuInput != 1)
			{
				if (newGameMenuInput == 2) 
				{
					bool enoughCredit = newGame.PlayGame(hd);

					if (enoughCredit) {
						creditMenu.SetCredit(hd);
						newGame.NewGameMenuView(hd);

						if (currentWinCount < newGame.GetWinCount(hd))
						{
							std::cout << "Message: Won." << std::endl;
							currentWinCount = newGame.GetWinCount(hd);
						}
						else
						{
							std::cout << "Message: Lost." << std::endl;
						}
					}
					else
					{
						newGame.NewGameMenuView(hd);
						std::cout << "Message: Insufficient Credits." << std::endl;
					}
					std::cout << "\nUser Input : ";
					std::cin >> newGameMenuInput;
				}
				else
				{
					newGame.NewGameMenuView(hd);

					std::cout << "User Input : ";
					std::cin >> newGameMenuInput;
				}
			}
			MainMenuView(hd, mainMenu);
			break;
		default:
			MainMenuView(hd, mainMenu);
		}
		std::cout << "User Input : ";
		std::cin >> mainMenuInput;
	}
	return 0;
}

void MainMenuView(Heading& hd, const std::string& mainMenu) 
{
	system("clear");
	// system("cls");
	hd.updateHeading();
	std::cout << mainMenu << std::endl;
}