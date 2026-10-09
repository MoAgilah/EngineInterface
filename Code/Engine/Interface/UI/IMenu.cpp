#include "IMenu.h"

#include "../../../Utilities/Guards.h"
#include "../../../Utilities/Logger.h"
#include <format>
#include <unordered_set>
#include <utility>

IMenu::IMenu(float outlineThickness, const Vector2u& dimensions, const MenuPositionData& menuPositionData)
	: m_outlineThickness(outlineThickness), m_dimensions(dimensions), m_menuPositionData(menuPositionData), m_menuNavigation(KeyCode::Up, KeyCode::Down)
{
	ThrowIfFalse(
		dimensions.x > 0 && dimensions.y > 0,
		"Menu must have at least one column and one row."
	);
}


void IMenu::Update(float dt)
{
	// Process navigation input
	ProcessInput();

	if (!m_cursors.empty())
	{
		for (size_t i = 0; i < m_cursors.size(); ++i)
		{
			auto* cursor = m_cursors[i].get();

			if (!CheckNotNull(cursor,
				std::format("Invalid Pointer 'cursor' at index {}", i)))
				continue;

			auto& menuNav = cursor->GetMenuNav();

			if (menuNav.HasMoved())
			{
				const int cellNo = menuNav.GetCurrCursorPos();

				if (cellNo >= 0)
				{
					auto* cell = GetCellByCellNumber(
						static_cast<unsigned int>(cellNo));

					if (!cell)
					{
						Logger::GetDefaultLogger().Log(
							LogLevel::Error,
							std::format(
								"Invalid Pointer 'cell' from GetCellByCellNumber({})",
								cellNo));
					}
					else
					{
						cursor->SetPosition(cell->GetPosition());
						menuNav.SetPrevCursorPos(cellNo);
					}
				}
			}

			// Update cursor visuals every frame
			cursor->Update(dt);
		}
	}
	else
	{
		if (m_menuNavigation.HasMoved())
			SetActiveTextElement();
	}

	// Update active menu cells
	for (const size_t index : m_activeCells)
	{
		if (index >= m_cells.size())
			continue;

		auto* cell = m_cells[index].get();

		if (!CheckNotNull(cell,
			std::format("Invalid Pointer 'cell' at index {}", index)))
			continue;

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
#endif

	for (size_t i = 0; i < m_cells.size(); ++i)
	{
		auto* cell = m_cells[i].get();

		if (!CheckNotNull(cell,
			std::format("Invalid Pointer 'cell' at index {}", i)))
			continue;

		cell->Render(renderer);
	}

	for (size_t i = 0; i < m_cursors.size(); ++i)
	{
		auto* cursor = m_cursors[i].get();

		if (!CheckNotNull(cursor,
			std::format("Invalid Pointer 'cursor' at index {}", i)))
			continue;

		cursor->Render(renderer);
	}
}

void IMenu::SetActiveCells()
{
	std::unordered_set<int> usedSlotNumbers;
	std::vector<size_t> activeCells;

	for (size_t i = 0; i < m_cells.size(); ++i)
	{
		auto* cell = m_cells[i].get();

		if (!CheckNotNull(cell,
			std::format("Invalid Pointer 'cell' at index {}", i)))
			continue;

		const int slotNumber = cell->GetMenuSlotNumber();

		if (slotNumber < 0)
			continue;

		ThrowIfFalse(
			usedSlotNumbers.insert(slotNumber).second,
			std::format("Duplicate menu slot number {} at index {}",
				slotNumber, i)
		);

		activeCells.emplace_back(i);
	}

	// Validate that slot numbers are consecutive from zero
	for (size_t slot = 0; slot < usedSlotNumbers.size(); ++slot)
	{
		ThrowIfFalse(
			usedSlotNumbers.contains(static_cast<int>(slot)),
			std::format("Missing menu slot number {}", slot)
		);
	}

	m_activeCells = std::move(activeCells);
}

IMenuCursor* IMenu::GetCursor(unsigned int cursorNumber)
{
	if (cursorNumber < m_cursors.size())
		return m_cursors[cursorNumber].get();

	return nullptr;
}

MenuItem* IMenu::GetCell(const std::pair<int, int>& rowCol)
{
	const auto [row, col] = rowCol;

	if (row < 0 || col < 0)
		return nullptr;

	if (static_cast<unsigned int>(row) >= m_dimensions.y ||
		static_cast<unsigned int>(col) >= m_dimensions.x)
		return nullptr;

	const size_t index = CalculateCellIndex(row, col);

	if (index >= m_cells.size())
		return nullptr;

	return m_cells[index].get();
}

MenuItem* IMenu::GetCellByCellNumber(unsigned int cellNumber)
{
	for (const size_t index : m_activeCells)
	{
		if (index >= m_cells.size())
			continue;

		auto* cell = m_cells[index].get();

		if (cell && cell->GetMenuSlotNumber() == cellNumber)
			return cell;
	}

	return nullptr;
}

void IMenu::BuildMenuSpace()
{
	if (!CheckNotNull(m_menuSpace.get(), "Invalid menu space"))
	{
		throw std::runtime_error("Failed to initialise menu space");
	}

	const auto size = m_menuSpace->GetSize();

	m_menuSpace->SetOrigin(size / 2.f);

	switch (m_menuPositionData.m_positionMode)
	{
	case MenuPositionMode::Centered:
		m_menuSpace->SetPosition(*m_menuPositionData.m_centerPoint);
		break;

	case MenuPositionMode::Anchored:
		m_menuSpace->SetPosition(
			(*m_menuPositionData.m_anchorBounds - size) / 2.f
			+ m_menuSpace->GetOrigin()
		);
		break;
	}

	CalculateCellSize(size);

	CalculateMenuTopLeft(
		m_menuSpace->GetPosition(),
		m_menuSpace->GetOrigin()
	);
}

void IMenu::BuildCells(const CellFactory& factory)
{
	m_cells.clear();

	m_cells.reserve(
		static_cast<size_t>(m_dimensions.x) * m_dimensions.y
	);

	for (size_t row = 0; row < m_dimensions.y; ++row)
	{
		for (size_t col = 0; col < m_dimensions.x; ++col)
		{
			auto cell = factory(m_cellsSize, m_outlineThickness);

			if (!CheckNotNull(cell.get(), "Invalid Pointer 'cell'"))
				continue;

			cell->SetPosition(CalculateCellPosition(row, col));

			m_cells.emplace_back(std::move(cell));
		}
	}
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

			auto& menuNav = cursor->GetMenuNav();

			menuNav.HandleNavigation();
		}
	}
	else
	{
		m_menuNavigation.HandleNavigation();
	}
}

void IMenu::SetActiveTextElement()
{
	if (!m_passiveColour)
		return;

	for (const size_t index : m_activeCells)
	{
		if (index >= m_cells.size())
			continue;

		auto* cell = m_cells[index].get();

		if (!CheckNotNull(cell,
			std::format("Invalid Pointer 'cell' at index {}", index)))
			continue;

		auto* text = cell->GetTextElement();

		if (!text)
			continue;

		if (cell->GetMenuSlotNumber() ==
			m_menuNavigation.GetCurrCursorPos())
		{
			text->SetOutlineColour(text->GetDefaultColour());
		}
		else
		{
			text->SetOutlineColour(*m_passiveColour);
		}
	}
}

size_t IMenu::CalculateCellIndex(size_t row, size_t col) const
{
	return row * m_dimensions.x + col;
}

void IMenu::CalculateCellSize(const Vector2f& menuSize)
{
	m_cellsSize = {
	   menuSize.x / static_cast<float>(m_dimensions.x),
	   menuSize.y / static_cast<float>(m_dimensions.y)
	};
}

void IMenu::CalculateMenuTopLeft(const Vector2f& menuPosition, const Vector2f& menuOrigin)
{
	m_menuSpaceTopLeft = menuPosition - menuOrigin;
}

Vector2f IMenu::CalculateCellPosition(size_t row, size_t col) const
{
	return {
		m_menuSpaceTopLeft.x +
			(static_cast<float>(col) + 0.5f) * m_cellsSize.x,

		m_menuSpaceTopLeft.y +
			(static_cast<float>(row) + 0.5f) * m_cellsSize.y
	};
}