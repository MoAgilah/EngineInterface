#pragma once

#include "ITile.h"
#include "../Renderer/IRenderer.h"
#include "../../Core/Constants.h"
#include "../../Core/GameManager.h"
#include "../../../Utilities/Utils.h"
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

		for (const auto& tile : m_grid)
		{
			CONTINUE_IF_INVALID(tile);

			if (tile->GetActive())
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
		const auto tileSize = m_grid.front()->GetBoundingBox()->GetExtents();
		Vector2f pos = tileSize;

		for (int y = 0; y < m_rows; ++y)
		{
			for (int x = 0; x < m_columns; ++x)
			{
				auto tx = tileSize.x + (x * tileSize.x * 2);
				auto ty = tileSize.y + (y * tileSize.y * 2);

				int idx = y * m_columns + x;

				m_grid[idx]->SetPosition({tx, ty});
			}
		}
	}

	int m_rows = 0;
	int m_columns = 0;
	std::vector<std::shared_ptr<ITile>> m_grid;
};