#include "CppUnitTest.h"

#include <Engine/Core/GameManager.h>
#include <Fakes/Collisions/FakeGrid.h>
#include <Fakes/Collisions/FakeTile.h>
#include <Fakes/Input/FakeKeyConverter.h>
#include <Fakes/Scenes/FakeScene.h>
#include <Fakes/States/FakeGameState.h>
#include <Fakes/Renderer/FakeCamera.h>
#include <Fakes/Renderer/FakeRenderer.h>
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Engine
{
    namespace Core
    {
        TEST_CLASS(GameManagerTests)
        {
        public:
            TEST_METHOD(GameManager_ConstructsValidSingleton)
            {
                GameManager gm;

                Assert::IsTrue(&gm == GameManager::Get());
            }

            TEST_METHOD(GameManager_Get_ReturnsValidSelf)
            {
                GameManager gm;

                Assert::IsTrue(&gm == GameManager::Get());
            }

            TEST_METHOD(GameManager_GetCamera_WhenNotSetReturnsNull)
            {
                GameManager gm;

                Assert::IsNull(gm.GetCamera());
            }

            TEST_METHOD(GameManager_GetCamera_WhenSetReturnsValidPtr)
            {
                GameManager gm;

                gm.SetCamera(std::make_shared<FakeCamera>());

                Assert::IsNotNull(gm.GetCamera());
            }

            TEST_METHOD(GameManager_GetScene_WhenNotSetReturnsNull)
            {
                GameManager gm;

                Assert::IsNull(gm.GetScene());
            }

            TEST_METHOD(GameManager_GetScene_WhenSetReturnsValidPtr)
            {
                GameManager gm;

                gm.SetScene(std::make_shared<FakeScene>());

                Assert::IsNotNull(gm.GetScene());

            }

            TEST_METHOD(GameManager_GetRenderer_WhenNotSetReturnsNull)
            {
                GameManager gm;

                Assert::IsNull(gm.GetRenderer());
            }

            TEST_METHOD(GameManager_GetRenderer_WhenSetReturnsValidPtr)
            {
                GameManager gm;

                gm.SetRenderer(std::make_shared<FakeRenderer>());

                Assert::IsNotNull(gm.GetRenderer());
            }

            TEST_METHOD(GameManager_GetInputManager_WhenNotSetReturnsNull)
            {
                GameManager gm;

                Assert::IsNull(gm.GetInputManager());
            }

            TEST_METHOD(GameManager_GetInputManager_WhenSetReturnsValidPtr)
            {
                GameManager gm;

                gm.InitInputManager(std::make_shared<FakeKeyConverter>());

                Assert::IsNotNull(gm.GetInputManager());
            }

            TEST_METHOD(GameManager_GetCollisionManager_WhenNotSetReturnsNull)
            {
                GameManager gm;

                Assert::IsNull(gm.GetCollisionMgr());
            }

            TEST_METHOD(GameManager_GetCollisionManager_WhenSetReturnsValidPtr)
            {
                GameManager gm;

                gm.SetICollisionManager(std::make_shared<ICollisionManager>(nullptr));

                Assert::IsNotNull(gm.GetCollisionMgr());
            }

            TEST_METHOD(GameManager_CheckInView_DoesNothingWhenCollisionManagerIsNull)
            {
                GameManager gm;

                gm.CheckInView();
            }

            TEST_METHOD(GameManager_CheckInView_DoesNothingWhenCameraIsNull)
            {
                GameManager gm;

                gm.SetICollisionManager(std::make_shared<ICollisionManager>(nullptr));

                gm.CheckInView();
            }

            TEST_METHOD(GameManager_CheckInView_DoesNothingWhenGridIsEmpty)
            {
                GameManager gm;

                gm.SetCamera(std::make_shared<FakeCamera>());
                gm.SetICollisionManager(std::make_shared<ICollisionManager>(nullptr));

                gm.CheckInView();
            }

            TEST_METHOD(GameManager_CheckInView_SetsTilesActive)
            {
                GameManager gm;

                gm.SetCamera(std::make_shared<FakeCamera>());

                auto grid = std::make_shared<FakeGrid>(2, 10);

                gm.SetICollisionManager(
                    std::make_shared<ICollisionManager>(grid)
                );

                gm.CheckInView();

                for (size_t i = 0; i < 2; i++)
                {
                    for (size_t j = 0; j < 10; j ++)
                    {
                        ITile* t = grid->GetTile(i, j);
                        if (t)
                        {
                            Assert::IsTrue(t->GetActive());
                        }
                    }
                }
            }

            TEST_METHOD(GameManager_CheckInView_DoesNotCallSceneCheckIsInViewWhenSceneIsNull)
            {
                GameManager gm;

                gm.SetCamera(std::make_shared<FakeCamera>());

                auto grid = std::make_shared<FakeGrid>(2, 10);

                gm.SetICollisionManager(
                    std::make_shared<ICollisionManager>(grid)
                );

                gm.CheckInView();

            }

            TEST_METHOD(GameManager_CheckInView_CallsSceneCheckIsInView)
            {
                GameManager gm;

                gm.SetCamera(std::make_shared<FakeCamera>());

                auto grid = std::make_shared<FakeGrid>(2, 10);

                gm.SetICollisionManager(
                    std::make_shared<ICollisionManager>(grid)
                );

                gm.SetScene(std::make_shared<FakeScene>());

                auto* s = gm.GetScene();

                Assert::IsNotNull(s);

                auto* fs = dynamic_cast<FakeScene*>(s);

                Assert::IsNotNull(fs);

                gm.CheckInView(); // missing line

                Assert::IsTrue(fs->CheckIsInViewIsCalled);
            }

            TEST_METHOD(GameManager_Update_DoesNothingIfNoState)
            {
                GameManager gm;

                gm.GetGameStateMgr()->Update(0.1f);
            }

            TEST_METHOD(GameManager_Update_CallsTopState)
            {
                GameManager gm;

                auto* gsm = gm.GetGameStateMgr();

                Assert::IsNotNull(gsm);

                FakeGameState fgs("State1", &gm);

                gsm->ChangeState(&fgs);

                gsm->Update(0.1f);

                Assert::IsTrue(fgs.updateCalled);
            }

            TEST_METHOD(GameManager_Render_DoesNothingIfNoState)
            {
                GameManager gm;

                gm.GetGameStateMgr()->Render();
            }

            TEST_METHOD(GameManager_Render_CallsTopState)
            {
                GameManager gm;

                auto* gsm = gm.GetGameStateMgr();

                Assert::IsNotNull(gsm);

                FakeGameState fgs("State1", &gm);

                gsm->ChangeState(&fgs);

                gsm->Render();

                Assert::IsTrue(fgs.renderCalled);
            }
        };
    }
}