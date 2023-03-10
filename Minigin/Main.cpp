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
#include "RotatorComponent.h"
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

	auto pInvisGameObj = new GameObject();
	pInvisGameObj->SetPosition(216, 180);
	scene.Add(pInvisGameObj);

	auto pBigTom = new GameObject();
	auto rtu_FunnyMan = new RenderTextureComponent(pBigTom, nullptr);
	pBigTom->AddComponent(rtu_FunnyMan);
	pBigTom->GetComponent<RenderTextureComponent>()->SetTexture("funny-man.tga");
	auto rotComp1 = new RotatorComponent(pBigTom, 100, 0.0174533f ); // 1 deg to rad 
	pBigTom->SetPosition(216, 180);
	pBigTom->SetParent(pInvisGameObj, true);
	scene.Add(pBigTom);

	auto pTinyTom = new GameObject();
	auto rtu_FunnyTinyMan = new RenderTextureComponent(pTinyTom, nullptr);
	pTinyTom->AddComponent(rtu_FunnyTinyMan);
	pTinyTom->GetComponent<RenderTextureComponent>()->SetTexture("funny-tiny-man.tga");
	auto rotComp2 = new RotatorComponent(pTinyTom, 50, 0.0174533f * 4 ); // 1 deg to rad(hard coded just for testing, wanted it to be 4 times faster)
	pBigTom->AddComponent(rotComp1);
	pTinyTom->AddComponent(rotComp2);
	pTinyTom->SetPosition(150, 120);
	pTinyTom->SetParent(pBigTom, true);
	scene.Add(pTinyTom);

	pGameObj = new GameObject();
	auto pFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 14);
	auto renderText = new RenderTextComponent(pGameObj, " ", pFont);
	pGameObj->AddComponent(renderText);
	auto fps_Counter = new FPSComponent(pGameObj);
	pGameObj->AddComponent(fps_Counter);
	pGameObj->SetPosition(10, 5);
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