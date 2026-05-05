#pragma once

#include <Engine/Core/Constants.h>
#include <Engine/Interface/Drawables/IShape.h>
#include <Utilities/ShapeMath.h>
#include "FakeDrawable.h"
#include <memory>

template<typename TShape>
class FakeShape : public FakeDrawable<TShape>, public IShape
{
public:
	void Update(const Vector2f& pos) {}
	virtual void Render(IRenderer* renderer) {}

	void SetRotation(float rotation) {}

	Colour GetFillColour() { return Colour(); }
	void SetFillColour(const Colour& col) {}

	Colour GetOutlineColour() { return Colour(); }
	void SetOutlineColour(const Colour& col) {}

	float GetOutlineThickness() { return 0.0f; }
	void SetOutlineThickness(float scale) {}

};

class FakeBox : public FakeShape<FakeBox>, public IBoxShape
{
public:
	FakeBox()
	{
		SetScale(GameConstants::Scale);
	}

	FakeBox(const Vector2f& size, const Vector2f& pos)
		: FakeBox()
	{
		Reset(size);
		Update(pos);
	}

	void Update(const Vector2f& pos)
	{
		SetPosition(pos);
		this->SetCenter(GetPosition());
	}

	void Render(IRenderer* renderer) {}

	void Reset(const Vector2f& size)
	{
		SetSize(size);
		SetLocalSize(size);
		SetOrigin(size * 0.5f);
	}

	Vector2f GetSize() override
	{
		return FakeDrawable<FakeBox>::GetSize();
	}

	void SetSize(const Vector2f& size) override
	{
		FakeDrawable<FakeBox>::SetSize(size);
	}
};

class FakeCircle : public FakeShape<FakeCircle>, public ICircleShape
{
public:
	FakeCircle()
		: m_radius(0.0f)
	{
		SetScale(GameConstants::Scale);
	}

	FakeCircle(float radius, const Vector2f& pos)
		: FakeCircle()
	{
		Reset(radius);
		Update(pos);
	}

	void Update(const Vector2f& pos) override
	{
		SetPosition(pos);
		this->SetCenter(GetPosition());
	}

	void Render(IRenderer* renderer) override
	{

	}

	void Reset(float radius)
	{
		SetRadius(radius);
		SetOrigin(Vector2f(radius, radius));
	}

	float GetRadius() override { return m_radius; }
	void SetRadius(float radius) override { m_radius = radius; }

public:

	float m_radius = 0.0f;
};

class FakeCapsule : public FakeShape<FakeCapsule>, public ICapsuleShape
{
public:
	FakeCapsule()
	{
		m_body = std::make_shared<FakeBox>();
		SetScale(GameConstants::Scale);

		m_endCap1 = std::make_shared<FakeCircle>();
		m_endCap1->SetScale(GameConstants::Scale);

		m_endCap2 = std::make_shared<FakeCircle>();
		m_endCap2->SetScale(GameConstants::Scale);
	}

	FakeCapsule(float radius, float length, float angle, const Vector2f& pos)
		: FakeCapsule()
	{
		Reset(radius, length, angle);
		Update(pos);
	}

	void Update(const Vector2f& pos) override
	{
		SetPosition(pos);
		this->SetCenter(pos);

		float radians = m_angle * std::numbers::pi_v<float> / 180.0f;

		Vector2f dir(
			std::cos(radians),
			std::sin(radians)
		);

		auto scale = GetScale();
		float scaledLength = m_length * scale.x;

		Vector2f half = dir * (scaledLength * 0.5f);

		Vector2f end1 = pos - half;
		Vector2f end2 = pos + half;

		if (auto* cap1 = GetEndCap1())
			cap1->SetPosition(end1);

		if (auto* cap2 = GetEndCap2())
			cap2->SetPosition(end2);

		m_segment.start = end1;
		m_segment.end = end2;
	}

	void Render(IRenderer* renderer) override
	{

	}

	void Reset(float radius, float length, float angle)
	{
		m_angle = angle;
		m_radius = radius;
		m_length = length;

		SetSize(Vector2f(length, radius * 2.f));
		SetOrigin({ length / 2.f, radius });
		SetRotation(angle);

		auto* cap1 = GetEndCap1();
		if (cap1)
		{
			cap1->SetRadius(radius);
			cap1->SetOrigin({ radius, radius });
		}

		auto* cap2 = GetEndCap2();
		if (cap2)
		{
			cap2->SetRadius(radius);
			cap2->SetOrigin({ radius, radius });
		}
	}

	FakeBox* GetBody()
	{
		return m_body.get();
	}

	FakeCircle* GetEndCap1()
	{
		return m_endCap1.get();
	}

	FakeCircle* GetEndCap2()
	{
		return m_endCap2.get();
	}

	Vector2f GetSize() override
	{
		return GetBody()->GetSize();
	}

	void SetSize(const Vector2f& size) override
	{
		GetBody()->SetSize(size);
	}

private:

	std::shared_ptr<FakeBox> m_body;
	std::shared_ptr<FakeCircle> m_endCap1;
	std::shared_ptr<FakeCircle> m_endCap2;
};

template <>
struct CapsuleTraits<FakeCapsule>
{
	using CircleType = FakeCircle;
	using BoxType = FakeBox;
};