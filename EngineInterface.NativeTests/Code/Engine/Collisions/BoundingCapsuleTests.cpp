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
        TEST_CLASS(BoundingCapsuleTests)
        {
        public:
            TEST_METHOD(BoundingCapsule_DefaultConstructor_DoesNotThrow)
            {
                BoundingCapsule<FakeCapsule> bc;
            }

            TEST_METHOD(BoundingCapsule_WithRadiusAndLengthAndAngle_SetsAngle)
            {
               BoundingCapsule<FakeCapsule> bc(16.0f, 16.0f, 0.0f);

               Assert::AreEqual(0.f, bc.GetAngle());
            }

            TEST_METHOD(BoundingCapsule_WithRadiusAndLengthAndAngle_SetsRadius)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f, 16.0f, 0.0f);

                Assert::AreEqual(16.f, bc.GetRadius());
            }

            TEST_METHOD(BoundingCapsule_WithRadiusAndLengthAndAngle_SetsLength)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f, 16.0f, 0.0f);

                Assert::AreEqual(16.f, bc.GetLength());
            }

            TEST_METHOD(BoundingCapsule_WithRadiusAndLengthAndAngle_SetsOrigin)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f, 16.0f, 0.0f);

                auto ori = bc.GetOrigin();

                Assert::AreEqual(8.f, ori.x);
                Assert::AreEqual(16.f, ori.y);
            }

            TEST_METHOD(BoundingCapsule_WithRadiusAndLengthAndAngleAndPos_SetsAngle)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));

                Assert::AreEqual(0.f, bc.GetAngle());
            }

            TEST_METHOD(BoundingCapsule_WithRadiusAndLengthAndAngleAndPos_SetsRadius)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));

                Assert::AreEqual(16.f, bc.GetRadius());
            }

            TEST_METHOD(BoundingCapsule_WithRadiusAndLengthAndAngleAndPos_SetsLength)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));

                Assert::AreEqual(16.f, bc.GetLength());
            }

            TEST_METHOD(BoundingCapsule_WithRadiusAndLengthAndAngleAndPos_SetsOrigin)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));

                auto ori = bc.GetOrigin();

                Assert::AreEqual(8.f, ori.x);
                Assert::AreEqual(16.f, ori.y);
            }

            TEST_METHOD(BoundingCapsule_WithRadiusAndLengthAndAngleAndPos_SetsPosition)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));

                auto pos = bc.GetPosition();

                Assert::AreEqual(16.f, pos.x);
                Assert::AreEqual(16.f, pos.y);
            }

            TEST_METHOD(BoundingCapsule_WithRadiusAndLengthAndAngleAndPos_SetsCenter)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));

                auto cen = bc.GetCenter();

                Assert::AreEqual(16.f, cen.x);
                Assert::AreEqual(16.f, cen.y);
            }

            TEST_METHOD(BoundingCapsule_WithRadiusAndLengthAndAngleAndPos_SetsSegment)
            {
                BoundingCapsule<FakeCapsule> bc(
                    16.0f,
                    16.0f,
                    0.0f,
                    Vector2f(16.0f, 16.0f)
                );

                auto seg = bc.GetSegment();

                Assert::AreEqual(8.f, seg.start.x);
                Assert::AreEqual(16.f, seg.start.y);
                Assert::AreEqual(24.f, seg.end.x);
                Assert::AreEqual(16.f, seg.end.y);
            }

            TEST_METHOD(BoundingCapsule_WithRadiusAndSegment_SetsAngle)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f,
                    Line2f(
                        Vector2f(8.f, 16.f),
                        Vector2f(24.f, 16.0f)
                    )
                );

                Assert::AreEqual(0.f, bc.GetAngle());
            }

            TEST_METHOD(BoundingCapsule_WithRadiusAndSegment_SetsRadius)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f,
                    Line2f(
                        Vector2f(8.f, 16.f),
                        Vector2f(24.f, 16.0f)
                    )
                );

                Assert::AreEqual(16.f, bc.GetRadius());
            }

            TEST_METHOD(BoundingCapsule_WithRadiusAndSegment_SetsLength)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f,
                    Line2f(
                        Vector2f(8.f, 16.f),
                        Vector2f(24.f, 16.0f)
                    )
                );

                Assert::AreEqual(16.f, bc.GetLength());
            }

            TEST_METHOD(BoundingCapsule_WithRadiusAndSegment_SetsOrigin)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f,
                    Line2f(
                        Vector2f(8.f, 16.f),
                        Vector2f(24.f, 16.0f)
                    )
                );

                auto ori = bc.GetOrigin();

                Assert::AreEqual(8.f, ori.x);
                Assert::AreEqual(16.f, ori.y);
            }

            TEST_METHOD(BoundingCapsule_WithRadiusAndSegment_SetsPosition)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f,
                    Line2f(
                        Vector2f(8.f, 16.f),
                        Vector2f(24.f, 16.0f)
                    )
                );

                auto pos = bc.GetPosition();

                Assert::AreEqual(16.f, pos.x);
                Assert::AreEqual(16.f, pos.y);
            }

            TEST_METHOD(BoundingCapsule_WithRadiusAndSegment_SetsCenter)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f,
                    Line2f(
                        Vector2f(8.f, 16.f),
                        Vector2f(24.f, 16.0f)
                    )
                );

                auto cen = bc.GetCenter();

                Assert::AreEqual(16.f, cen.x);
                Assert::AreEqual(16.f, cen.y);
            }

            TEST_METHOD(BoundingCapsule_WithRadiusAndSegment_SetsSegment)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f,
                    Line2f(
                        Vector2f(8.f, 16.f),
                        Vector2f(24.f, 16.0f)
                    )
                );

                auto seg = bc.GetSegment();

                Assert::AreEqual(8.f, seg.start.x);
                Assert::AreEqual(16.f, seg.start.y);
                Assert::AreEqual(24.f, seg.end.x);
                Assert::AreEqual(16.f, seg.end.y);
            }

            TEST_METHOD(BoundingCapsule_ToBoundingBox_ProducesBoundingBox)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));

                auto bb = bc.ToBoundingBox();

                Assert::AreEqual(16.0f, bb.GetPosition().x);
                Assert::AreEqual(16.0f, bb.GetPosition().y);

                auto* box = static_cast<FakeBox*>(bb.GetNativeShape());

                Assert::AreEqual(48.f, box->GetSize().x);
                Assert::AreEqual(32.0f, box->GetSize().y);
            }

            TEST_METHOD(BoundingCapsule_GetNativeShape_CanBeCastToFakeCapsule)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));

                auto* cap = static_cast<FakeBox*>(bc.GetNativeShape());

                Assert::IsNotNull(cap);
            }

            TEST_METHOD(BoundingCapsule_GetRadius_ReturnsDefault)
            {
                BoundingCapsule<FakeCapsule> bc;

                Assert::AreEqual(0.f, bc.GetRadius());
            }

            TEST_METHOD(BoundingCapsule_GetLength_ReturnsDefault)
            {
                BoundingCapsule<FakeCapsule> bc;

                Assert::AreEqual(0.f, bc.GetLength());
            }

            TEST_METHOD(BoundingCapsule_GetAngle_ReturnsDefault)
            {
                BoundingCapsule<FakeCapsule> bc;

                Assert::AreEqual(0.f, bc.GetAngle());
            }

            TEST_METHOD(BoundingCapsule_GetSegment_ReturnsDefault)
            {
                BoundingCapsule<FakeCapsule> bc;

                auto seg = bc.GetSegment();

                Assert::AreEqual(0.f, seg.start.x);
                Assert::AreEqual(0.f, seg.start.y);
                Assert::AreEqual(0.f, seg.end.x);
                Assert::AreEqual(0.f, seg.end.x);
            }

            TEST_METHOD(BoundingCapsule_GetCenter_ReturnsDefault)
            {
                BoundingCapsule<FakeCapsule> bc;

                auto cen = bc.GetCenter();

                Assert::AreEqual(0.f, cen.x);
                Assert::AreEqual(0.f, cen.y);
            }

            TEST_METHOD(BoundingCapsule_SetCenter_UpdatesCenter)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));

                bc.SetCenter(Vector2f(32.f, 32.f));

                auto cen = bc.GetCenter();

                Assert::AreEqual(32.f, cen.x);
                Assert::AreEqual(32.f, cen.y);
            }

            TEST_METHOD(BoundingCapsule_GetPosition_ReturnsDefault)
            {
                BoundingCapsule<FakeCapsule> bc;
            }

            TEST_METHOD(BoundingCapsule_SetPosition_UpdatesPosition)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));

                bc.SetPosition(Vector2f(32.f, 32.f));

                auto pos = bc.GetPosition();

                Assert::AreEqual(32.f, pos.x);
                Assert::AreEqual(32.f, pos.y);
            }

            TEST_METHOD(BoundingCapsule_GetOrigin_ReturnsDefault)
            {
                BoundingCapsule<FakeCapsule> bc;

                auto ori = bc.GetCenter();

                Assert::AreEqual(0.f, ori.x);
                Assert::AreEqual(0.f, ori.y);
            }

            TEST_METHOD(BoundingCapsule_SetOrigin_UpdatesOrigin)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));

                bc.SetOrigin(Vector2f(32.f, 32.f));

                auto ori = bc.GetOrigin();

                Assert::AreEqual(32.f, ori.x);
                Assert::AreEqual(32.f, ori.y);
            }

            TEST_METHOD(BoundingCapsule_GetScale_ReturnsDefault)
            {
                BoundingCapsule<FakeCapsule> bc;

                auto scl = bc.GetScale();

                Assert::AreEqual(1.f, scl.x);
                Assert::AreEqual(1.f, scl.y);
            }

            TEST_METHOD(BoundingCapsule_SetScale_UpdatesScale)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));

                bc.SetScale(Vector2f(2.f, 2.f));

                auto scl = bc.GetScale();

                Assert::AreEqual(2.f, scl.x);
                Assert::AreEqual(2.f, scl.y);
            }

            TEST_METHOD(BoundingCapsule_GetPoint_Top_ReturnsTopSide)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));

                auto pnt = bc.GetPoint(Side::Top);

                Assert::AreEqual(8.f, pnt.x);
                Assert::AreEqual(16.f, pnt.y);
            }

            TEST_METHOD(BoundingCapsule_GetPoint_Bottom_ReturnsBottomSide)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));

                auto pnt = bc.GetPoint(Side::Bottom);

                Assert::AreEqual(24.f, pnt.x);
                Assert::AreEqual(16.f, pnt.y);
            }

            TEST_METHOD(BoundingCapsule_GetPoint_Left_ReturnsLeftSide)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));

                auto pnt = bc.GetPoint(Side::Left);

                Assert::AreEqual(8.f, pnt.x);
                Assert::AreEqual(16.f, pnt.y);
            }

            TEST_METHOD(BoundingCapsule_GetPoint_Right_ReturnsRightSide)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));

                auto pnt = bc.GetPoint(Side::Right);

                Assert::AreEqual(24.f, pnt.x);
                Assert::AreEqual(16.f, pnt.y);
            }

            TEST_METHOD(BoundingCapsule_GetPoint_Unknown_ReturnsDefault)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));

                auto pnt = bc.GetPoint(static_cast<Side>(-1));

                Assert::AreEqual(0.f, pnt.x);
                Assert::AreEqual(0.f, pnt.y);
            }

            TEST_METHOD(BoundingCapsule_Intersects_Point_AtCentre_ReturnsTrue)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));

                bool result = bc.Intersects(Vector2f(16.0f, 16.0f));

                Assert::IsTrue(result);
            }

            TEST_METHOD(BoundingCapsule_Intersects_Point_OnRadiusEdge_ReturnsTrue)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));

                bool result = bc.Intersects(Vector2f(16.0f, 32.0f));

                Assert::IsTrue(result);
            }

            TEST_METHOD(BoundingCapsule_Intersects_Point_ReturnsTrue)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));

                bool result = bc.Intersects(Vector2f(16.0f, 30.0f));

                Assert::IsTrue(result);
            }

            TEST_METHOD(BoundingCapsule_Intersects_Point_ReturnsFalse)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));

                bool result = bc.Intersects(Vector2f(16.0f, 33.0f));

                Assert::IsFalse(result);
            }

            TEST_METHOD(BoundingCapsule_Intersects_Box_ReturnsTrue)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));
                BoundingBox<FakeBox> aabb(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));

                bool result = bc.Intersects(static_cast<IBoundingVolume*>(&aabb));

                Assert::IsTrue(result);
            }

            TEST_METHOD(BoundingCapsule_Intersects_Box_ReturnsFalse)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f, 16.0f, 0.0f, Vector2f(50.0f, 50.0f));
                BoundingBox<FakeBox> aabb(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));

                bool result = bc.Intersects(static_cast<IBoundingVolume*>(&aabb));

                Assert::IsFalse(result);
            }

            TEST_METHOD(BoundingCapsule_Intersects_Circle_ReturnsTrue)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));
                BoundingCircle<FakeCircle> circle(16, Vector2f(16.f, 16.0f));

                bool result = bc.Intersects(static_cast<IBoundingVolume*>(&circle));

                Assert::IsTrue(result);
            }

            TEST_METHOD(BoundingCapsule_Intersects_Circle_ReturnsFalse)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f, 16.0f, 0.0f, Vector2f(50.0f, 50.0f));
                BoundingCircle<FakeCircle> circle(16, Vector2f(16.f, 16.0f));

                bool result = bc.Intersects(static_cast<IBoundingVolume*>(&circle));

                Assert::IsFalse(result);
            }

            TEST_METHOD(BoundingCapsule_Intersects_Capsule_ReturnsTrue)
            {
                BoundingCapsule<FakeCapsule> bc1(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));
                BoundingCapsule<FakeCapsule> bc2(16.0f, 16.0f, 0.0f, Vector2f(30.0f, 16.0f));

                bool result = bc1.Intersects(static_cast<IBoundingVolume*>(&bc2));

                Assert::IsTrue(result);
            }

            TEST_METHOD(BoundingCapsule_Intersects_Capsule_ReturnsFalse)
            {
                BoundingCapsule<FakeCapsule> bc1(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));
                BoundingCapsule<FakeCapsule> bc2(16.0f, 16.0f, 0.0f, Vector2f(66.0f, 16.0f));

                bool result = bc1.Intersects(static_cast<IBoundingVolume*>(&bc2));

                Assert::IsFalse(result);
            }

            TEST_METHOD(BoundingCapsule_Intersects_Unknown_ReturnsFalse)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));

                bool result = bc.Intersects(static_cast<IBoundingVolume*>(nullptr));

                Assert::IsFalse(result);
            }

            TEST_METHOD(BoundingCapsule_IntersectsMovingVsUnknown_ReturnsFalse)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));

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

            TEST_METHOD(BoundingCapsule_IntersectsMovingVsStatic_Box_ReturnsTrue)
            {
                BoundingCapsule<FakeCapsule> staticCapsule(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));
                BoundingBox<FakeBox> movingBox(Vector2f(16.0f, 16.0f), Vector2f(40.0f, 16.0f));

                float tfirst = 0.0f;
                float tlast = 0.0f;

                bool result = staticCapsule.IntersectsMoving(
                    static_cast<IBoundingVolume*>(&movingBox),
                    Vector2f(0.0f, 0.0f),
                    Vector2f(-24.0f, 0.0f),
                    tfirst,
                    tlast
                );

                Assert::IsTrue(result);
            }

            TEST_METHOD(BoundingCapsule_IntersectsMovingVsStatic_Box_ReturnsFalse)
            {
                BoundingCapsule<FakeCapsule> staticCapsule(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));
                BoundingBox<FakeBox> movingBox(Vector2f(16.0f, 16.0f), Vector2f(40.0f, 64.0f));

                float tfirst = 0.0f;
                float tlast = 0.0f;

                bool result = staticCapsule.IntersectsMoving(
                    static_cast<IBoundingVolume*>(&movingBox),
                    Vector2f(0.0f, 0.0f),
                    Vector2f(-24.0f, 0.0f),
                    tfirst,
                    tlast
                );

                Assert::IsFalse(result);
            }

            TEST_METHOD(BoundingCapsule_IntersectsMovingVsStatic_Circle_ReturnsTrue)
            {
                BoundingCapsule<FakeCapsule> staticCapsule(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));
                BoundingCircle<FakeCircle> movingCircle(16.0f, Vector2f(40.0f, 16.0f));

                float tfirst = 0.0f;
                float tlast = 0.0f;

                bool result = staticCapsule.IntersectsMoving(
                    static_cast<IBoundingVolume*>(&movingCircle),
                    Vector2f(0.0f, 0.0f),
                    Vector2f(-24.0f, 0.0f),
                    tfirst,
                    tlast
                );

                Assert::IsTrue(result);
            }

            TEST_METHOD(BoundingCapsule_IntersectsMovingVsStatic_Circle_ReturnsFalse)
            {
                BoundingCapsule<FakeCapsule> staticCapsule(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));
                BoundingCircle<FakeCircle> movingCircle(16.0f, Vector2f(40.0f, 64.0f));

                float tfirst = 0.0f;
                float tlast = 0.0f;

                bool result = staticCapsule.IntersectsMoving(
                    static_cast<IBoundingVolume*>(&movingCircle),
                    Vector2f(0.0f, 0.0f),
                    Vector2f(-24.0f, 0.0f),
                    tfirst,
                    tlast
                );

                Assert::IsFalse(result);
            }

            TEST_METHOD(BoundingCapsule_IntersectsMovingVsStatic_Capsule_ReturnsTrue)
            {
                BoundingCapsule<FakeCapsule> staticCapsule(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));
                BoundingCapsule<FakeCapsule> movingCapsule(16.0f, 16.0f, 0.0f, Vector2f(80.0f, 16.0f));

                float tfirst = 0.0f;
                float tlast = 1.0f;

                bool result = staticCapsule.IntersectsMoving(
                    static_cast<IBoundingVolume*>(&movingCapsule),
                    Vector2f(0.0f, 0.0f),
                    Vector2f(-40.0f, 0.0f),
                    tfirst,
                    tlast
                );

                Assert::IsTrue(result);
            }

            TEST_METHOD(BoundingCapsule_IntersectsMovingVsStatic_Capsule_ReturnsFalse)
            {
                BoundingCapsule<FakeCapsule> staticCapsule(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));
                BoundingCapsule<FakeCapsule> movingCapsule(16.0f, 16.0f, 0.0f, Vector2f(100.0f, 16.0f));

                float tfirst = 0.0f;
                float tlast = 1.0f;

                bool result = staticCapsule.IntersectsMoving(
                    static_cast<IBoundingVolume*>(&movingCapsule),
                    Vector2f(0.0f, 0.0f),
                    Vector2f(-20.0f, 0.0f),
                    tfirst,
                    tlast
                );

                Assert::IsFalse(result);
            }

            TEST_METHOD(BoundingCapsule_IntersectsIntersectsMovingVsDynamic_Box_ReturnsTrue)
            {
                BoundingCapsule<FakeCapsule> movingCapsule(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));
                BoundingBox<FakeBox> movingBox(Vector2f(16.0f, 16.0f), Vector2f(40.0f, 16.0f));

                float tfirst = 0.0f;
                float tlast = 0.0f;

                bool result = movingCapsule.IntersectsMoving(
                    static_cast<IBoundingVolume*>(&movingBox),
                    Vector2f(12.0f, 0.0f),
                    Vector2f(-12.0f, 0.0f),
                    tfirst,
                    tlast
                );

                Assert::IsTrue(result);
            }

            TEST_METHOD(BoundingCapsule_IntersectsMovingVsDynamic_Box_ReturnsFalse)
            {
                BoundingCapsule<FakeCapsule> movingCapsule(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));
                BoundingBox<FakeBox> movingBox(Vector2f(16.0f, 16.0f), Vector2f(40.0f, 64.0f));

                float tfirst = 0.0f;
                float tlast = 0.0f;

                bool result = movingCapsule.IntersectsMoving(
                    static_cast<IBoundingVolume*>(&movingBox),
                    Vector2f(12.0f, 0.0f),
                    Vector2f(-12.0f, 0.0f),
                    tfirst,
                    tlast
                );

                Assert::IsFalse(result);
            }

            TEST_METHOD(BoundingCapsule_IntersectsMovingVsDynamic_Circle_ReturnsTrue)
            {
                BoundingCapsule<FakeCapsule> movingCapsule(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));
                BoundingCircle<FakeCircle> movingCircle(16.0f, Vector2f(40.0f, 16.0f));

                float tfirst = 0.0f;
                float tlast = 0.0f;

                bool result = movingCapsule.IntersectsMoving(
                    static_cast<IBoundingVolume*>(&movingCircle),
                    Vector2f(12.0f, 0.0f),
                    Vector2f(-12.0f, 0.0f),
                    tfirst,
                    tlast
                );

                Assert::IsTrue(result);
            }

            TEST_METHOD(BoundingCapsule_IntersectsMovingVsDynamic_Circle_ReturnsFalse)
            {
                BoundingCapsule<FakeCapsule> movingCapsule(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));
                BoundingCircle<FakeCircle> movingCircle(16.0f, Vector2f(40.0f, 64.0f));

                float tfirst = 0.0f;
                float tlast = 0.0f;

                bool result = movingCapsule.IntersectsMoving(
                    static_cast<IBoundingVolume*>(&movingCircle),
                    Vector2f(12.0f, 0.0f),
                    Vector2f(-12.0f, 0.0f),
                    tfirst,
                    tlast
                );

                Assert::IsFalse(result);
            }

            TEST_METHOD(BoundingCapsule_IntersectsMovingVsDynamic_Capsule_ReturnsTrue)
            {
                BoundingCapsule<FakeCapsule> movingCapsule1(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));
                BoundingCapsule<FakeCapsule> movingCapsule2(16.0f, 16.0f, 0.0f, Vector2f(80.0f, 16.0f));

                float tfirst = 0.0f;
                float tlast = 1.0f;

                bool result = movingCapsule1.IntersectsMoving(
                    static_cast<IBoundingVolume*>(&movingCapsule2),
                    Vector2f(20.0f, 0.0f),
                    Vector2f(-20.0f, 0.0f),
                    tfirst,
                    tlast
                );

                Assert::IsTrue(result);
            }

            TEST_METHOD(BoundingCapsule_IntersectsMovingVsDynamic_Capsule_ReturnsFalse)
            {
                BoundingCapsule<FakeCapsule> movingCapsule1(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));
                BoundingCapsule<FakeCapsule> movingCapsule2(16.0f, 16.0f, 0.0f, Vector2f(100.0f, 16.0f));

                float tfirst = 0.0f;
                float tlast = 1.0f;

                bool result = movingCapsule1.IntersectsMoving(
                    static_cast<IBoundingVolume*>(&movingCapsule2),
                    Vector2f(10.0f, 0.0f),
                    Vector2f(-10.0f, 0.0f),
                    tfirst,
                    tlast
                );

                Assert::IsFalse(result);
            }

            TEST_METHOD(BoundingCapsule_GetSeparationVector_Box_ReturnsSeparationOnCollision)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));
                BoundingBox<FakeBox> aabb(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));

                bool result = bc.Intersects(static_cast<IBoundingVolume*>(&aabb));

                Assert::IsTrue(result);

                auto sepVec = bc.GetSeparationVector(static_cast<IBoundingVolume*>(&aabb));

                Assert::AreEqual(16.01f, sepVec.x);
                Assert::AreEqual(0.f, sepVec.y);
            }

            TEST_METHOD(BoundingCapsule_GetSeparationVector_Box_ReturnsDefaultOnNoCollision)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f, 16.0f, 0.0f, Vector2f(50.0f, 50.0f));
                BoundingBox<FakeBox> aabb(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));

                bool result = bc.Intersects(static_cast<IBoundingVolume*>(&aabb));

                Assert::IsFalse(result);

                auto sepVec = bc.GetSeparationVector(static_cast<IBoundingVolume*>(&aabb));

                Assert::AreEqual(0.f, sepVec.x);
                Assert::AreEqual(0.f, sepVec.y);
            }

            TEST_METHOD(BoundingCapsule_GetSeparationVector_Circle_ReturnsSeparationOnCollision)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));
                BoundingCircle<FakeCircle> circle(16, Vector2f(16.f, 16.0f));

                bool result = bc.Intersects(static_cast<IBoundingVolume*>(&circle));

                Assert::IsTrue(result);

                auto sepVec = bc.GetSeparationVector(static_cast<IBoundingVolume*>(&circle));

                Assert::AreEqual(0.0f, sepVec.x);
                Assert::AreEqual(32.01f, sepVec.y);
            }

            TEST_METHOD(BoundingCapsule_GetSeparationVector_Circle_ReturnsDefaultOnNoCollision)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f, 16.0f, 0.0f, Vector2f(50.0f, 50.0f));
                BoundingCircle<FakeCircle> circle(16, Vector2f(16.f, 16.0f));

                bool result = bc.Intersects(static_cast<IBoundingVolume*>(&circle));

                Assert::IsFalse(result);

                auto sepVec = bc.GetSeparationVector(static_cast<IBoundingVolume*>(&circle));

                Assert::AreEqual(0.f, sepVec.x);
                Assert::AreEqual(0.f, sepVec.y);
            }

            TEST_METHOD(BoundingCapsule_GetSeparationVector_Capsule_ReturnsSeparationOnCollision)
            {
                BoundingCapsule<FakeCapsule> bc1(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));
                BoundingCapsule<FakeCapsule> bc2(16.0f, 16.0f, 0.0f, Vector2f(30.0f, 16.0f));

                bool result = bc1.Intersects(static_cast<IBoundingVolume*>(&bc2));

                Assert::IsTrue(result);

                auto sepVec = bc1.GetSeparationVector(static_cast<IBoundingVolume*>(&bc2));

                Assert::AreEqual(0.f, sepVec.x);
                Assert::AreEqual(-32.01f, sepVec.y);
            }

            TEST_METHOD(BoundingCapsule_GetSeparationVector_Capsule_ReturnsDefaultOnNoCollision)
            {
                BoundingCapsule<FakeCapsule> bc1(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));
                BoundingCapsule<FakeCapsule> bc2(16.0f, 16.0f, 0.0f, Vector2f(66.0f, 16.0f));

                bool result = bc1.Intersects(static_cast<IBoundingVolume*>(&bc2));

                Assert::IsFalse(result);

                auto sepVec = bc1.GetSeparationVector(static_cast<IBoundingVolume*>(&bc2));

                Assert::AreEqual(0.f, sepVec.x);
                Assert::AreEqual(0.f, sepVec.y);
            }

            TEST_METHOD(BoundingCapsule_GetSeparationVector_Unknown_ReturnsDefault)
            {
                BoundingCapsule<FakeCapsule> bc(16.0f, 16.0f, 0.0f, Vector2f(16.0f, 16.0f));

                auto sepVec = bc.GetSeparationVector(static_cast<IBoundingVolume*>(nullptr));

                Assert::AreEqual(0.f, sepVec.x);
                Assert::AreEqual(0.f, sepVec.y);
            }
        };
    }
}