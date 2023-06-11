#pragma once
#include "Singleton.h"
#include <map>
#include <vector>
#include <functional>
#include <SDL.h>
#include <memory>
#include "Command.h"
#include "Keyboard.h"
#include "Controller.h"
namespace dae
{


	class InputManager final : public Singleton<InputManager>
	{
	public: enum class inputCondition
	{
		Hold, Press, Release
	};
	private:
		using ControllerKey = std::pair<unsigned int, Controller::ControllerButton>;
		/*struct ControllerKeyHash {
			size_t operator()(const ControllerKey& ck) const
			{
				return std::hash<unsigned int>{}(ck.first);

			}
		};*/
		using ControllerCommandsMap = std::map < std::pair<ControllerKey, inputCondition>, std::unique_ptr<Command>>;
		using KeyboardCommandsMap = std::map<std::pair<SDL_Scancode,inputCondition>, std::unique_ptr<Command>>;
		ControllerCommandsMap m_Commands{};
		ControllerCommandsMap m_CommandsBuffer{};
		KeyboardCommandsMap m_kbCommands{};
		KeyboardCommandsMap m_kbCommandsBuffer{};
		std::vector<std::unique_ptr<Controller>> m_Controllers{};
		std::unique_ptr<Keyboard> m_Keyboard;
		bool m_CanProcess{ true };
	public:
		InputManager()
		{
			m_Keyboard = std::make_unique<Keyboard>();
		}
		bool ProcessInput();
		void Clear();
		void AddMapping(unsigned int index, std::unique_ptr<Command> command, Controller::ControllerButton button,inputCondition condition);
		void AddKeyboardMapping(std::unique_ptr<Command> command, SDL_Scancode kbInputs,inputCondition condition);
		void AddController(std::unique_ptr<Controller> cont) { m_Controllers.emplace_back(std::move(cont)); }
		void SetCanProcess(bool canProcess) { m_CanProcess = canProcess; }
	};

}
