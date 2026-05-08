#pragma once

#include "ITile.h"
#include "../Renderer/IRenderer.h"
#include "../../Core/Constants.h"
#include "../../Core/GameManager.h"
#include "../../../Utilities/Guards.h"
#include <format>
#include <fstream>
#include <sstream>

class IGrid
{
public:
	IGrid(int rows, int columns)
		: m_rows(rows), m_columns(columns)
	{}

	virtual ~IGrid() = default;

	virtual void Render(IRenderer* renderer)
	{
		if (!GameConstants::DRender)
			return;

		for (size_t i = 0; i < m_grid.size(); ++i)
		{
			auto* tile = m_grid[i].get();

			if (!CheckNotNull(tile,
				std::format("Invalid Pointer 'tile' at index {}", i)))
				continue;

			if (!tile->GetActive())
				continue;

			tile->Render(renderer);
		}
	}

	ITile* GetTile(int x, int y)
	{
		std::string id = std::format("{},{}", x, y);

		auto it = std::find_if(m_grid.begin(), m_grid.end(),
			[id](const auto n) { return n->GetID() == id; });

		if (it != m_grid.end())
			return it->get();

		return nullptr;
	}

	const std::vector<std::shared_ptr<ITile>>& GetGrid() const { return m_grid; }

protected:

	virtual void Init(const std::string& fontName, const std::string& tileFilePaths) = 0;

	void LoadTileTypes(const std::string& tileFilePaths)
	{
		if (!std::filesystem::exists(tileFilePaths))
			throw std::runtime_error("Tile file path does not exist: " + tileFilePaths);

		std::ifstream inFile(tileFilePaths);
		if (!inFile)
			throw std::runtime_error("Failed to open tile file: " + tileFilePaths);

		std::vector<int> types(std::istream_iterator<int>(inFile), {});
		inFile.close();

		if (types.size() != m_grid.size())
			throw std::runtime_error("Mismatch between tile data and grid size.");

		for (size_t i = 0; i < types.size(); ++i)
			m_grid[i]->SetType(types[i]);
	}

	void ArrangeTilePositions()
	{
		if (m_grid.empty())
			return;

		auto* firstTile = m_grid.front().get();

		if (!CheckNotNull(firstTile, "Invalid Pointer 'firstTile'"))
			return;

		const float tileWidth = firstTile->GetTileWidth();
		const float tileHeight = firstTile->GetTileHeight();

		if (m_grid.size() != static_cast<size_t>(m_rows * m_columns))
			throw std::runtime_error("Grid size does not match rows * columns.");

		for (int row = 0; row < m_rows; ++row)
		{
			for (int col = 0; col < m_columns; ++col)
			{
				const size_t index = static_cast<size_t>(row * m_columns + col);

				auto* tile = m_grid[index].get();

				if (!tile)
					continue;

				Vector2f pos(
					(tileWidth * 0.5f) + col * tileWidth,
					(tileHeight * 0.5f) + row * tileHeight
				);

				tile->SetPosition(pos);

				if (auto* box = tile->GetBoundingBox())
					box->Update(pos);
			}
		}
	}

	int m_rows = 0;
	int m_columns = 0;
	std::vector<std::shared_ptr<ITile>> m_grid;
};