#include <cstdint>

#include "CreditMenu.h"
#include "Heading.h"
#include <iostream>

// forward declaration
// class Heading;

void CreditMenu::AddCredit(int32_t value, Heading& hd)
{
	if (value > 0)
	{
		hd.AddCredit(value);
	}
}

void CreditMenu::SetCredit(Heading& hd)
{
	if (hd.GetCredit() - hd.GetBet() >= 0)
	{
		hd.DecreaseCredit(hd.GetBet());
	}
}

uint32_t CreditMenu::GetCredit(Heading& hd)
{
	return hd.GetCredit();
}

void CreditMenu::CreditMenuView(Heading& hd)
{
	system("clear");
	// system("cls");
	hd.updateHeading();
	std::cout << m_defaultOutput << std::endl;
	std::cout << "User Input : ";
}

void CreditMenu::AddCreditView(Heading& hd)
{
	system("clear");
	// system("cls");
	hd.updateHeading();
	std::cout << "\nEnter Amount: ";
}

void CreditMenu::CashOut(Heading& hd)
{
	hd.CashOut();
}
