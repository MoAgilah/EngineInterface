# EngineInterface

A modern C++ software architecture that demonstrates interface-driven design, backend abstraction and modular system composition.

EngineInterface separates engine systems from backend implementations through stable interface contracts. Rather than depending on a specific graphics library or platform, application code communicates exclusively with abstract interfaces, allowing rendering, input, resources and other services to evolve independently of the technologies used beneath them.

The project focuses on software architecture rather than rendering features, providing a reusable foundation that supports multiple backend implementations while remaining maintainable, extensible and testable.

---

## The Engineering Problem

Many graphics applications become tightly coupled to the frameworks they use. Rendering, input handling, resource management and window creation often depend directly on a single backend, making future changes increasingly difficult as projects grow.

EngineInterface addresses this challenge by introducing a stable abstraction layer between engine systems and their implementations. High-level modules depend on interfaces rather than concrete classes, allowing backend technologies to be replaced without affecting application logic.

---

## Framework Architecture

<p align="center">
  <img alt="EngineInterfaceArchitecture2" src="https://github.com/user-attachments/assets/17fc0ceb-f855-4d62-afee-9d6df5180244" width="600">
</p>

The framework is organised into distinct architectural layers that separate responsibilities and minimise coupling between systems. Engine systems depend only on abstract interfaces, while shared infrastructure provides reusable functionality without introducing backend dependencies. Dedicated testing projects support isolated validation of framework components.

---

## Architecture Goals

The project was designed to demonstrate:

- Interface-driven architecture
- Backend abstraction
- Dependency inversion
- Modular system design
- Layered architecture
- Native testing support
- Reusable C++ components

Although demonstrated through engine development, these architectural principles apply equally to simulation software, technical tooling, robotics, embedded systems and other STEM software applications.

---

## Key Features

- Backend-agnostic C++ interface framework
- Stable abstractions for rendering, input, resources and engine systems
- Clear separation between application logic and backend implementations
- Swappable backend integrations
- Native testing and test-support projects
- Modular architecture designed for extension and long-term maintainability

---

## Technologies & Engineering Practices

### Development

- Modern C++
- Visual Studio
- Git

### Engineering Practices

- Interface-Driven Architecture
- Dependency Inversion
- Backend Abstraction
- Modular Architecture
- Layered Architecture
- RAII
- Native Testing

## Architecture Highlights

- Backend-agnostic interface layer
- Stable contracts between engine systems and implementations
- Modular subsystem organisation
- Native testing support
- Reusable architectural foundation

---

## Engineering Outcome

EngineInterface demonstrates how interface-driven architecture and dependency inversion can be applied to build flexible, maintainable C++ software.

The framework establishes stable contracts across rendering, input, resources and engine systems while isolating backend implementations from higher-level application code. This separation improves maintainability, supports testing and provides a reusable architectural foundation that can evolve alongside future technologies.

---
