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
#include "UIComponent.h"
#include "Scene.h"
#include "Controller.h"
#include "AllCommands.h"

using namespace dae;

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	
	GameObject* pGameObj = new GameObject();
	RenderTextureComponent* rt_Background = new RenderTextureComponent(pGameObj, nullptr);
	pGameObj->AddComponent(rt_Background);
	pGameObj->GetComponent<RenderTextureComponent>()->SetTexture("background.tga");
	scene.Add(pGameObj);
#pragma region Players
	auto pBigTom = new GameObject();
	auto rtu_FunnyMan = new RenderTextureComponent(pBigTom, nullptr);
	pBigTom->AddComponent(rtu_FunnyMan);
	pBigTom->AddComponent(new HealthComponent(pBigTom, 3, 25));
	pBigTom->GetComponent<RenderTextureComponent>()->SetTexture("funny-man.tga");
	pBigTom->SetPosition(216, 180);
	pBigTom->SetSpeed(150.f);
	scene.Add(pBigTom);

	auto pTinyTom = new GameObject();
	auto rtu_FunnyTinyMan = new RenderTextureComponent(pTinyTom, nullptr);
	auto tinyTomHealth = new HealthComponent(pTinyTom,3,20);
	pTinyTom->AddComponent(tinyTomHealth);
	pTinyTom->AddComponent(rtu_FunnyTinyMan);
	pTinyTom->GetComponent<RenderTextureComponent>()->SetTexture("funny-tiny-man.tga");
	pTinyTom->SetPosition(150, 120);
	pTinyTom->SetSpeed(300.f);
	scene.Add(pTinyTom);

#pragma endregion Players
	auto player1UI = new GameObject();
	player1UI->SetPosition(10, 100);

	auto pFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 14);
	auto renderLives = new RenderTextComponent(player1UI, " ", pFont);
	player1UI->AddComponent(renderLives);

	auto UIComp = new UIComponent(player1UI,pTinyTom);
	player1UI->AddComponent(UIComp);

	scene.Add(player1UI);

	auto player2UI = new GameObject();
	player2UI->SetPosition(10, 150);

	player2UI->AddComponent(new RenderTextComponent(player2UI, " ", pFont));

	player2UI->AddComponent(new UIComponent(player2UI, pBigTom));

	scene.Add(player2UI);

	pGameObj = new GameObject();
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
	std::unique_ptr<MoveCommand> moveUpCommand = std::make_unique<MoveCommand>(pBigTom, glm::vec3{ 0,1,0 });
	InputManager::GetInstance().AddMapping(0, std::move(moveUpCommand), Controller::ControllerButton::DPadUp);

	std::unique_ptr<MoveCommand> moveDownCommand = std::make_unique<MoveCommand>(pBigTom, glm::vec3{ 0,-1,0 });
	InputManager::GetInstance().AddMapping(0, std::move(moveDownCommand), Controller::ControllerButton::DPadDown);

	std::unique_ptr<MoveCommand> moveRightCommand = std::make_unique<MoveCommand>(pBigTom, glm::vec3{ -1,0,0 });
	InputManager::GetInstance().AddMapping(0, std::move(moveRightCommand), Controller::ControllerButton::DPadRight);

	std::unique_ptr<MoveCommand> moveLeftCommand = std::make_unique<MoveCommand>(pBigTom, glm::vec3{ 1,0,0 });
	InputManager::GetInstance().AddMapping(0, std::move(moveLeftCommand), Controller::ControllerButton::DPadLeft);

	std::unique_ptr<KillCommand> damageBigTom = std::make_unique<KillCommand>(pBigTom);
	InputManager::GetInstance().AddMapping(0, std::move(damageBigTom), Controller::ControllerButton::RightShoulder);

	//--------------------------------------------
	// KEYBOARD
	//--------------------------------------------
#pragma region MOVE COMMANDS
	std::unique_ptr<MoveCommand> kbmoveLeftCommand = std::make_unique<MoveCommand>(pTinyTom,glm::vec3{1,0,0});
	InputManager::GetInstance().AddKeyboardMapping(std::move(kbmoveLeftCommand),SDL_SCANCODE_A);

	std::unique_ptr<MoveCommand> kbmoveUpCommand = std::make_unique<MoveCommand>(pTinyTom, glm::vec3{ 0,1,0 });
	InputManager::GetInstance().AddKeyboardMapping(std::move(kbmoveUpCommand),SDL_SCANCODE_W);

	std::unique_ptr<MoveCommand> kbmoveDownCommand = std::make_unique<MoveCommand>(pTinyTom, glm::vec3{ 0,-1,0 });
	InputManager::GetInstance().AddKeyboardMapping(std::move(kbmoveDownCommand), SDL_SCANCODE_S);

	std::unique_ptr<MoveCommand> kbmoveRightCommand = std::make_unique<MoveCommand>(pTinyTom, glm::vec3{ -1,0,0 });
	InputManager::GetInstance().AddKeyboardMapping(std::move(kbmoveRightCommand), SDL_SCANCODE_D);
#pragma endregion MOVE COMMANDS

	std::unique_ptr<KillCommand> kbDamageTinyTom = std::make_unique<KillCommand>(pTinyTom);
	InputManager::GetInstance().AddKeyboardMapping(std::move(kbDamageTinyTom), SDL_SCANCODE_R);
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