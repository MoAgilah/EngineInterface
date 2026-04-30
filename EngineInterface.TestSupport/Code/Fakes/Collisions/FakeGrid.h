#pragma once

#include "FakeTile.h"
#include <Engine/Interface/Collisions/IGrid.h>

class FakeGrid : public IGrid
{
public:
	FakeGrid(int rows, int columns)
		: IGrid(rows, columns)
	{
		Init("", "");
	}

	void Init(const std::string& fontName, const std::string& tileFilePath) override
	{
		m_grid.reserve(m_rows * m_columns);

		for (int y = 0; y < m_rows; ++y)
		{
			for (int x = 0; x < m_columns; ++x)
				m_grid.emplace_back(std::make_shared<FakeTile>(x, y));
		}
	}
};