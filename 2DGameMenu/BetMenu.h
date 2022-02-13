#pragma once

#include <vector>

#include "Heading.h"

class BetMenu
{
public:
	bool SetBet(int16_t newBet, Heading& hd);
	void GetBetsList();
	uint16_t GetBet(Heading& hd);
	void BetMenuView(Heading& hd);

private:
	uint8_t m_currentBetIndex = 1;
	const std::string m_defaultOutput = { "Bet Menu Options:\n"
										"1. Back To Main Menu.\n"
										"2. Select Bet.\n" };

	std::vector<std::string> m_bets = { "1", "[5]", "10", "20", "50", "100", "200" };
};