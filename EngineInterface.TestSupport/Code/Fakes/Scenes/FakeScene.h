#pragma once

#include <Engine/Interface/Scene/IScene.h>

class FakeScene : public IScene
{
public:
	void CheckIsInView() override
	{
		CheckIsInViewIsCalled = true;
	}

	void SpawnGameObjectAt(const std::string& id, std::shared_ptr<GameObject> obj, const Vector2f& pos) override {}

protected:

	bool AddEnemies() override {}
	bool AddGUI() override {}
	bool AddObjects() override {}
	bool AddForeGroundObjects() override {}

	void UpdateGUI(float deltaTime) override {}

public:

	bool CheckIsInViewIsCalled = false;
};