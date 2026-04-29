#include "CppUnitTest.h"

#include <Engine/Input/InputManager.h>
#include <Fakes/FakeKeyConverter.h>
#include <memory>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Engine
{
	namespace Input
	{
		TEST_CLASS(InputManagerTests)
		{
		public:
			TEST_METHOD(InputManager_Constructor_AssignsKeyStatesFalse)
			{
				std::shared_ptr<IKeyConverter> converter = std::make_shared<FakeKeyConverter>();
				InputManager im(std::move(converter));

				for (int i = 0; i < KeyCount; i++)
				{
					Assert::IsFalse(im.GetKeyState(i));
				}
			}

			TEST_METHOD(InputManager_Constructor_AssignsInitialTimeStamp)
			{
				std::shared_ptr<IKeyConverter> converter = std::make_shared<FakeKeyConverter>();
				InputManager im(std::move(converter));

				auto min = std::chrono::steady_clock::time_point::min();

				for (int i = 0; i < KeyCount; i++)
				{
					Assert::IsTrue(im.GetKeyPressTimestamp(static_cast<KeyCode>(i)) == min);
				}
			}

			TEST_METHOD(InputManager_ProcessPlatformKeyPress_AssignsTrue)
			{
				std::shared_ptr<IKeyConverter> converter = std::make_shared<FakeKeyConverter>();
				InputManager im(std::move(converter));

				im.ProcessPlatformKeyPress(static_cast<int>(KeyCode::A));

				Assert::IsTrue(im.GetKeyState(static_cast<int>(KeyCode::A)));
			}

			TEST_METHOD(InputManager_ProcessPlatformKeyPress_WithUnknownKey_DoesNothing)
			{
				std::shared_ptr<IKeyConverter> converter = std::make_shared<FakeKeyConverter>();
				InputManager im(std::move(converter));

				im.ProcessPlatformKeyPress(static_cast<int>(KeyCount));
			}

			TEST_METHOD(InputManager_ProcessPlatformKeyPress_WhenKeyAlreadyPressed_DoesNotResetTimestamp)
			{
				std::shared_ptr<IKeyConverter> converter = std::make_shared<FakeKeyConverter>();
				InputManager im(std::move(converter));

				im.ProcessPlatformKeyPress(static_cast<int>(KeyCode::A));

				auto time = im.GetKeyPressTimestamp(KeyCode::A);

				im.ProcessPlatformKeyPress(static_cast<int>(KeyCode::A));

				Assert::IsTrue(im.GetKeyPressTimestamp(KeyCode::A) == time);
			}

			TEST_METHOD(InputManager_ProcessPlatformKeyRelease_AssignsFalse)
			{
				std::shared_ptr<IKeyConverter> converter = std::make_shared<FakeKeyConverter>();
				InputManager im(std::move(converter));

				im.ProcessPlatformKeyPress(static_cast<int>(KeyCode::A));

				Assert::IsTrue(im.GetKeyState(static_cast<int>(KeyCode::A)));

				im.ProcessPlatformKeyRelease(static_cast<int>(KeyCode::A));

				Assert::IsFalse(im.GetKeyState(static_cast<int>(KeyCode::A)));
			}

			TEST_METHOD(InputManager_ProcessPlatformKeyRelease_WithUnknownKey_DoesNothing)
			{
				std::shared_ptr<IKeyConverter> converter = std::make_shared<FakeKeyConverter>();
				InputManager im(std::move(converter));

				im.ProcessPlatformKeyRelease(static_cast<int>(KeyCount));
			}

			TEST_METHOD(InputManager_ProcessPlatformKeyRelease_ClearsTimestamp)
			{
				std::shared_ptr<IKeyConverter> converter = std::make_shared<FakeKeyConverter>();
				InputManager im(std::move(converter));

				im.ProcessPlatformKeyPress(static_cast<int>(KeyCode::A));

				auto min = std::chrono::steady_clock::time_point::min();

				Assert::IsTrue(im.GetKeyPressTimestamp(KeyCode::A) != min);

				im.ProcessPlatformKeyRelease(static_cast<int>(KeyCode::A));

				Assert::IsTrue(im.GetKeyPressTimestamp(KeyCode::A) == min);
			}

			TEST_METHOD(InputManager_IsAnyKeyPressed_ReturnsFalse)
			{
				std::shared_ptr<IKeyConverter> converter = std::make_shared<FakeKeyConverter>();
				InputManager im(std::move(converter));

				Assert::IsFalse(im.IsAnyKeyPressed());
			}

			TEST_METHOD(InputManager_IsAnyKeyPressed_ReturnsTrue)
			{
				std::shared_ptr<IKeyConverter> converter = std::make_shared<FakeKeyConverter>();
				InputManager im(std::move(converter));

				im.ProcessPlatformKeyPress(static_cast<int>(KeyCode::A));

				Assert::IsTrue(im.IsAnyKeyPressed());
			}

			TEST_METHOD(InputManager_GetFirstPressedKey_ReturnsKeyCodeUnknown)
			{
				std::shared_ptr<IKeyConverter> converter = std::make_shared<FakeKeyConverter>();
				InputManager im(std::move(converter));

				auto key = im.GetFirstPressedKey(
					{
						KeyCode::Left,
						KeyCode::Right,
					}
				);

				Assert::AreEqual(
					static_cast<int>(KeyCode::Unknown),
					static_cast<int>(key)
				);
			}

			TEST_METHOD(InputManager_GetFirstPressedKey_ReturnsKeyCode)
			{
				std::shared_ptr<IKeyConverter> converter = std::make_shared<FakeKeyConverter>();
				InputManager im(std::move(converter));

				im.ProcessPlatformKeyPress(static_cast<int>(KeyCode::A));

				auto key = im.GetFirstPressedKey(
					{
						KeyCode::A,
					}
					);

				Assert::AreEqual(
					static_cast<int>(KeyCode::A),
					static_cast<int>(key)
				);
			}

			TEST_METHOD(InputManager_GetFirstPressedKey_WithMultiplePressedKeys_ReturnsEarliestPressed)
			{
				std::shared_ptr<IKeyConverter> converter = std::make_shared<FakeKeyConverter>();
				InputManager im(std::move(converter));

				im.ProcessPlatformKeyPress(static_cast<int>(KeyCode::C));
				im.ProcessPlatformKeyPress(static_cast<int>(KeyCode::B));
				im.ProcessPlatformKeyPress(static_cast<int>(KeyCode::A));

				auto key = im.GetFirstPressedKey(
					{
						KeyCode::A,
						KeyCode::B,
						KeyCode::C,
					}
					);

				Assert::AreEqual(
					static_cast<int>(KeyCode::C),
					static_cast<int>(key)
				);
			}

		};
	}
}