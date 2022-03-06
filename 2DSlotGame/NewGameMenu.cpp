#include <iostream>
#include <fstream>
#include <sstream>

#include "NewGameMenu.h"
#include "Heading.h"

uint16_t NewGameMenu::GetWinAmount(Heading& hd)
{
	return hd.GetWinAmount();
}

void NewGameMenu::NewGameMenuView(Heading& hd)
{
	// system("clear");
	system("cls");
	hd.UpdateHeading();
	std::cout << m_defaultOutput << std::endl;
}

void NewGameMenu::PlayGame(Heading& hd)
{
	std::vector<std::vector<uint16_t>> result(NewGameMenu::ROWS, std::vector<uint16_t> (NewGameMenu::COLS));
	std::map<uint16_t, uint32_t> winsMap;

	if (hd.GetCredit() < hd.GetBet())
	{
		NewGameMenuView(hd);
		std::cout << "Message: Insufficient Credits." << std::endl;
	}
	else
	{
		for (uint8_t col = 0; col < NewGameMenu::COLS; ++col)
		{
			uint8_t index = static_cast<uint8_t>(rand() % m_reels[col].size());
			
			if (index == 0)
			{
				result[0][col] = m_reels[col][m_reels[col].size() - 1];
				result[1][col] = m_reels[col][index];
				result[2][col] = m_reels[col][index + 1];
			}
			else if (index == m_reels[col].size() - 1)
			{
				result[0][col] = m_reels[col][index - 1];
				result[1][col] = m_reels[col][index];
				result[2][col] = m_reels[col][0];
			}
			else
			{
				result[0][col] = m_reels[col][index - 1];
				result[1][col] = m_reels[col][index];
				result[2][col] = m_reels[col][index + 1];
			}
			
			/*
			Star7      Lemon2       Watermelon4  Watermelon4  Orange1
            Cherry0    Cherry0      Cherry0      Plum3        Orange1
            Cherry0    Grapes5      Lemon2       Grapes5      Star7
			*/

			
			// result = { {7,2,4,4,1}, {0,0,0,3,1}, {0,5,2,5,7} };
		}
		
		winsMap = CheckLines(result, hd);
		NewGameMenuView(hd);
		PrintFigureNames(result);

		if (winsMap.empty()) 
		{
			std::cout << "\n    Status : Lost" << std::endl;
		}
		else
		{
			std::cout << "\n    Winner Lines\n" << std::endl;
			PrintWinsMap(winsMap);
			std::cout << "\n    Status : Win" << std::endl;
			hd.AddCredit(hd.GetWinAmount());
		}
	}
}

void NewGameMenu::PrintFigureNames(std::vector<std::vector<uint16_t>>& result)
{
	std::cout << "    Result From Game:\n" << std::endl;

	for (uint8_t row = 0; row < NewGameMenu::ROWS; row++)
	{
		for (uint8_t col = 0; col < NewGameMenu::COLS; col++)
		{
			std::string whitespacesToAdd (12 - m_figureNames[result[row][col]].length(), ' ');

			if (col == 0)
			{
				std::cout << "        " << m_figureNames[result[row][col]] + whitespacesToAdd;
			}
			else if (col < 4) 
			{
				std::cout << m_figureNames[result[row][col]] + whitespacesToAdd;
			}
			else if (col == 4) 
			{
				std::cout << m_figureNames[result[row][col]] << std::endl;
			}
		}
	}
}

uint16_t NewGameMenu::CheckScatter(std::vector<std::vector<uint16_t>>& result, Heading& hd)
{
	uint16_t scatterWin = 0;
	uint16_t starsCount = 0;

	for (uint8_t col = 0; col < NewGameMenu::COLS; ++col)
	{
		for (uint8_t row = 0; row < NewGameMenu::ROWS; ++row)
		{
			if (m_figureNames[result[row][col]] == "Star")
			{
				starsCount++;
				break;
			}
		}
	}

	if (starsCount == 0)
	{
		starsCount++;
	}

	scatterWin = hd.GetBet() * m_multipliers[Figures::Star][starsCount - 1];
	
	return scatterWin;
}

std::map<uint16_t, uint32_t> NewGameMenu::CheckLines(std::vector<std::vector<uint16_t>>& result, Heading& hd)
{
	std::map<uint16_t, uint32_t> winsMap;
	uint32_t totalWin = 0;

	for (uint8_t line = 0; line < NewGameMenu::LINES; ++line)
	{
		bool selected = false;
		std::string winningFigure;
		uint16_t winningFigureID = 0;
		uint8_t matchesCount = 0;
		uint32_t currentWin = 0;
		
		
		for (uint8_t col = 0; col < NewGameMenu::COLS; ++col)
		{
			uint16_t currentFigureID = result[m_lines[line][col]][col];
			std::string currentFigure = m_figureNames[currentFigureID];
			
			if (currentFigure != "Star")
			{
				if (!selected)
				{
					selected = true;
					winningFigure = currentFigure;
					winningFigureID = currentFigureID;
				}
				else
				{
					if (currentFigure != winningFigure)
					{
						if (currentFigure == "Seven")
						{
							matchesCount += 1;
						}
						else if (winningFigure == "Seven")
						{
							matchesCount += 1;
							winningFigure = currentFigure;
							winningFigureID = currentFigureID;
						}
						else
						{
							break;
						}
					}
					else
					{
						matchesCount += 1;
					}
				}
			}
			else
			{
				break;
			}
		}

		currentWin = (hd.GetBet() / LINES) * m_multipliers[winningFigureID][matchesCount];

		if (currentWin > 0) 
		{
			totalWin += currentWin;
			winsMap[line + 1] = currentWin;
		}
	}

	uint16_t scatterWin = CheckScatter(result, hd);
	
	if (scatterWin > 0)
	{
		totalWin += scatterWin;
		winsMap[46] = scatterWin;
	}

	hd.UpdateWinAmount(totalWin);
	hd.DecreaseCredit(hd.GetBet());
	return winsMap;
}

void NewGameMenu::PrintWinsMap(std::map<uint16_t, uint32_t>& winsMap)
{
	for (const auto& kv_pair : winsMap)
	{
		if (kv_pair.first != 46)
		{
			std::cout << "        Line " << kv_pair.first << " - " << kv_pair.second << " EUR" << std::endl;
		}
		else
		{
			std::cout << "        Scatter - " << kv_pair.second << " EUR" << std::endl;
		}
	}
}

void NewGameMenu::LoadLines()
{
	std::string newline;
	std::ifstream linesFile;
	linesFile.open("C:\\Users\\Rumen\\Desktop\\cpp_projects\\lines.txt");

	if (!linesFile)
	{
		std::cout << "Unable to open lines.txt" << std::endl;
	}
	else
	{
		uint8_t lineNumber = 0;
		while (std::getline(linesFile, newline))
		{
			std::istringstream iss(newline);

			uint8_t coordinatePosition = 0;
			while (iss >> m_lines[lineNumber][coordinatePosition])
			{
				if (coordinatePosition == 4)
				{
					break;
				}
				coordinatePosition++;
			}
			lineNumber++;	
		}
	}
	linesFile.close();
}

void NewGameMenu::LoadMultipliers()
{
	std::string newline;
	std::ifstream multipliersFile;
	multipliersFile.open("C:\\Users\\Rumen\\Desktop\\cpp_projects\\multipliers.txt");

	if (!multipliersFile)
	{
		std::cout << "Unable to open multipliers.txt" << std::endl;
	}
	else
	{
		uint8_t multiplierLine = 0;
		while (std::getline(multipliersFile, newline))
		{
			std::istringstream iss(newline);

			uint8_t multiplierPosition = 0;
			while (iss >> m_multipliers[multiplierLine][multiplierPosition])
			{
				if (multiplierPosition == 4)
				{
					break;
				}
				multiplierPosition += 1;
			}
			multiplierLine += 1;
		}
	}
	multipliersFile.close();
}

void NewGameMenu::LoadReels()
{
	std::string newline;
	std::ifstream reelsFile;
	reelsFile.open("C:\\Users\\Rumen\\Desktop\\cpp_projects\\reels.txt");

	if (!reelsFile)
	{
		std::cout << "Unable to open reels.txt" << std::endl;
	}
	else
	{
		uint8_t reel = 0;
		while (std::getline(reelsFile, newline))
		{
			std::istringstream iss(newline);

			uint16_t reelValue = 0;
			while (iss >> reelValue)
			{
				m_reels[reel].push_back(reelValue);
			}
			reel += 1;
		}
	}
	reelsFile.close();
}

NewGameMenu::NewGameMenu()
{
	LoadLines();
	LoadMultipliers();
	LoadReels();
}
