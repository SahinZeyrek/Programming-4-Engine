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
#include "AchievementManager.h"
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
#include <iostream>
#include "WinGameAch.h"






using namespace dae;

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");


	GameObject* pBackground = new GameObject();
	RenderTextureComponent* rt_Background = new RenderTextureComponent(pBackground, nullptr);
	pBackground->AddComponent(rt_Background);
	pBackground->GetComponent<RenderTextureComponent>()->SetTexture("Level1 Background.png");
	pBackground->SetPosition(0, 50);
	scene.Add(pBackground);
#pragma region Players
	auto pBigTom = new GameObject();
	auto rtu_FunnyMan = new RenderTextureComponent(pBigTom, nullptr);
	pBigTom->AddComponent(rtu_FunnyMan);
	pBigTom->AddComponent(new HealthComponent(pBigTom, 3, 25));
	pBigTom->AddComponent(new ScoreComponent(pBigTom, 0));
	pBigTom->GetComponent<RenderTextureComponent>()->SetTexture("funny-man.tga");
	pBigTom->SetPosition(216, 180);
	pBigTom->SetSpeed(150.f);
	scene.Add(pBigTom);

	auto pTinyTom = new GameObject();
	auto rtu_FunnyTinyMan = new RenderTextureComponent(pTinyTom, nullptr);
	auto tinyTomHealth = new HealthComponent(pTinyTom, 3, 20);
	pTinyTom->AddComponent(tinyTomHealth);
	pTinyTom->AddComponent(rtu_FunnyTinyMan);
	pTinyTom->AddComponent(new ScoreComponent(pTinyTom, 0));
	pTinyTom->GetComponent<RenderTextureComponent>()->SetTexture("Digger.png");
	pTinyTom->SetPosition(150, 120);
	pTinyTom->SetSpeed(300.f);
	scene.Add(pTinyTom);

#pragma endregion Players

	auto player1LivesUI = new GameObject();
	player1LivesUI->SetPosition(10, 5);

	auto pFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 14);
	auto renderLives = new RenderTextComponent(player1LivesUI, " ", pFont);
	player1LivesUI->AddComponent(renderLives);

	auto healthUIComp = new UIComponent(player1LivesUI, pTinyTom->GetComponent<HealthComponent>());
	player1LivesUI->AddComponent(healthUIComp);

	scene.Add(player1LivesUI);

	auto player1ScoreUI = new GameObject();
	player1ScoreUI->SetPosition(10, 35);

	auto renderScore = new RenderTextComponent(player1ScoreUI, " ", pFont);
	player1ScoreUI->AddComponent(renderScore);

	auto scoreUIComp = new UIComponent(player1ScoreUI, pTinyTom->GetComponent<ScoreComponent>());
	player1ScoreUI->AddComponent(scoreUIComp);

	scene.Add(player1ScoreUI);




	auto player2HealthUI = new GameObject();
	player2HealthUI->SetPosition(80, 5);

	player2HealthUI->AddComponent(new RenderTextComponent(player2HealthUI, " ", pFont));

	player2HealthUI->AddComponent(new UIComponent(player2HealthUI, pBigTom->GetComponent<HealthComponent>()));

	scene.Add(player2HealthUI);

	auto player2ScoreUI = new GameObject();
	player2ScoreUI->SetPosition(80, 35);

	player2ScoreUI->AddComponent(new RenderTextComponent(player2ScoreUI, " ", pFont));

	player2ScoreUI->AddComponent(new UIComponent(player2ScoreUI, pBigTom->GetComponent<ScoreComponent>()));

	scene.Add(player2ScoreUI);
	std::unique_ptr<WinGameAch> winGameAch = std::make_unique<WinGameAch>();
	auto ach = AchievementManager::GetInstance().AddAchievement(std::move(winGameAch));
	pTinyTom->GetComponent<ScoreComponent>()->BindOnScoreChanged(ach);
	pBigTom->GetComponent<ScoreComponent>()->BindOnScoreChanged(ach);


	//pGameObj = new GameObject();
	//auto renderText = new RenderTextComponent(pGameObj, " ", pFont);
	//pGameObj->AddComponent(renderText);
	//auto fps_Counter = new FPSComponent(pGameObj);
	//pGameObj->AddComponent(fps_Counter);
	//pGameObj->SetPosition(10, 5);
	//scene.Add(pGameObj);

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

	std::unique_ptr<AddScoreCommand> addScoreBigTom = std::make_unique<AddScoreCommand>(pBigTom);
	InputManager::GetInstance().AddMapping(0, std::move(addScoreBigTom), Controller::ControllerButton::ButtonX);

	//--------------------------------------------
	// KEYBOARD
	//--------------------------------------------
#pragma region MOVE COMMANDS
	std::unique_ptr<MoveCommand> kbmoveLeftCommand = std::make_unique<MoveCommand>(pTinyTom, glm::vec3{ 1,0,0 });
	InputManager::GetInstance().AddKeyboardMapping(std::move(kbmoveLeftCommand), SDL_SCANCODE_A);

	std::unique_ptr<MoveCommand> kbmoveUpCommand = std::make_unique<MoveCommand>(pTinyTom, glm::vec3{ 0,1,0 });
	InputManager::GetInstance().AddKeyboardMapping(std::move(kbmoveUpCommand), SDL_SCANCODE_W);

	std::unique_ptr<MoveCommand> kbmoveDownCommand = std::make_unique<MoveCommand>(pTinyTom, glm::vec3{ 0,-1,0 });
	InputManager::GetInstance().AddKeyboardMapping(std::move(kbmoveDownCommand), SDL_SCANCODE_S);

	std::unique_ptr<MoveCommand> kbmoveRightCommand = std::make_unique<MoveCommand>(pTinyTom, glm::vec3{ -1,0,0 });
	InputManager::GetInstance().AddKeyboardMapping(std::move(kbmoveRightCommand), SDL_SCANCODE_D);
#pragma endregion MOVE COMMANDS

	std::unique_ptr<KillCommand> kbDamageTinyTom = std::make_unique<KillCommand>(pTinyTom);
	InputManager::GetInstance().AddKeyboardMapping(std::move(kbDamageTinyTom), SDL_SCANCODE_R);

	std::unique_ptr<AddScoreCommand> kbAddScoreTinyTom = std::make_unique<AddScoreCommand>(pTinyTom);
	InputManager::GetInstance().AddKeyboardMapping(std::move(kbAddScoreTinyTom), SDL_SCANCODE_Q);



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