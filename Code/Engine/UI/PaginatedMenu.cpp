#include "PaginatedMenu.h"

#include "../../Utilities/Guards.h"

IMenu* PaginatedMenu::AddMenu(std::shared_ptr<IMenu> menu)
{
	if (!CheckNotNull(menu.get(), "Invalid Pointer 'menu'"))
		return nullptr;

	m_menuPages.push_back(std::move(menu));
	return m_menuPages.back().get();
}

IMenu* PaginatedMenu::GetMenuByNumber(int menuNo)
{
	if (m_menuPages.empty())
		return nullptr;

	if (menuNo >= 0 && menuNo < static_cast<int>(m_menuPages.size()))
		return m_menuPages[menuNo].get();

	return nullptr;
}

void PaginatedMenu::Update(float deltaTime)
{
	if (m_currentMenuNum >= m_menuPages.size())
		return;

	auto* currPage = m_menuPages[m_currentMenuNum].get();
	if (!CheckNotNull(currPage, std::format("Invalid Pointer 'currPage' from m_menuPages[{}]", m_currentMenuNum)))
		return;

	currPage->Update(deltaTime);
}

void PaginatedMenu::Render(IRenderer* renderer)
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

void PaginatedMenu::SetCurrentMenuNumber(int menuNo)
{
	if (menuNo >= 0 &&
		static_cast<size_t>(menuNo) < m_menuPages.size())
	{
		m_currentMenuNum = menuNo;
	}
}