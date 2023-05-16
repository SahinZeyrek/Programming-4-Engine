#pragma once
#include <vector>
#include <glm/glm.hpp>
namespace dae
{
    class Grid final
    {
        struct Cell
        {
            Cell(float xPos, float yPos, int _cellSize) { location.x = xPos, location.y = yPos,cellSize = _cellSize; };
            bool isActive{ true };
            int cellSize{}, index{};
            glm::vec2 location{};
        };
    public:

        Grid(int rows, int cols, int cellsize);
        void Init();
        glm::vec2 GetCellCenter(float xPos, float yPos);
        bool IsNearCellCenter(float radius,float xPos,float yPos);

        const std::vector<Cell>& GetCells() const { return m_Cells; };
        //------------------------------------------------
        // RULE OF FIVE 
        //------------------------------------------------
        ~Grid() = default;
        Grid(const Grid& other) = delete;
        Grid(Grid&& other) = delete;
        Grid& operator=(const Grid& other) = delete;
        Grid& operator=(Grid&& other) = delete;
    private:
        int m_Rows{}, m_Cols{}, m_CellSize{}, m_ScreenOffset{ 40 };
        std::vector<Cell> m_Cells{};
    };

}


