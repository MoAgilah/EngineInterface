#pragma once

#include "IMenuCursor.h"
#include "../Drawables/IDrawable.h"
#include "../Drawables/ISprite.h"
#include "../../UI/MenuItem.h"
#include "../../UI/MenuNavigation.h"
#include "../../../Utilities/Vector2.h"
#include <functional>
#include <memory>
#include <optional>
#include <vector>

enum MenuPositionMode
{
	Centered,
	Anchored
};

struct MenuPositionData
{
	MenuPositionMode m_positionMode;
	std::optional<Vector2f> m_centerPoint;
	std::optional<Vector2f> m_anchorBounds;

	MenuPositionData(MenuPositionMode positionMode, const Vector2f& centerOrAnchor)
		: m_positionMode(positionMode)
	{
		switch (m_positionMode)
		{
		case Centered:
			m_centerPoint = centerOrAnchor;
			m_anchorBounds = std::nullopt;
			break;
		case Anchored:
			m_anchorBounds = centerOrAnchor;
			m_centerPoint = std::nullopt;
			break;
		}
	}
};

class IMenu
{
public:
	IMenu(float outlineThickness, const Vector2u& dimensions, const MenuPositionData& menuPositionData);
	virtual ~IMenu() = default;

	virtual void Update(float dt);
	virtual void Render(IRenderer* renderer);

	void SetActiveCells();

	MenuNav* GetMenuNav() { return &m_menuNavigation; }

	Vector2f GetCellSize() const { return m_cellsSize; }

	virtual void AddCursor(std::shared_ptr<ISprite> spr, const MenuNav& menuNav) = 0;
	IMenuCursor* GetCursor(unsigned int cursorNumber);

	void SetPassiveColour(const Colour& colour) { m_passiveColour = colour; }

	MenuItem* GetCell(const std::pair<int, int>& rowCol);
	MenuItem* GetCellByCellNumber(unsigned int cellNumber);

protected:

	using CellFactory = std::function<
		std::shared_ptr<MenuItem>(const Vector2f&, float)
	>;

	void BuildMenuSpace();
	void BuildCells(const CellFactory& factory);

	void ProcessInput();

	void SetActiveTextElement();

	size_t CalculateCellIndex(size_t row, size_t col) const;
	void CalculateCellSize(const Vector2f& menuSize);
	void CalculateMenuTopLeft(const Vector2f& menuPosition, const Vector2f& menuOrigin);
	Vector2f CalculateCellPosition(size_t row, size_t col) const;

	Vector2f m_cellsSize;
	Vector2u m_dimensions;
	Vector2f m_menuSpaceTopLeft;
	float m_outlineThickness;
	MenuNav m_menuNavigation;
	std::shared_ptr<IDrawable> m_menuSpace;
	MenuPositionData m_menuPositionData;
	std::optional<Colour> m_passiveColour;
	std::vector<std::shared_ptr<MenuItem>> m_cells;
	std::vector<size_t> m_activeCells;
	std::vector<std::shared_ptr<IMenuCursor>> m_cursors;
};