#include "GridRenderer.h"
#include "Renderer.h"

namespace dae
{
	void GridRenderer::Update()
	{
	}
	void GridRenderer::Render()
	{
		auto& renderer = Renderer::GetInstance();
		auto& cells = m_Grid->GetCells();
		SDL_SetRenderDrawColor(renderer.GetSDLRenderer(), 255, 255, 255, 255);
		for (size_t i = 0; i < m_Grid->GetCells().size(); ++i)
		{
			SDL_Rect rect{ static_cast<int>(cells[i].location.x),
					 static_cast<int>(cells[i].location.y),
					 cells[i].cellSize,
					 cells[i].cellSize };
			if (!cells[i].isActive)
			{
				SDL_SetRenderDrawColor(renderer.GetSDLRenderer(),0, 0, 0, 255);
				SDL_RenderFillRect(renderer.GetSDLRenderer(), &rect);
			}
			else
			{
				SDL_RenderDrawRect(renderer.GetSDLRenderer(), &rect);
			}
			auto cellCenter =m_Grid->GetCellCenter(cells[i].location.x, cells[i].location.y);
			//SDL_SetRenderDrawColor(renderer.GetSDLRenderer(), 0, 1, 0, 1);
			SDL_SetRenderDrawColor(renderer.GetSDLRenderer(), 255, 255, 255, 255);

			SDL_RenderDrawPoint(renderer.GetSDLRenderer(), static_cast<int>(cellCenter.x), static_cast<int>(cellCenter.y));
		}
		SDL_SetRenderDrawColor(renderer.GetSDLRenderer(), 1, 1, 1, 1);
	}

}

