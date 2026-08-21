#pragma once

#include <Engine/UI/MenuNavigation.h>

class TestableMenuNav : public MenuNav
{
public:
	TestableMenuNav(KeyCode ascKey, KeyCode desKey)
		: MenuNav(ascKey, desKey)
	{}

	KeyCode GetAscKeyForTesting() { return m_ascKey; }
	KeyCode GetDesKeyForTesting() { return m_desKey; }

	int GetPrevCurrCursorPosForTesting() const { return m_prevCursorPos; }

	bool GetCanAscForTesting() { return m_canAsc; }
	bool GetCanDesForTesting() { return m_canDes; }

	const std::vector<int>& GetCursorRangeForTesting() { return m_cursorRange; }
};