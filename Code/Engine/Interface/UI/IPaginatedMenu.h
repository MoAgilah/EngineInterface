#pragma once

#include "IMenu.h"
#include "../../../Utilities/Guards.h"
#include <vector>
#include <format>

class IPaginatedMenu
{
public:
	virtual ~IPaginatedMenu() = default;

	void Update(float deltaTime)
	{
		if (m_currentMenuNum >= m_menuPages.size())
			return;

		auto* currPage = m_menuPages[m_currentMenuNum].get();
		if (!CheckNotNull(currPage, std::format("Invalid Pointer 'currPage' from m_menuPages[{}]", m_currentMenuNum)))
			return;

		currPage->Update(deltaTime);
	}

	void Render(IRenderer* renderer)
	{
		if (!CheckNotNull(renderer, "Invalid Pointer 'renderer'"))
			return;

		if (m_currentMenuNum >= m_menuPages.size())
			return;

		auto* currPage = m_menuPages[m_currentMenuNum].get();
		if (!CheckNotNull(currPage, std::format("Invalid Pointer 'currPage' from m_menuPages[{}]", m_currentMenuNum)))
			return;

		currPage->Render(renderer);
	}

	int GetCurrentMenuNumber() const { return m_currentMenuNum; }

	void SetCurrentMenuNumber(int menuNo)
	{
		if (menuNo >= 0 && menuNo < m_menuPages.size())
		{
			m_currentMenuNum = menuNo;
		}
	}

	IMenu* AddMenu(IMenu* menu)
	{
		if (!CheckNotNull(menu, "Invalid Pointer 'menu'"))
			return __nullptr;

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