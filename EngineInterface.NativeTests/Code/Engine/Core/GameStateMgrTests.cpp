#include "CppUnitTest.h"

#include <Engine/Core/GameManager.h>
#include <Engine/Core/GameStateMgr.h>
#include <Fakes/FakeGameState.h>
#include <string_view>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Engine
{
    namespace Core
    {
        TEST_CLASS(GameStateMgrTests)
        {
        public:
            TEST_METHOD(GameStateMgr_GetStateName_WhenEmpty_ReturnsEmpty)
            {
                GameStateMgr<IGameState> gsm;

                Assert::AreEqual(std::string_view(), gsm.GetStateName());
            }

            TEST_METHOD(GameStateMgr_GetStateName_ReturnsName)
            {
                GameManager gm;
                GameStateMgr<IGameState> gsm;

                gsm.ChangeState(new FakeGameState("State1", &gm));

                Assert::AreEqual(std::string_view("State1"), gsm.GetStateName());
            }

            TEST_METHOD(GameStateMgr_GetStateName_AfterPush_ReturnsTopStateName)
            {
                GameManager gm;
                GameStateMgr<IGameState> gsm;

                gsm.ChangeState(new FakeGameState("State1", &gm));
                gsm.PushState(new FakeGameState("State2", &gm));

                Assert::AreEqual(std::string_view("State2"), gsm.GetStateName());
            }

            TEST_METHOD(GameStateMgr_GetStateName_AfterPop_ReturnsPreviousStateName)
            {
                GameManager gm;
                GameStateMgr<IGameState> gsm;

                gsm.ChangeState(new FakeGameState("State1", &gm));
                gsm.PushState(new FakeGameState("State2", &gm));
                gsm.PopState();

                Assert::AreEqual(std::string_view("State1"), gsm.GetStateName());
            }

            TEST_METHOD(GameStateMgr_ChangeState_CallsGameStateInitialisation)
            {
                GameManager gm;
                GameStateMgr<IGameState> gsm;

                FakeGameState fgs("State1", &gm);

                gsm.ChangeState(&fgs);

                Assert::IsTrue(fgs.initialisedCalled);
            }

            TEST_METHOD(GameStateMgr_ChangeState_ClearsPreviousStateStack)
            {
                GameManager gm;
                GameStateMgr<IGameState> gsm;

                FakeGameState state1("State1", &gm);
                FakeGameState state2("State2", &gm);
                FakeGameState state3("State3", &gm);

                gsm.PushState(&state1);
                gsm.PushState(&state2);

                gsm.ChangeState(&state3);

                Assert::AreEqual(std::string_view("State3"), gsm.GetStateName());

                gsm.PopState();

                Assert::AreEqual(std::string_view(""), gsm.GetStateName());
            }

            TEST_METHOD(GameStateMgr_ChangeState_DoesNotPausePreviousState)
            {
                GameManager gm;
                GameStateMgr<IGameState> gsm;

                FakeGameState state1("State1", &gm);
                FakeGameState state2("State2", &gm);

                gsm.ChangeState(&state1);
                gsm.ChangeState(&state2);

                Assert::IsFalse(state1.pauseCalled);
            }

            TEST_METHOD(GameStateMgr_ChangeState_DoesNotResumePreviousState)
            {
                GameManager gm;
                GameStateMgr<IGameState> gsm;

                FakeGameState state1("State1", &gm);
                FakeGameState state2("State2", &gm);

                gsm.ChangeState(&state1);
                gsm.ChangeState(&state2);

                Assert::IsFalse(state1.resumeCalled);
            }

            TEST_METHOD(GameStateMgr_PushState_PausesPreviousState)
            {
                GameManager gm;
                GameStateMgr<IGameState> gsm;

                FakeGameState state1("State1", &gm);
                FakeGameState state2("State2", &gm);

                gsm.ChangeState(&state1);
                gsm.PushState(&state2);

                Assert::IsTrue(state1.pauseCalled);
            }

            TEST_METHOD(GameStateMgr_PushState_PauseCalledExactlyOnce)
            {
                GameManager gm;
                GameStateMgr<IGameState> gsm;

                FakeGameState state1("State1", &gm);
                FakeGameState state2("State2", &gm);

                gsm.ChangeState(&state1);
                gsm.PushState(&state2);

                Assert::AreEqual(1, state1.pauseCallCount);
            }

            TEST_METHOD(GameStateMgr_PushState_GameStateCallsInitialisation)
            {
                GameManager gm;
                GameStateMgr<IGameState> gsm;

                FakeGameState fgs1("State1", &gm);
                FakeGameState fgs2("State2", &gm);

                gsm.ChangeState(&fgs1);
                gsm.PushState(&fgs2);

                Assert::IsTrue(fgs2.initialisedCalled);
            }

            TEST_METHOD(GameStateMgr_PushMultipleStates_StackMaintainsCorrectOrder)
            {
                GameManager gm;
                GameStateMgr<IGameState> gsm;

                FakeGameState state1("State1", &gm);
                FakeGameState state2("State2", &gm);
                FakeGameState state3("State3", &gm);

                gsm.PushState(&state1);
                gsm.PushState(&state2);
                gsm.PushState(&state3);

                Assert::AreEqual(std::string_view("State3"), gsm.GetStateName());

                gsm.PopState();

                Assert::AreEqual(std::string_view("State2"), gsm.GetStateName());

                gsm.PopState();

                Assert::AreEqual(std::string_view("State1"), gsm.GetStateName());

                gsm.PopState();

                Assert::AreEqual(std::string_view(""), gsm.GetStateName());
            }

            TEST_METHOD(GameStateMgr_PopState_WhenEmpty_DoesNothing)
            {
                GameManager gm;
                GameStateMgr<IGameState> gsm;

                gsm.PopState();

                Assert::AreEqual(std::string_view(""), gsm.GetStateName());
            }

            TEST_METHOD(GameStateMgr_PopState_WhenOneState_RemovesStateAndLeavesEmpty)
            {
                GameManager gm;
                GameStateMgr<IGameState> gsm;

                FakeGameState state1("State1", &gm);

                gsm.PushState(&state1);

                Assert::AreEqual(std::string_view("State1"), gsm.GetStateName());

                gsm.PopState();

                Assert::AreEqual(std::string_view(""), gsm.GetStateName());
            }

            TEST_METHOD(GameStateMgr_PopState_ResumesPreviousState)
            {
                GameManager gm;
                GameStateMgr<IGameState> gsm;

                FakeGameState state1("State1", &gm);
                FakeGameState state2("State2", &gm);

                gsm.PushState(&state1);

                Assert::AreEqual(std::string_view("State1"), gsm.GetStateName());

                gsm.PushState(&state2);

                Assert::IsTrue(state1.pauseCalled);

                gsm.PopState();

                Assert::AreEqual(std::string_view("State1"), gsm.GetStateName());

                Assert::IsTrue(state1.resumeCalled);
            }

            TEST_METHOD(GameStateMgr_PopState_ResumeCalledExactlyOnce)
            {
                GameManager gm;
                GameStateMgr<IGameState> gsm;

                FakeGameState state1("State1", &gm);
                FakeGameState state2("State2", &gm);

                gsm.PushState(&state1);

                Assert::AreEqual(std::string_view("State1"), gsm.GetStateName());

                gsm.PushState(&state2);

                Assert::IsTrue(state1.pauseCalled);

                gsm.PopState();

                Assert::AreEqual(std::string_view("State1"), gsm.GetStateName());

                Assert::IsTrue(state1.resumeCalled);
                Assert::AreEqual(1, state1.resumeCallCount);
            }

            TEST_METHOD(GameStateMgr_PopState_RemovesTopStateOnly)
            {
                GameManager gm;
                GameStateMgr<IGameState> gsm;

                FakeGameState state1("State1", &gm);
                FakeGameState state2("State2", &gm);

                gsm.PushState(&state1);
                gsm.PushState(&state2);

                gsm.PopState();

                Assert::AreEqual(std::string_view("State1"), gsm.GetStateName());
            }

            TEST_METHOD(GameStateMgr_PushThenPop_StateRestoresCorrectly)
            {
                GameManager gm;
                GameStateMgr<IGameState> gsm;

                FakeGameState state1("State1", &gm);
                FakeGameState state2("State2", &gm);

                gsm.PushState(&state1);
                gsm.PushState(&state2);

                Assert::AreEqual(std::string_view("State2"), gsm.GetStateName());

                gsm.PopState();

                Assert::AreEqual(std::string_view("State1"), gsm.GetStateName());

                gsm.PushState(&state2);

                Assert::AreEqual(std::string_view("State2"), gsm.GetStateName());
            }

            TEST_METHOD(GameStateMgr_ClearState_RemovesAllStates)
            {
                GameManager gm;
                GameStateMgr<IGameState> gsm;

                FakeGameState state1("State1", &gm);

                gsm.PushState(&state1);

                gsm.ClearStates();

                Assert::AreEqual(std::string_view(""), gsm.GetStateName());
            }

            TEST_METHOD(GameStateMgr_ClearState_WhenMultipleStates_RemovesAll)
            {
                GameManager gm;
                GameStateMgr<IGameState> gsm;

                FakeGameState state1("State1", &gm);
                FakeGameState state2("State2", &gm);

                gsm.PushState(&state1);
                gsm.PushState(&state2);

                gsm.ClearStates();

                Assert::AreEqual(std::string_view(""), gsm.GetStateName());
            }

            TEST_METHOD(GameStateMgr_ProcessInputs_WhenNoState_DoesNothing)
            {
                GameStateMgr<IGameState> gsm;

                gsm.ProcessInputs();
            }

            TEST_METHOD(GameStateMgr_ProcessInputs_CallsGameStateProcessInputs)
            {
                GameManager gm;
                GameStateMgr<IGameState> gsm;

                FakeGameState state1("State1", &gm);

                gsm.ChangeState(&state1);

                gsm.ProcessInputs();

                Assert::IsTrue(state1.processInputCalled);
            }

            TEST_METHOD(GameStateMgr_ProcessInputs_OnlyTopStateIsCalled)
            {
                GameManager gm;
                GameStateMgr<IGameState> gsm;

                FakeGameState state1("State1", &gm);
                FakeGameState state2("State2", &gm);

                gsm.PushState(&state1);
                gsm.PushState(&state2);

                gsm.ProcessInputs();

                Assert::IsFalse(state1.processInputCalled);
                Assert::IsTrue(state2.processInputCalled);
            }

            TEST_METHOD(GameStateMgr_Update_WhenNoState_DoesNothing)
            {
                GameStateMgr<IGameState> gsm;

                gsm.Update(0.0f);
            }

            TEST_METHOD(GameStateMgr_Update_CallsGameStateUpdate)
            {
                GameManager gm;
                GameStateMgr<IGameState> gsm;

                FakeGameState state1("State1", &gm);

                gsm.ChangeState(&state1);

                gsm.Update(0.0f);

                Assert::IsTrue(state1.updateCalled);
            }

            TEST_METHOD(GameStateMgr_Update_OnlyTopStateIsUpdated)
            {
                GameManager gm;
                GameStateMgr<IGameState> gsm;

                FakeGameState state1("State1", &gm);
                FakeGameState state2("State2", &gm);

                gsm.PushState(&state1);
                gsm.PushState(&state2);

                gsm.Update(0.0f);

                Assert::IsFalse(state1.updateCalled);
                Assert::IsTrue(state2.updateCalled);
            }

            TEST_METHOD(GameStateMgr_Render_WhenNoState_DoesNothing)
            {
                GameStateMgr<IGameState> gsm;

                gsm.Render();
            }

            TEST_METHOD(GameStateMgr_Render_CallsGameStateRender)
            {
                GameManager gm;
                GameStateMgr<IGameState> gsm;

                FakeGameState state1("State1", &gm);

                gsm.ChangeState(&state1);

                gsm.Render();

                Assert::IsTrue(state1.renderCalled);
            }

            TEST_METHOD(GameStateMgr_Render_OnlyTopStateIsRendered)
            {
                GameManager gm;
                GameStateMgr<IGameState> gsm;

                FakeGameState state1("State1", &gm);
                FakeGameState state2("State2", &gm);

                gsm.PushState(&state1);
                gsm.PushState(&state2);

                gsm.Render();

                Assert::IsFalse(state1.renderCalled);
                Assert::IsTrue(state2.renderCalled);
            }
        };
    }
}