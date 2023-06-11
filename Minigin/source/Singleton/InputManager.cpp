#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <xinput.h>
#include <SDL.h>
#include "InputManager.h"/*
#include "backends/imgui_impl_sdl2.h"*/


bool dae::InputManager::ProcessInput()
{
	if (!m_CommandsBuffer.empty())
	{
		m_CommandsBuffer.clear();
	}
	if (!m_kbCommandsBuffer.empty())
	{
		m_kbCommandsBuffer.clear();
	}
		if (!m_Commands.empty())
		{
			for (auto& [key, command] : m_Commands)
			{
				// nested pair, key.first.first == index
				// key.second == inputcondition
				// key.first.second == button
				std::unique_ptr<Controller>& controller = m_Controllers[key.first.first];
				switch (key.second)
				{
				case inputCondition::Press:
				{
					if (controller->IsDown(key.first.second))
					{
						command->Execute();
					}
					break;
				}
				case inputCondition::Hold:
				{
					if (controller->IsPressed(key.first.second))
					{
						command->Execute();
					}
					break;
				}

				case inputCondition::Release:
				{
					if (controller->IsUp(key.first.second))
					{
						command->Execute();
					}
					break;
				}
				default:
					break;
				}
			}

		}
		for (auto& controller : m_Controllers)
		{
			controller->Update();
		}
		if (!m_kbCommands.empty())
		{
			for (auto& [key, command] : m_kbCommands)
			{
				switch (key.second)
				{

				case inputCondition::Press:
				{
					if (m_Keyboard->IsDown(key.first))
					{
						command->Execute();
					}
					break;
				}
				case inputCondition::Hold:
				{
					if (m_Keyboard->IsPressed(key.first))
					{
						command->Execute();
					}
					break;
				}
				case inputCondition::Release:
				{
					if (m_Keyboard->IsUp(key.first))
					{
						command->Execute();
					}
					break;
				}
				default:
					break;
				}

			}
		}
	
	m_Keyboard->Update();
	// KB
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}/*
		ImGui_ImplSDL2_ProcessEvent(&e);*/
		// etc...
	}

	return true;
}

void dae::InputManager::Clear()
{
	m_kbCommandsBuffer = std::move(m_kbCommands);
	m_kbCommands = KeyboardCommandsMap();
	m_CommandsBuffer = std::move(m_Commands);
	m_CommandsBuffer = ControllerCommandsMap();
}

void dae::InputManager::AddMapping(unsigned int index, std::unique_ptr<Command> command, Controller::ControllerButton button, inputCondition condition)
{
	ControllerKey controllerKey{ index,button };
	m_Commands.insert({ std::make_pair(controllerKey,condition), std::move(command) });

}

void dae::InputManager::AddKeyboardMapping(std::unique_ptr<Command> command, SDL_Scancode kbInputs, inputCondition condition)
{
	m_kbCommands.insert({ std::make_pair(kbInputs,condition),std::move(command) });
}
