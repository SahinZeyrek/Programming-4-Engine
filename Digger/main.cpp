#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "Singleton/SceneManager.h"
#include "Singleton/InputManager.h"
#include "Singleton/AchievementManager.h"
#include "Singleton/ResourceManager.h"
#include "AllComponents.h"
#include "Scene.h"
#include "Controller.h"
#include "AllCommands.h"
#include "WinGameAch.h"
#include "Grid.h"

#include "ServiceLocator.h"
#include "sound/DefaultSoundSystem.h"
#include "sound/LogSoundSys.h"
#include "SoloGameMode.h"
#include "FiniteStateMachine.h"

#include <iostream>

#include "Font.h"

using namespace dae;

namespace dae
{

	void LoadStartScreen()
	{

	}
	void StartScreen(Scene* scene)
	{

#if _DEBUG
		ServiceLocator::RegisterSoundSystem(std::make_unique<LogSoundSys>(std::make_unique<DefaultSoundSystem>()));
#else
		ServiceLocator::RegisterSoundSystem(std::make_unique<DefaultSoundSystem>());
#endif
#pragma region Misc
		ServiceLocator::GetSoundSystem().SetVolume(1.f);

		GameObject* pBackground = new GameObject();
		RenderTextureComponent* rt_Background = new RenderTextureComponent(pBackground, nullptr);
		pBackground->AddComponent(rt_Background);
		pBackground->GetComponent<RenderTextureComponent>()->SetTexture("background_resized.png");
		pBackground->SetPosition(0, 40);
		scene->Add(pBackground);
		GameObject* pTitle = new GameObject();
		auto pFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 100);
		pTitle->AddComponent(new RenderTextComponent(pTitle, " ", pFont));
		pTitle->GetComponent<RenderTextComponent>()->SetText("DIGGER");
		pTitle->SetPosition(100.f, 100.f);
		scene->Add(pTitle);
		GameObject* pHighScoreTitle = new GameObject();
		pHighScoreTitle->AddComponent(new RenderTextComponent(pTitle, " ", pFont));
		pHighScoreTitle->GetComponent<RenderTextComponent>()->SetText("HIGHSCORES");
		pHighScoreTitle->SetPosition(100.f, 100.f);
		pHighScoreTitle->SetIsActive(false);
		scene->Add(pHighScoreTitle);

		auto& fsm = FiniteStateMachine::GetInstance();
		fsm.mainMenuState->SetTitle(pTitle);
		fsm.highscoreState->SetTitle(pHighScoreTitle);
		fsm.Push(fsm.mainMenuState.get());

		auto pTinyFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
		auto& objs = fsm.highscoreState->GetHighScoreObjs();
		objs.clear();

		for (size_t i = 0; i < fsm.highscoreState->GetAmountHighScores(); ++i)
		{
			auto highscore = new GameObject();
			highscore->AddComponent(new RenderTextComponent(highscore, "  ", pTinyFont));
			highscore->SetIsActive(false);
			highscore->SetPosition(200.f, 25.f * static_cast<float>(i) + 200.f);
			fsm.highscoreState->AddHighScoreObj(highscore);
			scene->Add(highscore);
		}
		auto& im = InputManager::GetInstance();
		std::unique_ptr<PopStateCommand> kbPopMenu = std::make_unique<PopStateCommand>();
		im.AddKeyboardMapping(std::move(kbPopMenu), SDL_SCANCODE_ESCAPE, InputManager::inputCondition::Press);
		std::unique_ptr<PushState> kbPushHighScores = std::make_unique<PushState>(FiniteStateMachine::GetInstance().highscoreState.get());
		im.AddKeyboardMapping(std::move(kbPushHighScores), SDL_SCANCODE_P, InputManager::inputCondition::Press);
		std::unique_ptr<SwapSceneCommand> kbStartGame = std::make_unique<SwapSceneCommand>("LevelOne");
		im.AddKeyboardMapping(std::move(kbStartGame), SDL_SCANCODE_RETURN, InputManager::inputCondition::Press);

		//
		//		const std::string gridStructure
		//		{
		//				 "ooooooo####ooooooo##"
		//				 "ooooooo####ooooooo##"
		//				 "ooooooo####ooooooo##"
		//				 "oooo#oo#############"
		//				 "ooooooo####ooooooooo"
		//				 "ooooooo####ooooooooo"
		//				 "#oooooo####oooooooo#"
		//				 "###oooo####oooo#####"
		//				 "ooo############ooooo"
		//				 "oooooo#####ooooooooo"
		//				 "oooooo#####ooooooooo"
		//				 "oooooo#####ooooooooo"
		//				 "oooooo#####ooooooooo"
		//				 "oooooo#####ooooooooo"
		//				 "oooooo#####ooooooooo"
		//				 "oooooo#####ooooooooo"
		//				 "oooooo#####ooooooooo"
		//				 "oooooo#####ooooooooo"
		//				 "o##################o"
		//				 "oooooooooooooooooooo"
		//
		//		};
		//		int rows{ 20 }, cols{ 20 }, cellSize{ 40 };
		//		std::shared_ptr<Grid> pGrid = std::make_shared<Grid>(rows, cols, cellSize, gridStructure);
		//		auto pGridObj = new GameObject();
		//		pGridObj->AddComponent(new GridRenderer(pGridObj, pGrid));
		//		scene->Add(pGridObj);
		//
		//		size_t amountOfItems{ 20 };
		//		for (size_t i{ 0 }; i < amountOfItems; ++i)
		//		{
		//			auto item = new GameObject();
		//			item->AddComponent(new RenderTextureComponent(item, nullptr));
		//			item->GetComponent<RenderTextureComponent>()->SetTexture("emerald.png");
		//			item->AddComponent(new ColliderComponent(item, nullptr, 40.f, 40.f));
		//			item->AddComponent(new ItemComponent(item));
		//			item->AddComponent(new SoundComponent(item, "../Data/EmeraldPickUp.wav", 1.f));
		//			scene->Add(item);
		//			pGrid->AddGameObj(item);
		//		}
		//		pGrid->DistributeItems();
		//
		//#pragma endregion Misc
		//
		//#pragma region Players
		//
		//		auto pBigTom = new GameObject();
		//		auto rtu_FunnyMan = new RenderTextureComponent(pBigTom, nullptr);
		//		pBigTom->AddComponent(rtu_FunnyMan);
		//		pBigTom->AddComponent(new HealthComponent(pBigTom, 5, 3));
		//		pBigTom->AddComponent(new ScoreComponent(pBigTom, 0));
		//		pBigTom->AddComponent(new SoundComponent(pBigTom, "aughh.wav", 1.f));
		//		pBigTom->AddComponent(new SpeedComponent(pBigTom, 100.f));
		//		pBigTom->GetComponent<RenderTextureComponent>()->SetTexture("funny-man.png");
		//		pBigTom->AddComponent(new ColliderComponent(pBigTom, nullptr, 40.f, 40.f));
		//		pBigTom->AddComponent(new EnemyComponent(pBigTom));
		//		pBigTom->SetPosition(240, 200);
		//
		//		scene->Add(pBigTom);
		//
		//		auto pProjectile = new GameObject();
		//		pProjectile->AddComponent(new SpeedComponent(pProjectile, 200.f));
		//		pProjectile->AddComponent(new MovementDirectionComponent(pProjectile));
		//		pProjectile->AddComponent(new RenderTextureComponent(pProjectile, nullptr));
		//		pProjectile->AddComponent(new ColliderComponent(pProjectile, pBigTom, 40.f, 40.f));
		//		pProjectile->GetComponent<RenderTextureComponent>()->SetTexture("Projectile.png");
		//		pProjectile->SetPosition(-100.f, -100.f);
		//		scene-Add(pProjectile);
		//
		//		auto pDigger = new GameObject();
		//		auto diggerTexture = new RenderTextureComponent(pDigger, nullptr);
		//		pDigger->AddComponent(new MovementDirectionComponent(pDigger));
		//		pDigger->AddComponent(new HealthComponent(pDigger, 1, 3));
		//		pDigger->AddComponent(diggerTexture);
		//		pDigger->AddComponent(new GridComponent(pDigger, nullptr));
		//		pDigger->AddComponent(new ScoreComponent(pDigger, 0));
		//		pDigger->AddComponent(new SpeedComponent(pDigger, 100.f));
		//		pDigger->AddComponent(new SoundComponent(pDigger, "aughh.wav", 0.1f));
		//		pDigger->AddComponent(new PlayerComponent(pDigger, { 200.f,120.f }));
		//		pDigger->AddComponent(new ProjectileComponent(pDigger, pProjectile, 5.f));
		//		pDigger->GetComponent<HealthComponent>()->AddObserver(pDigger->GetComponent<PlayerComponent>());
		//		pDigger->GetComponent<RenderTextureComponent>()->SetTexture("Digger.png");
		//		pDigger->GetComponent<ProjectileComponent>()->AddObserver(pBigTom->GetComponent<EnemyComponent>());
		//		pDigger->SetPosition(200, 120);
		//		scene.Add(pDigger);
		//		pBigTom->GetComponent<ColliderComponent>()->SetTarget(pDigger);
		//#pragma endregion Players
		//
		//		auto player1LivesUI = new GameObject();
		//		player1LivesUI->SetPosition(10, 5);
		//
		//		auto pFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 14);
		//		auto renderLives = new RenderTextComponent(player1LivesUI, " ", pFont);
		//		player1LivesUI->AddComponent(renderLives);
		//
		//		auto healthUIComp = new UIComponent(player1LivesUI, pDigger->GetComponent<HealthComponent>());
		//		player1LivesUI->AddComponent(healthUIComp);
		//
		//		scene.Add(player1LivesUI);
		//		pBigTom->GetComponent<EnemyComponent>()->AddObserver(healthUIComp);
		//
		//		auto player1ScoreUI = new GameObject();
		//		player1ScoreUI->SetPosition(10, 35);
		//
		//		auto renderScore = new RenderTextComponent(player1ScoreUI, " ", pFont);
		//		player1ScoreUI->AddComponent(renderScore);
		//
		//		auto scoreUIComp = new UIComponent(player1ScoreUI, pDigger->GetComponent<ScoreComponent>());
		//		player1ScoreUI->AddComponent(scoreUIComp);
		//
		//		scene.Add(player1ScoreUI);
		//
		//		for (size_t i{ 0 }; i < amountOfItems; ++i)
		//		{
		//			pGrid->GetItems()[i]->GetComponent<ColliderComponent>()->SetTarget(pDigger);
		//			pGrid->GetItems()[i]->GetComponent<ItemComponent>()->AddObserver(scoreUIComp);
		//		}
		//
		//
		//
		//		auto player2HealthUI = new GameObject();
		//		player2HealthUI->SetPosition(80, 5);
		//
		//		player2HealthUI->AddComponent(new RenderTextComponent(player2HealthUI, " ", pFont));
		//
		//		player2HealthUI->AddComponent(new UIComponent(player2HealthUI, pBigTom->GetComponent<HealthComponent>()));
		//
		//		scene.Add(player2HealthUI);
		//
		//		auto player2ScoreUI = new GameObject();
		//		player2ScoreUI->SetPosition(80, 35);
		//
		//		player2ScoreUI->AddComponent(new RenderTextComponent(player2ScoreUI, " ", pFont));
		//
		//		player2ScoreUI->AddComponent(new UIComponent(player2ScoreUI, pBigTom->GetComponent<ScoreComponent>()));
		//
		//		scene.Add(player2ScoreUI);
		//		//std::unique_ptr<WinGameAch> winGameAch = std::make_unique<WinGameAch>();
		//		//auto ach = AchievementManager::GetInstance().AddAchievement(std::move(winGameAch));
		//		//pDigger->GetComponent<ScoreComponent>()->BindOnScoreChanged(ach);
		//		//pBigTom->GetComponent<ScoreComponent>()->BindOnScoreChanged(ach);
		//
		//
		//		//pGameObj = new GameObject();
		//		//auto renderText = new RenderTextComponent(pGameObj, " ", pFont);
		//		//pGameObj->AddComponent(renderText);
		//		//auto fps_Counter = new FPSComponent(pGameObj);
		//		//pGameObj->AddComponent(fps_Counter);
		//		//pGameObj->SetPosition(10, 5);
		//		//scene.Add(pGameObj);
		//
		//		auto& inputManager = dae::InputManager::GetInstance();
		//		//--------------------------------------------
		//		// CONTROLLER
		//		//--------------------------------------------
		//		std::unique_ptr<Controller> controller = std::make_unique<Controller>(0);
		//		inputManager.AddController(std::move(controller));
		//		//std::unique_ptr<MoveCommand> moveUpCommand = std::make_unique<MoveCommand>(pBigTom, glm::vec3{ 0,1,0 });
		//		//inputManager.AddMapping(0, std::move(moveUpCommand), Controller::ControllerButton::DPadUp);
		//
		//		//std::unique_ptr<MoveCommand> moveDownCommand = std::make_unique<MoveCommand>(pBigTom, glm::vec3{ 0,-1,0 });
		//		//inputManager.AddMapping(0, std::move(moveDownCommand), Controller::ControllerButton::DPadDown);
		//
		//		//std::unique_ptr<MoveCommand> moveRightCommand = std::make_unique<MoveCommand>(pBigTom, glm::vec3{ -1,0,0 });
		//		//inputManager.AddMapping(0, std::move(moveRightCommand), Controller::ControllerButton::DPadRight);
		//
		//		//std::unique_ptr<MoveCommand> moveLeftCommand = std::make_unique<MoveCommand>(pBigTom, glm::vec3{ 1,0,0 });
		//		//inputManager.AddMapping(0, std::move(moveLeftCommand), Controller::ControllerButton::DPadLeft);
		//
		//		std::unique_ptr<KillCommand> damageBigTom = std::make_unique<KillCommand>(pBigTom);
		//		inputManager.AddMapping(0, std::move(damageBigTom), Controller::ControllerButton::RightShoulder, InputManager::inputCondition::Press);
		//
		//		std::unique_ptr<AddScoreCommand> addScoreBigTom = std::make_unique<AddScoreCommand>(pBigTom);
		//		inputManager.AddMapping(0, std::move(addScoreBigTom), Controller::ControllerButton::ButtonX, InputManager::inputCondition::Press);
		//
		//		//--------------------------------------------
		//		// KEYBOARD
		//		//--------------------------------------------
		//#pragma region MOVE COMMANDS
		//	//--------------------------------------------
		//		std::unique_ptr<StartMovingCommand> kbLeftStart = std::make_unique<StartMovingCommand>(pDigger, pGrid, MovementDirectionComponent::MovementDirection::West);
		//		inputManager.AddKeyboardMapping(std::move(kbLeftStart), SDL_SCANCODE_A, InputManager::inputCondition::Press);
		//
		//		std::unique_ptr<MoveCommand> kbMoveLeftCommand = std::make_unique<MoveCommand>(pDigger, pGrid, MovementDirectionComponent::MovementDirection::West);
		//		inputManager.AddKeyboardMapping(std::move(kbMoveLeftCommand), SDL_SCANCODE_A, InputManager::inputCondition::Hold);
		//
		//		std::unique_ptr<StopMovingCommand> kbLeftEnd = std::make_unique<StopMovingCommand>(pDigger);
		//		inputManager.AddKeyboardMapping(std::move(kbLeftEnd), SDL_SCANCODE_A, InputManager::inputCondition::Release);
		//
		//
		//		//--------------------------------------------
		//
		//		std::unique_ptr<StartMovingCommand> kbUpStart = std::make_unique<StartMovingCommand>(pDigger, pGrid, MovementDirectionComponent::MovementDirection::North);
		//		inputManager.AddKeyboardMapping(std::move(kbUpStart), SDL_SCANCODE_W, InputManager::inputCondition::Press);
		//
		//		std::unique_ptr<MoveCommand> kbMoveUpCommand = std::make_unique<MoveCommand>(pDigger, pGrid, MovementDirectionComponent::MovementDirection::North);
		//		inputManager.AddKeyboardMapping(std::move(kbMoveUpCommand), SDL_SCANCODE_W, InputManager::inputCondition::Hold);
		//
		//		std::unique_ptr<StopMovingCommand> kbUpEnd = std::make_unique<StopMovingCommand>(pDigger);
		//		inputManager.AddKeyboardMapping(std::move(kbUpEnd), SDL_SCANCODE_W, InputManager::inputCondition::Release);
		//
		//
		//		//--------------------------------------------
		//		std::unique_ptr<StartMovingCommand> kbDownStart = std::make_unique<StartMovingCommand>(pDigger, pGrid, MovementDirectionComponent::MovementDirection::South);
		//		inputManager.AddKeyboardMapping(std::move(kbDownStart), SDL_SCANCODE_S, InputManager::inputCondition::Press);
		//
		//		std::unique_ptr<MoveCommand> kbMoveDownCommand = std::make_unique<MoveCommand>(pDigger, pGrid, MovementDirectionComponent::MovementDirection::South);
		//		inputManager.AddKeyboardMapping(std::move(kbMoveDownCommand), SDL_SCANCODE_S, InputManager::inputCondition::Hold);
		//
		//		std::unique_ptr<StopMovingCommand> kbDownEnd = std::make_unique<StopMovingCommand>(pDigger);
		//		inputManager.AddKeyboardMapping(std::move(kbDownEnd), SDL_SCANCODE_S, InputManager::inputCondition::Release);
		//
		//		//--------------------------------------------
		//		std::unique_ptr<StartMovingCommand> kbRightStart = std::make_unique<StartMovingCommand>(pDigger, pGrid, MovementDirectionComponent::MovementDirection::East);
		//		inputManager.AddKeyboardMapping(std::move(kbRightStart), SDL_SCANCODE_D, InputManager::inputCondition::Press);
		//
		//		std::unique_ptr<MoveCommand> kbmoveRightCommand = std::make_unique<MoveCommand>(pDigger, pGrid, MovementDirectionComponent::MovementDirection::East);
		//		inputManager.AddKeyboardMapping(std::move(kbmoveRightCommand), SDL_SCANCODE_D, InputManager::inputCondition::Hold);
		//
		//		std::unique_ptr<StopMovingCommand> kbRightEnd = std::make_unique<StopMovingCommand>(pDigger);
		//		inputManager.AddKeyboardMapping(std::move(kbRightEnd), SDL_SCANCODE_D, InputManager::inputCondition::Release);
		//
		//
		//		//--------------------------------------------
		//#pragma endregion MOVE COMMANDS
		//
		//		std::unique_ptr<KillCommand> kbDamageTinyTom = std::make_unique<KillCommand>(pDigger);
		//		inputManager.AddKeyboardMapping(std::move(kbDamageTinyTom), SDL_SCANCODE_R, InputManager::inputCondition::Press);
		//
		//		std::unique_ptr<AddScoreCommand> kbAddScoreTinyTom = std::make_unique<AddScoreCommand>(pDigger);
		//		inputManager.AddKeyboardMapping(std::move(kbAddScoreTinyTom), SDL_SCANCODE_Q, InputManager::inputCondition::Press);
		//
		//		std::unique_ptr<ShootCommand> kbShoot = std::make_unique<ShootCommand>(pDigger);
		//		inputManager.AddKeyboardMapping(std::move(kbShoot), SDL_SCANCODE_SPACE, InputManager::inputCondition::Press);
		//
		//
		//		// -------------------------------------------
		//		// TITLE
		//		// -------------------------------------------
		//		/*pGameObj = new GameObject();
		//		pGameObj->SetPosition(80, 20);
		//		auto pFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
		//		auto pTO = new TextObject("Programming 4 Assignment", pFont);
		//		auto rtxt_Title = new RenderTextComponent(pGameObj, pTO);
		//		pGameObj->AddComponent(rtxt_Title);
		//		rtxt_Title->GetOwnerPosition();
		//		scene.Add(pGameObj);*/
	}

	void LoadLevel1(Scene* scene)
	{
#if _DEBUG
		ServiceLocator::RegisterSoundSystem(std::make_unique<LogSoundSys>(std::make_unique<DefaultSoundSystem>()));
#else
		ServiceLocator::RegisterSoundSystem(std::make_unique<DefaultSoundSystem>());
#endif
#pragma region Misc
		ServiceLocator::GetSoundSystem().SetVolume(1.f);

		GameObject* pBackground = new GameObject();
		RenderTextureComponent* rt_Background = new RenderTextureComponent(pBackground, nullptr);
		pBackground->AddComponent(rt_Background);
		pBackground->GetComponent<RenderTextureComponent>()->SetTexture("Level1 Background.png");
		pBackground->SetPosition(0, 40);
		scene->Add(pBackground);


		const std::string gridStructure
		{
				 "ooooooo####ooooooo##"
				 "oo####o####ooooooo##"
				 "oo####o####ooooooo##"
				 "oo####o#############"
				 "oo####o####ooooooooo"
				 "oo####o####ooooooooo"
				 "#oooooo####oooooooo#"
				 "###oooo####oooo#####"
				 "oooooooooooooooooooo"
				 "oooooooooooooooooooo"
				 "oooooooooooooooooooo"
				 "oooooooooooooooooooo"
				 "oooooooooooooooooooo"
				 "oooooooooooooooooooo"
				 "oooooooooooooooooooo"
				 "oooooooooooooooooooo"
				 "oooooooooooooooooooo"
				 "oooooooooooooooooooo"
				 "o##################o"
				 "oooooooooooooooooooo"

		};
		int rows{ 20 }, cols{ 20 }, cellSize{ 40 };
		std::shared_ptr<Grid> pGrid = std::make_shared<Grid>(rows, cols, cellSize, gridStructure);
		auto pGridObj = new GameObject();
		pGridObj->AddComponent(new GridRenderer(pGridObj, pGrid));
		scene->Add(pGridObj);

		size_t amountOfItems{ 1 };
		for (size_t i{ 0 }; i < amountOfItems; ++i)
		{
			auto item = new GameObject();
			item->AddComponent(new RenderTextureComponent(item, nullptr));
			item->GetComponent<RenderTextureComponent>()->SetTexture("emerald.png");
			item->AddComponent(new ColliderComponent(item, nullptr, 40.f, 40.f));
			item->AddComponent(new ItemComponent(item));
			item->AddComponent(new SoundComponent(item, "../Data/EmeraldPickUp.wav", 1.f));
			scene->Add(item);
			pGrid->AddGameObj(item);
		}
		pGrid->DistributeItems();
		pGrid->SetAmountItems(amountOfItems);

#pragma endregion Misc

#pragma region Players

		auto pBigTom = new GameObject();
		auto rtu_FunnyMan = new RenderTextureComponent(pBigTom, nullptr);
		pBigTom->AddComponent(rtu_FunnyMan);
		pBigTom->AddComponent(new HealthComponent(pBigTom, 5, 3));
		pBigTom->AddComponent(new ScoreComponent(pBigTom, 0));
		pBigTom->AddComponent(new SoundComponent(pBigTom, "aughh.wav", 1.f));
		pBigTom->AddComponent(new SpeedComponent(pBigTom, 100.f));
		pBigTom->GetComponent<RenderTextureComponent>()->SetTexture("funny-man-rescaled.png");
		pBigTom->AddComponent(new ColliderComponent(pBigTom, nullptr, 40.f, 40.f));
		pBigTom->AddComponent(new EnemyComponent(pBigTom));
		pBigTom->AddComponent(new EnemyMover(pBigTom, pGrid.get()));
		pBigTom->SetPosition(240, 200);

		scene->Add(pBigTom);

		auto pProjectile = new GameObject();
		pProjectile->AddComponent(new SpeedComponent(pProjectile, 200.f));
		pProjectile->AddComponent(new MovementDirectionComponent(pProjectile));
		pProjectile->AddComponent(new RenderTextureComponent(pProjectile, nullptr));
		pProjectile->AddComponent(new ColliderComponent(pProjectile, pBigTom, 40.f, 40.f));
		pProjectile->GetComponent<RenderTextureComponent>()->SetTexture("Projectile.png");
		pProjectile->SetPosition(-100.f, -100.f);
		scene->Add(pProjectile);

		auto pDigger = new GameObject();
		auto diggerTexture = new RenderTextureComponent(pDigger, nullptr);
		pDigger->AddComponent(new MovementDirectionComponent(pDigger));
		pDigger->AddComponent(new HealthComponent(pDigger, 1, 3));
		pDigger->AddComponent(diggerTexture);
		pDigger->AddComponent(new GridComponent(pDigger, pGrid.get()));
		pDigger->AddComponent(new ScoreComponent(pDigger, 0));
		pDigger->AddComponent(new SpeedComponent(pDigger, 100.f));
		pDigger->AddComponent(new SoundComponent(pDigger, "aughh.wav", 0.1f));
		pDigger->AddComponent(new PlayerComponent(pDigger, { 200.f,120.f }));
		pDigger->AddComponent(new ProjectileComponent(pDigger, pProjectile, 5.f));
		pDigger->GetComponent<HealthComponent>()->AddObserver(pDigger->GetComponent<PlayerComponent>());
		pDigger->GetComponent<RenderTextureComponent>()->SetTexture("Digger.png");
		pDigger->GetComponent<ProjectileComponent>()->AddObserver(pBigTom->GetComponent<EnemyComponent>());
		pDigger->SetPosition(200, 120);
		scene->Add(pDigger);
		pBigTom->GetComponent<ColliderComponent>()->SetTarget(pDigger);
#pragma endregion Players

		auto player1LivesUI = new GameObject();
		player1LivesUI->SetPosition(10, 5);

		auto pFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 14);
		auto renderLives = new RenderTextComponent(player1LivesUI, " ", pFont);
		player1LivesUI->AddComponent(renderLives);

		auto healthUIComp = new UIComponent(player1LivesUI, pDigger->GetComponent<HealthComponent>());
		player1LivesUI->AddComponent(healthUIComp);

		scene->Add(player1LivesUI);
		pBigTom->GetComponent<EnemyComponent>()->AddObserver(healthUIComp);

		auto player1ScoreUI = new GameObject();
		player1ScoreUI->SetPosition(10, 35);

		auto renderScore = new RenderTextComponent(player1ScoreUI, " ", pFont);
		player1ScoreUI->AddComponent(renderScore);

		auto scoreUIComp = new UIComponent(player1ScoreUI, pDigger->GetComponent<ScoreComponent>());
		player1ScoreUI->AddComponent(scoreUIComp);
		pGrid->AddObserver(scoreUIComp);

		scene->Add(player1ScoreUI);

		for (size_t i{ 0 }; i < amountOfItems; ++i)
		{
			pGrid->GetItems()[i]->GetComponent<ColliderComponent>()->SetTarget(pDigger);
			pGrid->GetItems()[i]->GetComponent<ItemComponent>()->AddObserver(scoreUIComp);
			pGrid->GetItems()[i]->GetComponent<ItemComponent>()->AddObserver(pGrid.get());
		}
		auto player2HealthUI = new GameObject();
		player2HealthUI->SetPosition(80, 5);

		player2HealthUI->AddComponent(new RenderTextComponent(player2HealthUI, " ", pFont));

		player2HealthUI->AddComponent(new UIComponent(player2HealthUI, pBigTom->GetComponent<HealthComponent>()));

		scene->Add(player2HealthUI);

		auto player2ScoreUI = new GameObject();
		player2ScoreUI->SetPosition(80, 35);

		player2ScoreUI->AddComponent(new RenderTextComponent(player2ScoreUI, " ", pFont));

		player2ScoreUI->AddComponent(new UIComponent(player2ScoreUI, pBigTom->GetComponent<ScoreComponent>()));

		scene->Add(player2ScoreUI);
		//std::unique_ptr<WinGameAch> winGameAch = std::make_unique<WinGameAch>();
		//auto ach = AchievementManager::GetInstance().AddAchievement(std::move(winGameAch));
		//pDigger->GetComponent<ScoreComponent>()->BindOnScoreChanged(ach);
		//pBigTom->GetComponent<ScoreComponent>()->BindOnScoreChanged(ach);


		//pGameObj = new GameObject();
		//auto renderText = new RenderTextComponent(pGameObj, " ", pFont);
		//pGameObj->AddComponent(renderText);
		//auto fps_Counter = new FPSComponent(pGameObj);
		//pGameObj->AddComponent(fps_Counter);
		//pGameObj->SetPosition(10, 5);
		//scene.Add(pGameObj);

		auto& inputManager = dae::InputManager::GetInstance();
		//--------------------------------------------
	// CONTROLLER
	//--------------------------------------------
		std::unique_ptr<Controller> controller = std::make_unique<Controller>(0);
		inputManager.AddController(std::move(controller));

		//-----------------------------------------------------------------
		std::unique_ptr<StartMovingCommand> startMoveUp = std::make_unique<StartMovingCommand>(pDigger, pGrid, StartMovingCommand::MoveDir::North);
		inputManager.AddMapping(0, std::move(startMoveUp), Controller::ControllerButton::DPadUp, InputManager::inputCondition::Press);

		std::unique_ptr<MoveCommand> moveUp = std::make_unique<MoveCommand>(pDigger, pGrid, StartMovingCommand::MoveDir::North);
		inputManager.AddMapping(0, std::move(moveUp), Controller::ControllerButton::DPadUp, InputManager::inputCondition::Hold);

		std::unique_ptr<StopMovingCommand> endMoveUp = std::make_unique<StopMovingCommand>(pDigger);
		inputManager.AddMapping(0, std::move(endMoveUp), Controller::ControllerButton::DPadUp, InputManager::inputCondition::Release);
		//-----------------------------------------------------------------
		std::unique_ptr<StartMovingCommand> startMoveRight = std::make_unique<StartMovingCommand>(pDigger, pGrid, StartMovingCommand::MoveDir::East);
		inputManager.AddMapping(0, std::move(startMoveRight), Controller::ControllerButton::DPadRight, InputManager::inputCondition::Press);

		std::unique_ptr<MoveCommand> moveRight = std::make_unique<MoveCommand>(pDigger, pGrid, StartMovingCommand::MoveDir::East);
		inputManager.AddMapping(0, std::move(moveRight), Controller::ControllerButton::DPadRight, InputManager::inputCondition::Hold);

		std::unique_ptr<StopMovingCommand> endMoveRight = std::make_unique<StopMovingCommand>(pDigger);
		inputManager.AddMapping(0, std::move(endMoveRight), Controller::ControllerButton::DPadRight, InputManager::inputCondition::Release);
		//-----------------------------------------------------------------
		std::unique_ptr<StartMovingCommand> startMoveDown = std::make_unique<StartMovingCommand>(pDigger, pGrid, StartMovingCommand::MoveDir::South);
		inputManager.AddMapping(0, std::move(startMoveDown), Controller::ControllerButton::DPadDown, InputManager::inputCondition::Press);

		std::unique_ptr<MoveCommand> moveDown = std::make_unique<MoveCommand>(pDigger, pGrid, StartMovingCommand::MoveDir::South);
		inputManager.AddMapping(0, std::move(moveDown), Controller::ControllerButton::DPadDown, InputManager::inputCondition::Hold);

		std::unique_ptr<StopMovingCommand> endMoveDown = std::make_unique<StopMovingCommand>(pDigger);
		inputManager.AddMapping(0, std::move(endMoveDown), Controller::ControllerButton::DPadDown, InputManager::inputCondition::Release);

		//-----------------------------------------------------------------
		std::unique_ptr<StartMovingCommand> startMoveLeft = std::make_unique<StartMovingCommand>(pDigger, pGrid, StartMovingCommand::MoveDir::West);
		inputManager.AddMapping(0, std::move(startMoveLeft), Controller::ControllerButton::DPadLeft, InputManager::inputCondition::Press);

		std::unique_ptr<MoveCommand> moveLeft = std::make_unique<MoveCommand>(pDigger, pGrid, StartMovingCommand::MoveDir::West);
		inputManager.AddMapping(0, std::move(moveLeft), Controller::ControllerButton::DPadLeft, InputManager::inputCondition::Hold);

		std::unique_ptr<StopMovingCommand> endMoveLeft = std::make_unique<StopMovingCommand>(pDigger);
		inputManager.AddMapping(0, std::move(endMoveLeft), Controller::ControllerButton::DPadLeft, InputManager::inputCondition::Release);


		//-----------------------------------------------------------------

		std::unique_ptr<ShootCommand> shoot = std::make_unique<ShootCommand>(pDigger);
		inputManager.AddMapping(0, std::move(shoot), Controller::ControllerButton::ButtonX, InputManager::inputCondition::Press);

		//--------------------------------------------
		// KEYBOARD
		//--------------------------------------------
#pragma region MOVE COMMANDS
	//--------------------------------------------
		std::unique_ptr<StartMovingCommand> kbLeftStart = std::make_unique<StartMovingCommand>(pDigger, pGrid, MovementDirectionComponent::MovementDirection::West);
		inputManager.AddKeyboardMapping(std::move(kbLeftStart), SDL_SCANCODE_A, InputManager::inputCondition::Press);

		std::unique_ptr<MoveCommand> kbMoveLeftCommand = std::make_unique<MoveCommand>(pDigger, pGrid, MovementDirectionComponent::MovementDirection::West);
		inputManager.AddKeyboardMapping(std::move(kbMoveLeftCommand), SDL_SCANCODE_A, InputManager::inputCondition::Hold);

		std::unique_ptr<StopMovingCommand> kbLeftEnd = std::make_unique<StopMovingCommand>(pDigger);
		inputManager.AddKeyboardMapping(std::move(kbLeftEnd), SDL_SCANCODE_A, InputManager::inputCondition::Release);


		//--------------------------------------------

		std::unique_ptr<StartMovingCommand> kbUpStart = std::make_unique<StartMovingCommand>(pDigger, pGrid, MovementDirectionComponent::MovementDirection::North);
		inputManager.AddKeyboardMapping(std::move(kbUpStart), SDL_SCANCODE_W, InputManager::inputCondition::Press);

		std::unique_ptr<MoveCommand> kbMoveUpCommand = std::make_unique<MoveCommand>(pDigger, pGrid, MovementDirectionComponent::MovementDirection::North);
		inputManager.AddKeyboardMapping(std::move(kbMoveUpCommand), SDL_SCANCODE_W, InputManager::inputCondition::Hold);

		std::unique_ptr<StopMovingCommand> kbUpEnd = std::make_unique<StopMovingCommand>(pDigger);
		inputManager.AddKeyboardMapping(std::move(kbUpEnd), SDL_SCANCODE_W, InputManager::inputCondition::Release);


		//--------------------------------------------
		std::unique_ptr<StartMovingCommand> kbDownStart = std::make_unique<StartMovingCommand>(pDigger, pGrid, MovementDirectionComponent::MovementDirection::South);
		inputManager.AddKeyboardMapping(std::move(kbDownStart), SDL_SCANCODE_S, InputManager::inputCondition::Press);

		std::unique_ptr<MoveCommand> kbMoveDownCommand = std::make_unique<MoveCommand>(pDigger, pGrid, MovementDirectionComponent::MovementDirection::South);
		inputManager.AddKeyboardMapping(std::move(kbMoveDownCommand), SDL_SCANCODE_S, InputManager::inputCondition::Hold);

		std::unique_ptr<StopMovingCommand> kbDownEnd = std::make_unique<StopMovingCommand>(pDigger);
		inputManager.AddKeyboardMapping(std::move(kbDownEnd), SDL_SCANCODE_S, InputManager::inputCondition::Release);

		//--------------------------------------------
		std::unique_ptr<StartMovingCommand> kbRightStart = std::make_unique<StartMovingCommand>(pDigger, pGrid, MovementDirectionComponent::MovementDirection::East);
		inputManager.AddKeyboardMapping(std::move(kbRightStart), SDL_SCANCODE_D, InputManager::inputCondition::Press);

		std::unique_ptr<MoveCommand> kbmoveRightCommand = std::make_unique<MoveCommand>(pDigger, pGrid, MovementDirectionComponent::MovementDirection::East);
		inputManager.AddKeyboardMapping(std::move(kbmoveRightCommand), SDL_SCANCODE_D, InputManager::inputCondition::Hold);

		std::unique_ptr<StopMovingCommand> kbRightEnd = std::make_unique<StopMovingCommand>(pDigger);
		inputManager.AddKeyboardMapping(std::move(kbRightEnd), SDL_SCANCODE_D, InputManager::inputCondition::Release);


		//--------------------------------------------
#pragma endregion MOVE COMMANDS

		std::unique_ptr<MuteSoundCommand> kbMute = std::make_unique<MuteSoundCommand>();
		inputManager.AddKeyboardMapping(std::move(kbMute), SDL_SCANCODE_M, InputManager::inputCondition::Press);
		std::unique_ptr<KillCommand> kbDamageTinyTom = std::make_unique<KillCommand>(pDigger);
		inputManager.AddKeyboardMapping(std::move(kbDamageTinyTom), SDL_SCANCODE_R, InputManager::inputCondition::Press);

		std::unique_ptr<AddScoreCommand> kbAddScoreTinyTom = std::make_unique<AddScoreCommand>(pDigger);
		inputManager.AddKeyboardMapping(std::move(kbAddScoreTinyTom), SDL_SCANCODE_Q, InputManager::inputCondition::Press);

		std::unique_ptr<ShootCommand> kbShoot = std::make_unique<ShootCommand>(pDigger);
		inputManager.AddKeyboardMapping(std::move(kbShoot), SDL_SCANCODE_SPACE, InputManager::inputCondition::Press);

		std::unique_ptr<SwapSceneCommand> kbSwapScene = std::make_unique<SwapSceneCommand>("LevelTwo");
		inputManager.AddKeyboardMapping(std::move(kbSwapScene), SDL_SCANCODE_F1, InputManager::inputCondition::Press);

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

	void LoadLevel2(Scene* scene)
	{
#if _DEBUG
		ServiceLocator::RegisterSoundSystem(std::make_unique<LogSoundSys>(std::make_unique<DefaultSoundSystem>()));
#else
		ServiceLocator::RegisterSoundSystem(std::make_unique<DefaultSoundSystem>());
#endif
#pragma region Misc
		ServiceLocator::GetSoundSystem().SetVolume(1.f);
		std::cout << "-------------------------------------------------------------------------------\n";
		std::cout << "PRESS Q TO PLAY A SOUND (might be loud, careful even though volume is set to 1)\n";
		std::cout << "-------------------------------------------------------------------------------\n";

		GameObject* pBackground = new GameObject();
		RenderTextureComponent* rt_Background = new RenderTextureComponent(pBackground, nullptr);
		pBackground->AddComponent(rt_Background);
		pBackground->GetComponent<RenderTextureComponent>()->SetTexture("Level1 Background.png");
		pBackground->SetPosition(0, 40);
		scene->Add(pBackground);


		const std::string gridStructure
		{
				 "ooooooo####ooooooo##"
				 "ooooooo####ooooooo##"
				 "ooooooo####ooooooo##"
				 "oooo#oo#############"
				 "ooooooo####ooooooooo"
				 "ooooooo####ooooooooo"
				 "#oooooo####oooooooo#"
				 "###oooo####oooo#####"
				 "ooo############ooooo"
				 "oooooo#####ooooooooo"
				 "oooooo#####ooooooooo"
				 "oooooo#####ooooooooo"
				 "oooooo#####ooooooooo"
				 "oooooo#####ooooooooo"
				 "oooooo#####ooooooooo"
				 "oooooo#####ooooooooo"
				 "oooooo#####ooooooooo"
				 "oooooo#####ooooooooo"
				 "o##################o"
				 "ooooooo####ooooooooo"

		};
		int rows{ 20 }, cols{ 20 }, cellSize{ 40 };
		std::shared_ptr<Grid> pGrid = std::make_shared<Grid>(rows, cols, cellSize, gridStructure);
		auto pGridObj = new GameObject();
		pGridObj->AddComponent(new GridRenderer(pGridObj, pGrid));
		scene->Add(pGridObj);

		size_t amountOfItems{ 20 };
		for (size_t i{ 0 }; i < amountOfItems; ++i)
		{
			auto item = new GameObject();
			item->AddComponent(new RenderTextureComponent(item, nullptr));
			item->GetComponent<RenderTextureComponent>()->SetTexture("emerald.png");
			item->AddComponent(new ColliderComponent(item, nullptr, 40.f, 40.f));
			item->AddComponent(new ItemComponent(item));
			item->AddComponent(new SoundComponent(item, "../Data/EmeraldPickUp.wav", 1.f));
			scene->Add(item);
			pGrid->AddGameObj(item);
		}
		pGrid->DistributeItems();
		pGrid->SetAmountItems(amountOfItems);

#pragma endregion Misc

#pragma region Players

		auto pBigTom = new GameObject();
		auto rtu_FunnyMan = new RenderTextureComponent(pBigTom, nullptr);
		pBigTom->AddComponent(rtu_FunnyMan);
		pBigTom->AddComponent(new HealthComponent(pBigTom, 5, 3));
		pBigTom->AddComponent(new ScoreComponent(pBigTom, 0));
		pBigTom->AddComponent(new SoundComponent(pBigTom, "aughh.wav", 1.f));
		pBigTom->AddComponent(new SpeedComponent(pBigTom, 100.f));
		pBigTom->GetComponent<RenderTextureComponent>()->SetTexture("funny-man-rescaled.png");
		pBigTom->AddComponent(new ColliderComponent(pBigTom, nullptr, 40.f, 40.f));
		pBigTom->AddComponent(new EnemyComponent(pBigTom));
		pBigTom->AddComponent(new EnemyMover(pBigTom, pGrid.get()));
		pBigTom->SetPosition(360, 40);

		scene->Add(pBigTom);

		auto pProjectile = new GameObject();
		pProjectile->AddComponent(new SpeedComponent(pProjectile, 200.f));
		pProjectile->AddComponent(new MovementDirectionComponent(pProjectile));
		pProjectile->AddComponent(new RenderTextureComponent(pProjectile, nullptr));
		pProjectile->AddComponent(new ColliderComponent(pProjectile, pBigTom, 40.f, 40.f));
		pProjectile->GetComponent<RenderTextureComponent>()->SetTexture("Projectile.png");
		pProjectile->SetPosition(-100.f, -100.f);
		scene->Add(pProjectile);

		auto pDigger = new GameObject();
		auto diggerTexture = new RenderTextureComponent(pDigger, nullptr);
		pDigger->AddComponent(new MovementDirectionComponent(pDigger));
		pDigger->AddComponent(new HealthComponent(pDigger, 1, 3));
		pDigger->AddComponent(diggerTexture);
		pDigger->AddComponent(new GridComponent(pDigger, pGrid.get()));
		pDigger->AddComponent(new ScoreComponent(pDigger, 0));
		pDigger->AddComponent(new SpeedComponent(pDigger, 100.f));
		pDigger->AddComponent(new SoundComponent(pDigger, "aughh.wav", 0.1f));
		pDigger->AddComponent(new PlayerComponent(pDigger, { 40.f,40.f }));
		pDigger->AddComponent(new ProjectileComponent(pDigger, pProjectile, 5.f));
		pDigger->GetComponent<HealthComponent>()->AddObserver(pDigger->GetComponent<PlayerComponent>());
		pDigger->GetComponent<RenderTextureComponent>()->SetTexture("Digger.png");
		pDigger->GetComponent<ProjectileComponent>()->AddObserver(pBigTom->GetComponent<EnemyComponent>());
		pDigger->SetPosition(200, 120);
		scene->Add(pDigger);
		pBigTom->GetComponent<ColliderComponent>()->SetTarget(pDigger);
#pragma endregion Players

		auto player1LivesUI = new GameObject();
		player1LivesUI->SetPosition(10, 5);

		auto pFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 14);
		auto renderLives = new RenderTextComponent(player1LivesUI, " ", pFont);
		player1LivesUI->AddComponent(renderLives);

		auto healthUIComp = new UIComponent(player1LivesUI, pDigger->GetComponent<HealthComponent>());
		player1LivesUI->AddComponent(healthUIComp);

		scene->Add(player1LivesUI);
		pBigTom->GetComponent<EnemyComponent>()->AddObserver(healthUIComp);

		auto player1ScoreUI = new GameObject();
		player1ScoreUI->SetPosition(10, 35);

		auto renderScore = new RenderTextComponent(player1ScoreUI, " ", pFont);
		player1ScoreUI->AddComponent(renderScore);

		auto scoreUIComp = new UIComponent(player1ScoreUI, pDigger->GetComponent<ScoreComponent>());
		player1ScoreUI->AddComponent(scoreUIComp);

		scene->Add(player1ScoreUI);

		for (size_t i{ 0 }; i < amountOfItems; ++i)
		{
			pGrid->GetItems()[i]->GetComponent<ColliderComponent>()->SetTarget(pDigger);
			pGrid->GetItems()[i]->GetComponent<ItemComponent>()->AddObserver(scoreUIComp);
			pGrid->GetItems()[i]->GetComponent<ItemComponent>()->AddObserver(pGrid.get());
		}
		auto player2HealthUI = new GameObject();
		player2HealthUI->SetPosition(80, 5);

		player2HealthUI->AddComponent(new RenderTextComponent(player2HealthUI, " ", pFont));

		player2HealthUI->AddComponent(new UIComponent(player2HealthUI, pBigTom->GetComponent<HealthComponent>()));

		scene->Add(player2HealthUI);

		auto player2ScoreUI = new GameObject();
		player2ScoreUI->SetPosition(80, 35);

		player2ScoreUI->AddComponent(new RenderTextComponent(player2ScoreUI, " ", pFont));

		player2ScoreUI->AddComponent(new UIComponent(player2ScoreUI, pBigTom->GetComponent<ScoreComponent>()));

		scene->Add(player2ScoreUI);


		auto& inputManager = dae::InputManager::GetInstance();
		//--------------------------------------------
	// CONTROLLER
	//--------------------------------------------
		std::unique_ptr<Controller> controller = std::make_unique<Controller>(0);
		inputManager.AddController(std::move(controller));

		//-----------------------------------------------------------------
		std::unique_ptr<StartMovingCommand> startMoveUp = std::make_unique<StartMovingCommand>(pDigger, pGrid, StartMovingCommand::MoveDir::North);
		inputManager.AddMapping(0, std::move(startMoveUp), Controller::ControllerButton::DPadUp, InputManager::inputCondition::Press);

		std::unique_ptr<MoveCommand> moveUp = std::make_unique<MoveCommand>(pDigger, pGrid, StartMovingCommand::MoveDir::North);
		inputManager.AddMapping(0, std::move(moveUp), Controller::ControllerButton::DPadUp, InputManager::inputCondition::Hold);

		std::unique_ptr<StopMovingCommand> endMoveUp = std::make_unique<StopMovingCommand>(pDigger);
		inputManager.AddMapping(0, std::move(endMoveUp), Controller::ControllerButton::DPadUp, InputManager::inputCondition::Release);
		//-----------------------------------------------------------------
		std::unique_ptr<StartMovingCommand> startMoveRight = std::make_unique<StartMovingCommand>(pDigger, pGrid, StartMovingCommand::MoveDir::East);
		inputManager.AddMapping(0, std::move(startMoveRight), Controller::ControllerButton::DPadRight, InputManager::inputCondition::Press);

		std::unique_ptr<MoveCommand> moveRight = std::make_unique<MoveCommand>(pDigger, pGrid, StartMovingCommand::MoveDir::East);
		inputManager.AddMapping(0, std::move(moveRight), Controller::ControllerButton::DPadRight, InputManager::inputCondition::Hold);

		std::unique_ptr<StopMovingCommand> endMoveRight = std::make_unique<StopMovingCommand>(pDigger);
		inputManager.AddMapping(0, std::move(endMoveRight), Controller::ControllerButton::DPadRight, InputManager::inputCondition::Release);
		//-----------------------------------------------------------------
		std::unique_ptr<StartMovingCommand> startMoveDown = std::make_unique<StartMovingCommand>(pDigger, pGrid, StartMovingCommand::MoveDir::South);
		inputManager.AddMapping(0, std::move(startMoveDown), Controller::ControllerButton::DPadDown, InputManager::inputCondition::Press);

		std::unique_ptr<MoveCommand> moveDown = std::make_unique<MoveCommand>(pDigger, pGrid, StartMovingCommand::MoveDir::South);
		inputManager.AddMapping(0, std::move(moveDown), Controller::ControllerButton::DPadDown, InputManager::inputCondition::Hold);

		std::unique_ptr<StopMovingCommand> endMoveDown = std::make_unique<StopMovingCommand>(pDigger);
		inputManager.AddMapping(0, std::move(endMoveDown), Controller::ControllerButton::DPadDown, InputManager::inputCondition::Release);

		//-----------------------------------------------------------------
		std::unique_ptr<StartMovingCommand> startMoveLeft = std::make_unique<StartMovingCommand>(pDigger, pGrid, StartMovingCommand::MoveDir::West);
		inputManager.AddMapping(0, std::move(startMoveLeft), Controller::ControllerButton::DPadLeft, InputManager::inputCondition::Press);

		std::unique_ptr<MoveCommand> moveLeft = std::make_unique<MoveCommand>(pDigger, pGrid, StartMovingCommand::MoveDir::West);
		inputManager.AddMapping(0, std::move(moveLeft), Controller::ControllerButton::DPadLeft, InputManager::inputCondition::Hold);

		std::unique_ptr<StopMovingCommand> endMoveLeft = std::make_unique<StopMovingCommand>(pDigger);
		inputManager.AddMapping(0, std::move(endMoveLeft), Controller::ControllerButton::DPadLeft, InputManager::inputCondition::Release);


		//-----------------------------------------------------------------

		std::unique_ptr<ShootCommand> shoot = std::make_unique<ShootCommand>(pDigger);
		inputManager.AddMapping(0, std::move(shoot), Controller::ControllerButton::ButtonX, InputManager::inputCondition::Press);
		//--------------------------------------------
		// KEYBOARD
		//--------------------------------------------
#pragma region MOVE COMMANDS
	//--------------------------------------------
		std::unique_ptr<StartMovingCommand> kbLeftStart = std::make_unique<StartMovingCommand>(pDigger, pGrid, MovementDirectionComponent::MovementDirection::West);
		inputManager.AddKeyboardMapping(std::move(kbLeftStart), SDL_SCANCODE_A, InputManager::inputCondition::Press);

		std::unique_ptr<MoveCommand> kbMoveLeftCommand = std::make_unique<MoveCommand>(pDigger, pGrid, MovementDirectionComponent::MovementDirection::West);
		inputManager.AddKeyboardMapping(std::move(kbMoveLeftCommand), SDL_SCANCODE_A, InputManager::inputCondition::Hold);

		std::unique_ptr<StopMovingCommand> kbLeftEnd = std::make_unique<StopMovingCommand>(pDigger);
		inputManager.AddKeyboardMapping(std::move(kbLeftEnd), SDL_SCANCODE_A, InputManager::inputCondition::Release);


		//--------------------------------------------

		std::unique_ptr<StartMovingCommand> kbUpStart = std::make_unique<StartMovingCommand>(pDigger, pGrid, MovementDirectionComponent::MovementDirection::North);
		inputManager.AddKeyboardMapping(std::move(kbUpStart), SDL_SCANCODE_W, InputManager::inputCondition::Press);

		std::unique_ptr<MoveCommand> kbMoveUpCommand = std::make_unique<MoveCommand>(pDigger, pGrid, MovementDirectionComponent::MovementDirection::North);
		inputManager.AddKeyboardMapping(std::move(kbMoveUpCommand), SDL_SCANCODE_W, InputManager::inputCondition::Hold);

		std::unique_ptr<StopMovingCommand> kbUpEnd = std::make_unique<StopMovingCommand>(pDigger);
		inputManager.AddKeyboardMapping(std::move(kbUpEnd), SDL_SCANCODE_W, InputManager::inputCondition::Release);


		//--------------------------------------------
		std::unique_ptr<StartMovingCommand> kbDownStart = std::make_unique<StartMovingCommand>(pDigger, pGrid, MovementDirectionComponent::MovementDirection::South);
		inputManager.AddKeyboardMapping(std::move(kbDownStart), SDL_SCANCODE_S, InputManager::inputCondition::Press);

		std::unique_ptr<MoveCommand> kbMoveDownCommand = std::make_unique<MoveCommand>(pDigger, pGrid, MovementDirectionComponent::MovementDirection::South);
		inputManager.AddKeyboardMapping(std::move(kbMoveDownCommand), SDL_SCANCODE_S, InputManager::inputCondition::Hold);

		std::unique_ptr<StopMovingCommand> kbDownEnd = std::make_unique<StopMovingCommand>(pDigger);
		inputManager.AddKeyboardMapping(std::move(kbDownEnd), SDL_SCANCODE_S, InputManager::inputCondition::Release);

		//--------------------------------------------
		std::unique_ptr<StartMovingCommand> kbRightStart = std::make_unique<StartMovingCommand>(pDigger, pGrid, MovementDirectionComponent::MovementDirection::East);
		inputManager.AddKeyboardMapping(std::move(kbRightStart), SDL_SCANCODE_D, InputManager::inputCondition::Press);

		std::unique_ptr<MoveCommand> kbmoveRightCommand = std::make_unique<MoveCommand>(pDigger, pGrid, MovementDirectionComponent::MovementDirection::East);
		inputManager.AddKeyboardMapping(std::move(kbmoveRightCommand), SDL_SCANCODE_D, InputManager::inputCondition::Hold);

		std::unique_ptr<StopMovingCommand> kbRightEnd = std::make_unique<StopMovingCommand>(pDigger);
		inputManager.AddKeyboardMapping(std::move(kbRightEnd), SDL_SCANCODE_D, InputManager::inputCondition::Release);


		//--------------------------------------------
#pragma endregion MOVE COMMANDS

		std::unique_ptr<MuteSoundCommand> kbMute = std::make_unique<MuteSoundCommand>();
		inputManager.AddKeyboardMapping(std::move(kbMute), SDL_SCANCODE_M, InputManager::inputCondition::Press);
		std::unique_ptr<KillCommand> kbDamageTinyTom = std::make_unique<KillCommand>(pDigger);
		inputManager.AddKeyboardMapping(std::move(kbDamageTinyTom), SDL_SCANCODE_R, InputManager::inputCondition::Press);

		std::unique_ptr<AddScoreCommand> kbAddScoreTinyTom = std::make_unique<AddScoreCommand>(pDigger);
		inputManager.AddKeyboardMapping(std::move(kbAddScoreTinyTom), SDL_SCANCODE_Q, InputManager::inputCondition::Press);

		std::unique_ptr<ShootCommand> kbShoot = std::make_unique<ShootCommand>(pDigger);
		inputManager.AddKeyboardMapping(std::move(kbShoot), SDL_SCANCODE_SPACE, InputManager::inputCondition::Press);

		std::unique_ptr<SwapSceneCommand> kbSwapScene = std::make_unique<SwapSceneCommand>("LevelThree");
		inputManager.AddKeyboardMapping(std::move(kbSwapScene), SDL_SCANCODE_F1, InputManager::inputCondition::Press);

	}
	void LoadLevel3(Scene* scene)
	{
#if _DEBUG
		ServiceLocator::RegisterSoundSystem(std::make_unique<LogSoundSys>(std::make_unique<DefaultSoundSystem>()));
#else
		ServiceLocator::RegisterSoundSystem(std::make_unique<DefaultSoundSystem>());
#endif
#pragma region Misc
		ServiceLocator::GetSoundSystem().SetVolume(1.f);

		GameObject* pBackground = new GameObject();
		RenderTextureComponent* rt_Background = new RenderTextureComponent(pBackground, nullptr);
		pBackground->AddComponent(rt_Background);
		pBackground->GetComponent<RenderTextureComponent>()->SetTexture("Level1 Background.png");
		pBackground->SetPosition(0, 40);
		scene->Add(pBackground);


		const std::string gridStructure
		{
				 "ooooooo####ooooooo##"
				 "ooooooo####ooooooo##"
				 "ooooooo####ooooooo##"
				 "oooo#oo####ooooooo##"
				 "oooooooooooooooooooo"
				 "oooooooooooooooooooo"
				 "oooooooooooooooooooo"
				 "###oooo####oooo#####"
				 "ooo############ooooo"
				 "oooooooooooooooooooo"
				 "oooooooooooooooooooo"
				 "oooooooooooooooooooo"
				 "oooooooooooooooooooo"
				 "oooooooooooooooooooo"
				 "oooooooooooooooooooo"
				 "oooooooooooooooooooo"
				 "oooooooooooooooooooo"
				 "oooooooooooooooooooo"
				 "o##################o"
				 "ooooooo####ooooooooo"

		};
		int rows{ 20 }, cols{ 20 }, cellSize{ 40 };
		std::shared_ptr<Grid> pGrid = std::make_shared<Grid>(rows, cols, cellSize, gridStructure);
		auto pGridObj = new GameObject();
		pGridObj->AddComponent(new GridRenderer(pGridObj, pGrid));
		scene->Add(pGridObj);

		size_t amountOfItems{ 1 };
		for (size_t i{ 0 }; i < amountOfItems; ++i)
		{
			auto item = new GameObject();
			item->AddComponent(new RenderTextureComponent(item, nullptr));
			item->GetComponent<RenderTextureComponent>()->SetTexture("emerald.png");
			item->AddComponent(new ColliderComponent(item, nullptr, 40.f, 40.f));
			item->AddComponent(new ItemComponent(item));
			item->AddComponent(new SoundComponent(item, "../Data/EmeraldPickUp.wav", 1.f));
			scene->Add(item);
			pGrid->AddGameObj(item);
		}
		pGrid->DistributeItems();
		pGrid->SetAmountItems(amountOfItems);

#pragma endregion Misc

#pragma region Players

		auto pBigTom = new GameObject();
		auto rtu_FunnyMan = new RenderTextureComponent(pBigTom, nullptr);
		pBigTom->AddComponent(rtu_FunnyMan);
		pBigTom->AddComponent(new HealthComponent(pBigTom, 5, 3));
		pBigTom->AddComponent(new ScoreComponent(pBigTom, 0));
		pBigTom->AddComponent(new SoundComponent(pBigTom, "aughh.wav", 1.f));
		pBigTom->AddComponent(new SpeedComponent(pBigTom, 100.f));
		pBigTom->GetComponent<RenderTextureComponent>()->SetTexture("funny-man-rescaled.png");
		pBigTom->AddComponent(new ColliderComponent(pBigTom, nullptr, 40.f, 40.f));
		pBigTom->AddComponent(new EnemyComponent(pBigTom));
		pBigTom->AddComponent(new EnemyMover(pBigTom, pGrid.get()));
		pBigTom->SetPosition(360, 40);

		scene->Add(pBigTom);

		auto pProjectile = new GameObject();
		pProjectile->AddComponent(new SpeedComponent(pProjectile, 200.f));
		pProjectile->AddComponent(new MovementDirectionComponent(pProjectile));
		pProjectile->AddComponent(new RenderTextureComponent(pProjectile, nullptr));
		pProjectile->AddComponent(new ColliderComponent(pProjectile, pBigTom, 40.f, 40.f));
		pProjectile->GetComponent<RenderTextureComponent>()->SetTexture("Projectile.png");
		pProjectile->SetPosition(-100.f, -100.f);
		scene->Add(pProjectile);

		auto pDigger = new GameObject();
		auto diggerTexture = new RenderTextureComponent(pDigger, nullptr);
		pDigger->AddComponent(new MovementDirectionComponent(pDigger));
		pDigger->AddComponent(new HealthComponent(pDigger, 1, 3));
		pDigger->AddComponent(diggerTexture);
		pDigger->AddComponent(new GridComponent(pDigger, pGrid.get()));
		pDigger->AddComponent(new ScoreComponent(pDigger, 0));
		pDigger->AddComponent(new SpeedComponent(pDigger, 100.f));
		pDigger->AddComponent(new SoundComponent(pDigger, "aughh.wav", 0.1f));
		pDigger->AddComponent(new PlayerComponent(pDigger, { 40.f,40.f }));
		pDigger->AddComponent(new ProjectileComponent(pDigger, pProjectile, 5.f));
		pDigger->GetComponent<HealthComponent>()->AddObserver(pDigger->GetComponent<PlayerComponent>());
		pDigger->GetComponent<RenderTextureComponent>()->SetTexture("Digger.png");
		pDigger->GetComponent<ProjectileComponent>()->AddObserver(pBigTom->GetComponent<EnemyComponent>());
		pDigger->SetPosition(520, 520);
		scene->Add(pDigger);
		pBigTom->GetComponent<ColliderComponent>()->SetTarget(pDigger);
#pragma endregion Players

		auto player1LivesUI = new GameObject();
		player1LivesUI->SetPosition(10, 5);

		auto pFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 14);
		auto renderLives = new RenderTextComponent(player1LivesUI, " ", pFont);
		player1LivesUI->AddComponent(renderLives);

		auto healthUIComp = new UIComponent(player1LivesUI, pDigger->GetComponent<HealthComponent>());
		player1LivesUI->AddComponent(healthUIComp);

		scene->Add(player1LivesUI);
		pBigTom->GetComponent<EnemyComponent>()->AddObserver(healthUIComp);

		auto player1ScoreUI = new GameObject();
		player1ScoreUI->SetPosition(10, 35);

		auto renderScore = new RenderTextComponent(player1ScoreUI, " ", pFont);
		player1ScoreUI->AddComponent(renderScore);

		auto scoreUIComp = new UIComponent(player1ScoreUI, pDigger->GetComponent<ScoreComponent>());
		player1ScoreUI->AddComponent(scoreUIComp);

		pGrid->AddObserver(scoreUIComp);
		scene->Add(player1ScoreUI);

		for (size_t i{ 0 }; i < amountOfItems; ++i)
		{
			pGrid->GetItems()[i]->GetComponent<ColliderComponent>()->SetTarget(pDigger);
			pGrid->GetItems()[i]->GetComponent<ItemComponent>()->AddObserver(scoreUIComp);
			pGrid->GetItems()[i]->GetComponent<ItemComponent>()->AddObserver(pGrid.get());
		}
		auto player2HealthUI = new GameObject();
		player2HealthUI->SetPosition(80, 5);

		player2HealthUI->AddComponent(new RenderTextComponent(player2HealthUI, " ", pFont));

		player2HealthUI->AddComponent(new UIComponent(player2HealthUI, pBigTom->GetComponent<HealthComponent>()));

		scene->Add(player2HealthUI);

		auto player2ScoreUI = new GameObject();
		player2ScoreUI->SetPosition(80, 35);

		player2ScoreUI->AddComponent(new RenderTextComponent(player2ScoreUI, " ", pFont));

		player2ScoreUI->AddComponent(new UIComponent(player2ScoreUI, pBigTom->GetComponent<ScoreComponent>()));

		scene->Add(player2ScoreUI);
		//std::unique_ptr<WinGameAch> winGameAch = std::make_unique<WinGameAch>();
		//auto ach = AchievementManager::GetInstance().AddAchievement(std::move(winGameAch));
		//pDigger->GetComponent<ScoreComponent>()->BindOnScoreChanged(ach);
		//pBigTom->GetComponent<ScoreComponent>()->BindOnScoreChanged(ach);


		//pGameObj = new GameObject();
		//auto renderText = new RenderTextComponent(pGameObj, " ", pFont);
		//pGameObj->AddComponent(renderText);
		//auto fps_Counter = new FPSComponent(pGameObj);
		//pGameObj->AddComponent(fps_Counter);
		//pGameObj->SetPosition(10, 5);
		//scene.Add(pGameObj);

		auto& inputManager = dae::InputManager::GetInstance();
		//--------------------------------------------
	// CONTROLLER
	//--------------------------------------------
		std::unique_ptr<Controller> controller = std::make_unique<Controller>(0);
		inputManager.AddController(std::move(controller));

		//-----------------------------------------------------------------
		std::unique_ptr<StartMovingCommand> startMoveUp = std::make_unique<StartMovingCommand>(pDigger, pGrid, StartMovingCommand::MoveDir::North);
		inputManager.AddMapping(0, std::move(startMoveUp), Controller::ControllerButton::DPadUp, InputManager::inputCondition::Press);

		std::unique_ptr<MoveCommand> moveUp = std::make_unique<MoveCommand>(pDigger, pGrid, StartMovingCommand::MoveDir::North);
		inputManager.AddMapping(0, std::move(moveUp), Controller::ControllerButton::DPadUp, InputManager::inputCondition::Hold);

		std::unique_ptr<StopMovingCommand> endMoveUp = std::make_unique<StopMovingCommand>(pDigger);
		inputManager.AddMapping(0, std::move(endMoveUp), Controller::ControllerButton::DPadUp, InputManager::inputCondition::Release);
		//-----------------------------------------------------------------
		std::unique_ptr<StartMovingCommand> startMoveRight = std::make_unique<StartMovingCommand>(pDigger, pGrid, StartMovingCommand::MoveDir::East);
		inputManager.AddMapping(0, std::move(startMoveRight), Controller::ControllerButton::DPadRight, InputManager::inputCondition::Press);

		std::unique_ptr<MoveCommand> moveRight = std::make_unique<MoveCommand>(pDigger, pGrid, StartMovingCommand::MoveDir::East);
		inputManager.AddMapping(0, std::move(moveRight), Controller::ControllerButton::DPadRight, InputManager::inputCondition::Hold);

		std::unique_ptr<StopMovingCommand> endMoveRight = std::make_unique<StopMovingCommand>(pDigger);
		inputManager.AddMapping(0, std::move(endMoveRight), Controller::ControllerButton::DPadRight, InputManager::inputCondition::Release);
		//-----------------------------------------------------------------
		std::unique_ptr<StartMovingCommand> startMoveDown = std::make_unique<StartMovingCommand>(pDigger, pGrid, StartMovingCommand::MoveDir::South);
		inputManager.AddMapping(0, std::move(startMoveDown), Controller::ControllerButton::DPadDown, InputManager::inputCondition::Press);

		std::unique_ptr<MoveCommand> moveDown = std::make_unique<MoveCommand>(pDigger, pGrid, StartMovingCommand::MoveDir::South);
		inputManager.AddMapping(0, std::move(moveDown), Controller::ControllerButton::DPadDown, InputManager::inputCondition::Hold);

		std::unique_ptr<StopMovingCommand> endMoveDown = std::make_unique<StopMovingCommand>(pDigger);
		inputManager.AddMapping(0, std::move(endMoveDown), Controller::ControllerButton::DPadDown, InputManager::inputCondition::Release);

		//-----------------------------------------------------------------
		std::unique_ptr<StartMovingCommand> startMoveLeft = std::make_unique<StartMovingCommand>(pDigger, pGrid, StartMovingCommand::MoveDir::West);
		inputManager.AddMapping(0, std::move(startMoveLeft), Controller::ControllerButton::DPadLeft, InputManager::inputCondition::Press);

		std::unique_ptr<MoveCommand> moveLeft = std::make_unique<MoveCommand>(pDigger, pGrid, StartMovingCommand::MoveDir::West);
		inputManager.AddMapping(0, std::move(moveLeft), Controller::ControllerButton::DPadLeft, InputManager::inputCondition::Hold);

		std::unique_ptr<StopMovingCommand> endMoveLeft = std::make_unique<StopMovingCommand>(pDigger);
		inputManager.AddMapping(0, std::move(endMoveLeft), Controller::ControllerButton::DPadLeft, InputManager::inputCondition::Release);


		//-----------------------------------------------------------------

		std::unique_ptr<ShootCommand> shoot = std::make_unique<ShootCommand>(pDigger);
		inputManager.AddMapping(0, std::move(shoot), Controller::ControllerButton::ButtonX, InputManager::inputCondition::Press);
		//-----------------------------------------------------------------

		//std::unique_ptr<MoveCommand> moveUpCommand = std::make_unique<MoveCommand>(pBigTom, glm::vec3{ 0,1,0 });
		//inputManager.AddMapping(0, std::move(moveUpCommand), Controller::ControllerButton::DPadUp);

		//std::unique_ptr<MoveCommand> moveDownCommand = std::make_unique<MoveCommand>(pBigTom, glm::vec3{ 0,-1,0 });
		//inputManager.AddMapping(0, std::move(moveDownCommand), Controller::ControllerButton::DPadDown);

		//std::unique_ptr<MoveCommand> moveRightCommand = std::make_unique<MoveCommand>(pBigTom, glm::vec3{ -1,0,0 });
		//inputManager.AddMapping(0, std::move(moveRightCommand), Controller::ControllerButton::DPadRight);

		//std::unique_ptr<MoveCommand> moveLeftCommand = std::make_unique<MoveCommand>(pBigTom, glm::vec3{ 1,0,0 });
		//inputManager.AddMapping(0, std::move(moveLeftCommand), Controller::ControllerButton::DPadLeft);

		//std::unique_ptr<KillCommand> damageBigTom = std::make_unique<KillCommand>(pBigTom);
		//inputManager.AddMapping(0, std::move(damageBigTom), Controller::ControllerButton::RightShoulder, InputManager::inputCondition::Press);
		//
		//std::unique_ptr<AddScoreCommand> addScoreBigTom = std::make_unique<AddScoreCommand>(pBigTom);
		//inputManager.AddMapping(0, std::move(addScoreBigTom), Controller::ControllerButton::ButtonX, InputManager::inputCondition::Press);

		//--------------------------------------------
		// KEYBOARD
		//--------------------------------------------
#pragma region MOVE COMMANDS
	//--------------------------------------------
		std::unique_ptr<StartMovingCommand> kbLeftStart = std::make_unique<StartMovingCommand>(pDigger, pGrid, MovementDirectionComponent::MovementDirection::West);
		inputManager.AddKeyboardMapping(std::move(kbLeftStart), SDL_SCANCODE_A, InputManager::inputCondition::Press);

		std::unique_ptr<MoveCommand> kbMoveLeftCommand = std::make_unique<MoveCommand>(pDigger, pGrid, MovementDirectionComponent::MovementDirection::West);
		inputManager.AddKeyboardMapping(std::move(kbMoveLeftCommand), SDL_SCANCODE_A, InputManager::inputCondition::Hold);

		std::unique_ptr<StopMovingCommand> kbLeftEnd = std::make_unique<StopMovingCommand>(pDigger);
		inputManager.AddKeyboardMapping(std::move(kbLeftEnd), SDL_SCANCODE_A, InputManager::inputCondition::Release);


		//--------------------------------------------

		std::unique_ptr<StartMovingCommand> kbUpStart = std::make_unique<StartMovingCommand>(pDigger, pGrid, MovementDirectionComponent::MovementDirection::North);
		inputManager.AddKeyboardMapping(std::move(kbUpStart), SDL_SCANCODE_W, InputManager::inputCondition::Press);

		std::unique_ptr<MoveCommand> kbMoveUpCommand = std::make_unique<MoveCommand>(pDigger, pGrid, MovementDirectionComponent::MovementDirection::North);
		inputManager.AddKeyboardMapping(std::move(kbMoveUpCommand), SDL_SCANCODE_W, InputManager::inputCondition::Hold);

		std::unique_ptr<StopMovingCommand> kbUpEnd = std::make_unique<StopMovingCommand>(pDigger);
		inputManager.AddKeyboardMapping(std::move(kbUpEnd), SDL_SCANCODE_W, InputManager::inputCondition::Release);


		//--------------------------------------------
		std::unique_ptr<StartMovingCommand> kbDownStart = std::make_unique<StartMovingCommand>(pDigger, pGrid, MovementDirectionComponent::MovementDirection::South);
		inputManager.AddKeyboardMapping(std::move(kbDownStart), SDL_SCANCODE_S, InputManager::inputCondition::Press);

		std::unique_ptr<MoveCommand> kbMoveDownCommand = std::make_unique<MoveCommand>(pDigger, pGrid, MovementDirectionComponent::MovementDirection::South);
		inputManager.AddKeyboardMapping(std::move(kbMoveDownCommand), SDL_SCANCODE_S, InputManager::inputCondition::Hold);

		std::unique_ptr<StopMovingCommand> kbDownEnd = std::make_unique<StopMovingCommand>(pDigger);
		inputManager.AddKeyboardMapping(std::move(kbDownEnd), SDL_SCANCODE_S, InputManager::inputCondition::Release);

		//--------------------------------------------
		std::unique_ptr<StartMovingCommand> kbRightStart = std::make_unique<StartMovingCommand>(pDigger, pGrid, MovementDirectionComponent::MovementDirection::East);
		inputManager.AddKeyboardMapping(std::move(kbRightStart), SDL_SCANCODE_D, InputManager::inputCondition::Press);

		std::unique_ptr<MoveCommand> kbmoveRightCommand = std::make_unique<MoveCommand>(pDigger, pGrid, MovementDirectionComponent::MovementDirection::East);
		inputManager.AddKeyboardMapping(std::move(kbmoveRightCommand), SDL_SCANCODE_D, InputManager::inputCondition::Hold);

		std::unique_ptr<StopMovingCommand> kbRightEnd = std::make_unique<StopMovingCommand>(pDigger);
		inputManager.AddKeyboardMapping(std::move(kbRightEnd), SDL_SCANCODE_D, InputManager::inputCondition::Release);


		//--------------------------------------------
#pragma endregion MOVE COMMANDS

		std::unique_ptr<MuteSoundCommand> kbMute = std::make_unique<MuteSoundCommand>();
		inputManager.AddKeyboardMapping(std::move(kbMute), SDL_SCANCODE_M, InputManager::inputCondition::Press);
		

		std::unique_ptr<ShootCommand> kbShoot = std::make_unique<ShootCommand>(pDigger);
		inputManager.AddKeyboardMapping(std::move(kbShoot), SDL_SCANCODE_SPACE, InputManager::inputCondition::Press);

		std::unique_ptr<SwapSceneCommand> kbSwapScene = std::make_unique<SwapSceneCommand>("StartScene");
		inputManager.AddKeyboardMapping(std::move(kbSwapScene), SDL_SCANCODE_F1, InputManager::inputCondition::Press);

	}
}

int main(int, char* [])
{
	SoloGameMode sgm;
	const std::string gridStructure
	{
			 "ooooooo####ooooooo##"
			 "ooooooo####ooooooo##"
			 "ooooooo####ooooooo##"
			 "oooo#oo#############"
			 "ooooooo####ooooooooo"
			 "ooooooo####ooooooooo"
			 "#oooooo####oooooooo#"
			 "###oooo####oooo#####"
			 "ooo############ooooo"
			 "oooooo#####ooooooooo"
			 "oooooo#####ooooooooo"
			 "oooooo#####ooooooooo"
			 "oooooo#####ooooooooo"
			 "oooooo#####ooooooooo"
			 "oooooo#####ooooooooo"
			 "oooooo#####ooooooooo"
			 "oooooo#####ooooooooo"
			 "oooooo#####ooooooooo"
			 "o##################o"
			 "oooooooooooooooooooo"

	};
	auto& startScene = SceneManager::GetInstance().CreateScene("StartScene");
	auto& level1 = SceneManager::GetInstance().CreateScene("LevelOne");
	auto& level2 = SceneManager::GetInstance().CreateScene("LevelTwo");
	auto& level3 = SceneManager::GetInstance().CreateScene("LevelThree");
	level1.BindOnLoad([&level1]()
		{
			LoadLevel1(&level1);
		});
	level2.BindOnLoad([&level2]()
		{
			LoadLevel2(&level2);
		});
	level3.BindOnLoad([&level3]()
		{
			LoadLevel3(&level3);
		});
	SceneManager::GetInstance().SetCurrentScene(&startScene);
	startScene.BindOnLoad([&startScene]()
		{
			StartScreen(&startScene);
		});
	dae::Minigin engine("../Data/");
	engine.Run([&startScene]()
		{
			StartScreen(&startScene);
		});
	return 0;
}