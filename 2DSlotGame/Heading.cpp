#include <iostream>
#include <string>

#include "Heading.h"

void Heading::UpdateHeading()
{
	std::cout << "--------------------------- Slot Game -------------------------\n";
	std::cout << "[Bet - " << std::to_string(m_currentBet) << "] [Credit - ";
	std::cout << std::to_string(m_credit) << "] [Win - " << std::to_string(m_win);
	std::cout << "]\n---------------------------- Options --------------------------\n";
}

uint16_t Heading::GetBet() const
{
	return m_currentBet;
}

void Heading::SetBet(int16_t newBet)
{
	m_currentBet = newBet;
}

uint16_t Heading::GetWinAmount() const
{
	return m_win;
}

void Heading::UpdateWinAmount(int totalWin)
{
	m_win = totalWin;
}

uint32_t Heading::GetCredit() const
{
	return m_credit;
}

void Heading::CashOut()
{
	m_credit = 0;
}

void Heading::DecreaseCredit(uint16_t bet)
{
	m_credit -= bet;
}

void Heading::AddCredit(int32_t newCredit)
{
	m_credit += newCredit;
}
