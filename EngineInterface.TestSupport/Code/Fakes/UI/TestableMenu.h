#pragma once

#include "../Drawables/FakeShape.h"
#include <Engine/Interface/UI/IMenu.h>

class TestableMenu : public IMenu
{
public:
	TestableMenu(const Vector2f& menuSize, float outlineThickness, const Vector2u& dimensions, const MenuPositionData& menuPositionData)
		: IMenu(outlineThickness, dimensions, menuPositionData)
	{
		m_menuSpace = std::make_shared<FakeBox>(menuSize, Vector2f());
	}

	void BuildTestCells()
	{
		BuildMenuSpace();

		BuildCells([](const Vector2f& cellSize, float outlineThickness)
			{
				auto box = std::make_shared<FakeBox>(
					cellSize,
					Vector2f{}
				);

				box->SetOrigin(cellSize / 2.f);

				return std::make_shared<MenuItem>(std::move(box));
			});
	}

	const std::vector<size_t>& GetActiveCellsForTesting() const
	{
		return m_activeCells;
	}

	void AddCursor(std::shared_ptr<ISprite> spr, const MenuNav& menuNav) override
	{}

	size_t CalculateCellIndexForTesting(size_t row, size_t col) const
	{
		return IMenu::CalculateCellIndex(row, col);
	}

	Vector2f CalculateCellSizeForTesting(const Vector2f& menuSize)
	{
		IMenu::CalculateCellSize(menuSize);

		return m_cellsSize;
	}

	Vector2f CalculateMenuTopLeftForTesting(const Vector2f& menuPosition, const Vector2f& menuOrigin)
	{
		IMenu::CalculateMenuTopLeft(menuPosition, menuOrigin);
		return m_menuSpaceTopLeft;
	}

	Vector2f CalculateCellPositionForTesting(size_t row, size_t col) const
	{
		return IMenu::CalculateCellPosition(row, col);
	}
};