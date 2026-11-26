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
#include <unordered_set>
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

struct MenuConfig
{
	float outlineThickness;
	Vector2u dimensions;
	MenuPositionData positionData;

	NavigationStyles defaultTextStyles;
	NavigationStyles defaultSpriteStyles;
};

struct MenuCellConfig
{
	int slotNumber = -1;

	std::shared_ptr<IText> text;
	std::shared_ptr<ISprite> sprite;

	std::optional<NavigationStyles> textStyles;
	std::optional<NavigationStyles> spriteStyles;
};

class IMenu
{
public:
	IMenu(const MenuConfig& config);
	virtual ~IMenu() = default;

	void ConfigureCell(int row, int col,
		const MenuCellConfig& config);

	virtual void Update(float dt);
	virtual void Render(IRenderer* renderer);

	void SetActiveCells();

	MenuNav* GetMenuNav() { return &m_menuNavigation; }

	Vector2f GetCellSize() const { return m_cellsSize; }

	virtual IMenuCursor* AddCursor(std::shared_ptr<ISprite> spr, const MenuNav& menuNav) = 0;
	IMenuCursor* GetCursor(unsigned int cursorNumber);

	MenuItem* GetCell(const std::pair<int, int>& rowCol);
	MenuItem* GetCellByIndex(size_t index);
	MenuItem* GetCellBySlotNumber(int slotNumber);

protected:

	using CellFactory = std::function<
		std::shared_ptr<MenuItem>(const Vector2f&, float)
	>;

	void BuildMenuSpace();
	void BuildCells(const CellFactory& factory);

	void ProcessInput();

	void CollectNavigationPositions(const MenuNav& menuNav,
		std::unordered_set<int>& prevPositions,
		std::unordered_set<int>& currPositions);

	void UpdateCursorPosition(IMenuCursor* cursor);
	void UpdateSelectedItems(const std::unordered_set<int>& prevPositions,
		const std::unordered_set<int>& currPositions);

	size_t CalculateCellIndex(size_t row, size_t col) const;
	void CalculateCellSize(const Vector2f& menuSize);
	void CalculateMenuTopLeft(const Vector2f& menuPosition, const Vector2f& menuOrigin);
	Vector2f CalculateCellPosition(size_t row, size_t col) const;

	Vector2f m_cellsSize;
	Vector2f m_menuSpaceTopLeft;
	MenuConfig m_config;
	MenuNav m_menuNavigation;
	std::shared_ptr<IDrawable> m_menuSpace;
	std::vector<std::shared_ptr<MenuItem>> m_cells;
	std::vector<size_t> m_activeCells;
	std::vector<std::shared_ptr<IMenuCursor>> m_cursors;
};