#include <iostream>
#include <vector>

#include "InfoMenu.h"

void InfoMenu::setNewPage()
{
	if (m_it != m_pages.end())
	{
		auto index = std::distance(m_pages.begin(), m_it);
		m_pages[index] = m_pages[index].substr(1, m_pages[index].length() - 2);
		m_it++;

		if (m_it == m_pages.end())
		{
			m_it = m_pages.begin();
		}
		index = std::distance(m_pages.begin(), m_it);
		m_pages[index] = "[" + m_pages[index] + "]";
	}
}

void InfoMenu::InfoMenuView(Heading& hd)
{
	system("clear");
	// system("cls");
	hd.updateHeading();
	std::cout << m_defaultOutput;
	std::cout << "\t- ";

	for (int i = 0; i < m_pages.size() - 1; i++)
	{
		std::cout << m_pages[i] + ", ";
	}
	std::cout << m_pages.back() << "\n\n";
}
