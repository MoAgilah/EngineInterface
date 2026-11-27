#include "IMenu.h"

#include "../../../Utilities/Guards.h"
#include "../../../Utilities/Logger.h"
#include <format>
#include <utility>

IMenu::IMenu(const MenuConfig& config)
	: m_config(config), m_menuNavigation(KeyCode::Up, KeyCode::Down)
{
	auto& dimensions = m_config.dimensions;

	ThrowIfFalse(
		dimensions.x > 0 && dimensions.y > 0,
		"Menu must have at least one column and one row."
	);
}

void IMenu::ConfigureCell(int row, int col, const MenuCellConfig& config)
{
	auto* cell = GetCell({row,col});

	if (!CheckNotNull(cell, std::format("Invalid Pointer 'cell({},{})'", row, col)))
		return;

	cell->SetMenuSlotNumber(config.slotNumber);

	if (config.text)
	{
		cell->AddTextElement(config.text,
			config.textStyles.value_or(m_config.defaultTextStyles));
	}

	if (config.sprite)
	{
		cell->AddSpriteElement(config.sprite,
			config.spriteStyles.value_or(m_config.defaultSpriteStyles));
	}
}

void IMenu::Update(float dt)
{
	ProcessInput();

	std::unordered_set<int> previousPositions;
	std::unordered_set<int> currentPositions;

	if (!m_cursors.empty())
	{
		for (size_t i = 0; i < m_cursors.size(); ++i)
		{
			auto* cursor = m_cursors[i].get();

			if (!CheckNotNull(cursor,
				std::format("Invalid Pointer 'cursor' at index {}", i)))
				continue;

			auto& menuNav = cursor->GetMenuNav();

			CollectNavigationPositions(menuNav, previousPositions, currentPositions);

			UpdateCursorPosition(cursor);

			cursor->Update(dt);
		}
	}
	else
	{
		CollectNavigationPositions(m_menuNavigation, previousPositions, currentPositions);

		if (m_menuNavigation.HasMoved())
			m_menuNavigation.SetPrevCursorPos(m_menuNavigation.GetCurrCursorPos());
	}

	UpdateSelectedItems(previousPositions, currentPositions);

	for (size_t i = 0; i < m_cells.size(); ++i)
	{
		auto* cell = m_cells[i].get();

		if (!CheckNotNull(cell,
			std::format("Invalid Pointer 'cell' at index {}", i)))
			continue;

		cell->Update(dt);
	}
}


void IMenu::Render(IRenderer* renderer)
{
	if (!CheckNotNull(renderer, "Invalid Pointer 'renderer'"))
		return;

#if defined _DEBUG
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

	auto& dimensions = m_config.dimensions;

	if (static_cast<unsigned int>(row) >= dimensions.y ||
		static_cast<unsigned int>(col) >= dimensions.x)
		return nullptr;

	const size_t index = CalculateCellIndex(row, col);

	return GetCellByIndex(index);
}

MenuItem* IMenu::GetCellByIndex(size_t index)
{
	if (index >= m_cells.size())
		return nullptr;

	return m_cells[index].get();
}

MenuItem* IMenu::GetCellBySlotNumber(int slotNumber)
{
	if (slotNumber < 0)
		return nullptr;

	for (const size_t index : m_activeCells)
	{
		if (index >= m_cells.size())
			continue;

		auto* cell = m_cells[index].get();

		if (!cell)
			continue;

		if (cell->GetMenuSlotNumber() == slotNumber)
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

	auto& menuPosData = m_config.positionData;

	switch (menuPosData.m_positionMode)
	{
	case MenuPositionMode::Centered:
		m_menuSpace->SetPosition(*menuPosData.m_centerPoint);
		break;

	case MenuPositionMode::Anchored:
		m_menuSpace->SetPosition(
			(*menuPosData.m_anchorBounds - size) / 2.f
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
	m_activeCells.clear();
	m_cells.clear();

	auto& dimensions = m_config.dimensions;

	m_cells.reserve(
		static_cast<size_t>(dimensions.x) * dimensions.y
	);

	for (size_t row = 0; row < dimensions.y; ++row)
	{
		for (size_t col = 0; col < dimensions.x; ++col)
		{
			auto cell = factory(m_cellsSize, m_config.outlineThickness);

			if (!CheckNotNull(cell.get(), "Invalid Pointer 'cell'"))
			{
				throw std::runtime_error("Failed to build menu cell: cell factory returned a null pointer");
			}

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

void IMenu::CollectNavigationPositions(const MenuNav& menuNav, std::unordered_set<int>& prevPositions, std::unordered_set<int>& currPositions)
{
	const int currPos = menuNav.GetCurrCursorPos();
	const int prevPos = menuNav.GetPrevCursorPos();

	if (currPos != MenuNav::s_InvalidPos)
		currPositions.insert(currPos);

	if (prevPos != MenuNav::s_InvalidPos)
		prevPositions.insert(prevPos);
}

void IMenu::UpdateCursorPosition(IMenuCursor* cursor)
{
	auto& menuNav = cursor->GetMenuNav();

	if (!menuNav.HasMoved())
		return;

	const int cellNo = menuNav.GetCurrCursorPos();

	auto* cell = GetCellBySlotNumber(cellNo);

	if (!cell)
	{
		Logger::GetDefaultLogger().Log(
			LogLevel::Error,
			std::format(
				"Invalid Pointer 'cell' from GetCellBySlotNumber({})",
				cellNo));
		return;
	}

	cursor->SetPosition(cell->GetPosition());
	menuNav.SetPrevCursorPos(cellNo);
}

void IMenu::UpdateSelectedItems(const std::unordered_set<int>& prevPositions, const std::unordered_set<int>& currPositions)
{
	for (const auto& position : prevPositions)
	{
		if (currPositions.contains(position))
			continue;

		auto* cell = GetCellBySlotNumber(position);

		if (!cell)
		{
			Logger::GetDefaultLogger().Log(
				LogLevel::Error,
				std::format(
					"Invalid Pointer 'cell' from GetCellBySlotNumber({})",
					position));
			continue;
		}

		cell->SetSelected(false);
	}

	for (const auto& position : currPositions)
	{
		if (prevPositions.contains(position))
			continue;

		auto* cell = GetCellBySlotNumber(position);

		if (!cell)
		{
			Logger::GetDefaultLogger().Log(
				LogLevel::Error,
				std::format(
					"Invalid Pointer 'cell' from GetCellBySlotNumber({})",
					position));
			continue;
		}

		cell->SetSelected(true);
	}
}

size_t IMenu::CalculateCellIndex(size_t row, size_t col) const
{
	return row * m_config.dimensions.x + col;
}

void IMenu::CalculateCellSize(const Vector2f& menuSize)
{
	auto& dimensions = m_config.dimensions;

	m_cellsSize = {
	   menuSize.x / static_cast<float>(dimensions.x),
	   menuSize.y / static_cast<float>(dimensions.y)
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