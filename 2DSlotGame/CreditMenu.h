#pragma once
#include <string>

#include "Heading.h"

class CreditMenu
{
public:
	void AddCredit(int32_t value, Heading& hd);
	void SetCredit(Heading& hd);
	uint32_t GetCredit(Heading& hd);
	void CreditMenuView(Heading& hd);
	void AddCreditView(Heading& hd);
	void CashOut(Heading& hd);

private:
	const std::string m_defaultOutput = { "1. Back To Main Menu.\n"
										"2. Add Credit.\n"
										"3. Cashout.\n" };
};
