#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <array>
#include <map>

#include "Heading.h"

class NewGameMenu
{
public:
	uint16_t GetWinAmount(Heading& hd);
	void NewGameMenuView(Heading& hd);
	void PlayGame(Heading& hd);

	void PrintWinsMap(std::map<uint16_t, uint32_t>& winsMap);
	void PrintFigureNames(std::vector<std::vector<uint16_t>>& result);
	std::map<uint16_t, uint32_t> CheckLines(std::vector<std::vector<uint16_t>>& result, Heading& hd);

	uint16_t CheckScatter(std::vector<std::vector<uint16_t>>& result, Heading& hd);

	void LoadLines();
	void LoadMultipliers();
	void LoadReels();

	NewGameMenu();

private:
	static constexpr int COLS = 5;
	static constexpr int ROWS = 3;
	static constexpr int LINES = 20;

	/*
	* 3D std::array generates "too many initializer values" error... why?
	*/

	enum Figures
	{
		Cherry,
		Orange,
		Lemon,
		Plum,
		Watermelon,
		Grapes,
		Seven,
		Star,
		COUNT
	};

	std::array<std::array<uint16_t, 5>, 20> m_lines;
	std::array<std::array<uint16_t, 5>, 8> m_multipliers;
	std::array<std::vector<uint16_t>, 5> m_reels;

	const std::array<std::string, Figures::COUNT> m_figureNames = { "Cherry", "Orange", "Lemon", "Plum", "Watermelon", "Grapes", "Seven", "Star" };

	uint16_t m_win = 0;
	const std::string m_defaultOutput = { "1. Back To Main Menu.\n"
										  "2. Start New Game.\n" };
};
