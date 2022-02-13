#pragma once
#include <cstdint>
#include <string>

#include "Heading.h"

// forward declaration.
// class Heading; 

class NewGameMenu
{
public:
	uint16_t GetWinCount(Heading& hd);
	void NewGameMenuView(Heading& hd);
	bool PlayGame(Heading& hd);

private:
	uint16_t m_win = 0;
	const std::string m_defaultOutput = { "Start New Game Options:\n"
										"1. Back To Main Menu.\n"
										"2. Start New Game.\n" };
};
