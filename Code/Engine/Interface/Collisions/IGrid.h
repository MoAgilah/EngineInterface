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
		int x = 0;
		int begin = x;

		Vector2f pos(m_grid.front()->GetBoundingBox()->GetExtents());
		m_grid[x]->SetPosition(pos);

		for (x = x + 1; x < 313; x++)
		{
			pos = Vector2f(pos.x + (m_grid.front()->GetBoundingBox()->GetExtents().x * 2), pos.y);
			m_grid[x]->SetPosition(pos);
		}

		//remaining rows
		for (int i = 0; i < 14; i++)
		{
			pos = Vector2f(m_grid[begin]->GetPosition().x, m_grid[begin]->GetPosition().y + (m_grid.front()->GetBoundingBox()->GetExtents().y * 2));
			m_grid[x]->SetPosition(pos);
			begin = x;

			int val = 2 + i;

			for (x = x + 1; x < 313 * val; x++)
			{
				pos = Vector2f(pos.x + (m_grid.front()->GetBoundingBox()->GetExtents().x * 2), pos.y);
				m_grid[x]->SetPosition(pos);
			}
		}

		for (auto tile : m_grid)
		{
			tile->GetBoundingBox()->Update(tile->GetPosition());
		}

	}

	int m_rows = 0;
	int m_columns = 0;
	std::vector<std::shared_ptr<ITile>> m_grid;
};