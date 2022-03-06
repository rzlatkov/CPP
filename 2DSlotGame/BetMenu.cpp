#include <cstdint>
#include <iostream>

#include "BetMenu.h"
#include <string>

bool BetMenu::SetBet(int16_t newBet, Heading& hd)
{
	if (hd.GetBet() == newBet) {
		return true;
	}

	auto iter = std::find(m_bets.begin(), m_bets.end(), std::to_string(newBet));

	if (iter != m_bets.end())
	{
		uint8_t newBetIndex = static_cast<uint8_t>(std::distance(m_bets.begin(), iter));
		m_bets[newBetIndex] = "[" + m_bets[newBetIndex] + "]";

		m_bets[m_currentBetIndex] = m_bets[m_currentBetIndex].substr(1, m_bets[m_currentBetIndex].length() - 2);

		hd.SetBet(newBet);
		m_currentBetIndex = newBetIndex;

		return true;
	}
	return false;
}

void BetMenu::GetBetsList()
{
	std::cout << "Select Bet From List - {";

	for (int i = 0; i < m_bets.size() - 1; i++)
	{
		std::cout << m_bets[i] + ", ";
	}

	std::cout << m_bets.back() << "}\n\n";
}

uint16_t BetMenu::GetBet(Heading& hd)
{
	return hd.GetBet();
}

void BetMenu::BetMenuView(Heading& hd)
{
	// system("clear");
	system("cls");
	hd.UpdateHeading();
	std::cout << m_defaultOutput << std::endl;
}
