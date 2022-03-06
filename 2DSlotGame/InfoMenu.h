#pragma once

#include "Heading.h"

class InfoMenu
{
public:
	void setNewPage();
	void InfoMenuView(Heading& hd);
private:
	const std::string m_defaultOutput = { "1. Back to Main Menu.\n"
										"2. Change Info Page.\n" };

	std::vector<std::string> m_pages = { "[Paytable]", "Rules", "Gamble", "Convertor", "Free spins" };
	std::vector<std::string>::iterator m_it = m_pages.begin();
};