#include "RenderTextComponent.h"
#include "TextObject.h"
namespace dae
{
	RenderTextComponent::RenderTextComponent(GameObjectPtr owner, TextObjectPtr to) : Component(owner)
	{
		m_pTextObject = to;
	}
	void RenderTextComponent::Render()
	{
		
		m_pTextObject->Render();
	}

	void RenderTextComponent::Update()
	{
	}
	
}

