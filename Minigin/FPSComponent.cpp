#include "FPSComponent.h"
#include "RenderTextComponent.h"
#include "Time.h"
#include "TextObject.h"
#include "TextObject.h"
namespace dae
{
	void FPSComponent::Update()
	{
		m_Timer += Time::deltaTime;
		++m_FPS;
		if (m_Timer > m_MaxTime)
		{
			m_TextureObj->SetText(std::to_string(m_FPS) + " FPS");
			m_TextureObj->Update();
			m_Timer -= m_MaxTime;
			m_FPS = 0;
		}
	}
	void FPSComponent::Render()
	{
		m_TextureObj->Render();
	}
	FPSComponent::TextObjectPtr FPSComponent::GetTextureComp() const
	{
		return m_TextureObj;
	}
	FPSComponent::FPSComponent(GameObjectPtr owner, TextObjectPtr txt) : Component(owner)
	{
		m_TextureObj = txt;
		m_TextureObj->Update();
	}

	FPSComponent::~FPSComponent()
	{
		delete m_TextureObj;
		m_TextureObj = nullptr;
	}
	

}
