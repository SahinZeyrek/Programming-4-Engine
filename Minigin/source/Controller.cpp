#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include "Controller.h"
#include <xinput.h>
namespace dae
{
	class Controller::ControllerImpl
	{
		XINPUT_STATE previousState{};
		XINPUT_STATE currentState{};

		WORD buttonsPressedThisFrame{};
		WORD buttonsReleasedThisFrame{};

		int index;
	public:
		ControllerImpl(int controllerIndex)
		{
			index = controllerIndex;
			ZeroMemory(&previousState, sizeof(XINPUT_STATE));
			ZeroMemory(&currentState, sizeof(XINPUT_STATE));
		}

		void Update()
		{
			CopyMemory(&previousState, &currentState, sizeof(XINPUT_STATE));
			ZeroMemory(&currentState, sizeof(XINPUT_STATE));
			XInputGetState(index, &currentState);

			auto buttonChanges = currentState.Gamepad.wButtons ^ previousState.Gamepad.wButtons;
			buttonsPressedThisFrame = buttonChanges & currentState.Gamepad.wButtons;
			buttonsReleasedThisFrame = buttonChanges & (~currentState.Gamepad.wButtons);
		}

		bool IsDownThisFrame(unsigned int button) const
		{
			return buttonsPressedThisFrame & button;
		}
		bool IsUpThisFrame(unsigned int button) const
		{
			return buttonsReleasedThisFrame & button;
		}
		bool IsPresssed(unsigned int button) const
		{
			return currentState.Gamepad.wButtons & button;
		}
	};

	void Controller::Update()
	{
		pImpl->Update();
	}

	bool Controller::IsDown(ControllerButton button) const
	{
		return pImpl->IsDownThisFrame(static_cast<unsigned int>(button));
	}

	bool Controller::IsUp(ControllerButton button) const
	{
		return pImpl->IsUpThisFrame(static_cast<unsigned int>(button));
	}

	bool Controller::IsPressed(ControllerButton button) const
	{
		return pImpl->IsPresssed(static_cast<unsigned int>(button));
	}

	Controller::Controller(int controllerIndex)
	{
		pImpl = new ControllerImpl(controllerIndex);
	}

	Controller::~Controller()
	{
		delete pImpl;
	}

}
