#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <string>
#include "MovementDirectionComponent.h"
#include "GameObject.h"
#include "Subject.h"
namespace dae
{
    class Grid final: public Observer
    {
        struct Cell
        {
            Cell(float xPos, float yPos, int _cellSize) { location.x = xPos, location.y = yPos,cellSize = _cellSize; };
            bool isActive{ false   };
            int cellSize{}, index{};
            glm::vec2 location{};
        };
    public:
        virtual void OnEvent(Event e) override;

        Grid(int rows, int cols, int cellsize);
        Grid(int rows, int cols, int cellsize, const std::string& gridStructure);
        void Init();
        glm::vec2 GetCellCenter(const float xPos, const float yPos);
        glm::vec2 GetCellTopLeft(const float xPos, const float yPos, MovementDirectionComponent::MovementDirection moveDir );
        bool IsNearCellCenter(const float radius,const float xPos,const float yPos);
        bool IsNearCellTopLeft(const float radius,const float xPos, const float yPos);
        Cell* GetCellFromIndex(const size_t index);
        int GetIndexFromPos(const float x, const float y);
        int GetCellSize() const { return m_CellSize; }
        void AddObserver(Observer* observer);
        void SetAmountItems(size_t amount) { m_AmountItems = amount; }
        std::vector<GameObject*> GetItems();
        std::vector<Cell> GetCells();
        void AddGameObj(GameObject* go);
        void DistributeItems();
        
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
        size_t m_AmountItems;
        std::vector<Cell> m_Cells{};
        std::vector<GameObject*>m_GameObjects;
        Subject m_Subject;
    };

}


