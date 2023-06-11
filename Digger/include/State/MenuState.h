#pragma once
namespace dae
{
	class MenuState
	{
	public:
		virtual void OnEnter() = 0;
		virtual void OnExit() = 0;
		virtual ~MenuState() = default;
	};
	
}


