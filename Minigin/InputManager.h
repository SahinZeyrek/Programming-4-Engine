#pragma once
#include "Singleton.h"
#include <unordered_map>
#include <vector>
#include <functional>
#include <SDL.h>
#include <memory>
#include "Command.h"
#include "Controller.h"
namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
		using ControllerKey = std::pair<unsigned int, Controller::ControllerButton>;
		struct ControllerKeyHash {
			size_t operator()(const ControllerKey& ck) const
			{
				return std::hash<unsigned int>{}(ck.first);

			}
		};
		using ControllerCommandsMap = std::unordered_map < ControllerKey, std::unique_ptr<Command>, ControllerKeyHash>;
		using KeyboardCommandsMap = std::unordered_map<SDL_Scancode, std::unique_ptr<Command>>;
		ControllerCommandsMap m_Commands{};
		KeyboardCommandsMap m_kbCommands{};
		std::vector<std::unique_ptr<Controller>> m_Controllers{};
	public:
		bool ProcessInput();
		void AddMapping(unsigned int index,std::unique_ptr<Command> command, Controller::ControllerButton button);
		void AddKeyboardMapping(std::unique_ptr<Command> command, SDL_Scancode kbInputs);
		void AddController(std::unique_ptr<Controller> cont) { m_Controllers.emplace_back(std::move(cont)); }
	};

}
