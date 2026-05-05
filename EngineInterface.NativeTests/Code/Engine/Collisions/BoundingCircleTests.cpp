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
        TEST_CLASS(BoundingCircleTests)
        {
        public:
            TEST_METHOD(BoundingCircle_DefaultConstructor_DoesNotThrow)
            {
                BoundingCircle<FakeCircle> bc;
            }

            TEST_METHOD(BoundingCircle_GetRadius_ReturnsDefault)
            {
                BoundingCircle<FakeCircle> bc;

                Assert::AreEqual(0.0f, bc.GetRadius());
            }

            TEST_METHOD(BoundingCircle_Constructor_WithRadius_DoesNotThrow)
            {
                BoundingCircle<FakeCircle> bc(16.f);

                Assert::AreEqual(16.0f, bc.GetRadius());
            }

            TEST_METHOD(BoundingCircle_Constructor_WithRadius_SetsOrigins)
            {
                BoundingCircle<FakeCircle> bc(16.f);

                auto ori = bc.GetOrigin();

                Assert::AreEqual(16.f, ori.x);
                Assert::AreEqual(16.f, ori.y);
            }

            TEST_METHOD(BoundingCircle_Constructor_WithRadiusAndPos_SetsRadius)
            {
                BoundingCircle<FakeCircle> bc(16.f, Vector2f(16.f, 16.f));

                Assert::AreEqual(16.0f, bc.GetRadius());
            }

            TEST_METHOD(BoundingCircle_Constructor_WithRadiusAndPos_SetsOrigins)
            {
                BoundingCircle<FakeCircle> bc(16.f, Vector2f(16.f, 16.f));

                auto ori = bc.GetOrigin();

                Assert::AreEqual(16.f, ori.x);
                Assert::AreEqual(16.f, ori.y);
            }

            TEST_METHOD(BoundingCircle_Constructor_WithRadiusAndPos_SetsPosition)
            {
                BoundingCircle<FakeCircle> bc(16.f, Vector2f(16.f, 16.f));

                auto pos = bc.GetPosition();

                Assert::AreEqual(16.f, pos.x);
                Assert::AreEqual(16.f, pos.y);
            }

            TEST_METHOD(BoundingCircle_Constructor_WithRadiusAndPos_SetsCenter)
            {
                BoundingCircle<FakeCircle> bc(16.f, Vector2f(16.f, 16.f));

                auto cen = bc.GetCenter();

                Assert::AreEqual(16.f, cen.x);
                Assert::AreEqual(16.f, cen.y);
            }

            TEST_METHOD(BoundingCircle_GetNativeShape_CanBeCastToRealShape)
            {
                BoundingCircle<FakeCircle> bc(16.f, Vector2f(16.f, 16.f));

                auto* circle = static_cast<FakeCircle*>(bc.GetNativeShape());

                Assert::IsNotNull(circle);
            }

            TEST_METHOD(BoundingCircle_GetCenter_ReturnsDefault)
            {
                BoundingCircle<FakeCircle> bc;

                auto cen = bc.GetCenter();

                Assert::AreEqual(0.f, cen.x);
                Assert::AreEqual(0.f, cen.y);
            }

            TEST_METHOD(BoundingCircle_SetCenter_UpdatesCenter)
            {
                BoundingCircle<FakeCircle> bc(16.f, Vector2f(16.f, 16.f));

                bc.SetCenter(Vector2f(32.f, 32.f));

                auto cen = bc.GetCenter();

                Assert::AreEqual(32.f, cen.x);
                Assert::AreEqual(32.f, cen.y);
            }

            TEST_METHOD(BoundingCircle_GetPosition_ReturnsDefault)
            {
                BoundingCircle<FakeCircle> bc;

                auto pos = bc.GetPosition();

                Assert::AreEqual(0.f, pos.x);
                Assert::AreEqual(0.f, pos.y);
            }

            TEST_METHOD(BoundingCircle_SetPosition_UpdatesPosition)
            {
                BoundingCircle<FakeCircle> bc(16.f, Vector2f(16.f, 16.f));

                bc.SetPosition(Vector2f(32.f, 32.f));

                auto pos = bc.GetPosition();

                Assert::AreEqual(32.f, pos.x);
                Assert::AreEqual(32.f, pos.y);
            }

            TEST_METHOD(BoundingCircle_GetOrigin_ReturnsDefault)
            {
                BoundingCircle<FakeCircle> bc;

                auto ori = bc.GetOrigin();

                Assert::AreEqual(0.f, ori.x);
                Assert::AreEqual(0.f, ori.y);
            }

            TEST_METHOD(BoundingCircle_SetOrigin_UpdatesOrigin)
            {
                BoundingCircle<FakeCircle> bc(16.f, Vector2f(16.f, 16.f));

                bc.SetOrigin(Vector2f(32.f, 32.f));

                auto ori = bc.GetOrigin();

                Assert::AreEqual(32.f, ori.x);
                Assert::AreEqual(32.f, ori.y);
            }

            TEST_METHOD(BoundingCircle_GetScale_ReturnsDefault)
            {
                BoundingCircle<FakeCircle> bc(16.f, Vector2f(16.f, 16.f));

                auto scl = bc.GetScale();

                Assert::AreEqual(1.f, scl.x);
                Assert::AreEqual(1.f, scl.y);
            }

            TEST_METHOD(BoundingCircle_SetScale_UpdatesScale)
            {
                BoundingCircle<FakeCircle> bc(16.f, Vector2f(16.f, 16.f));

                bc.SetScale(Vector2f(2.f, 2.f));

                auto scl = bc.GetScale();

                Assert::AreEqual(2.f, scl.x);
                Assert::AreEqual(2.f, scl.y);
            }

            TEST_METHOD(BoundingCircle_GetPoint_Left_ReturnsCorrectPoint)
            {
                BoundingCircle<FakeCircle> bc(16.f, Vector2f(16.f, 16.f));

                auto pnt = bc.GetPoint(Side::Left);

                Assert::AreEqual(0.f, pnt.x);
                Assert::AreEqual(16.f, pnt.y);
            }

            TEST_METHOD(BoundingCircle_GetPoint_Right_ReturnsCorrectPoint)
            {
                BoundingCircle<FakeCircle> bc(16.f, Vector2f(16.f, 16.f));

                auto pnt = bc.GetPoint(Side::Right);

                Assert::AreEqual(32.f, pnt.x);
                Assert::AreEqual(16.f, pnt.y);
            }

            TEST_METHOD(BoundingCircle_GetPoint_Top_ReturnsCorrectPoint)
            {
                BoundingCircle<FakeCircle> bc(16.f, Vector2f(16.f, 16.f));

                auto pnt = bc.GetPoint(Side::Top);

                Assert::AreEqual(16.f, pnt.x);
                Assert::AreEqual(0.f, pnt.y);
            }

            TEST_METHOD(BoundingCircle_GetPoint_Bottom_ReturnsCorrectPoint)
            {
                BoundingCircle<FakeCircle> bc(16.f, Vector2f(16.f, 16.f));

                auto pnt = bc.GetPoint(Side::Bottom);

                Assert::AreEqual(16.f, pnt.x);
                Assert::AreEqual(32.f, pnt.y);
            }

            TEST_METHOD(BoundingBox_GetPoint_Unknown_ReturnsDefault)
            {
                BoundingCircle<FakeCircle> bc(16.f, Vector2f(16.f, 16.f));

                auto pnt = bc.GetPoint(static_cast<Side>(-1));

                Assert::AreEqual(0.f, pnt.x);
                Assert::AreEqual(0.f, pnt.y);
            }

            TEST_METHOD(BoundingCircle_Intersects_Point_ReturnsTrue)
            {
                BoundingCircle<FakeCircle> bc(16.f, Vector2f(16.0f, 16.0f));

                bool result = bc.Intersects(Vector2f(16.0f, 16.0f));

                Assert::IsTrue(result);
            }

            TEST_METHOD(BoundingCircle_Intersects_Point_ReturnsFalse)
            {
                BoundingCircle<FakeCircle> bc(16.f, Vector2f(16.0f, 16.0f));

                bool result = bc.Intersects(Vector2f(30.0f, 30.0f));

                Assert::IsFalse(result);
            }

            TEST_METHOD(BoundingCircle_Intersects_Box_ReturnsTrue)
            {
                BoundingCircle<FakeCircle> bc(16, Vector2f(16.0f, 16.0f));
                BoundingBox<FakeBox> aabb(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));

                bool result = bc.Intersects(static_cast<IBoundingVolume*>(&aabb));

                Assert::IsTrue(result);
            }

            TEST_METHOD(BoundingCircle_Intersects_Box_ReturnsFalse)
            {
                BoundingCircle<FakeCircle> bc(16, Vector2f(16.f, 16.0f));
                BoundingBox<FakeBox> aabb(Vector2f(16.0f, 16.0f), Vector2f(40.0f, 40.0f));

                bool result = bc.Intersects(static_cast<IBoundingVolume*>(&aabb));

                Assert::IsFalse(result);
            }

            TEST_METHOD(BoundingCircle_Intersects_Circle_ReturnsTrue)
            {
                BoundingCircle<FakeCircle> bc1(16, Vector2f(16.0f, 16.0f));
                BoundingCircle<FakeCircle> bc2(16, Vector2f(16.0f, 16.0f));

                bool result = bc1.Intersects(static_cast<IBoundingVolume*>(&bc2));

                Assert::IsTrue(result);
            }

            TEST_METHOD(BoundingCircle_Intersects_Circle_ReturnsFalse)
            {
                BoundingCircle<FakeCircle> bc1(16, Vector2f(16.0f, 16.0f));
                BoundingCircle<FakeCircle> bc2(16, Vector2f(40.0f, 40.0f));

                bool result = bc1.Intersects(static_cast<IBoundingVolume*>(&bc2));

                Assert::IsFalse(result);
            }

            TEST_METHOD(BoundingCircle_Intersects_Capsule_ReturnsTrue)
            {
                BoundingCircle<FakeCircle> bc(16, Vector2f(16.f, 16.0f));
                BoundingCapsule<FakeCapsule> capsule(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));

                bool result = bc.Intersects(static_cast<IBoundingVolume*>(&capsule));

                Assert::IsTrue(result);
            }

            TEST_METHOD(BoundingCircle_Intersects_Capsule_ReturnsFalse)
            {
                BoundingCircle<FakeCircle> bc(16, Vector2f(16.f, 16.0f));
                BoundingCapsule<FakeCapsule> capsule(16.0f, 16.0f, 0.0f, Vector2f(50.0f, 50.0f));

                bool result = bc.Intersects(static_cast<IBoundingVolume*>(&capsule));

                Assert::IsFalse(result);
            }

            TEST_METHOD(BoundingCircle_Intersects_Unknown_ReturnsFalse)
            {
                BoundingCircle<FakeCircle> bc(16, Vector2f(16.f, 16.0f));

                bool result = bc.Intersects(static_cast<IBoundingVolume*>(nullptr));

                Assert::IsFalse(result);
            }

            TEST_METHOD(BoundingBox_MovingVsUnknown_ReturnsFalse)
            {
                BoundingCircle<FakeCircle> bc(16, Vector2f(16.f, 16.0f));

                float tfirst = 0.0f;
                float tlast = 0.0f;

                bool result = bc.IntersectsMoving(
                    static_cast<IBoundingVolume*>(nullptr),
                    Vector2f(0.0f, 0.0f),
                    Vector2f(0.0f, 0.0f),
                    tfirst,
                    tlast
                );

                Assert::IsFalse(result);
            }

            TEST_METHOD(BoundingCircle_IntersectsMovingVsStatic_Box_ReturnsTrue)
            {
                BoundingCircle<FakeCircle> staticCircle(16.0f, Vector2f(16.0f, 16.0f));
                BoundingBox<FakeBox> movingBox(Vector2f(16.0f, 16.0f), Vector2f(40.0f, 16.0f));

                float tfirst = 0.0f;
                float tlast = 0.0f;

                bool result = staticCircle.IntersectsMoving(
                    static_cast<IBoundingVolume*>(&movingBox),
                    Vector2f(0.0f, 0.0f),
                    Vector2f(-24.0f, 0.0f),
                    tfirst,
                    tlast
                );

                Assert::IsTrue(result);
            }

            TEST_METHOD(BoundingCircle_IntersectsMovingVsStatic_Box_ReturnsFalse)
            {
                BoundingCircle<FakeCircle> staticCircle(16.0f, Vector2f(16.0f, 16.0f));
                BoundingBox<FakeBox> movingBox(Vector2f(16.0f, 16.0f), Vector2f(40.0f, 64.0f));

                float tfirst = 0.0f;
                float tlast = 0.0f;

                bool result = staticCircle.IntersectsMoving(
                    static_cast<IBoundingVolume*>(&movingBox),
                    Vector2f(0.0f, 0.0f),
                    Vector2f(-24.0f, 0.0f),
                    tfirst,
                    tlast
                );

                Assert::IsFalse(result);
            }

            TEST_METHOD(BoundingCircle_IntersectsMovingVsStatic_Circle_ReturnsTrue)
            {
                BoundingCircle<FakeCircle> staticCircle(16.0f, Vector2f(16.0f, 16.0f));
                BoundingCircle<FakeCircle> movingCircle(16.0f, Vector2f(40.0f, 16.0f));

                float tfirst = 0.0f;
                float tlast = 0.0f;

                bool result = staticCircle.IntersectsMoving(
                    static_cast<IBoundingVolume*>(&movingCircle),
                    Vector2f(0.0f, 0.0f),
                    Vector2f(-24.0f, 0.0f),
                    tfirst,
                    tlast
                );

                Assert::IsTrue(result);
            }

            TEST_METHOD(BoundingCircle_IntersectsMovingVsStatic_Circle_ReturnsFalse)
            {
                BoundingCircle<FakeCircle> staticCircle(16.0f, Vector2f(16.0f, 16.0f));
                BoundingCircle<FakeCircle> movingCircle(16.0f, Vector2f(40.0f, 64.0f));

                float tfirst = 0.0f;
                float tlast = 0.0f;

                bool result = staticCircle.IntersectsMoving(
                    static_cast<IBoundingVolume*>(&movingCircle),
                    Vector2f(0.0f, 0.0f),
                    Vector2f(-24.0f, 0.0f),
                    tfirst,
                    tlast
                );

                Assert::IsFalse(result);
            }

            TEST_METHOD(BoundingCircle_IntersectsMovingVsStatic_Capsule_ReturnsTrue)
            {
                BoundingCircle<FakeCircle> staticCircle(16.0f, Vector2f(16.0f, 16.0f));
                BoundingCapsule<FakeCapsule> movingCapsule(16.0f, 16.0f, 0.0f, Vector2f(40.0f, 16.0f));

                float tfirst = 0.0f;
                float tlast = 0.0f;

                bool result = staticCircle.IntersectsMoving(
                    static_cast<IBoundingVolume*>(&movingCapsule),
                    Vector2f(0.0f, 0.0f),
                    Vector2f(-24.0f, 0.0f),
                    tfirst,
                    tlast
                );

                Assert::IsTrue(result);
            }

            TEST_METHOD(BoundingCircle_IntersectsMovingVsStatic_Capsule_ReturnsFalse)
            {
                BoundingCircle<FakeCircle> staticCircle(16.0f, Vector2f(16.0f, 16.0f));
                BoundingCapsule<FakeCapsule> movingCapsule(16.0f, 16.0f, 0.0f, Vector2f(40.0f, 64.0f));

                float tfirst = 0.0f;
                float tlast = 0.0f;

                bool result = staticCircle.IntersectsMoving(
                    static_cast<IBoundingVolume*>(&movingCapsule),
                    Vector2f(0.0f, 0.0f),
                    Vector2f(-24.0f, 0.0f),
                    tfirst,
                    tlast
                );

                Assert::IsFalse(result);
            }

            TEST_METHOD(BoundingCircle_IntersectsMovingVsDynamic_Box_ReturnsTrue)
            {
                BoundingCircle<FakeCircle> movingCircle(16.0f, Vector2f(16.0f, 16.0f));
                BoundingBox<FakeBox> movingBox(Vector2f(16.0f, 16.0f), Vector2f(40.0f, 16.0f));

                float tfirst = 0.0f;
                float tlast = 0.0f;

                bool result = movingCircle.IntersectsMoving(
                    static_cast<IBoundingVolume*>(&movingBox),
                    Vector2f(12.0f, 0.0f),
                    Vector2f(-12.0f, 0.0f),
                    tfirst,
                    tlast
                );

                Assert::IsTrue(result);
            }

            TEST_METHOD(BoundingCircle_IntersectsMovingVsDynamic_Box_ReturnsFalse)
            {
                BoundingCircle<FakeCircle> movingCircle(16.0f, Vector2f(16.0f, 16.0f));
                BoundingBox<FakeBox> movingBox(Vector2f(16.0f, 16.0f), Vector2f(40.0f, 64.0f));

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

            TEST_METHOD(BoundingCircle_IntersectsMovingVsDynamic_Circle_ReturnsTrue)
            {
                BoundingCircle<FakeCircle> movingCircle1(16.0f, Vector2f(16.0f, 16.0f));
                BoundingCircle<FakeCircle> movingCircle2(16.0f, Vector2f(40.0f, 16.0f));

                float tfirst = 0.0f;
                float tlast = 0.0f;

                bool result = movingCircle1.IntersectsMoving(
                    static_cast<IBoundingVolume*>(&movingCircle2),
                    Vector2f(12.0f, 0.0f),
                    Vector2f(-12.0f, 0.0f),
                    tfirst,
                    tlast
                );

                Assert::IsTrue(result);
            }

            TEST_METHOD(BoundingCircle_IntersectsMovingVsDynamic_Circle_ReturnsFalse)
            {
                BoundingCircle<FakeCircle> movingCircle1(16.0f, Vector2f(16.0f, 16.0f));
                BoundingCircle<FakeCircle> movingCircle2(16.0f, Vector2f(40.0f, 64.0f));

                float tfirst = 0.0f;
                float tlast = 0.0f;

                bool result = movingCircle1.IntersectsMoving(
                    static_cast<IBoundingVolume*>(&movingCircle2),
                    Vector2f(12.0f, 0.0f),
                    Vector2f(-12.0f, 0.0f),
                    tfirst,
                    tlast
                );

                Assert::IsFalse(result);
            }

            TEST_METHOD(BoundingCircle_IntersectsMovingVsDynamic_Capsule_ReturnsTrue)
            {
                BoundingCircle<FakeCircle> movingCircle(16.0f, Vector2f(16.0f, 16.0f));
                BoundingCapsule<FakeCapsule> movingCapsule(16.0f, 16.0f, 0.0f, Vector2f(40.0f, 16.0f));

                float tfirst = 0.0f;
                float tlast = 0.0f;

                bool result = movingCircle.IntersectsMoving(
                    static_cast<IBoundingVolume*>(&movingCapsule),
                    Vector2f(12.0f, 0.0f),
                    Vector2f(-12.0f, 0.0f),
                    tfirst,
                    tlast
                );

                Assert::IsTrue(result);
            }

            TEST_METHOD(BoundingCircle_IntersectsMovingVsDynamic_Capsule_ReturnsFalse)
            {
                BoundingCircle<FakeCircle> movingCircle(16.0f, Vector2f(16.0f, 16.0f));
                BoundingCapsule<FakeCapsule> movingCapsule(16.0f, 16.0f, 0.0f, Vector2f(40.0f, 64.0f));

                float tfirst = 0.0f;
                float tlast = 0.0f;

                bool result = movingCircle.IntersectsMoving(
                    static_cast<IBoundingVolume*>(&movingCapsule),
                    Vector2f(12.0f, 0.0f),
                    Vector2f(-12.0f, 0.0f),
                    tfirst,
                    tlast
                );

                Assert::IsFalse(result);
            }

            TEST_METHOD(BoundingCircle_GetSeparationVector_Box_ReturnsSeparationOnCollision)
            {
                BoundingCircle<FakeCircle> bc(16, Vector2f(16.0f, 16.0f));
                BoundingBox<FakeBox> aabb(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));

                bool result = bc.Intersects(static_cast<IBoundingVolume*>(&aabb));

                Assert::IsTrue(result);

                auto sepVec = bc.GetSeparationVector(static_cast<IBoundingVolume*>(&aabb));

                Assert::AreEqual(0.f, sepVec.x);
                Assert::AreEqual(-16.01f, sepVec.y);
            }

            TEST_METHOD(BoundingCircle_GetSeparationVector_Box_ReturnsDefaultOnNoCollision)
            {
                BoundingCircle<FakeCircle> bc(16, Vector2f(16.f, 16.0f));
                BoundingBox<FakeBox> aabb(Vector2f(16.0f, 16.0f), Vector2f(40.0f, 40.0f));

                bool result = bc.Intersects(static_cast<IBoundingVolume*>(&aabb));

                Assert::IsFalse(result);

                auto sepVec = bc.GetSeparationVector(static_cast<IBoundingVolume*>(&aabb));

                Assert::AreEqual(0.f, sepVec.x);
                Assert::AreEqual(0.f, sepVec.y);
            }

            TEST_METHOD(BoundingCircle_GetSeparationVector_Circle_ReturnsSeparationOnCollision)
            {
                BoundingCircle<FakeCircle> bc1(16, Vector2f(16.0f, 16.0f));
                BoundingCircle<FakeCircle> bc2(16, Vector2f(16.0f, 16.0f));

                bool result = bc1.Intersects(static_cast<IBoundingVolume*>(&bc2));

                Assert::IsTrue(result);

                auto sepVec = bc1.GetSeparationVector(static_cast<IBoundingVolume*>(&bc2));

                Assert::AreEqual(0.f, sepVec.x);
                Assert::AreEqual(-32.01f, sepVec.y);
            }

            TEST_METHOD(BoundingCircle_GetSeparationVector_Circle_ReturnsDefaultOnNoCollision)
            {
                BoundingCircle<FakeCircle> bc1(16, Vector2f(16.0f, 16.0f));
                BoundingCircle<FakeCircle> bc2(16, Vector2f(40.0f, 40.0f));

                bool result = bc1.Intersects(static_cast<IBoundingVolume*>(&bc2));

                Assert::IsFalse(result);

                auto sepVec = bc1.GetSeparationVector(static_cast<IBoundingVolume*>(&bc2));

                Assert::AreEqual(0.f, sepVec.x);
                Assert::AreEqual(0.f, sepVec.y);
            }

            TEST_METHOD(BoundingCircle_GetSeparationVector_Capsule_ReturnsSeparationOnCollision)
            {
                BoundingCircle<FakeCircle> bc(16, Vector2f(16.f, 16.0f));
                BoundingCapsule<FakeCapsule> capsule(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));

                bool result = bc.Intersects(static_cast<IBoundingVolume*>(&capsule));

                Assert::IsTrue(result);

                auto sepVec = bc.GetSeparationVector(static_cast<IBoundingVolume*>(&capsule));

                Assert::AreEqual(0.f, sepVec.x);
                Assert::AreEqual(-32.01f, sepVec.y);
            }

            TEST_METHOD(BoundingCircle_GetSeparationVector_Capsule_ReturnsDefaultOnNoCollision)
            {
                BoundingCircle<FakeCircle> bc(16, Vector2f(16.f, 16.0f));
                BoundingCapsule<FakeCapsule> capsule(16.0f, 16.0f, 0.0f, Vector2f(50.0f, 50.0f));

                bool result = bc.Intersects(static_cast<IBoundingVolume*>(&capsule));

                Assert::IsFalse(result);

                auto sepVec = bc.GetSeparationVector(static_cast<IBoundingVolume*>(&capsule));

                Assert::AreEqual(0.f, sepVec.x);
                Assert::AreEqual(0.f, sepVec.y);
            }

            TEST_METHOD(BoundingCircle_GetSeparationVector_Unknown_ReturnsDefault)
            {
                BoundingCircle<FakeCircle> bc(16.f, Vector2f(16.f, 16.f));

                auto sepVec = bc.GetSeparationVector(static_cast<IBoundingVolume*>(nullptr));

                Assert::AreEqual(0.f, sepVec.x);
                Assert::AreEqual(0.f, sepVec.y);
            }
        };
    }
}