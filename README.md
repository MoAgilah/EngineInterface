# EngineInterface

> A lightweight, reusable C++ interface layer for game/visual apps that lets you plug in different graphics/audio/input backends (e.g., SFML, SDL, etc.) without changing game code.

---

## Why?

Decouple your game/application logic from any specific multimedia library. Write to a stable set of C++ interfaces once; swap the backend later (PC → mobile, SFML → SDL/Vulkan, mock → headless tests) with minimal churn.

---

## Features (current & planned)

- 🧩 **Pure virtual interfaces** for windowing, rendering, input, timing, and resources  
- 🔌 **Backend-agnostic**: implement once per backend (e.g., SFML)  
- 🧪 **Testability**: provide mock implementations for unit tests  
- 🧰 **Gradual adoption**: start with one backend, keep the same game code  
- 📦 **Simple integration**: add as a Git submodule and include the headers  

> A reference backend using **SFML** lives in a separate repo: _SFMLEngine_.

---

## Repository layout
'''
EngineInterface/
├─ Code/ # Header-only or headers+minimal sources for the interfaces
├─ Resources/ # Any shared assets/helpers for samples or tests
├─ EngineInterface.sln # VS solution (if you use MSBuild)
└─ README.md
'''

> The exact headers may evolve, but the design aims to model:
> - `IWindow`, `IRenderer` / `IGraphicsContext`
> - Drawable/resource abstractions (`ITexture`, `ISprite`, `IFont`, `IText`)
> - `IInput` (keyboard/mouse/gamepad), `IAudio` (optional)
> - `ITime/Clock`, `IResourceProvider`
> - A small factory (`IEngineFactory`) that wires up a concrete backend

---

## Getting started

### 1) Add as a submodule

```bash
git submodule add https://github.com/MoAgilah/EngineInterface external/EngineInterface
git commit -m "Add EngineInterface submodule"

