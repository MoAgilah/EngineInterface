#include "MenuItem.h"

#include "../../Utilities/Guards.h"
#include "../../Utilities/Vector2.h"

MenuItem::MenuItem(std::shared_ptr<IDrawable> cellSpace)
	: m_menuSlotNumber(-1),
	m_cellSpace(std::move(cellSpace)),
	m_textElement(nullptr),
	m_spriteElement(nullptr)
{
	if (!CheckNotNull(m_cellSpace.get(), "Invalid Pointer 'm_cellSpace'"))
		throw std::invalid_argument("MenuItem requires a valid drawable");
}

void MenuItem::SetSelected(bool isSelected)
{
	if (m_selected == isSelected)
		return;

	m_selected = isSelected;

	if (m_textElement)
		m_textElement->SetSelected(m_selected);

	if (m_spriteElement)
		m_spriteElement->SetSelected(m_selected);
}

void MenuItem::Update(float deltaTime)
{
	if (auto* txt = GetText())
		txt->Update(deltaTime);

	if (auto* spr = GetSprite())
		spr->Update(deltaTime);
}

void MenuItem::Render(IRenderer* renderer)
{
	if (!CheckNotNull(renderer, "Invalid Pointer 'renderer'"))
		return;

#if defined _DEBUG
	m_cellSpace->Render(renderer);
#endif

	if (auto* txt = GetText())
		txt->Render(renderer);

	if (auto* spr = GetSprite())
		spr->Render(renderer);
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

void MenuItem::AddTextElement(std::shared_ptr<IText> text, const NavigationStyles& styles)
{
	m_textElement = std::make_shared<MenuElement<IText>>(std::move(text), styles);
}

IText* MenuItem::GetText()
{
	if (m_textElement)
		return m_textElement->GetDrawable();

	return nullptr;
}

void MenuItem::AddSpriteElement(std::shared_ptr<ISprite> spr, const NavigationStyles& styles)
{
	m_spriteElement = std::make_shared<MenuElement<ISprite>>(std::move(spr), styles);
}

ISprite* MenuItem::GetSprite()
{
	if (m_spriteElement)
		return m_spriteElement->GetDrawable();

	return nullptr;
}