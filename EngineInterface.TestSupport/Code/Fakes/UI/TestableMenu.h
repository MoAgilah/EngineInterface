#pragma once

#include "../Drawables/FakeShape.h"
#include "../UI/TestableMenuCursor.h"
#include <Engine/Interface/UI/IMenu.h>

class TestableMenu : public IMenu
{
public:
	TestableMenu(const MenuConfig& config, const Vector2f& menuSize)
		: IMenu(config)
	{
		m_menuSpace = std::make_shared<FakeBox>(menuSize, Vector2f());
	}

	void Update(float deltaTime) override
	{
		IMenu::Update(deltaTime);
	}

	IDrawable* GetMenuSpace() { return m_menuSpace.get(); }

	std::shared_ptr<MenuItem> GetSharedCellForTesting(size_t index) const
	{
		return m_cells.at(index);
	}

	void SetMenuSpaceToNullForTesting()
	{
		m_menuSpace = nullptr;
	}

	void BuildTestMenuSpace()
	{
		BuildMenuSpace();
	}

	void BuildTestCells()
	{
		BuildTestCellsWithFactory(
			[&](const Vector2f& cellSize, float outlineThickness)
			{
				receivedCellSize = cellSize;
				receivedOutlineThickness = outlineThickness;
				++factoryCallCount;

				auto box = std::make_shared<FakeBox>(
					cellSize,
					Vector2f{}
				);

				box->SetOrigin(cellSize / 2.f);

				return std::make_shared<MenuItem>(std::move(box));
			}
		);
	}

	void BuildTestCellsWithFactory(const CellFactory& factory)
	{
		BuildMenuSpace();
		BuildCells(factory);
	}


	void AddTestTextCell(unsigned int row, unsigned int col, int slotNumber, const Colour& defaultColour, const std::string& id, const NavigationStyles& styles)
	{
		ConfigureCell(row, col, {
			.slotNumber = slotNumber,
			.text = std::make_shared<FakeText>(
			TextConfig("fontName", 12, Vector2f(), defaultColour),
			id),
			.textStyles = styles });
	}

	const std::vector<size_t>& GetActiveCellsForTesting() const
	{
		return m_activeCells;
	}

	IMenuCursor* AddCursor(std::shared_ptr<ISprite> spr, const MenuNav& menuNav) override
	{
		auto fSprite = std::dynamic_pointer_cast<FakeSprite>(spr);

		if (!CheckNotNull(fSprite.get(), "Invalid Pointer 'fSprite'"))
			return nullptr;

		auto cursor = std::make_shared<TestableMenuCursor>(
			std::move(fSprite),
			menuNav
		);

		m_cursors.emplace_back(std::move(cursor));

		return m_cursors.back().get();
	}

	size_t GetNumberOfCells() const
	{
		return m_cells.size();
	}

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

public:

	Vector2f receivedCellSize{};
	float receivedOutlineThickness = 0.f;
	int factoryCallCount = 0;
};