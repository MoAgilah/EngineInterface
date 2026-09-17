#pragma once

#include "FakeTile.h"
#include <Engine/Interface/Collisions/IGrid.h>
#include <memory>

class FakeGrid : public IGrid
{
public:
	using IGrid::LoadTileTypes;
	using IGrid::ArrangeTilePositions;

	FakeGrid(int rows, int columns)
		: IGrid(rows, columns)
	{
		Init("", "");
	}

	FakeGrid(int rows, int columns, const std::string& tileFilePath)
		: IGrid(rows, columns), fullInitialisation(true)
	{
		Init("", tileFilePath);


	}

	void SetTileNull(std::size_t index)
	{
		m_grid.at(index) = nullptr;
	}

	void SetTileActive(std::size_t index, bool active)
	{
		m_grid.at(index)->SetActive(active);
	}

	void Init(const std::string& fontName, const std::string& tileFilePath) override
	{
		m_grid.reserve(m_rows * m_columns);

		for (int y = 0; y < m_rows; ++y)
		{
			for (int x = 0; x < m_columns; ++x)
				m_grid.emplace_back(std::make_shared<FakeTile>(x, y));
		}

		if (!fullInitialisation)
			return;

		LoadTileTypes(tileFilePath);
		ArrangeTilePositions();
	}

private:

	bool fullInitialisation = false;
};