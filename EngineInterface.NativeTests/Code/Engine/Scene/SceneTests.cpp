#include "CppUnitTest.h"

#include <Fakes/Drawables/FakeSprite.h>
#include <Fakes/Renderer/FakeRenderer.h>
#include <Fakes/Scenes/FakeScene.h>
#include <Engine/Core/GameManager.h>
#include <memory>
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Engine
{
    namespace Scene
    {
        TEST_CLASS(SceneTests)
        {
        public:

            // ======================================================
            // Initialisation flow
            // ======================================================

            TEST_METHOD(Scene_Initialise_WhenAllAddMethodsSucceed_ReturnsTrue)
            {
                FakeScene scene;
                scene.addEnemiesResult = true;
                scene.addGUIResult = true;
                scene.addObjectsResult = true;
                scene.addForeGroundObjectsResult = true;

                Assert::IsTrue(scene.Initialise());
            }

            TEST_METHOD(Scene_Initialise_WhenAddEnemiesFails_Throws)
            {
                FakeScene scene;
                scene.addEnemiesResult = false;
                scene.addGUIResult = true;
                scene.addObjectsResult = true;
                scene.addForeGroundObjectsResult = true;

                Assert::ExpectException<std::runtime_error>(
                    [&]()
                    {
                        scene.Initialise();
                    });
            }

            TEST_METHOD(Scene_Initialise_WhenAddGUIFails_Throws)
            {
                FakeScene scene;
                scene.addEnemiesResult = true;
                scene.addGUIResult = false;
                scene.addObjectsResult = true;
                scene.addForeGroundObjectsResult = true;

                Assert::ExpectException<std::runtime_error>(
                    [&]()
                    {
                        scene.Initialise();
                    });
            }

            TEST_METHOD(Scene_Initialise_WhenAddObjectsFails_Throws)
            {
                FakeScene scene;
                scene.addEnemiesResult = true;
                scene.addGUIResult = true;
                scene.addObjectsResult = false;
                scene.addForeGroundObjectsResult = true;

                Assert::ExpectException<std::runtime_error>(
                    [&]()
                    {
                        scene.Initialise();
                    });
            }

            TEST_METHOD(Scene_Initialise_WhenAddForegroundObjectsFails_Throws)
            {
                FakeScene scene;
                scene.addEnemiesResult = true;
                scene.addGUIResult = true;
                scene.addObjectsResult = true;
                scene.addForeGroundObjectsResult = false;

                Assert::ExpectException<std::runtime_error>(
                    [&]()
                    {
                        scene.Initialise();
                    });
            }

            // ======================================================
            // Emplace helper behaviour
            // ======================================================

            TEST_METHOD(Scene_EmplaceObjectOrThrow_AddsObject)
            {
                FakeScene scene;

                scene.EmplaceObjectOrThrow<FakeDynamicGameObject>("Object1", std::make_shared<FakeSprite>("Obj1"), std::make_shared<BoundingBox<FakeBox>>(), true);

                Assert::AreEqual(std::size_t(1), scene.m_objects.size());
            }

            TEST_METHOD(Scene_EmplaceEnemyOrThrow_AddsEnemy)
            {
                FakeScene scene;

                scene.EmplaceEnemyOrThrow<FakeEnemy>("Enemy1", "Enmy1", false);

                Assert::AreEqual(std::size_t(1), scene.m_enemies.size());
            }

            TEST_METHOD(EmplaceForegroundObjectOrThrow_AddsForegroundObject)
            {
                FakeScene scene;

                scene.EmplaceForegroundObjectOrThrow<FakeGameObject>("ForeGroundObjects1", std::make_shared<FakeSprite>("FgObj1"), std::make_shared<BoundingBox<FakeBox>>(), true);

                Assert::AreEqual(std::size_t(1), scene.m_foregroundObjects.size());
            }

            TEST_METHOD(Scene_EmplaceGUISpriteOrThrow_AddsSprite)
            {
                FakeScene scene;

                scene.EmplaceGUISpriteOrThrow<FakeSprite>("Sprite1", "Spr1");

                Assert::AreEqual(std::size_t(1), scene.m_sprites.size());
            }

            TEST_METHOD(Scene_EmplaceGUITextOrThrow_AddsText)
            {
                FakeScene scene;

                scene.EmplaceGUITextOrThrow<FakeText>(
                    "Text1",
                    TextConfig("fontName", 12, Vector2f(), TextAnimType::Static),
                    "Txt1"
                );

                Assert::AreEqual(std::size_t(1), scene.m_texts.size());
            }

            TEST_METHOD(Scene_EmplaceObjectOrThrow_WhenDuplicateKey_Throws)
            {
                FakeScene scene;

                scene.EmplaceObjectOrThrow<FakeDynamicGameObject>("Object1", std::make_shared<FakeSprite>("Obj1"), std::make_shared<BoundingBox<FakeBox>>(), true);

                Assert::ExpectException<std::invalid_argument>(
                    [&]()
                    {
                        scene.EmplaceObjectOrThrow<FakeDynamicGameObject>("Object1", std::make_shared<FakeSprite>("Obj1"), std::make_shared<BoundingBox<FakeBox>>(), true);
                    });

                Assert::AreEqual(std::size_t(1), scene.m_objects.size());
            }

            TEST_METHOD(Scene_EmplaceEnemyOrThrow_WhenDuplicateKey_Throws)
            {
                FakeScene scene;

                scene.EmplaceEnemyOrThrow<FakeEnemy>("Enemy1", "Enmy1", false);

                Assert::ExpectException<std::invalid_argument>(
                    [&]()
                    {
                        scene.EmplaceEnemyOrThrow<FakeEnemy>("Enemy1", "Enmy1", false);
                    });

                Assert::AreEqual(std::size_t(1), scene.m_enemies.size());
            }

            TEST_METHOD(EmplaceForegroundObjectOrThrow_WhenDuplicateKey_Throws)
            {
                FakeScene scene;

                scene.EmplaceForegroundObjectOrThrow<FakeGameObject>("ForeGroundObjects1", std::make_shared<FakeSprite>("FgObj1"), std::make_shared<BoundingBox<FakeBox>>(), true);

                Assert::ExpectException<std::invalid_argument>(
                    [&]()
                    {
                        scene.EmplaceForegroundObjectOrThrow<FakeGameObject>("ForeGroundObjects1", std::make_shared<FakeSprite>("FgObj1"), std::make_shared<BoundingBox<FakeBox>>(), true);
                    });

                Assert::AreEqual(std::size_t(1), scene.m_foregroundObjects.size());
            }

            TEST_METHOD(Scene_EmplaceGUISpriteOrThrow_WhenDuplicateKey_Throws)
            {
                FakeScene scene;

                scene.EmplaceGUISpriteOrThrow<FakeSprite>("Sprite1", "Spr1");

                Assert::ExpectException<std::invalid_argument>(
                    [&]()
                    {
                        scene.EmplaceGUISpriteOrThrow<FakeSprite>("Sprite1", "Spr1");
                    });

                Assert::AreEqual(std::size_t(1), scene.m_sprites.size());
            }

            TEST_METHOD(Scene_EmplaceGUITextOrThrow_WhenDuplicateKey_Throws)
            {
                FakeScene scene;

                scene.EmplaceGUITextOrThrow<FakeText>(
                    "Text1",
                    TextConfig("fontName", 12, Vector2f(), TextAnimType::Static),
                    "Txt1"
                );

                Assert::ExpectException<std::invalid_argument>(
                    [&]()
                    {
                        scene.EmplaceGUITextOrThrow<FakeText>(
                            "Text1",
                            TextConfig("fontName", 12, Vector2f(), TextAnimType::Static),
                            "Txt1"
                        );
                    });

                Assert::AreEqual(std::size_t(1), scene.m_texts.size());
            }

            // ======================================================
            // Spawn behaviour
            // ======================================================

            TEST_METHOD(Scene_SpawnGameObjectAt_AddsObjectToScene)
            {
                FakeScene scene;

                scene.SpawnGameObjectAt(
                    "Object1",
                    std::make_shared<FakeDynamicGameObject>(std::make_shared<FakeSprite>("Obj1"), std::make_shared<BoundingBox<FakeBox>>(), true),
                    Vector2f(16.f, 16.f));

                Assert::AreEqual(std::size_t(1), scene.m_objects.size());
            }

            TEST_METHOD(Scene_SpawnGameObjectAt_SetsObjectPosition)
            {
                FakeScene scene;

                scene.SpawnGameObjectAt(
                    "Object1",
                    std::make_shared<FakeDynamicGameObject>(std::make_shared<FakeSprite>("Obj1"), std::make_shared<BoundingBox<FakeBox>>(), true),
                    Vector2f(16.f, 32.f));

                Assert::AreEqual(std::size_t(1), scene.m_objects.size());

                auto it = scene.m_objects.find("Object1");
                Assert::IsTrue(it != scene.m_objects.end());

                auto pos = (*it).second->GetPosition();

                Assert::AreEqual(16.f, pos.x);
                Assert::AreEqual(32.f, pos.y);
            }

            TEST_METHOD(Scene_SpawnGameObjectAt_AddsSpawnedKey)
            {
                FakeScene scene;

                scene.SpawnGameObjectAt(
                    "Object1",
                    std::make_shared<FakeDynamicGameObject>(std::make_shared<FakeSprite>("Obj1"), std::make_shared<BoundingBox<FakeBox>>(), true),
                    Vector2f(16.f, 32.f));

                Assert::AreEqual(std::size_t(1), scene.m_objects.size());
                Assert::AreEqual(std::size_t(1), scene.m_spawnedObjKeys.size());
                Assert::AreEqual(std::string("Object1"), scene.m_spawnedObjKeys.front());
            }

            TEST_METHOD(Scene_SpawnGameObjectAt_WhenDuplicateKey_Throws)
            {
                FakeScene scene;

                scene.SpawnGameObjectAt(
                    "Object1",
                    std::make_shared<FakeDynamicGameObject>(std::make_shared<FakeSprite>("Obj1"), std::make_shared<BoundingBox<FakeBox>>(), true),
                    Vector2f(16.f, 32.f));

                Assert::ExpectException<std::runtime_error>(
                    [&]()
                    {
                        scene.SpawnGameObjectAt(
                            "Object1",
                            std::make_shared<FakeDynamicGameObject>(std::make_shared<FakeSprite>("Obj1"), std::make_shared<BoundingBox<FakeBox>>(), true),
                            Vector2f(16.f, 32.f));
                    });

                Assert::AreEqual(std::size_t(1), scene.m_objects.size());
            }

            // ======================================================
            // Lookup behaviour
            // ======================================================

            TEST_METHOD(Scene_GetObjectByNane_ReturnsCorrectObject)
            {
                FakeScene scene;

                scene.EmplaceObjectOrThrow<FakeGameObject>(
                    "Object1",
                    std::make_shared<FakeSprite>("Obj1"),
                    std::make_shared<BoundingBox<FakeBox>>(),
                    true
                );

                scene.EmplaceObjectOrThrow<FakeGameObject>(
                    "Object2",
                    std::make_shared<FakeSprite>("Obj2"),
                    std::make_shared<BoundingBox<FakeBox>>(),
                    true
                );

                auto expected = scene.m_objects.at("Object2").get();
                auto actual = scene.GetObjectByName("Object2");

                Assert::IsTrue(expected == actual);
            }

            TEST_METHOD(Scene_GetEnemyByNane_ReturnsCorrectEnemy)
            {
                FakeScene scene;

                scene.EmplaceEnemyOrThrow<FakeEnemy>("Enemy1", "Enmy1", true);

                scene.EmplaceEnemyOrThrow<FakeEnemy>("Enemy2", "Enmy2", true);

                auto expected = scene.m_enemies.at("Enemy2").get();
                auto actual = scene.GetEnemyByName("Enemy2");

                Assert::IsTrue(expected == actual);
            }

            TEST_METHOD(Scene_GetForegroundObjectByNane_ReturnsCorrectForegroundObject)
            {
                FakeScene scene;

                scene.EmplaceForegroundObjectOrThrow<FakeGameObject>(
                    "ForeGroundObjects1",
                    std::make_shared<FakeSprite>("FgObj1"), std::make_shared<BoundingBox<FakeBox>>(),
                    true
                );

                scene.EmplaceForegroundObjectOrThrow<FakeGameObject>(
                    "ForeGroundObjects2",
                    std::make_shared<FakeSprite>("FgObj2"), std::make_shared<BoundingBox<FakeBox>>(),
                    true
                );

                auto expected = scene.m_foregroundObjects.at("ForeGroundObjects2").get();
                auto actual = scene.GetForegroundObjectByName("ForeGroundObjects2");

                Assert::IsTrue(expected == actual);
            }

            TEST_METHOD(Scene_GetGUISpriteByNane_ReturnsCorrectGUISprite)
            {
                FakeScene scene;

                scene.EmplaceGUISpriteOrThrow<FakeSprite>("Sprite1", "Spr1");

                scene.EmplaceGUISpriteOrThrow<FakeSprite>("Sprite2", "Spr2");

                auto expected = scene.m_sprites.at("Sprite2").get();
                auto actual = scene.GetGUISpriteByName("Sprite2");

                Assert::IsTrue(expected == actual);
            }

            TEST_METHOD(Scene_GetGUITextByNane_ReturnsCorrectGUIText)
            {
                FakeScene scene;

                scene.EmplaceGUITextOrThrow<FakeText>(
                    "Text1",
                    TextConfig("fontName", 12, Vector2f(), TextAnimType::Static),
                    "Txt1"
                );

                scene.EmplaceGUITextOrThrow<FakeText>(
                    "Text2",
                    TextConfig("fontName", 12, Vector2f(), TextAnimType::Static),
                    "Txt2"
                );

                auto expected = scene.m_texts.at("Text2").get();
                auto actual = scene.GetGUITextByName("Text2");

                Assert::IsTrue(expected == actual);
            }

            TEST_METHOD(Scene_GetObjectByNane_ReturnsNull)
            {
                FakeScene scene;

                Assert::IsNull(scene.GetObjectByName("AName"));
            }

            TEST_METHOD(Scene_GetEnemyByNane_ReturnsNull)
            {
                FakeScene scene;

                Assert::IsNull(scene.GetEnemyByName("AName"));
            }

            TEST_METHOD(Scene_GetForegroundObjectByNane_ReturnsNull)
            {
                FakeScene scene;

                Assert::IsNull(scene.GetForegroundObjectByName("AName"));
            }

            TEST_METHOD(Scene_GetGUISpriteByNane_ReturnsNull)
            {
                FakeScene scene;

                Assert::IsNull(scene.GetGUISpriteByName("AName"));
            }

            TEST_METHOD(Scene_GetGUITextByNane_ReturnsNull)
            {
                FakeScene scene;

                Assert::IsNull(scene.GetGUITextByName("AName"));
            }

            // ======================================================
            // Initialisation population
            // ======================================================

            TEST_METHOD(Scene_Initialise_AddEnemies_PopulatesEnemyContainer)
            {
                FakeScene scene;
                scene.addEnemiesResult = true;
                scene.addGUIResult = true;
                scene.addObjectsResult = true;
                scene.addForeGroundObjectsResult = true;

                Assert::IsTrue(scene.Initialise());

                Assert::AreEqual(std::size_t(2), scene.m_enemies.size());
            }

            TEST_METHOD(Scene_Initialise_AddObjects_PopulatesObjectContainer)
            {
                FakeScene scene;
                scene.addEnemiesResult = true;
                scene.addGUIResult = true;
                scene.addObjectsResult = true;
                scene.addForeGroundObjectsResult = true;

                Assert::IsTrue(scene.Initialise());

                Assert::AreEqual(std::size_t(2), scene.m_objects.size());
            }

            TEST_METHOD(Scene_Initialise_AddObjects_PopulatesForegroundObjectContainer)
            {
                FakeScene scene;
                scene.addEnemiesResult = true;
                scene.addGUIResult = true;
                scene.addObjectsResult = true;
                scene.addForeGroundObjectsResult = true;

                Assert::IsTrue(scene.Initialise());

                Assert::AreEqual(std::size_t(2), scene.m_foregroundObjects.size());
            }

            TEST_METHOD(Scene_Initialise_AddGUI_PopulatesSpriteContainer)
            {
                FakeScene scene;
                scene.addEnemiesResult = true;
                scene.addGUIResult = true;
                scene.addObjectsResult = true;
                scene.addForeGroundObjectsResult = true;

                Assert::IsTrue(scene.Initialise());

                Assert::AreEqual(std::size_t(2), scene.m_sprites.size());
            }

            TEST_METHOD(Scene_Initialise_AddGUI_PopulatesTextContainer)
            {
                FakeScene scene;
                scene.addEnemiesResult = true;
                scene.addGUIResult = true;
                scene.addObjectsResult = true;
                scene.addForeGroundObjectsResult = true;

                Assert::IsTrue(scene.Initialise());

                Assert::AreEqual(std::size_t(2), scene.m_texts.size());
            }

            TEST_METHOD(Scene_Initialise_AddForegroundObjects_PopulatesForegroundContainer)
            {
                FakeScene scene;
                scene.addEnemiesResult = true;
                scene.addGUIResult = true;
                scene.addObjectsResult = true;
                scene.addForeGroundObjectsResult = true;

                Assert::IsTrue(scene.Initialise());

                Assert::AreEqual(std::size_t(2), scene.m_enemies.size());
            }

            // ======================================================
            // Update orchestration
            // ======================================================

            TEST_METHOD(Scene_Update_CallsUpdateGUI)
            {
                FakeScene scene;
                scene.addEnemiesResult = true;
                scene.addGUIResult = true;
                scene.addObjectsResult = true;
                scene.addForeGroundObjectsResult = true;

                Assert::IsTrue(scene.Initialise());

                scene.Update(0.f);

                Assert::IsTrue(scene.updateGUICalled);
            }

            TEST_METHOD(Scene_Update_PassesDeltaTimeToUpdateGUI)
            {
                FakeScene scene;
                scene.addEnemiesResult = true;
                scene.addGUIResult = true;
                scene.addObjectsResult = true;
                scene.addForeGroundObjectsResult = true;

                Assert::IsTrue(scene.Initialise());

                scene.Update(0.66f);

                Assert::AreEqual(0.66f, scene.lastGUIDeltaTime);
            }

            TEST_METHOD(Scene_Update_UpdatesActiveObjects)
            {
                FakeScene scene;
                scene.addEnemiesResult = true;
                scene.addGUIResult = true;
                scene.addObjectsResult = true;
                scene.addForeGroundObjectsResult = true;

                Assert::IsTrue(scene.Initialise());

                scene.Update(0.66f);

                for (auto& [_, object] : scene.m_objects)
                {
                    if (!object)
                        continue;

                    if (!object->GetActive())
                        continue;

                    auto* fo = dynamic_cast<IFakeObject*>(object.get());

                    if (!fo)
                        continue;

                    Assert::AreEqual(1, fo->updateCount);
                }
            }

            TEST_METHOD(Scene_Update_DoesNotUpdateInactiveObjects)
            {
                FakeScene scene;
                scene.addEnemiesResult = true;
                scene.addGUIResult = true;
                scene.addObjectsResult = true;
                scene.addForeGroundObjectsResult = true;

                Assert::IsTrue(scene.Initialise());

                scene.Update(0.66f);

                for (auto& [_, object] : scene.m_objects)
                {
                    if (!object)
                        continue;

                    if (object->GetActive())
                        continue;

                    auto* fo = dynamic_cast<IFakeObject*>(object.get());

                    if (!fo)
                        continue;

                    Assert::AreEqual(0, fo->updateCount);
                }
            }

            TEST_METHOD(Scene_Update_UpdatesActiveEnemies)
            {
                FakeScene scene;
                scene.addEnemiesResult = true;
                scene.addGUIResult = true;
                scene.addObjectsResult = true;
                scene.addForeGroundObjectsResult = true;

                Assert::IsTrue(scene.Initialise());

                scene.Update(0.66f);

                for (auto& [_, enemy] : scene.m_enemies)
                {
                    if (!enemy)
                        continue;

                    if (!enemy->GetActive())
                        continue;

                    auto* fo = dynamic_cast<IFakeObject*>(enemy.get());

                    if (!fo)
                        continue;

                    Assert::AreEqual(1, fo->updateCount);
                }
            }

            TEST_METHOD(Scene_Update_DoesNotUpdateInactiveEnemies)
            {
                FakeScene scene;
                scene.addEnemiesResult = true;
                scene.addGUIResult = true;
                scene.addObjectsResult = true;
                scene.addForeGroundObjectsResult = true;

                Assert::IsTrue(scene.Initialise());

                scene.Update(0.66f);

                for (auto& [_, enemy] : scene.m_enemies)
                {
                    if (!enemy)
                        continue;

                    if (!enemy->GetActive())
                        continue;

                    auto* fo = dynamic_cast<IFakeObject*>(enemy.get());

                    if (!fo)
                        continue;

                    Assert::AreEqual(0, fo->updateCount);
                }
            }

            TEST_METHOD(Scene_Update_PassesDeltaTimeToObjects)
            {
                FakeScene scene;
                scene.addEnemiesResult = true;
                scene.addGUIResult = true;
                scene.addObjectsResult = true;
                scene.addForeGroundObjectsResult = true;

                Assert::IsTrue(scene.Initialise());

                scene.Update(0.66f);

                for (auto& [_, object] : scene.m_objects)
                {
                    if (!object)
                        continue;

                    if (!object->GetActive())
                        continue;

                    auto* fo = dynamic_cast<IFakeObject*>(object.get());

                    if (!fo)
                        continue;

                    Assert::AreEqual(0.66f, fo->lastDeltaTime);
                }
            }

            TEST_METHOD(Scene_Update_PassesDeltaTimeToEnemies)
            {
                FakeScene scene;
                scene.addEnemiesResult = true;
                scene.addGUIResult = true;
                scene.addObjectsResult = true;
                scene.addForeGroundObjectsResult = true;

                Assert::IsTrue(scene.Initialise());

                scene.Update(0.66f);

                for (auto& [_, enemy] : scene.m_enemies)
                {
                    if (!enemy)
                        continue;

                    if (!enemy->GetActive())
                        continue;

                    auto* fo = dynamic_cast<IFakeObject*>(enemy.get());

                    if (!fo)
                        continue;

                    Assert::AreEqual(0.66f, fo->lastDeltaTime);
                }
            }

            TEST_METHOD(Scene_UpdateGUI_UpdatesSprites)
            {
                FakeScene scene;
                scene.addEnemiesResult = true;
                scene.addGUIResult = true;
                scene.addObjectsResult = true;
                scene.addForeGroundObjectsResult = true;

                Assert::IsTrue(scene.Initialise());

                scene.Update(0.66f);

                for (auto& [_, sprite] : scene.m_sprites)
                {
                    if (!sprite)
                        continue;

                    auto* fs = dynamic_cast<FakeSprite*>(sprite.get());

                    if (!fs)
                        continue;

                    Assert::AreEqual(1, fs->updateCount);
                }
            }

            TEST_METHOD(Scene_UpdateGUI_PassesDeltaTimeToSprites)
            {
                FakeScene scene;
                scene.addEnemiesResult = true;
                scene.addGUIResult = true;
                scene.addObjectsResult = true;
                scene.addForeGroundObjectsResult = true;

                Assert::IsTrue(scene.Initialise());

                scene.Update(0.66f);

                for (auto& [_, sprite] : scene.m_sprites)
                {
                    if (!sprite)
                        continue;

                    auto* fs = dynamic_cast<FakeSprite*>(sprite.get());

                    if (!fs)
                        continue;

                    Assert::AreEqual(0.66f, fs->lastDeltaTime);
                }
            }

            TEST_METHOD(Scene_UpdateGUI_UpdatesTexts)
            {
                FakeScene scene;
                scene.addEnemiesResult = true;
                scene.addGUIResult = true;
                scene.addObjectsResult = true;
                scene.addForeGroundObjectsResult = true;

                Assert::IsTrue(scene.Initialise());

                scene.Update(0.66f);

                for (auto& [_, text] : scene.m_texts)
                {
                    if (!text)
                        continue;

                    auto* ft = dynamic_cast<FakeText*>(text.get());

                    if (!ft)
                        continue;

                    Assert::AreEqual(1, ft->updateCount);
                }
            }

            TEST_METHOD(Scene_UpdateGUI_PassesDeltaTimeToTexts)
            {
                FakeScene scene;
                scene.addEnemiesResult = true;
                scene.addGUIResult = true;
                scene.addObjectsResult = true;
                scene.addForeGroundObjectsResult = true;

                Assert::IsTrue(scene.Initialise());

                scene.Update(0.66f);

                for (auto& [_, text] : scene.m_texts)
                {
                    if (!text)
                        continue;

                    auto* ft = dynamic_cast<FakeText*>(text.get());

                    if (!ft)
                        continue;

                    Assert::AreEqual(0.66f, ft->lastDeltaTime);
                }
            }

            // ======================================================
            // Render orchestration
            // ======================================================

            TEST_METHOD(Scene_Render_CallsRendersBackgroundSprite)
            {
                FakeScene scene;
                scene.addEnemiesResult = true;
                scene.addGUIResult = true;
                scene.addObjectsResult = true;
                scene.addForeGroundObjectsResult = true;

                FakeRenderer fr;

                scene.Render(&fr);

                auto* fs = static_cast<FakeSprite*>(scene.m_backgroundSpr.get());

                Assert::IsNotNull(fs);

                Assert::AreEqual(1, fs->renderCount);
            }

            TEST_METHOD(Scene_Render_CallsRendersObjects)
            {
                FakeScene scene;
                scene.addEnemiesResult = true;
                scene.addGUIResult = true;
                scene.addObjectsResult = true;
                scene.addForeGroundObjectsResult = true;

                Assert::IsTrue(scene.Initialise());

                FakeRenderer fr;

                scene.Render(&fr);

                int count = 0;

                for (auto& [_, object] : scene.m_objects)
                {
                    if (!object)
                        continue;

                    if (!object->GetActive())
                        continue;

                    auto* fo = dynamic_cast<IFakeObject*>(object.get());

                    if (!fo)
                        continue;

                    count += fo->renderCount;
                }

                Assert::AreEqual(1, count);
            }

            TEST_METHOD(Scene_Render_CallsRendersEnemies)
            {
                FakeScene scene;
                scene.addEnemiesResult = true;
                scene.addGUIResult = true;
                scene.addObjectsResult = true;
                scene.addForeGroundObjectsResult = true;

                Assert::IsTrue(scene.Initialise());

                FakeRenderer fr;

                scene.Render(&fr);

                for (auto& [_, enemy] : scene.m_enemies)
                {
                    if (!enemy)
                        continue;

                    if (!enemy->GetActive())
                        continue;

                    auto* fo = dynamic_cast<IFakeObject*>(enemy.get());

                    if (!fo)
                        continue;

                    Assert::AreEqual(1, fo->renderCount);
                }
            }

            TEST_METHOD(Scene_Render_CallsRendersGUISprites)
            {
                FakeScene scene;
                scene.addEnemiesResult = true;
                scene.addGUIResult = true;
                scene.addObjectsResult = true;
                scene.addForeGroundObjectsResult = true;

                Assert::IsTrue(scene.Initialise());

                FakeRenderer fr;

                scene.Render(&fr);

                for (auto& [_, sprite] : scene.m_sprites)
                {
                    if (!sprite)
                        continue;

                    auto* fs = dynamic_cast<FakeSprite*>(sprite.get());

                    if (!fs)
                        continue;

                    Assert::AreEqual(1, fs->renderCount);
                }
            }

            TEST_METHOD(Scene_Render_CallsRendersGUIText)
            {
                FakeScene scene;
                scene.addEnemiesResult = true;
                scene.addGUIResult = true;
                scene.addObjectsResult = true;
                scene.addForeGroundObjectsResult = true;

                Assert::IsTrue(scene.Initialise());

                FakeRenderer fr;

                scene.Render(&fr);

                for (auto& [_, text] : scene.m_texts)
                {
                    if (!text)
                        continue;

                    auto* ft = dynamic_cast<FakeText*>(text.get());

                    if (!ft)
                        continue;

                    Assert::AreEqual(1, ft->renderCount);
                }
            }

            TEST_METHOD(Scene_Render_DoesNotCallRenderInactiveObjects)
            {
                FakeScene scene;
                scene.addEnemiesResult = true;
                scene.addGUIResult = true;
                scene.addObjectsResult = true;
                scene.addForeGroundObjectsResult = true;

                Assert::IsTrue(scene.Initialise());

                FakeRenderer fr;

                scene.Render(&fr);

                for (auto& [_, object] : scene.m_objects)
                {
                    if (!object)
                        continue;

                    if (object->GetActive())
                        continue;

                    auto* fo = dynamic_cast<IFakeObject*>(object.get());

                    if (!fo)
                        continue;

                    Assert::AreEqual(0, fo->renderCount);
                }
            }

            TEST_METHOD(Scene_Render_DoesNotCallRenderInactiveEnemies)
            {
                FakeScene scene;
                scene.addEnemiesResult = true;
                scene.addGUIResult = true;
                scene.addObjectsResult = true;
                scene.addForeGroundObjectsResult = true;

                Assert::IsTrue(scene.Initialise());

                FakeRenderer fr;

                scene.Render(&fr);

                for (auto& [_, enemy] : scene.m_enemies)
                {
                    if (!enemy)
                        continue;

                    if (enemy->GetActive())
                        continue;

                    auto* fo = dynamic_cast<IFakeObject*>(enemy.get());

                    if (!fo)
                        continue;

                    Assert::AreEqual(0, fo->renderCount);
                }
            }

            // ======================================================
            // Render ordering
            // ======================================================

            TEST_METHOD(Scene_Render_RendersBackgroundBeforeObjects)
            {
                FakeScene scene;
                scene.addEnemiesResult = true;
                scene.addGUIResult = true;
                scene.addObjectsResult = true;
                scene.addForeGroundObjectsResult = true;

                Assert::IsTrue(scene.Initialise());

                std::vector<std::string> log;
                scene.SetRenderLog(log);

                FakeRenderer fr;

                scene.Render(&fr);

                Assert::IsFalse(log.empty());
                Assert::AreEqual(std::string("BkgSpr"), log.front());
            }

            TEST_METHOD(Scene_Render_RendersObjectsBeforeForeground)
            {
                FakeScene scene;
                scene.addEnemiesResult = true;
                scene.addGUIResult = true;
                scene.addObjectsResult = true;
                scene.addForeGroundObjectsResult = true;

                Assert::IsTrue(scene.Initialise());

                std::vector<std::string> log;
                scene.SetRenderLog(log);

                FakeRenderer fr;

                scene.Render(&fr);

                Assert::IsFalse(log.empty());

                auto Obj = std::find(log.begin(), log.end(), "Obj1");
                auto FgObj = std::find(log.begin(), log.end(), "FgObj2");

                Assert::IsTrue(Obj != log.end());
                Assert::IsTrue(FgObj != log.end());

                Assert::IsTrue(
                    std::distance(log.begin(), Obj) <
                    std::distance(log.begin(), FgObj)
                );
            }

            TEST_METHOD(Scene_Render_RendersEnemysAfterObjects)
            {
                FakeScene scene;
                scene.addEnemiesResult = true;
                scene.addGUIResult = true;
                scene.addObjectsResult = true;
                scene.addForeGroundObjectsResult = true;

                Assert::IsTrue(scene.Initialise());

                std::vector<std::string> log;
                scene.SetRenderLog(log);

                FakeRenderer fr;

                scene.Render(&fr);

                Assert::IsFalse(log.empty());

                auto Obj = std::find(log.begin(), log.end(), "Obj1");
                auto Enmy = std::find(log.begin(), log.end(), "Enmy2");

                Assert::IsTrue(Obj != log.end());
                Assert::IsTrue(Enmy != log.end());

                Assert::IsTrue(
                    std::distance(log.begin(), Obj) <
                    std::distance(log.begin(), Enmy)
                );
            }

            TEST_METHOD(Scene_Render_RendersForegroundBeforeGUI)
            {
                FakeScene scene;
                scene.addEnemiesResult = true;
                scene.addGUIResult = true;
                scene.addObjectsResult = true;
                scene.addForeGroundObjectsResult = true;

                Assert::IsTrue(scene.Initialise());

                std::vector<std::string> log;
                scene.SetRenderLog(log);

                FakeRenderer fr;

                scene.Render(&fr);

                Assert::IsFalse(log.empty());

                auto FgObj = std::find(log.begin(), log.end(), "FgObj2");
                auto Spr = std::find(log.begin(), log.end(), "Spr1");

                Assert::IsTrue(FgObj != log.end());
                Assert::IsTrue(Spr != log.end());

                Assert::IsTrue(
                    std::distance(log.begin(), FgObj) <
                    std::distance(log.begin(), Spr)
                );
            }

            TEST_METHOD(Scene_Render_RendersGUISpritesBeforeGUIText)
            {
                FakeScene scene;
                scene.addEnemiesResult = true;
                scene.addGUIResult = true;
                scene.addObjectsResult = true;
                scene.addForeGroundObjectsResult = true;

                Assert::IsTrue(scene.Initialise());

                std::vector<std::string> log;
                scene.SetRenderLog(log);

                FakeRenderer fr;

                scene.Render(&fr);

                Assert::IsFalse(log.empty());

                auto Spr = std::find(log.begin(), log.end(), "Spr2");
                auto Txt = std::find(log.begin(), log.end(), "Txt1");

                Assert::IsTrue(Spr != log.end());
                Assert::IsTrue(Txt != log.end());

                Assert::IsTrue(
                    std::distance(log.begin(), Spr) <
                    std::distance(log.begin(), Txt)
                );
            }

            // ======================================================
            // Reset behaviour
            // ======================================================

            TEST_METHOD(Scene_ResetScene_ResetsObjects)
            {
               /* FakeScene scene;

                scene.EmplaceObjectOrThrow<FakeDynamicGameObject>("Object1", std::make_shared<FakeSprite>("Obj1"), std::make_shared<BoundingBox<FakeBox>>(), true);

                Assert::AreEqual(std::size_t(1), scene.m_objects.size());

                scene.m_objects*/
            }

            TEST_METHOD(Scene_ResetScene_ResetsEnemies)
            {

            }

            TEST_METHOD(Scene_ResetScene_RemovesSpawnedObjects)
            {

            }

            TEST_METHOD(Scene_ResetScene_ClearsSpawnedObjectKeyList)
            {

            }

            TEST_METHOD(Scene_ResetScene_DoesNotRemoveNonSpawnedObjects)
            {

            }


            // ======================================================
            // GetByName behaviour
            // ======================================================

            TEST_METHOD(Scene_GetObjectByName_WhenObjectExists_ReturnsObject)
            {

            }

            TEST_METHOD(Scene_GetObjectByName_WhenObjectDoesNotExist_ReturnsNullptr)
            {

            }

            TEST_METHOD(Scene_GetEnemyByName_WhenEnemyExists_ReturnsEnemy)
            {

            }

            TEST_METHOD(Scene_GetEnemyByName_WhenEnemyDoesNotExist_ReturnsNullptr)
            {

            }
        };
    }
}