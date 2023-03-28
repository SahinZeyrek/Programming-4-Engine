#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "SDL.h"
#include "ResourceManager.h"
#include "RenderTextureComponent.h"
#include "RenderTextComponent.h"
#include "FPSComponent.h"
#include "TextObject.h"
#include "RotatorComponent.h"
#include "Scene.h"
#include "Controller.h"
#include "AllCommands.h"

using namespace dae;
// ADD TextObject to the render component
void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	
	GameObject* pGameObj = new GameObject();
	RenderTextureComponent* rt_Background = new RenderTextureComponent(pGameObj, nullptr);
	pGameObj->AddComponent(rt_Background);
	pGameObj->GetComponent<RenderTextureComponent>()->SetTexture("background.tga");
	scene.Add(pGameObj);

	auto pInvisGameObj = new GameObject();
	pInvisGameObj->SetPosition(216, 180);
	scene.Add(pInvisGameObj);

	auto pBigTom = new GameObject();
	auto rtu_FunnyMan = new RenderTextureComponent(pBigTom, nullptr);
	pBigTom->AddComponent(rtu_FunnyMan);
	pBigTom->GetComponent<RenderTextureComponent>()->SetTexture("funny-man.tga");
	pBigTom->SetPosition(216, 180);
	pBigTom->SetSpeed(150.f);
	scene.Add(pBigTom);

	auto pTinyTom = new GameObject();
	auto rtu_FunnyTinyMan = new RenderTextureComponent(pTinyTom, nullptr);
	pTinyTom->AddComponent(rtu_FunnyTinyMan);
	pTinyTom->GetComponent<RenderTextureComponent>()->SetTexture("funny-tiny-man.tga");
	pTinyTom->SetPosition(150, 120);
	pTinyTom->SetSpeed(300.f);
	scene.Add(pTinyTom);

	pGameObj = new GameObject();
	auto pFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 14);
	auto renderText = new RenderTextComponent(pGameObj, " ", pFont);
	pGameObj->AddComponent(renderText);
	auto fps_Counter = new FPSComponent(pGameObj);
	pGameObj->AddComponent(fps_Counter);
	pGameObj->SetPosition(10, 5);
	scene.Add(pGameObj);

	//--------------------------------------------
	// CONTROLLER
	//--------------------------------------------
	std::unique_ptr<Controller> controller = std::make_unique<Controller>(0);
	InputManager::GetInstance().AddController(std::move(controller));
	std::unique_ptr<MoveUpCommand> moveUpCommand = std::make_unique<MoveUpCommand>(pBigTom);
	InputManager::GetInstance().AddMapping(0, std::move(moveUpCommand), Controller::ControllerButton::DPadUp);

	std::unique_ptr<MoveDownCommand> moveDownCommand = std::make_unique<MoveDownCommand>(pBigTom);
	InputManager::GetInstance().AddMapping(0, std::move(moveDownCommand), Controller::ControllerButton::DPadDown);

	std::unique_ptr<MoveRightCommand> moveRightCommand = std::make_unique<MoveRightCommand>(pBigTom);
	InputManager::GetInstance().AddMapping(0, std::move(moveRightCommand), Controller::ControllerButton::DPadRight);

	std::unique_ptr<MoveLeftCommand> moveLeftCommand = std::make_unique<MoveLeftCommand>(pBigTom);
	InputManager::GetInstance().AddMapping(0, std::move(moveLeftCommand), Controller::ControllerButton::DPadLeft);

	//--------------------------------------------
	// KEYBOARD
	//--------------------------------------------

	std::unique_ptr<MoveLeftCommand> kbmoveLeftCommand = std::make_unique<MoveLeftCommand>(pTinyTom);
	InputManager::GetInstance().AddKeyboardMapping(std::move(kbmoveLeftCommand),SDL_SCANCODE_A);

	std::unique_ptr<MoveUpCommand> kbmoveUpCommand = std::make_unique<MoveUpCommand>(pTinyTom);
	InputManager::GetInstance().AddKeyboardMapping(std::move(kbmoveUpCommand),SDL_SCANCODE_W);

	std::unique_ptr<MoveDownCommand> kbmoveDownCommand = std::make_unique<MoveDownCommand>(pTinyTom);
	InputManager::GetInstance().AddKeyboardMapping(std::move(kbmoveDownCommand), SDL_SCANCODE_S);

	std::unique_ptr<MoveRightCommand> kbmoveRightCommand = std::make_unique<MoveRightCommand>(pTinyTom);
	InputManager::GetInstance().AddKeyboardMapping(std::move(kbmoveRightCommand), SDL_SCANCODE_D);

	// -------------------------------------------
	// TITLE
	// -------------------------------------------
	/*pGameObj = new GameObject();
	pGameObj->SetPosition(80, 20);
	auto pFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto pTO = new TextObject("Programming 4 Assignment", pFont);
	auto rtxt_Title = new RenderTextComponent(pGameObj, pTO);
	pGameObj->AddComponent(rtxt_Title);
	rtxt_Title->GetOwnerPosition();
	scene.Add(pGameObj);*/
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);

	return 0;
}