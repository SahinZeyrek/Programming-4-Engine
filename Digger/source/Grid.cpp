#include "Grid.h"
#include <iostream>
namespace dae
{
	Grid::Grid(int rows, int cols, int cellsize)
	{
		m_Rows = rows;
		m_Cols = cols;
		m_CellSize = cellsize;
		for (float i = 0; i < m_Rows; ++i)
		{
			for (float j = 0; j < m_Cols; ++j)
			{
				Cell currentPoint{ m_CellSize * i, m_CellSize * j + m_ScreenOffset,m_CellSize };
				currentPoint.index = static_cast<int>(j + i * static_cast<float>(m_Cols));
				m_Cells.push_back(currentPoint);
			}
		}
	}

	Grid::Grid(int rows, int cols, int cellsize, const std::string& gridStructure)
	{
		m_Rows = rows;
		m_Cols = cols;
		m_CellSize = cellsize;
		for (float i = 0; i < m_Cols; ++i)
		{
			for (float j = 0; j < m_Rows; ++j)
			{
				Cell currentPoint{ m_CellSize * j, m_CellSize * i + m_ScreenOffset,m_CellSize };
				currentPoint.index = static_cast<int>(j + i * static_cast<float>(m_Rows));
				std::cout << "index : " << currentPoint.index << '\n';
				m_Cells.push_back(currentPoint);
			}
		}

		for (int i{ 0 }; i < m_Cells.size(); ++i)
		{
			switch (gridStructure[i])
			{
			case '#':
				m_Cells[i].isActive = false;
				break;
			case 'o':
				m_Cells[i].isActive = true;
				break;
			default:
				break;
			}
		}
	}

	void Grid::Init()
	{

	}
	glm::vec2 Grid::GetCellCenter(const float xPos, const float yPos)
	{
		float cellX{ std::ceil(xPos / m_CellSize) };
		float cellY{ std::ceil(yPos / m_CellSize) };
		float cellHalf{ m_CellSize / 2.f };
		glm::vec2 CellCenter{ cellX * m_CellSize + cellHalf,cellY * m_CellSize + cellHalf };
		return CellCenter;
	}
	bool Grid::IsNearCellCenter(float radius, float xPos, float yPos)
	{
		glm::vec2 currentCellCenter = GetCellCenter(xPos, yPos);
		glm::vec2 differntial{ currentCellCenter.x - xPos,currentCellCenter.y - yPos };
		float distance = glm::dot(differntial, differntial);
		if (distance * distance < radius * radius)
		{
			return true;
		}return false;
	}
}

