#include "RenderTextureComponent.h"
#include "Texture2D.h"
#include "GameObject.h"

namespace dae
{
	RenderTextureComponent::RenderTextureComponent(Component::GameObjectPtr owner, TextureObjectPtr texture) : Component(owner)
	{
		m_Texture = texture;
	}

	void RenderTextureComponent::Update()
	{

	}

	void RenderTextureComponent::Render()
	{
		Renderer::GetInstance().RenderTexture(*(m_Texture.get()), GetOwnerPosition().x, GetOwnerPosition().y);
	}

	void RenderTextureComponent::SetTexture(const std::string& filename)
	{
		m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
	}

}
