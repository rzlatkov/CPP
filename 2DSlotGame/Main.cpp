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

template<typename T>
void UserInput(T& input);

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

	const std::string mainMenu = {	"1. Exit.\n"
									"2. Enter Info Menu.\n"
									"3. Enter Credit Menu.\n"
									"4. Enter Bet Menu.\n"
									"5. Start New Game.\n"  };

	MainMenuView(hd, mainMenu);

	std::cout << "User Input : ";
	UserInput(mainMenuInput);

	while (mainMenuInput != 1) 
	{
		switch (mainMenuInput)
		{
		case 2:
			do 
			{
				infoMenu.InfoMenuView(hd);

				std::cout << "User Input : ";
				UserInput(infoMenuInput);

				if (infoMenuInput == 2) {
					infoMenu.setNewPage();
				}
			} while (infoMenuInput != 1);

			MainMenuView(hd, mainMenu);
			break;
		case 3:
			creditMenu.CreditMenuView(hd);
			UserInput(creditMenuInput);

			while (creditMenuInput != 1) 
			{
				if (creditMenuInput == 2) 
				{
					creditMenu.AddCreditView(hd);
					UserInput(creditMenuInput);

					creditMenu.AddCredit(creditMenuInput, hd);
				}
				else if (creditMenuInput == 3) 
				{
					creditMenu.CashOut(hd);
				}
				creditMenu.CreditMenuView(hd);
				UserInput(creditMenuInput);
			}

			MainMenuView(hd, mainMenu);
			break;
		case 4:
			do 
			{
				betMenu.BetMenuView(hd);

				std::cout << "User Input : ";
				UserInput(mainMenuInput);

				if (mainMenuInput == 2) 
				{
					// system("clear");
					system("cls");
					hd.UpdateHeading();
					betMenu.GetBetsList();

					std::cout << "User Input : ";
					UserInput(betMenuInput);

					while (!betMenu.SetBet(betMenuInput, hd)) 
					{
						// system("clear");
						system("cls");
						hd.UpdateHeading();
						betMenu.GetBetsList();

						std::cout << "Error! Please select bet from the list." << std::endl;
						std::cout << "\nUser Input : ";
						UserInput(betMenuInput);
					}
				}
			} while (mainMenuInput != 1);
			
			MainMenuView(hd, mainMenu);
			break;
		case 5:
			newGame.NewGameMenuView(hd);

			std::cout << "User Input : ";
			UserInput(newGameMenuInput);

			while (newGameMenuInput != 1)
			{
				if (newGameMenuInput == 2) 
				{
					newGame.PlayGame(hd);
					std::cout << "\nUser Input : ";
					UserInput(newGameMenuInput);
				}
				else
				{
					hd.UpdateWinAmount(0);
					newGame.NewGameMenuView(hd);

					std::cout << "User Input : ";
					UserInput(newGameMenuInput);
				}
			}
			hd.UpdateWinAmount(0);
			MainMenuView(hd, mainMenu);		
			break;
		default:
			MainMenuView(hd, mainMenu);
		}
		std::cout << "User Input : ";
		UserInput(mainMenuInput);
	}
	return 0;
}

void MainMenuView(Heading& hd, const std::string& mainMenu) 
{
	// system("clear");
	system("cls");
	hd.UpdateHeading();
	std::cout << mainMenu << std::endl;
}

template<typename T>
void UserInput(T& input) 
{
	std::cin >> input;
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore();
	}
}