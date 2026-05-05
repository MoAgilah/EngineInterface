#include "CppUnitTest.h"

#include <Engine/Collisions/BoundingBox.h>
#include <Engine/Collisions/BoundingCircle.h>
#include <Engine/Collisions/BoundingCapsule.h>
#include <Fakes/Drawables/FakeShape.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Engine
{
    namespace Collisions
    {
        TEST_CLASS(BoundingBoxTests)
        {
        public:
            TEST_METHOD(BoundingBox_DefaultConstructor_DoesNotThrow)
            {
                BoundingBox<FakeBox> aabb;
            }

            TEST_METHOD(BoundingBox_Constructor_WithSize_DoesNotThrow)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16.f, 16.f));
            }

            TEST_METHOD(BoundingBox_Constructor_WithSize_SetsExtents)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16.f, 16.f));

                auto ext = aabb.GetExtents();

                Assert::AreEqual(8.f, ext.x);
                Assert::AreEqual(8.f, ext.y);
            }

            TEST_METHOD(BoundingBox_Constructor_WithSize_SetsOrigin)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16.f, 16.f));

                auto ori = aabb.GetOrigin();

                Assert::AreEqual(8.f, ori.x);
                Assert::AreEqual(8.f, ori.y);
            }

            TEST_METHOD(BoundingBox_Constructor_WithSizeAndPos_DoesNotThrow)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16, 16), Vector2f(16, 16));
            }


            TEST_METHOD(BoundingBox_Constructor_WithSizeAndPos_SetsExtents)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16, 16), Vector2f(16, 16));

                auto ext = aabb.GetExtents();

                Assert::AreEqual(8.f, ext.x);
                Assert::AreEqual(8.f, ext.y);
            }

            TEST_METHOD(BoundingBox_Constructor_WithSizeAndPos_SetsOrigin)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16, 16), Vector2f(16, 16));

                auto ori = aabb.GetOrigin();

                Assert::AreEqual(8.f, ori.x);
                Assert::AreEqual(8.f, ori.y);
            }

            TEST_METHOD(BoundingBox_Constructor_WithSizeAndPos_SetsMin)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16, 16), Vector2f(16, 16));

                auto min = aabb.GetMin();

                Assert::AreEqual(8.f, min.x);
                Assert::AreEqual(8.f, min.y);
            }

            TEST_METHOD(BoundingBox_Constructor_WithSizeAndPos_SetsMax)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16, 16), Vector2f(16, 16));

                auto max = aabb.GetMax();

                Assert::AreEqual(24.f, max.x);
                Assert::AreEqual(24.f, max.y);
            }

            TEST_METHOD(BoundingBox_Constructor_WithSizeAndPos_SetsPosition)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16, 16), Vector2f(16, 16));

                auto pos = aabb.GetPosition();

                Assert::AreEqual(16.f, pos.x);
                Assert::AreEqual(16.f, pos.y);
            }

            TEST_METHOD(BoundingBox_Constructor_WithSizeAndPos_SetsCenter)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16, 16), Vector2f(16, 16));

                auto cen = aabb.GetCenter();

                Assert::AreEqual(16.f, cen.x);
                Assert::AreEqual(16.f, cen.y);
            }

            TEST_METHOD(BoundingBox_GetNativeShape_CanBeCastToFakeBox)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16, 16), Vector2f(16, 16));

                auto* box = static_cast<FakeBox*>(aabb.GetNativeShape());

                Assert::IsNotNull(box);
            }

            TEST_METHOD(BoundingBox_GetCenter_ReturnsDefault)
            {
                BoundingBox<FakeBox> aabb;

                auto cen = aabb.GetCenter();

                Assert::AreEqual(0.f, cen.x);
                Assert::AreEqual(0.f, cen.y);
            }

            TEST_METHOD(BoundingBox_SetCenter_UpdatesCenter)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16, 16), Vector2f(16, 16));

                aabb.SetCenter(Vector2f(32.f, 32.f));

                auto cen = aabb.GetCenter();

                Assert::AreEqual(32.f, cen.x);
                Assert::AreEqual(32.f, cen.y);
            }

            TEST_METHOD(BoundingBox_GetPosition_ReturnsDefault)
            {
                BoundingBox<FakeBox> aabb;

                auto pos = aabb.GetPosition();

                Assert::AreEqual(0.f, pos.x);
                Assert::AreEqual(0.f, pos.y);
            }

            TEST_METHOD(BoundingBox_SetPosition_UpdatesPosition)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16, 16), Vector2f(16, 16));

                aabb.SetPosition(Vector2f(32.f, 32.f));

                auto pos = aabb.GetPosition();

                Assert::AreEqual(32.f, pos.x);
                Assert::AreEqual(32.f, pos.y);
            }

            TEST_METHOD(BoundingBox_GetOrigin_ReturnsDefault)
            {
                BoundingBox<FakeBox> aabb;

                auto ori = aabb.GetOrigin();

                Assert::AreEqual(0.f, ori.x);
                Assert::AreEqual(0.f, ori.y);
            }

            TEST_METHOD(BoundingBox_SetOrigin_UpdatesOrigin)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16, 16), Vector2f(16, 16));

                aabb.SetOrigin(Vector2f(0.f, 0.f));

                auto ori = aabb.GetOrigin();

                Assert::AreEqual(0.f, ori.x);
                Assert::AreEqual(0.f, ori.y);
            }

            TEST_METHOD(BoundingBox_GetScale_ReturnsDefault)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16, 16), Vector2f(16, 16));

                auto scl = aabb.GetScale();

                Assert::AreEqual(1.f, scl.x);
                Assert::AreEqual(1.f, scl.y);
            }

            TEST_METHOD(BoundingBox_SetScale_UpdatesScale)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16, 16), Vector2f(16, 16));

                aabb.SetScale(Vector2f(2, 2));

                auto scl = aabb.GetScale();

                Assert::AreEqual(2.f, scl.x);
                Assert::AreEqual(2.f, scl.y);
            }

            TEST_METHOD(BoundingBox_GetMin_ReturnsDefault)
            {
                BoundingBox<FakeBox> aabb;

                auto min = aabb.GetMin();

                Assert::AreEqual(0.f, min.x);
                Assert::AreEqual(0.f, min.y);
            }

            TEST_METHOD(BoundingBox_GetMin_ReturnsMin)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16, 16), Vector2f(16, 16));

                auto min = aabb.GetMin();

                Assert::AreEqual(8.f, min.x);
                Assert::AreEqual(8.f, min.y);
            }

            TEST_METHOD(BoundingBox_GetMax_ReturnsDefault)
            {
                BoundingBox<FakeBox> aabb;

                auto max = aabb.GetMax();

                Assert::AreEqual(0.f, max.x);
                Assert::AreEqual(0.f, max.y);
            }

            TEST_METHOD(BoundingBox_GetMax_ReturnsMax)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16, 16), Vector2f(16, 16));

                auto max = aabb.GetMax();

                Assert::AreEqual(24.f, max.x);
                Assert::AreEqual(24.f, max.y);
            }

            TEST_METHOD(BoundingBox_GetExtents_ReturnsDefault)
            {
                BoundingBox<FakeBox> aabb;

                auto ext = aabb.GetExtents();

                Assert::AreEqual(0.f, ext.x);
                Assert::AreEqual(0.f, ext.y);
            }

            TEST_METHOD(BoundingBox_GetExtents_ReturnsExtents)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16, 16), Vector2f(16, 16));

                auto ext = aabb.GetExtents();

                Assert::AreEqual(8.f, ext.x);
                Assert::AreEqual(8.f, ext.y);
            }

            TEST_METHOD(BoundingBox_GetSide_Top_ReturnsTopSide)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16, 16), Vector2f(16, 16));

                auto side = aabb.GetSide(Side::Top);

                Assert::AreEqual(8.f, side.start.x);
                Assert::AreEqual(8.f, side.start.y);
                Assert::AreEqual(24.f, side.end.x);
                Assert::AreEqual(8.f, side.end.y);
            }

            TEST_METHOD(BoundingBox_GetSide_Bottom_ReturnsBottomSide)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16, 16), Vector2f(16, 16));

                auto side = aabb.GetSide(Side::Bottom);

                Assert::AreEqual(8.f, side.start.x);
                Assert::AreEqual(24.f, side.start.y);
                Assert::AreEqual(24.f, side.end.x);
                Assert::AreEqual(24.f, side.end.y);
            }

            TEST_METHOD(BoundingBox_GetSide_Left_ReturnsLeftSide)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16, 16), Vector2f(16, 16));

                auto side = aabb.GetSide(Side::Left);

                Assert::AreEqual(8.f, side.start.x);
                Assert::AreEqual(8.f, side.start.y);
                Assert::AreEqual(8.f, side.end.x);
                Assert::AreEqual(24.f, side.end.y);
            }

            TEST_METHOD(BoundingBox_GetSide_Right_ReturnsRightSide)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16, 16), Vector2f(16, 16));

                auto side = aabb.GetSide(Side::Right);

                Assert::AreEqual(24.f, side.start.x);
                Assert::AreEqual(8.f, side.start.y);
                Assert::AreEqual(24.f, side.end.x);
                Assert::AreEqual(24.f, side.end.y);
            }

            TEST_METHOD(BoundingBox_GetSide_Unknown_ReturnsDefault)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16, 16), Vector2f(16, 16));

                auto side = aabb.GetSide(static_cast<Side>(-1));

                Assert::AreEqual(0.f, side.start.x);
                Assert::AreEqual(0.f, side.start.y);
                Assert::AreEqual(0.f, side.end.x);
                Assert::AreEqual(0.f, side.end.y);
            }

            TEST_METHOD(BoundingBox_GetPoint_Left_ReturnsCorrectPoint)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16, 16), Vector2f(16, 16));

                auto pnt = aabb.GetPoint(Side::Left);

                Assert::AreEqual(8.f, pnt.x);
                Assert::AreEqual(16.f, pnt.y);
            }

            TEST_METHOD(BoundingBox_GetPoint_Right_ReturnsCorrectPoint)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16, 16), Vector2f(16, 16));

                auto pnt = aabb.GetPoint(Side::Right);

                Assert::AreEqual(24.f, pnt.x);
                Assert::AreEqual(16.f, pnt.y);
            }

            TEST_METHOD(BoundingBox_GetPoint_Top_ReturnsCorrectPoint)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16, 16), Vector2f(16, 16));

                auto pnt = aabb.GetPoint(Side::Top);

                Assert::AreEqual(16.f, pnt.x);
                Assert::AreEqual(8.f, pnt.y);
            }

            TEST_METHOD(BoundingBox_GetPoint_Bottom_ReturnsCorrectPoint)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16, 16), Vector2f(16, 16));

                auto pnt = aabb.GetPoint(Side::Bottom);

                Assert::AreEqual(16.f, pnt.x);
                Assert::AreEqual(24.f, pnt.y);
            }

            TEST_METHOD(BoundingBox_GetPoint_Unknown_ReturnsDefault)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16, 16), Vector2f(16, 16));

                auto pnt = aabb.GetPoint(static_cast<Side>(-1));

                Assert::AreEqual(0.f, pnt.x);
                Assert::AreEqual(0.f, pnt.y);
            }

            TEST_METHOD(BoundingBox_SqDistPoint_ReturnsResult)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));

                float result = aabb.SqDistPoint(Vector2f(30.0f, 30.0f));

                Assert::AreEqual(72.0f, result);
            }

            TEST_METHOD(BoundingBox_SqDistPoint_ReturnsZero_WhenPointInside)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));

                float result = aabb.SqDistPoint(Vector2f(10.0f, 10.0f));

                Assert::AreEqual(0.0f, result);
            }

            TEST_METHOD(BoundingBox_Intersects_Point_ReturnsTrue)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));

                bool result = aabb.Intersects(Vector2f(16.0f, 16.0f));

                Assert::IsTrue(result);
            }

            TEST_METHOD(BoundingBox_Intersects_Point_ReturnsFalse)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));

                bool result = aabb.Intersects(Vector2f(30.0f, 30.0f));

                Assert::IsFalse(result);
            }

            TEST_METHOD(BoundingBox_Intersects_Box_ReturnsTrue)
            {
                BoundingBox<FakeBox> aabb1(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));
                BoundingBox<FakeBox> aabb2(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));

                bool result = aabb1.Intersects(static_cast<IBoundingVolume*>(&aabb2));

                Assert::IsTrue(result);
            }

            TEST_METHOD(BoundingBox_Intersects_Box_ReturnsFalse)
            {
                BoundingBox<FakeBox> aabb1(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));
                BoundingBox<FakeBox> aabb2(Vector2f(16.0f, 16.0f), Vector2f(40.0f, 40.0f));

                bool result = aabb1.Intersects(static_cast<IBoundingVolume*>(&aabb2));

                Assert::IsFalse(result);
            }

            TEST_METHOD(BoundingBox_Intersects_Circle_ReturnsTrue)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));
                BoundingCircle<FakeCircle> circle(16, Vector2f(16.0f, 16.0f));

                bool result = aabb.Intersects(static_cast<IBoundingVolume*>(&circle));

                Assert::IsTrue(result);
            }

            TEST_METHOD(BoundingBox_Intersects_Circle_ReturnsFalse)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));
                BoundingCircle<FakeCircle> circle(16, Vector2f(40.f, 40.0f));

                bool result = aabb.Intersects(static_cast<IBoundingVolume*>(&circle));

                Assert::IsFalse(result);
            }

            TEST_METHOD(BoundingBox_Intersects_Capsule_ReturnsTrue)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));
                BoundingCapsule<FakeCapsule> capsule(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));

                bool result = aabb.Intersects(static_cast<IBoundingVolume*>(&capsule));

                Assert::IsTrue(result);
            }

            TEST_METHOD(BoundingBox_Intersects_Capsule_ReturnsFalse)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));
                BoundingCapsule<FakeCapsule> capsule(16.0f, 16.0f, 0.0f, Vector2f(50.0f, 50.0f));

                bool result = aabb.Intersects(static_cast<IBoundingVolume*>(&capsule));

                Assert::IsFalse(result);
            }

            TEST_METHOD(BoundingBox_Intersects_Unknown_ReturnsFalse)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));

                bool result = aabb.Intersects(static_cast<IBoundingVolume*>(nullptr));

                Assert::IsFalse(result);
            }

            TEST_METHOD(BoundingBox_MovingVsUnknown_ReturnsFalse)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));

                float tfirst = 0.0f;
                float tlast = 0.0f;

                bool result = aabb.IntersectsMoving(
                    static_cast<IBoundingVolume*>(nullptr),
                    Vector2f(0.0f, 0.0f),
                    Vector2f(0.0f, 0.0f),
                    tfirst,
                    tlast
                );

                Assert::IsFalse(result);
            }

            TEST_METHOD(BoundingBox_MovingVsStatic_Box_ReturnsTrue)
            {
                BoundingBox<FakeBox> staticBox(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));
                BoundingBox<FakeBox> movingBox(Vector2f(16.0f, 16.0f), Vector2f(40.0f, 16.0f));

                float tfirst = 0.0f;
                float tlast = 0.0f;

                bool result = staticBox.IntersectsMoving(
                    static_cast<IBoundingVolume*>(&movingBox),
                    Vector2f(0.0f, 0.0f),
                    Vector2f(-24.0f, 0.0f),
                    tfirst,
                    tlast
                );

                Assert::IsTrue(result);
            }

            TEST_METHOD(BoundingBox_MovingVsStatic_Box_ReturnsFalse)
            {
                BoundingBox<FakeBox> staticBox(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));
                BoundingBox<FakeBox> movingBox(Vector2f(16.0f, 16.0f), Vector2f(40.0f, 40.0f));

                float tfirst = 0.0f;
                float tlast = 0.0f;

                bool result = staticBox.IntersectsMoving(
                    static_cast<IBoundingVolume*>(&movingBox),
                    Vector2f(0.0f, 0.0f),
                    Vector2f(-24.0f, 0.0f),
                    tfirst,
                    tlast
                );

                Assert::IsFalse(result);
            }

            TEST_METHOD(BoundingBox_MovingVsStatic_Circle_ReturnsTrue)
            {
                BoundingBox<FakeBox> staticBox(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));
                BoundingCircle<FakeCircle> movingCircle(16.0f, Vector2f(40.0f, 16.0f));

                float tfirst = 0.0f;
                float tlast = 0.0f;

                bool result = staticBox.IntersectsMoving(
                    static_cast<IBoundingVolume*>(&movingCircle),
                    Vector2f(0.0f, 0.0f),
                    Vector2f(-24.0f, 0.0f),
                    tfirst,
                    tlast
                );

                Assert::IsTrue(result);
            }

            TEST_METHOD(BoundingBox_MovingVsStatic_Circle_ReturnsFalse)
            {
                BoundingBox<FakeBox> staticBox(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));
                BoundingCircle<FakeCircle> movingCircle(16.0f, Vector2f(40.0f, 64.0f));

                float tfirst = 0.0f;
                float tlast = 0.0f;

                bool result = staticBox.IntersectsMoving(
                    static_cast<IBoundingVolume*>(&movingCircle),
                    Vector2f(0.0f, 0.0f),
                    Vector2f(-24.0f, 0.0f),
                    tfirst,
                    tlast
                );

                Assert::IsFalse(result);
            }

            TEST_METHOD(BoundingBox_MovingVsStatic_Capsule_ReturnsTrue)
            {
                BoundingBox<FakeBox> staticBox(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));
                BoundingCapsule<FakeCapsule> movingCapsule(16.0f, 16.0f, 0.0f, Vector2f(40.0f, 16.0f));

                float tfirst = 0.0f;
                float tlast = 0.0f;

                bool result = staticBox.IntersectsMoving(
                    static_cast<IBoundingVolume*>(&movingCapsule),
                    Vector2f(0.0f, 0.0f),
                    Vector2f(-24.0f, 0.0f),
                    tfirst,
                    tlast
                );

                Assert::IsTrue(result);
            }

            TEST_METHOD(BoundingBox_MovingVsStatic_Capsule_ReturnsFalse)
            {
                BoundingBox<FakeBox> staticBox(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));
                BoundingCapsule<FakeCapsule> movingCapsule(16.0f, 16.0f, 0.0f, Vector2f(40.0f, 64.0f));

                float tfirst = 0.0f;
                float tlast = 0.0f;

                bool result = staticBox.IntersectsMoving(
                    static_cast<IBoundingVolume*>(&movingCapsule),
                    Vector2f(0.0f, 0.0f),
                    Vector2f(-24.0f, 0.0f),
                    tfirst,
                    tlast
                );

                Assert::IsFalse(result);
            }

            TEST_METHOD(BoundingBox_MovingVsDynamic_Box_ReturnsTrue)
            {
                BoundingBox<FakeBox> movingBox1(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));
                BoundingBox<FakeBox> movingBox2(Vector2f(16.0f, 16.0f), Vector2f(40.0f, 16.0f));

                float tfirst = 0.0f;
                float tlast = 0.0f;

                bool result = movingBox1.IntersectsMoving(
                    static_cast<IBoundingVolume*>(&movingBox2),
                    Vector2f(12.0f, 0.0f),
                    Vector2f(-12.0f, 0.0f),
                    tfirst,
                    tlast
                );

                Assert::IsTrue(result);
            }

            TEST_METHOD(BoundingBox_MovingVsDynamic_Box_ReturnsFalse)
            {
                BoundingBox<FakeBox> movingBox1(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));
                BoundingBox<FakeBox> movingBox2(Vector2f(16.0f, 16.0f), Vector2f(40.0f, 40.0f));

                float tfirst = 0.0f;
                float tlast = 0.0f;

                bool result = movingBox1.IntersectsMoving(
                    static_cast<IBoundingVolume*>(&movingBox2),
                    Vector2f(12.0f, 0.0f),
                    Vector2f(-12.0f, 0.0f),
                    tfirst,
                    tlast
                );

                Assert::IsFalse(result);
            }

            TEST_METHOD(BoundingBox_MovingVsDynamic_Circle_ReturnsTrue)
            {
                BoundingBox<FakeBox> movingBox(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));
                BoundingCircle<FakeCircle> movingCircle(16.0f, Vector2f(40.0f, 16.0f));

                float tfirst = 0.0f;
                float tlast = 0.0f;

                bool result = movingBox.IntersectsMoving(
                    static_cast<IBoundingVolume*>(&movingCircle),
                    Vector2f(12.0f, 0.0f),
                    Vector2f(-12.0f, 0.0f),
                    tfirst,
                    tlast
                );

                Assert::IsTrue(result);
            }

            TEST_METHOD(BoundingBox_MovingVsDynamic_Circle_ReturnsFalse)
            {
                BoundingBox<FakeBox> movingBox(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));
                BoundingCircle<FakeCircle> movingCircle(16.0f, Vector2f(40.0f, 64.0f));

                float tfirst = 0.0f;
                float tlast = 0.0f;

                bool result = movingBox.IntersectsMoving(
                    static_cast<IBoundingVolume*>(&movingCircle),
                    Vector2f(12.0f, 0.0f),
                    Vector2f(-12.0f, 0.0f),
                    tfirst,
                    tlast
                );

                Assert::IsFalse(result);
            }

            TEST_METHOD(BoundingBox_MovingVsDynamic_Capsule_ReturnsTrue)
            {
                BoundingBox<FakeBox> movingBox(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));
                BoundingCapsule<FakeCapsule> movingCapsule(16.0f, 16.0f, 0.0f, Vector2f(40.0f, 16.0f));

                float tfirst = 0.0f;
                float tlast = 0.0f;

                bool result = movingBox.IntersectsMoving(
                    static_cast<IBoundingVolume*>(&movingCapsule),
                    Vector2f(12.0f, 0.0f),
                    Vector2f(-12.0f, 0.0f),
                    tfirst,
                    tlast
                );

                Assert::IsTrue(result);
            }

            TEST_METHOD(BoundingBox_MovingVsDynamic_Capsule_ReturnsFalse)
            {
                BoundingBox<FakeBox> movingBox(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));
                BoundingCapsule<FakeCapsule> movingCapsule(16.0f, 16.0f, 0.0f, Vector2f(40.0f, 64.0f));

                float tfirst = 0.0f;
                float tlast = 0.0f;

                bool result = movingBox.IntersectsMoving(
                    static_cast<IBoundingVolume*>(&movingCapsule),
                    Vector2f(12.0f, 0.0f),
                    Vector2f(-12.0f, 0.0f),
                    tfirst,
                    tlast
                );

                Assert::IsFalse(result);
            }

            TEST_METHOD(BoundingBox_GetSeparationVector_Box_ReturnsSeparationOnCollision)
            {
                BoundingBox<FakeBox> aabb1(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));
                BoundingBox<FakeBox> aabb2(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));

                bool result = aabb1.Intersects(static_cast<IBoundingVolume*>(&aabb2));

                Assert::IsTrue(result);

                auto sepVec = aabb1.GetSeparationVector(static_cast<IBoundingVolume*>(&aabb2));

                Assert::AreEqual(0.f, sepVec.x);
                Assert::AreEqual(16.01f, sepVec.y);
            }

            TEST_METHOD(BoundingBox_GetSeparationVector_Box_ReturnsDefaultOnNoCollision)
            {
                BoundingBox<FakeBox> aabb1(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));
                BoundingBox<FakeBox> aabb2(Vector2f(16.0f, 16.0f), Vector2f(40.0f, 40.0f));

                bool result = aabb1.Intersects(static_cast<IBoundingVolume*>(&aabb2));

                Assert::IsFalse(result);

                auto sepVec = aabb1.GetSeparationVector(static_cast<IBoundingVolume*>(&aabb2));

                Assert::AreEqual(0.f, sepVec.x);
                Assert::AreEqual(0.f, sepVec.y);
            }

            TEST_METHOD(BoundingBox_GetSeparationVector_Circle_ReturnsDefaultOnNoCollision)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));
                BoundingCircle<FakeCircle> circle(16, Vector2f(40.f, 40.0f));

                bool result = aabb.Intersects(static_cast<IBoundingVolume*>(&circle));

                Assert::IsFalse(result);

                auto sepVec = aabb.GetSeparationVector(static_cast<IBoundingVolume*>(&circle));

                Assert::AreEqual(0.f, sepVec.x);
                Assert::AreEqual(0.f, sepVec.y);
            }

            TEST_METHOD(BoundingBox_GetSeparationVector_Circle_ReturnsSeparationOnCollision)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));
                BoundingCircle<FakeCircle> circle(16, Vector2f(16.0f, 16.0f));

                bool result = aabb.Intersects(static_cast<IBoundingVolume*>(&circle));

                Assert::IsTrue(result);

                auto sepVec = aabb.GetSeparationVector(static_cast<IBoundingVolume*>(&circle));

                Assert::AreEqual(0.f, sepVec.x);
                Assert::AreEqual(16.01f, sepVec.y);
            }

            TEST_METHOD(BoundingBox_GetSeparationVector_Capsule_ReturnsDefaultOnNoCollision)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));
                BoundingCapsule<FakeCapsule> capsule(16.0f, 16.0f, 0.0f, Vector2f(50.0f, 50.0f));

                bool result = aabb.Intersects(static_cast<IBoundingVolume*>(&capsule));

                Assert::IsFalse(result);

                auto sepVec = aabb.GetSeparationVector(static_cast<IBoundingVolume*>(&capsule));

                Assert::AreEqual(0.f, sepVec.x);
                Assert::AreEqual(0.f, sepVec.y);
            }

            TEST_METHOD(BoundingBox_GetSeparationVector_Capsule_ReturnsSeparationOnCollision)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));
                BoundingCapsule<FakeCapsule> capsule(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));

                bool result = aabb.Intersects(static_cast<IBoundingVolume*>(&capsule));

                Assert::IsTrue(result);

                auto sepVec = aabb.GetSeparationVector(static_cast<IBoundingVolume*>(&capsule));

                Assert::AreEqual(-16.01f, sepVec.x);
                Assert::AreEqual(0.f, sepVec.y);
            }

            TEST_METHOD(BoundingBox_GetSeparationVector_Unknown_ReturnsDefault)
            {
                BoundingBox<FakeBox> aabb(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));

                auto sepVec = aabb.GetSeparationVector(static_cast<IBoundingVolume*>(nullptr));

                Assert::AreEqual(0.f, sepVec.x);
                Assert::AreEqual(0.f, sepVec.y);
            }
        };
    }
}