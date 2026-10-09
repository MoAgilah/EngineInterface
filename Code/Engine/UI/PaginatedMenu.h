#pragma once

#include "../Interface/UI/IMenu.h"
#include "../../Utilities/Guards.h"
#include <format>
#include <vector>

class PaginatedMenu
{
public:
	PaginatedMenu() = default;
	~PaginatedMenu() = default;

	IMenu* AddMenu(std::shared_ptr<IMenu> menu);
	IMenu* GetMenuByNumber(int menuNo);
	IMenu* GetCurrentMenu() { return GetMenuByNumber(m_currentMenuNum); }

	void Update(float deltaTime);

	void Render(IRenderer* renderer);

	int GetCurrentMenuNumber() const { return m_currentMenuNum; }

	void SetCurrentMenuNumber(int menuNo);

private:

	unsigned int m_currentMenuNum = 0;
	std::vector<std::shared_ptr<IMenu>> m_menuPages;
};