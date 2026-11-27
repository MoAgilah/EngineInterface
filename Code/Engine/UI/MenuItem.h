#pragma once

#include "MenuElement.h"
#include "../Interface/Drawables/IDrawable.h"
#include "../Interface/Drawables/ISprite.h"
#include "../Interface/Drawables/IText.h"
#include <memory>
#include <optional>

class MenuItem
{
public:
	MenuItem(std::shared_ptr<IDrawable> cellSpace);

	virtual ~MenuItem() = default;

	bool GetSelected() const { return m_selected; }
	void SetSelected(bool isSelected);

	void Update(float deltaTime);

	void Render(IRenderer* renderer);

	int GetMenuSlotNumber() const { return m_menuSlotNumber; }
	void SetMenuSlotNumber(int slotNumber) { m_menuSlotNumber = slotNumber; }

	Vector2f GetPosition() const;
	void SetPosition(const Vector2f& position);

	Vector2f GetOrigin() const;
	Vector2f GetSize() const;

	void AddTextElement(std::shared_ptr<IText> text, const NavigationStyles& styles);

	IText* GetText();

	void AddSpriteElement(std::shared_ptr<ISprite> spr, const NavigationStyles& styles);

	ISprite* GetSprite();

private:

	int m_menuSlotNumber;
	bool m_selected = false;
	std::shared_ptr<IDrawable> m_cellSpace;
	std::shared_ptr<MenuElement<IText>> m_textElement;
	std::shared_ptr<MenuElement<ISprite>> m_spriteElement;
};
