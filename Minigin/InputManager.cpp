#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <xinput.h>
#include <SDL.h>
#include "InputManager.h"
#include "backends/imgui_impl_sdl2.h"


bool dae::InputManager::ProcessInput()
{
	for (auto& controller : m_Controllers)
	{
		controller->Update();
	}
	for (auto& [key,command] : m_Commands)
	{
		std::unique_ptr<Controller>& controller = m_Controllers[key.first];
		if (controller->IsPressed(key.second))
		{
			command->Execute();
		}
	}
	for (auto& [key, command] : m_kbCommands)
	{
		if (SDL_GetKeyboardState(nullptr)[key])
		{
			command->Execute();
		}
	}

	// KB
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		ImGui_ImplSDL2_ProcessEvent(&e);
		// etc...
	}

	return true;
}

void dae::InputManager::AddMapping(unsigned int index, std::unique_ptr<Command> command, Controller::ControllerButton button)
{
	ControllerKey controllerKey{ index,button };
	m_Commands.insert({ controllerKey, std::move(command) });

}

void dae::InputManager::AddKeyboardMapping(std::unique_ptr<Command> command, SDL_Scancode kbInputs)
{
	m_kbCommands.insert({ kbInputs,std::move(command) });
}
