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
#include "TextObject.h"
#include "Scene.h"
using namespace dae;
// ADD TextObject to the render component
void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	GameObject* gameObj = new GameObject();
	RenderTextureComponent* rt_Background = new RenderTextureComponent(gameObj, nullptr);
	gameObj->AddComponent(rt_Background);
	gameObj->GetComponent<RenderTextureComponent>()->SetTexture("background.tga");
	scene.Add(gameObj);

	//gameObj = std::make_shared<dae::GameObject>();
	//auto rt_Logo = std::make_shared<RenderTextureComponent>(gameObj, nullptr);
	//gameObj->AddComponent(rt_Logo);
	//gameObj->GetComponent<RenderTextureComponent>()->SetTexture("logo.tga");
	//gameObj->SetPosition(216, 180);
	//scene.Add(gameObj);

	//auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//auto to = std::make_shared<dae::TextObject>("Programming 4 Assignment", font);
	//auto renderTextComp = std::make_shared<RenderTextComponent>(gameObj, to);
	//gameObj->AddComponent(renderTextComp);
	//to->SetPosition(80, 20);
	//scene.Add(gameObj);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);

    return 0;
}