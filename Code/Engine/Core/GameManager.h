#pragma once

#include "GameStateMgr.h"
#include "Timer.h"
#include "../Interface/Renderer/ICamera.h"
#include "../Interface/Collisions/ICollisionManager.h"
#include "../Interface/Renderer/IRenderer.h"
#include "../Interface/Scene/IScene.h"
#include "../Input/InputManager.h"
#include "../Resources/FontManager.h"
#include "../Resources/ShaderManager.h"
#include "../Resources/SoundManager.h"
#include "../Resources/TextureManager.h"
#include <array>
#include <memory>

class GameManager
{
public:
	GameManager();
	~GameManager();
	GameManager(const GameManager& obj) = delete;

	static GameManager* Get() { return m_instance; }

	void CheckInView();
	void Update(float deltaTime);
	void Render();

	// Getters
	[[nodiscard]] Timer& GetTimer() noexcept { return m_timer; }
	[[nodiscard]] ICamera* GetCamera() noexcept { return m_camera.get(); }
	[[nodiscard]] InputManager* GetInputManager() noexcept { return m_inputManager.get(); }
	[[nodiscard]] FontManager& GetFontMgr() noexcept { return m_fontManager; }
	[[nodiscard]] ShaderManager& GetShaderMgr() noexcept { return m_shaderManager; }
	[[nodiscard]] SoundManager& GetSoundMgr() noexcept { return m_soundManager; }
	[[nodiscard]] TextureManager& GetTextureMgr() noexcept { return m_texureManager; }
	[[nodiscard]] ICollisionManager* GetCollisionMgr() noexcept { return m_collisionManager.get(); }
	[[nodiscard]] GameStateMgr* GetGameStateMgr() noexcept { return &m_stateManager; }
	[[nodiscard]] IRenderer* GetRenderer() noexcept { return m_renderer.get(); }
	[[nodiscard]] IScene* GetScene() { return m_scene.get(); }

	void InitInputManager(IKeyConverter* converter) { m_inputManager = std::make_shared<InputManager>(converter); }

	// Setters
	void SetICollisionManager(std::shared_ptr<ICollisionManager> colMgr) { m_collisionManager = std::move(colMgr); }
	void SetScene(std::shared_ptr<IScene> scene) { m_scene = std::move(scene); }
	void SetCamera(std::shared_ptr<ICamera> camera) { m_camera = std::move(camera); }
	void SetRenderer(std::shared_ptr<IRenderer> renderer) { m_renderer = std::move(renderer); }

private:
	static GameManager* m_instance;

	Timer								m_timer;
	FontManager							m_fontManager;
	ShaderManager						m_shaderManager;
	SoundManager						m_soundManager;
	TextureManager						m_texureManager;
	GameStateMgr						m_stateManager;

	std::shared_ptr<ICamera>			m_camera;
	std::shared_ptr<InputManager>		m_inputManager;
	std::shared_ptr<IRenderer>			m_renderer;
	std::shared_ptr<ICollisionManager>	m_collisionManager;
	std::shared_ptr<IScene>				m_scene;
};
