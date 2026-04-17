#pragma once


#include "../Drawables/ISprite.h"
#include "../../UI/MenuNavigation.h"
#include "../../../Utilities/Guards.h"
#include <memory>
#include <string>
#include <vector>
#include <exception>

class IMenuCursor
{
public:
	IMenuCursor(ISprite* spr, const MenuNav& menuNav)
		: m_cursor(spr), m_menuNav(menuNav)
	{
		if (!CheckNotNull(m_cursor.get(), "Invalid Pointer 'm_cursor'"))
			throw std::invalid_argument("IMenuCursor requires a valid cursor");
	}

	virtual ~IMenuCursor() = default;

	virtual void Update(float deltaTime)
	{
		m_menuNav.HandleNavigation();

		if (m_cursor)
			m_cursor->Update(deltaTime);
	}

	virtual void Render(IRenderer* renderer)
	{
		if (m_cursor)
			m_cursor->Render(renderer);
	}

	virtual void SetPosition(const Vector2f& pos) = 0;
	virtual void SetScale(const Vector2f& cellSize) = 0;

	MenuNav* GetMenuNav() { return &m_menuNav; }
	ISprite* GetSprite() { return m_cursor.get(); }

protected:

	MenuNav m_menuNav;
	std::shared_ptr<ISprite> m_cursor;
};