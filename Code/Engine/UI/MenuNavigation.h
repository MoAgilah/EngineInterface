#pragma once

#include "../Input/KeyCode.h"
#include <vector>

class MenuNav
{
public:
	MenuNav(KeyCode ascKey, KeyCode desKey);
	~MenuNav() = default;

	void HandleNavigation();

	void ChangeNavKeys(KeyCode ascKey, KeyCode desKey);

	void SetCursorRange(const std::vector<int>& cursorRange);

	int GetCurrCursorPos() const { return m_currCursorPos; }
	void SetCurrCursorPos(int currPos);
	void SetPrevCursorPos(int prevPos) { m_prevCursorPos = prevPos; }

	bool HasMoved() const { return m_currCursorPos != m_prevCursorPos; }

private:

	void HandleDirection(bool isPressed, bool& canMove, int direction);

	bool m_canAsc = false;
	bool m_canDes = true;
	int m_currCursorPos = 0;
	int m_prevCursorPos = -1;
	KeyCode m_ascKey;
	KeyCode m_desKey;
	std::vector<int> m_cursorRange;
};