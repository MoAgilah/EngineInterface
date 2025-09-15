#pragma once

#include "../Drawables/IDrawable.h"
#include "../../../Utilities/Vector.h"
#include "../../../Utilities/Line.h"
#include <memory>

enum class VolumeType { None, Box, Circle, Capsule };
enum class Side { Left, Right, Top, Bottom };
enum class Direction { LDIR, RDIR, UDIR, DDIR };

// Forward declarations
class IBoundingVolume;
class IBoundingBox;
class IBoundingCircle;
class IBoundingCapsule;

class IBoundingVolume
{
public:
	IBoundingVolume(VolumeType type)
		: m_type(type) {}

	virtual ~IBoundingVolume() = default;

    VolumeType GetType() const { return m_type; }

	virtual void Update(const Vector2f& pos) = 0;
    virtual void Render(class IRenderer* renderer) = 0;

    virtual Vector2f GetCenter() const = 0;
    virtual void SetCenter(const Vector2f& center) = 0;

    virtual Vector2f GetPosition() const = 0;
    virtual void SetPosition(const Vector2f& pos) = 0;

    virtual Vector2f GetOrigin() const = 0;
    virtual void SetOrigin(const Vector2f& scl) = 0;

    virtual Vector2f GetScale() const = 0;
    virtual void SetScale(const Vector2f& scl) = 0;

    virtual void* GetNativeShape() = 0;

	virtual bool Intersects(const Vector2f& pnt) const = 0;
	virtual bool Intersects(IBoundingVolume* volume) = 0;
	virtual bool IntersectsMoving(IBoundingVolume* volume, const Vector2f& va, const Vector2f& vb, float& tfirst, float& tlast) = 0;
	virtual Vector2f GetSeparationVector(IBoundingVolume* volume) = 0;
	virtual Vector2f GetPoint(Side side) = 0;

protected:
	// Double dispatch methods
	virtual bool Intersects(IBoundingBox* box) = 0;
	virtual bool Intersects(IBoundingCircle* circle) = 0;
	virtual bool Intersects(IBoundingCapsule* capsule) = 0;

	virtual bool IntersectsMoving(IBoundingBox* box, const Vector2f&, const Vector2f&, float&, float&) = 0;
	virtual bool IntersectsMoving(IBoundingCircle* circle, const Vector2f&, const Vector2f&, float&, float&) = 0;
	virtual bool IntersectsMoving(IBoundingCapsule* capsule, const Vector2f&, const Vector2f&, float&, float&) = 0;

	virtual Vector2f GetSeparationVector(IBoundingBox* other) = 0;
	virtual Vector2f GetSeparationVector(IBoundingCircle* other) = 0;
	virtual Vector2f GetSeparationVector(IBoundingCapsule* other) = 0;

protected:

	VolumeType m_type;
};

template <typename PlatformType>
class BoundingVolume : public virtual IBoundingVolume
{
public:
    explicit BoundingVolume(VolumeType type) : IBoundingVolume(type) {}
    virtual ~BoundingVolume() = default;

    void Render(IRenderer* renderer) override
    {
        if (m_shape)
            m_shape->Render(renderer);
    }

    Vector2f GetCenter() const override
    {
        return m_shape ? m_shape->GetCenter() : Vector2f();
    }

    void SetCenter(const Vector2f& center) override
    {
        if (m_shape)
            m_shape->SetCenter(center);
    }

    // Commonly shared methods
    Vector2f GetPosition() const override
    {
        return m_shape ? m_shape->GetPosition() : Vector2f();
    }

    void SetPosition(const Vector2f& pos) override
    {
        if (m_shape)
            m_shape->SetPosition(pos);
    }

    Vector2f GetOrigin() const override
    {
        return m_shape ? m_shape->GetOrigin() : Vector2f();
    }

    void SetOrigin(const Vector2f& origin) override
    {
        if (m_shape)
            m_shape->SetOrigin(origin);
    }

    Vector2f GetScale() const override
    {
        return m_shape ? m_shape->GetScale() : Vector2f();
    }

    void SetScale(const Vector2f& scl) override
    {
        if (m_shape)
            m_shape->SetScale(scl);
    }

    void* GetNativeShape() override { return static_cast<void*>(m_shape.get()); }

    PlatformType* GetShape() { return m_shape.get(); }

protected:

    std::shared_ptr<PlatformType> m_shape = nullptr;
};

class IBoundingBox : public virtual IBoundingVolume {
public:
    IBoundingBox() : IBoundingVolume(VolumeType::Box) {}
    virtual ~IBoundingBox() = default;

    virtual const Vector2f& GetMin() const { return m_min; }
    virtual const Vector2f& GetMax() const { return m_max; }
    virtual const Vector2f& GetExtents() const { return m_extents; }
    virtual Linef GetSide(Side side) = 0;

protected:

    Vector2f m_min;
    Vector2f m_max;
    Vector2f m_extents;
};

class IBoundingCircle : public virtual IBoundingVolume {
public:
    IBoundingCircle() : IBoundingVolume(VolumeType::Circle) {}
    virtual ~IBoundingCircle() = default;

    virtual float GetRadius() const = 0;
};

class IBoundingCapsule : public virtual IBoundingVolume {
public:
    IBoundingCapsule() : IBoundingVolume(VolumeType::Capsule) {}
    virtual ~IBoundingCapsule() = default;

    virtual bool IntersectsMoving(const Linef& line,
        const Vector2f& va,
        const Vector2f& vb,
        float& tfirst,
        float& tlast) const = 0;

    virtual float GetRadius() const = 0;
    virtual float GetLength() const = 0;
    virtual float GetAngle()  const = 0;
    virtual const Linef GetSegment() const = 0;
};
