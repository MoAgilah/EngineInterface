#include "CppUnitTest.h"


#include <Engine/Collisions/BoundingBox.h>
#include <Engine/Collisions/BoundingCapsule.h>
#include <Engine/Collisions/BoundingCircle.h>
#include <Fakes/Drawables/FakeShape.h>
#include <Fakes/Renderer/TestableCamera.h>
#include <algorithm>
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Engine
{
    namespace Renderer
    {
        TEST_CLASS(CameraTests)
        {
        public:

            // ======================================================
            // Constructor
            // ======================================================

            TEST_METHOD(ICamera_Constructor_ThrowsIfBoundingBoxIsNull)
            {

                Assert::ExpectException<std::invalid_argument>([]
                    {
                        TestableCamera cam(nullptr);
                    });
            }

            TEST_METHOD(ICamera_Constructor_AcceptsValidBoundingBox)
            {
                auto viewBox = std::make_unique<BoundingBox<FakeBox>>();
                auto* originalPtr = viewBox.get();

                TestableCamera camera(std::move(viewBox));

                Assert::IsTrue(originalPtr == camera.GetViewBoxForTesting());
            }

            // ======================================================
            // IsInView
            // ======================================================

            TEST_METHOD(ICamera_IsInView_ReturnsFalseIfVolumeIsNull)
            {
                TestableCamera camera(
                    std::make_unique<BoundingBox<FakeBox>>(Vector2f(16, 16), Vector2f(16, 16))
                );

                Assert::IsFalse(camera.IsInView(nullptr));
            }

            TEST_METHOD(ICamera_IsInView_ReturnsFalseIfNotIntersecting)
            {
                TestableCamera camera(
                    std::make_unique<BoundingBox<FakeBox>>(Vector2f(16, 16), Vector2f(16, 16))
                );

                BoundingBox<FakeBox> aabb(Vector2f(16.0f, 16.0f), Vector2f(40.0f, 40.0f));

                Assert::IsFalse(camera.IsInView(&aabb));
            }

            TEST_METHOD(ICamera_IsInView_ReturnsTrueIfIntersecting)
            {
                TestableCamera camera(
                    std::make_unique<BoundingBox<FakeBox>>(Vector2f(16, 16), Vector2f(16, 16))
                );

                BoundingBox<FakeBox> aabb(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));

                Assert::IsTrue(camera.IsInView(&aabb));
            }

            // ======================================================
            // CheckVerticalBounds
            // ======================================================

            TEST_METHOD(ICamera_CheckVerticalBounds_ReturnsFalseIfVolumeIsNull)
            {
                TestableCamera camera(
                    std::make_unique<BoundingBox<FakeBox>>(Vector2f(16, 16), Vector2f(16, 16))
                );

                Assert::IsFalse(camera.CheckVerticalBounds(nullptr));
            }

            TEST_METHOD(ICamera_CheckVerticalBounds_ReturnsTrueIfExceedsVerticalBounds)
            {
                TestableCamera camera(
                    std::make_unique<BoundingBox<FakeBox>>(Vector2f(16, 16), Vector2f(16, 16))
                );

                BoundingBox<FakeBox> aabb(Vector2f(16.0f, 16.0f), Vector2f(40.0f, 40.0f));

                Assert::IsTrue(camera.CheckVerticalBounds(&aabb));
            }

            TEST_METHOD(ICamera_CheckVerticalBounds_ReturnsFalseIfWithinVerticalBounds)
            {
                TestableCamera camera(
                    std::make_unique<BoundingBox<FakeBox>>(Vector2f(16, 16), Vector2f(16, 16))
                );

                BoundingBox<FakeBox> aabb(Vector2f(16.0f, 16.0f), Vector2f(16.0f, 16.0f));

                Assert::IsFalse(camera.CheckVerticalBounds(&aabb));
            }

            // ======================================================
            // RenderDebug
            // ======================================================

            TEST_METHOD(ICamera_RenderDebug_DoesNothingIfRendererIsNull)
            {
                TestableCamera camera(std::make_unique<BoundingBox<FakeBox>>());

                camera.RenderDebug(nullptr);
            }
        };
    }
}