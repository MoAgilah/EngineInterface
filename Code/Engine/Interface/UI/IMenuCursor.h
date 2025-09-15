#pragma once

#include "../../UI/MenuNavigation.h"
#include "../Drawables/ISprite.h"
#include <string>
#include <vector>
#include <memory>

class IMenuCursor
{
public:
	IMenuCursor(ISprite* spr, const MenuNav& menuNav)
		: m_cursor(spr), m_menuNav(menuNav)
	{}

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