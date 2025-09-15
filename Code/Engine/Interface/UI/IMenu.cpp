#include "IMenu.h"

IMenu::IMenu(float outlineThickness, const Vector2f& dimensions, const MenuPositionData& menuPositionData)
	: m_outlineThickness(outlineThickness), m_dimensions(dimensions), m_menuPositionData(menuPositionData), m_menuNavigation(KeyCode::Up, KeyCode::Down)
{
}

void IMenu::Update(float dt)
{
	ProcessInput();

	if (!m_cursors.empty())
	{
		for (auto& cursor : m_cursors)
		{
			auto menuNav = cursor->GetMenuNav();

			if (menuNav->HasMoved())
			{
				int cellNo = menuNav->GetCurrCursorPos();
				auto cell = GetCellByCellNumber(cellNo);
				if (cell)
				{
					cursor->SetPosition(cell->GetPosition());
					menuNav->SetPrevCursorPos(cellNo);
				}
			}
		}
	}
	else
	{
		if (m_menuNavigation.HasMoved())
		{
			SetActiveTextElement();
		}
	}

	for (const auto& cellNo : m_activeCells)
	{
		auto cell = GetCell(cellNo);
		if (cell)
			cell->Update(dt);
	}
}

void IMenu::Render(IRenderer* renderer)
{
#if defined _DEBUG
	m_menuSpace->Render(renderer);

	for (auto& col : m_columns)
		col->Render(renderer);
#endif

	for (auto& row : m_rows)
	{
		for (auto& cell : row)
			cell->Render(renderer);
	}

	if (!m_cursors.empty())
	{
		for (auto& cursor : m_cursors)
			cursor->Render(renderer);
	}
}

void IMenu::SetActiveCells()
{
	for (size_t i = 0; i < m_rows.size(); i++)
	{
		for (size_t j = 0; j < m_rows[i].size(); j++)
		{
			if (m_rows[i][j]->GetMenuSlotNumber() >= 0)
			{
				m_activeCells.emplace_back(static_cast<int>(i), static_cast<int>(j));
			}
		}
	}
}

IMenuCursor* IMenu::GetCursor(unsigned int cursorNumber)
{
	if (cursorNumber >= 0 && cursorNumber < m_cursors.size())
		return m_cursors[cursorNumber].get();

	return nullptr;
}

IMenuItem* IMenu::GetCell(const std::pair<int, int>& colRow)
{
	if (colRow.first >= 0 && colRow.first < m_rows.size())
	{
		if (colRow.second >= 0 && colRow.second < m_rows[colRow.first].size())
			return m_rows[colRow.first][colRow.second].get();
	}

	return nullptr;
}

IMenuItem* IMenu::GetCellByCellNumber(unsigned int cellNumber)
{
	if (cellNumber >= 0 && cellNumber < m_activeCells.size())
		return GetCell(m_activeCells[cellNumber]);

	return nullptr;
}

void IMenu::ProcessInput()
{
	if (!m_cursors.empty())
	{
		for (auto& cursor : m_cursors)
			cursor->GetMenuNav()->HandleNavigation();
	}
	else
	{
		m_menuNavigation.HandleNavigation();
	}
}

void IMenu::SetActiveTextElement()
{
}