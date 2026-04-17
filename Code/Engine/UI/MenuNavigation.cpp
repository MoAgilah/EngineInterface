#include "MenuNavigation.h"

#include "../Core/GameManager.h"
#include "../../Utilities/Guards.h"

MenuNav::MenuNav(KeyCode ascKey, KeyCode desKey)
	: m_ascKey(ascKey), m_desKey(desKey)
{
}

void MenuNav::HandleNavigation()
{
	auto* gameMgr = GameManager::Get();
	if (!CheckNotNull(gameMgr, "Invalid Pointer 'gameMgr' from GameManager::Get()"))
		return;

	auto* inputMgr = gameMgr->GetInputManager();
	if (!CheckNotNull(inputMgr, "Invalid Pointer 'inputMgr' from gameMgr->GetInputManager()"))
		return;

	HandleDirection(inputMgr->GetKeyState((int)m_ascKey), m_canAsc, -1);
	HandleDirection(inputMgr->GetKeyState((int)m_desKey), m_canDes, 1);
}

void MenuNav::ChangeNavKeys(KeyCode ascKey, KeyCode desKey)
{
	m_ascKey = ascKey;
	m_desKey = desKey;
}

void MenuNav::SetCursorRange(const std::vector<int>& cursorRange)
{
	m_cursorRange = cursorRange;
}

void MenuNav::SetCurrCursorPos(int currPos)
{
	if (currPos >= *(m_cursorRange.begin()) && currPos <= *(m_cursorRange.rbegin()))
	{
		m_currCursorPos = currPos;
	}
}

void MenuNav::HandleDirection(bool isPressed, bool& canMove, int direction)
{
	if (isPressed)
	{
		if (canMove)
		{
			SetCurrCursorPos(m_currCursorPos + direction);
			canMove = false;
		}
	}
	else
	{
		canMove = true;
	}
}