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

	bool AddEnemies() override { return false; }
	bool AddGUI() override { return false; }
	bool AddObjects() override { return false; }
	bool AddForeGroundObjects() override { return false; }

	void UpdateGUI(float deltaTime) override {}

public:

	bool CheckIsInViewIsCalled = false;
};