#include "Grid.h"
#include <iostream>
#include <random>

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
		for (size_t i{ 0 }; i < m_Cells.size(); ++i)
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
		float cellX{ std::floor(xPos / m_CellSize) };
		float cellY{ std::floor(yPos / m_CellSize) };
		float cellHalf{ m_CellSize / 2.f };
		glm::vec2 CellCenter{ cellX * m_CellSize + cellHalf,cellY * m_CellSize + cellHalf };
		return CellCenter;
	}
	glm::vec2 Grid::GetCellTopLeft(const float xPos, const float yPos,MovementDirectionComponent::MovementDirection moveDir)
	{
		switch (moveDir)
		{
		case MovementDirectionComponent::MovementDirection::North:
			{
			float cellX{ std::floor(xPos / m_CellSize) };
			float cellY{ std::floor(yPos / m_CellSize) };
			glm::vec2 CellCenter{ cellX * m_CellSize,cellY * m_CellSize };
			return CellCenter;
			}
			break;
		case MovementDirectionComponent::MovementDirection::East:
			{
			float cellX{ std::ceil(xPos / m_CellSize) };
			float cellY{ std::floor(yPos / m_CellSize) };
			glm::vec2 CellCenter{ cellX * m_CellSize,cellY * m_CellSize };
			return CellCenter;
			}
			break;

		case MovementDirectionComponent::MovementDirection::South:
			{
			float cellX{ std::floor(xPos / m_CellSize) };
			float cellY{ std::ceil(yPos / m_CellSize) };
			glm::vec2 CellCenter{ cellX * m_CellSize,cellY * m_CellSize };
			return CellCenter;
			}
			break;
		case MovementDirectionComponent::MovementDirection::West:
			{
			float cellX{ std::floor(xPos / m_CellSize) };
			float cellY{ std::floor(yPos / m_CellSize) };
			glm::vec2 CellCenter{ cellX * m_CellSize,cellY * m_CellSize };
			return CellCenter;
			}
			break;
		case MovementDirectionComponent::MovementDirection::None: 
		{
			float cellX{ std::floor(xPos / m_CellSize) };
			float cellY{ std::floor(yPos / m_CellSize) };
			glm::vec2 CellCenter{ cellX * m_CellSize,cellY * m_CellSize };
			return CellCenter;
		}
			break;
		default: ;
		}
		float cellX{ std::floor(xPos / m_CellSize) };
		float cellY{ std::floor(yPos / m_CellSize) };
		glm::vec2 CellCenter{ cellX * m_CellSize,cellY * m_CellSize };
		return CellCenter;
	}

	bool Grid::IsNearCellCenter(float radius, float xPos, float yPos)
	{
		std::cout << "X: is " << xPos << '\n';
		std::cout << "Y is: " << yPos << '\n';
		glm::vec2 currentCellCenter = GetCellCenter(xPos, yPos);
		std::cout << "CellCenterX is " << currentCellCenter.x << '\n';
		std::cout << "CellCenterY is " << currentCellCenter.y << '\n';
		glm::vec2 differential{ currentCellCenter.x - xPos,currentCellCenter.y - yPos };
		float distance = glm::dot(differential, differential);
		if (distance * distance < radius * radius)
		{
			return true;
		}return false;
	}
	bool Grid::IsNearCellTopLeft(const float radius,const float xPos, const float yPos)
	{
		std::cout << "X: is " << xPos << '\n';
		std::cout << "Y is: " << yPos << '\n';
		glm::vec2 currentCellCenter = GetCellTopLeft(xPos, yPos, MovementDirectionComponent::MovementDirection::None);
		std::cout << "CellCenterX is " << currentCellCenter.x << '\n';
		std::cout << "CellCenterY is " << currentCellCenter.y << '\n';
		glm::vec2 differential{ currentCellCenter.x - xPos,currentCellCenter.y - yPos };
		float distance = glm::dot(differential, differential);
		if (distance * distance < radius * radius)
		{
			return true;
		}return false;
	}

	Grid::Cell* Grid::GetCellFromIndex(const size_t index)
	{
		if (index >= m_Cells.size())
		{
			return nullptr;
		}
		if (&m_Cells[index] != nullptr)
		{
			std::cout << "Index is : " << m_Cells[index].index << ", Pos is: " << m_Cells[index].location.x << ", " << m_Cells[index].location.x << '\n';
			return &m_Cells[index];
		}
		return nullptr;
		
	}

	int Grid::GetIndexFromPos(const float x, const float y)
	{
		const float cellX{ std::floor(x / m_CellSize) };
		const float cellY{ std::floor(y / m_CellSize) };
		const int index =  static_cast<int>( cellX + (cellY -1) * static_cast<float>(m_Cols));
		return index;
	}

	std::vector<GameObject*> Grid::GetItems()
	{
		return m_GameObjects;
	}

	void Grid::AddGameObj(GameObject* go)
	{
		m_GameObjects.push_back(go);
	}

	void Grid::DistributeItems()
	{
		std::random_device rd;
		std::mt19937 generator(rd());
		std::uniform_int_distribution<int> distribution(0, static_cast<int>(m_Cells.size() -1));
		std::vector<int> randomNumbers;
		for (auto obj : m_GameObjects)
		{
			int num;
			do
			{
				num = distribution(generator);
			} while (std::ranges::find(randomNumbers, num) != randomNumbers.end());
			randomNumbers.push_back(num);
			const auto cell = GetCellFromIndex(num);
			float offset{ 2.5f };
			obj->SetPosition(cell->location.x + offset, cell->location.y + offset );
		}
	}
}

