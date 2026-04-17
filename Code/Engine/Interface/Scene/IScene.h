#pragma once

#include "../Collisions/IBoundingVolume.h"
#include "../Drawables/ISprite.h"
#include "../UI/IText.h"
#include "../Renderer/IRenderer.h"
#include "../../../GameObjects/Enemy.h"
#include "../../../GameObjects/GameObject.h"
#include "../../../Utilities/Utils.h"
#include <array>
#include <map>
#include <memory>
#include <vector>
#include <string>
#include <type_traits>
#include <utility>

class IScene
{
public:
	virtual ~IScene() = default;

	bool Initialise();

	virtual void Update(float deltaTime);
	virtual void Render(IRenderer* renderer);
	virtual void ResetScene();

	virtual void CheckIsInView();

	virtual void SpawnGameObjectAt(const std::string& id, std::shared_ptr<GameObject> obj, const Vector2f& pos) = 0;

	[[nodiscard]] GameObject* GetObjectByName(const std::string& name);
	[[nodiscard]] Enemy* GetEnemyByName(const std::string& name);

	[[nodiscard]] ISprite* GetGUISpriteByName(const std::string& name);
	[[nodiscard]] IText* GetGUITextByName(const std::string& name);

protected:

	virtual bool AddEnemies() = 0;
	virtual bool AddGUI() = 0;
	virtual bool AddObjects() = 0;
	virtual bool AddForeGroundObjects() = 0;

	template <class T, class... Args>
	void EmplaceEnemyOrThrow(const std::string& id, Args&&... args)
	{
		EmplaceSharedOrThrow<decltype(m_enemies), T>(m_enemies, id, std::forward<Args>(args)...);
	}

	template <class T, class... Args>
	void EmplaceObjectOrThrow(const std::string& id, Args&&... args)
	{
		EmplaceSharedOrThrow<decltype(m_objects), T>(m_objects, id, std::forward<Args>(args)...);
	}

	template <class T, class... Args>
	void EmplaceGUISpriteOrThrow(const std::string& id, Args&&... args)
	{
		EmplaceSharedOrThrow<decltype(m_sprites), T>(m_sprites, id, std::forward<Args>(args)...);
	}

	template <class T, class... Args>
	void EmplaceGUITextOrThrow(const std::string& id, Args&&... args)
	{
		EmplaceSharedOrThrow<decltype(m_texts), T>(m_texts, id, std::forward<Args>(args)...);
	}

private:

// Generic "emplace-or-throw" for maps with std::string -> std::shared_ptr<U>
	template <class Map, class T, class... CtorArgs>
	void EmplaceSharedOrThrow(Map& m, const std::string& id, CtorArgs&&... args)
	{
		using key_t = typename std::remove_reference_t<Map>::key_type;
		using mapped_t = typename std::remove_reference_t<Map>::mapped_type;
		static_assert(std::is_same_v<key_t, std::string>, "Map key_type must be std::string");
		static_assert(std::is_same_v<mapped_t, std::shared_ptr<typename mapped_t::element_type>>,
			"Map mapped_type must be std::shared_ptr<U>");

		using U = typename mapped_t::element_type;
		static_assert(std::is_base_of_v<U, T> || std::is_same_v<U, T>,
			"T must be (or derive from) the map's element type");

		// Optional pre-check to avoid constructing on duplicates
#if __cpp_lib_unordered_map_contains || __cpp_lib_map_contains
		if (m.contains(id)) {
#else
		if (m.find(id) != m.end()) {
#endif
			THROW_IF_FALSE_MSG(false, "Key '{}' already exists", id);
		}

		auto ptr = std::make_shared<T>(std::forward<CtorArgs>(args)...);
		auto [it, inserted] = m.emplace(id, std::move(ptr));
		THROW_IF_FALSE_MSG(inserted, "Key '{}' already exists", id);
		}


protected:

	virtual void UpdateGUI(float deltaTime) = 0;
	virtual void RenderGUI(IRenderer* renderer);

	std::shared_ptr<ISprite> m_backgroundSpr;
	std::shared_ptr<IBoundingBox> m_foregroundBox;
	std::map<std::string, std::shared_ptr<IText>> m_texts;
	std::map<std::string, std::shared_ptr<ISprite>> m_sprites;
	std::vector<std::string> m_spawnedObjKeys;
	std::map<std::string, std::shared_ptr<Enemy>> m_enemies;
	std::map<std::string, std::shared_ptr<GameObject>> m_objects;
};