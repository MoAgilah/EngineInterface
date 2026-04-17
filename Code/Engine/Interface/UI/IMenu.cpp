#include "IMenu.h"

#include "../../../Utilities/Logger.h"
#include "../../../Utilities/Guards.h"
#include "../../../Utilities/Utils.h"
#include <format>

IMenu::IMenu(float outlineThickness, const Vector2f& dimensions, const MenuPositionData& menuPositionData)
	: m_outlineThickness(outlineThickness), m_dimensions(dimensions), m_menuPositionData(menuPositionData), m_menuNavigation(KeyCode::Up, KeyCode::Down)
{
}

void IMenu::Update(float dt)
{
	ProcessInput();

	if (!m_cursors.empty())
	{
		for (size_t i = 0; i < m_cursors.size(); ++i)
		{
			auto* cursor = m_cursors[i].get();
			if (!CheckNotNull(cursor,
				std::format("Invalid Pointer 'cursor' at index {}", i)))
				continue;

			auto* menuNav = cursor->GetMenuNav();
			if (!CheckNotNull(menuNav, "Invalid Pointer 'menuNav' from cursor->GetMenuNav()"))
				continue;

			if (menuNav->HasMoved())
			{
				int cellNo = menuNav->GetCurrCursorPos();

				auto* cell = GetCellByCellNumber(cellNo);
				if (!cell)
				{
					Logger::GetDefaultLogger().Log(
						LogLevel::Error,
						std::format("Invalid Pointer 'cell' from GetCellByCellNumber({})", cellNo));
					continue;
				}

				cursor->SetPosition(cell->GetPosition());
				menuNav->SetPrevCursorPos(cellNo);
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

	for (const auto& [col, row] : m_activeCells)
	{
		auto* cell = GetCell({ col, row });

		if (!cell)
		{
			Logger::GetDefaultLogger().Log(
				LogLevel::Error,
				std::format("Invalid Pointer 'cell' from GetCell({}, {})",
					col, row));
			continue;
		}

		cell->Update(dt);
	}
}

void IMenu::Render(IRenderer* renderer)
{
	if (!CheckNotNull(renderer, "Invalid Pointer 'renderer'"))
		return;

#if defined _DEBUG

	if (!CheckNotNull(m_menuSpace.get(), "Invalid Pointer 'm_menuSpace'"))
		return;

	m_menuSpace->Render(renderer);

	for (size_t i = 0; i < m_columns.size(); ++i)
	{
		auto* col = m_columns[i].get();
		if (!CheckNotNull(col,
			std::format("Invalid Pointer 'col' at index {}", i)))
			continue;

		col->Render(renderer);
	}
#endif

	for (size_t i = 0; i < m_rows.size(); ++i)
	{
		for (size_t j = 0; j < m_rows[i].size(); ++j)
		{
			auto* cell = m_rows[i][j].get();

			if (!cell)
			{
				Logger::GetDefaultLogger().Log(
					LogLevel::Error,
					std::format("Invalid Pointer 'cell' at ({}, {})", i, j));
				continue;
			}

			cell->Render(renderer);
		}
	}

	if (!m_cursors.empty())
	{
		for (size_t i = 0; i < m_cursors.size(); ++i)
		{
			auto* cursor = m_cursors[i].get();
			if (!CheckNotNull(cursor,
				std::format("Invalid Pointer 'cursor' at index {}", i)))
				continue;

			cursor->Render(renderer);
		}
	}
}

void IMenu::SetActiveCells()
{
	for (size_t i = 0; i < m_rows.size(); i++)
	{
		for (size_t j = 0; j < m_rows[i].size(); j++)
		{
			auto* cell = m_rows[i][j].get();

			if (!cell)
			{
				Logger::GetDefaultLogger().Log(
					LogLevel::Error,
					std::format("Invalid Pointer 'cell' at ({}, {})", i, j));
				continue;
			}

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
		for (size_t i = 0; i < m_cursors.size(); ++i)
		{
			auto* cursor = m_cursors[i].get();
			if (!CheckNotNull(cursor,
				std::format("Invalid Pointer 'cursor' at index {}", i)))
				continue;

			auto* menuNav = cursor->GetMenuNav();
			if (!CheckNotNull(menuNav, "Invalid Pointer 'menuNav' from cursor->GetMenuNav()"))
				continue;

			menuNav->HandleNavigation();
		}
	}
	else
	{
		m_menuNavigation.HandleNavigation();
	}
}