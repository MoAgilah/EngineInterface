#pragma once

#include <Engine/Interface/UI/IMenuCursor.h>
#include "../Drawables/FakeSprite.h"

class TestableMenuCursor : public IMenuCursor
{
public:
	TestableMenuCursor(std::shared_ptr<FakeSprite> spr, const MenuNav& menuNav)
		: IMenuCursor(std::move(spr), menuNav)
	{

	}

	void SetPosition(const Vector2f& pos) override
	{
		static_cast<FakeSprite*>(m_cursor.get())->SetPosition(pos);
	}

	void SetScale(const Vector2f& cellSize) override
	{
		static_cast<FakeSprite*>(m_cursor.get())->SetScale(cellSize);
	}
};

