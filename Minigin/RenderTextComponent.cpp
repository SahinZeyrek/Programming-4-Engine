#include "RenderTextComponent.h"
#include "TextObject.h"
#include "Font.h"
namespace dae
{
	using TextObjectPtr = TextObject*;
	RenderTextComponent::RenderTextComponent(GameObjectPtr owner, TextObjectPtr to) : Component(owner)
	{
		m_pTextObject = to;
		m_pTextObject->Update();
	}
	RenderTextComponent::~RenderTextComponent()
	{
		delete m_pTextObject;
		m_pTextObject = nullptr;
	}
	void RenderTextComponent::Render()
	{
		
		m_pTextObject->Render();
	}

	void RenderTextComponent::Update()
	{
		m_pTextObject->Update();
	}

	void RenderTextComponent::SetTexture(const Font& font)
	{
		if (font.GetFont())return;
	}

	TextObjectPtr RenderTextComponent::GetTexture()
	{
		return m_pTextObject;
	}
	
}

