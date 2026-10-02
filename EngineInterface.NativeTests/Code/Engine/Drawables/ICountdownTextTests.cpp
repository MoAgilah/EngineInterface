#include "CppUnitTest.h"

#include <Engine/Interface/Drawables/IText.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Engine
{
    namespace Drawables
    {
        TEST_CLASS(ICountdownTextTests)
        {
        public:

            // ======================================================
            // Construction
            // ======================================================

            TEST_METHOD(ICountdownText_Constructor_StoresInitialCount)
            {
                int startFrom = 3;

                ICountdownText text(1.f, startFrom, "Finito");

                Assert::AreEqual(startFrom, text.GetCount());
            }

            TEST_METHOD(ICountdownText_Constructor_StoresCountDownMessage)
            {
                std::string countdownMsg = "Finito";

                ICountdownText text(1.f, 3, countdownMsg);

                Assert::AreEqual(std::string_view(countdownMsg), text.GetCountDownMsg());
            }

            TEST_METHOD(ICountdownText_Constructor_ThrowsIfCountdownIntervalIsZero)
            {
                Assert::ExpectException<std::runtime_error>(
                    []()
                    {
                        ICountdownText text(0.f, 1, "Finito");
                    });
            }

            TEST_METHOD(ICountdownText_Constructor_ThrowsIfCountdownIntervalIsNegative)
            {
                Assert::ExpectException<std::runtime_error>(
                    []()
                    {
                        ICountdownText text(-1.f, 1, "Finito");
                    });
            }

            TEST_METHOD(ICountdownText_Constructor_ThrowsIfStartFromIsZero)
            {
                Assert::ExpectException<std::runtime_error>(
                    []()
                    {
                        ICountdownText text(1.f, 0, "Finito");
                    });
            }

            TEST_METHOD(ICountdownText_Constructor_ThrowsIfStartFromIsNegative)
            {
                Assert::ExpectException<std::runtime_error>(
                    []()
                    {
                        ICountdownText text(1.f, -1, "Finito");
                    });
            }

            // ======================================================
            // Update
            // ======================================================

            TEST_METHOD(ICountdownText_Update_DoesNotDecrementBeforeInterval)
            {
                int startFrom = 3;

                ICountdownText text(1.f, startFrom, "Finito");

                text.Update(0.25f);
                Assert::AreEqual(startFrom, text.GetCount());
            }

            TEST_METHOD(ICountdownText_Update_DecrementsCountWhenIntervalCompletes)
            {
                int startFrom = 3;

                ICountdownText text(1.f, startFrom, "Finito");

                text.Update(1.0f);
                Assert::AreEqual(2, text.GetCount());
            }

            TEST_METHOD(ICountdownText_Update_DecrementsAcrossMultipleIntervals)
            {
                int startFrom = 3;

                ICountdownText text(1.f, startFrom, "Finito");

                text.Update(1.0f);
                Assert::AreEqual(2, text.GetCount());

                text.Update(1.0f);
                Assert::AreEqual(1, text.GetCount());
            }

            TEST_METHOD(ICountdownText_Update_SetsCountEndedWhenCountdownCompletes)
            {
                int startFrom = 3;

                ICountdownText text(1.f, startFrom, "Finito");

                text.Update(1.0f);
                Assert::AreEqual(2, text.GetCount());

                text.Update(1.0f);
                Assert::AreEqual(1, text.GetCount());

                text.Update(1.0f);
                Assert::AreEqual(0, text.GetCount());

                Assert::IsTrue(text.CountHasEnded());
            }

            TEST_METHOD(ICountdownText_Update_DoesNotChangeCountAfterCountdownCompletes)
            {
                int startFrom = 3;

                ICountdownText text(1.f, startFrom, "Finito");

                text.Update(1.0f);
                Assert::AreEqual(2, text.GetCount());

                text.Update(1.0f);
                Assert::AreEqual(1, text.GetCount());

                text.Update(1.0f);
                Assert::AreEqual(0, text.GetCount());

                Assert::IsTrue(text.CountHasEnded());

                text.Update(1.0f);
                Assert::AreEqual(0, text.GetCount());
            }

            // ======================================================
            // Max Count
            // ======================================================

            TEST_METHOD(ICountdownText_SetMaxCount_UpdatesCount)
            {
                int startFrom = 3;

                ICountdownText text(1.f, startFrom, "Finito");

                text.SetMaxCount(4);

                Assert::AreEqual(4, text.GetCount());
            }

            TEST_METHOD(ICountdownText_SetMaxCount_ThrowsIfZero)
            {
                int startFrom = 3;

                ICountdownText text(1.f, startFrom, "Finito");

                Assert::ExpectException<std::runtime_error>(
                    [&]()
                    {
                        text.SetMaxCount(0);
                    });
            }

            TEST_METHOD(ICountdownText_SetMaxCount_ThrowsIfNegative)
            {
                int startFrom = 3;

                ICountdownText text(1.f, startFrom, "Finito");

                Assert::ExpectException<std::runtime_error>(
                    [&]()
                    {
                        text.SetMaxCount(-1);
                    });
            }

            TEST_METHOD(ICountdownText_SetMaxCount_ResetsEndedCountdown)
            {
                int startFrom = 3;

                ICountdownText text(1.f, startFrom, "Finito");

                text.Update(1.0f);
                text.Update(1.0f);
                text.Update(1.0f);

                Assert::IsTrue(text.CountHasEnded());

                text.SetMaxCount(4);

                Assert::AreEqual(4, text.GetCount());
                Assert::IsFalse(text.CountHasEnded());
            }

            // ======================================================
            // Countdown Message
            // ======================================================

            TEST_METHOD(ICountdownText_SetCountDownMsg_UpdatesCountdownMessage)
            {
                ICountdownText text(1.f, 3, "Finished");

                std::string countdownMsg = "Finito";

                text.SetCountDownMsg(countdownMsg);

                Assert::AreEqual(std::string_view(countdownMsg), text.GetCountDownMsg());
            }
        };
    }
}