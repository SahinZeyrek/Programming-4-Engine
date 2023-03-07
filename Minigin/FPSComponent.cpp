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
			m_TextComp->SetText(std::to_string(m_FPS) + " FPS");
			m_TextComp->Update();
			m_Timer -= m_MaxTime;
			m_FPS = 0;
		}
	}
	void FPSComponent::Render()
	{
		m_TextComp->Render();
	}
	FPSComponent::TextCompPtr FPSComponent::GetTextureComp() const
	{
		return GetOwner()->GetComponent<RenderTextComponent>();
	}
	FPSComponent::FPSComponent(GameObjectPtr owner) : Component(owner)
	{
		m_TextComp = GetTextureComp();
	}

	FPSComponent::~FPSComponent()
	{
	}
	

}
