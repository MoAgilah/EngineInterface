#pragma once

#include "../Drawables/ISprite.h"
#include "../UI/IText.h"
#include "../Renderer/IRenderer.h"
#include "../Collisions/IBoundingVolume.h"
#include "../../../GameObjects/GameObject.h"
#include "../../../GameObjects/Enemy.h"

#include <vector>
#include <array>
#include <map>
#include <memory>

class IScene
{
public:
	virtual ~IScene() = default;

	virtual void Update(float deltaTime);
	virtual void Render(IRenderer* renderer);
	virtual void ResetScene();

	void CheckIsInView();

	virtual void AddEnemies() = 0;
	virtual void AddGUI() = 0;
	virtual void AddObjects() = 0;
	virtual void AddForeGroundSprites() = 0;

	[[nodiscard]] GameObject* GetObjectByName(const std::string& name);
	[[nodiscard]] Enemy* GetEnemyByName(const std::string& name);

protected:

	virtual void UpdateGUI(float deltaTime) = 0;
	virtual void RenderGUI(IRenderer* renderer) = 0;

	std::shared_ptr<ISprite> m_backgroundSpr;
	std::shared_ptr<IBoundingBox> m_foregroundBox;
	std::vector<std::shared_ptr<IText>> m_texts;
	std::vector<std::shared_ptr<ISprite>> m_sprites;
	std::map<std::string, std::shared_ptr<Enemy>> m_enemies;
	std::map<std::string, std::shared_ptr<GameObject>> m_objects;
};