#include "MenuItem.h"

#include "../../Utilities/Guards.h"
#include "../../Utilities/Vector2.h"

MenuItem::MenuItem(std::shared_ptr<IDrawable> cellSpace)
	: m_menuSlotNumber(-1),
	m_cellSpace(std::move(cellSpace)),
	m_textElement(nullptr),
	m_spriteElement(nullptr)
{
	if (!m_cellSpace)
		throw std::invalid_argument("MenuItem requires a valid drawable");
}

void MenuItem::Update(float deltaTime)
{
	if (m_textElement)
		m_textElement->Update(deltaTime);

	if (m_spriteElement)
		m_spriteElement->Update(deltaTime);
}

void MenuItem::Render(IRenderer* renderer)
{
	if (!CheckNotNull(renderer, "Invalid Pointer 'renderer'"))
		return;

#if defined _DEBUG
	if (!CheckNotNull(m_cellSpace.get(), "Invalid Pointer 'm_cellSpace'"))
		return;

	m_cellSpace->Render(renderer);
#endif

	if (m_textElement)
		m_textElement->Render(renderer);

	if (m_spriteElement)
		m_spriteElement->Render(renderer);
}

Vector2f MenuItem::GetPosition() const
{
	if (!CheckNotNull(m_cellSpace.get(), "Invalid Pointer 'm_cellSpace'"))
		return Vector2f();

	return m_cellSpace->GetPosition();
}

void MenuItem::SetPosition(const Vector2f& position)
{
	if (!CheckNotNull(m_cellSpace.get(), "Invalid Pointer 'm_cellSpace'"))
		return;

	m_cellSpace->SetPosition(position);
}

Vector2f MenuItem::GetOrigin() const
{
	if (!CheckNotNull(m_cellSpace.get(), "Invalid Pointer 'm_cellSpace'"))
		return Vector2f();

	return m_cellSpace->GetOrigin();
}

Vector2f MenuItem::GetSize() const
{
	if (!CheckNotNull(m_cellSpace.get(), "Invalid Pointer 'm_cellSpace'"))
		return Vector2f();

	return m_cellSpace->GetSize();
}

IText* MenuItem::AddTextElement(std::shared_ptr<IText> text)
{
	m_textElement = std::move(text);
	return m_textElement.get();
}

IText* MenuItem::GetTextElement()
{
	if (m_textElement)
		return m_textElement.get();

	return nullptr;
}

ISprite* MenuItem::AddSpriteElement(std::shared_ptr<ISprite> spr)
{
	m_spriteElement = std::move(spr);
	return m_spriteElement.get();
}

ISprite* MenuItem::GetSpriteElement()
{
	if (m_spriteElement)
		return m_spriteElement.get();

	return nullptr;
}