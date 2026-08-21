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

	static constexpr int s_InvalidPos = -1;

protected:

	void HandleDirection(bool isPressed, bool& canMove, int direction);

	bool m_canAsc = true;
	bool m_canDes = true;
	int m_currCursorPos = s_InvalidPos;
	int m_prevCursorPos = s_InvalidPos;
	KeyCode m_ascKey;
	KeyCode m_desKey;
	std::vector<int> m_cursorRange;
};