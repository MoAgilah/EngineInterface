#pragma once

#include "../Interface/Drawables/IDrawable.h"
#include "../Interface/Drawables/ISprite.h"
#include "../Interface/Drawables/IText.h"
#include <memory>

class MenuItem
{
public:
	MenuItem(std::shared_ptr<IDrawable> cellSpace);

	virtual ~MenuItem() = default;

	void Update(float deltaTime);

	void Render(IRenderer* renderer);

	int GetMenuSlotNumber() const { return m_menuSlotNumber; }
	void SetMenuSlotNumber(int slotNumber) { m_menuSlotNumber = slotNumber; }

	Vector2f GetPosition() const;
	void SetPosition(const Vector2f& position);

	Vector2f GetOrigin() const;
	Vector2f GetSize() const;

	IText* AddTextElement(std::shared_ptr<IText> text);

	IText* GetTextElement();

	ISprite* AddSpriteElement(std::shared_ptr<ISprite> spr);

	ISprite* GetSpriteElement();

private:

	int m_menuSlotNumber;
	std::shared_ptr<IDrawable> m_cellSpace;
	std::shared_ptr<IText> m_textElement;
	std::shared_ptr<ISprite> m_spriteElement;
};
