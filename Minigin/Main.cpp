#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "RenderTextureComponent.h"
#include "RenderTextComponent.h"
#include "FPSComponent.h"
#include "TextObject.h"
#include "Scene.h"
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

	pGameObj = new GameObject();
	auto rtu_Logo = new RenderTextureComponent(pGameObj, nullptr);
	pGameObj->AddComponent(rtu_Logo);
	pGameObj->GetComponent<RenderTextureComponent>()->SetTexture("logo.tga");
	pGameObj->SetPosition(216, 180);
	scene.Add(pGameObj);

	pGameObj = new GameObject();
	auto pFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 14);
	auto pTO = new TextObject("FPS", pFont);
	auto fps_Counter = new FPSComponent(pGameObj, pTO);
	pGameObj->AddComponent(fps_Counter);
	pGameObj->SetPosition(80, 50);
	scene.Add(pGameObj);
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