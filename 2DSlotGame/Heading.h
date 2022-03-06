#pragma once
#include <cstdint>

class Heading
{
public:
	void UpdateHeading();
	uint16_t GetBet() const;
	void SetBet(int16_t newBet);
	uint16_t GetWinAmount() const;
	void UpdateWinAmount(int totalWin);
	uint32_t GetCredit() const;
	void CashOut();
	void DecreaseCredit(uint16_t bet);
	void AddCredit(int32_t newCredit);

private:
	uint16_t m_currentBet = 40;
	uint16_t m_win = 0;
	uint32_t m_credit = 0;

};
