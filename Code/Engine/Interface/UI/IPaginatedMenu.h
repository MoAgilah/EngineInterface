#pragma once

#include "IMenu.h"
#include <vector>

class IPaginatedMenu
{
public:
	virtual ~IPaginatedMenu() = default;

	void Update(float deltaTime)
	{
		if (m_menuPages.empty())
			return;

		m_menuPages[m_currentMenuNum]->Update(deltaTime);
	}

	void Render(IRenderer* renderer)
	{
		if (m_menuPages.empty())
			return;

		m_menuPages[m_currentMenuNum]->Render(renderer);
	}

	int GetCurrentMenuNumber() { return m_currentMenuNum; }

	void SetCurrentMenuNumber(int menuNo)
	{
		if (menuNo >= 0 && menuNo < m_menuPages.size())
		{
			m_currentMenuNum = menuNo;
		}
	}

	IMenu* AddMenu(IMenu* menu)
	{
		m_menuPages.push_back(std::shared_ptr<IMenu>(menu));
		return GetMenuByNumber(static_cast<int>(m_menuPages.size() - 1));
	}

	IMenu* GetMenuByNumber(int menuNo)
	{
		if (m_menuPages.empty())
			return nullptr;

		if (menuNo >= 0 && menuNo < static_cast<int>(m_menuPages.size()))
			return m_menuPages[menuNo].get();

		return nullptr;
	}

	IMenu* GetCurrentMenu() { return GetMenuByNumber(m_currentMenuNum); }

protected:

	unsigned int m_currentMenuNum = 0;
	unsigned int m_previousMenuNum = -1;
	std::vector<std::shared_ptr<IMenu>> m_menuPages;
};