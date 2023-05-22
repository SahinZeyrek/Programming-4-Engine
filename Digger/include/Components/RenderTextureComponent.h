#pragma once
#include "Component.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "Renderer.h"
#include <string>
namespace dae
{

	class RenderTextureComponent final : public Component
	{
		using TextureObjectPtr = std::shared_ptr<Texture2D>;
	public:
		RenderTextureComponent(Component::GameObjectPtr owner, TextureObjectPtr texture);
	
		virtual ~RenderTextureComponent() override = default;
		virtual void Update()override;
		virtual void Render() override;
		void SetTexture(const std::string& filename);
		TextureObjectPtr GetTexture() { return m_Texture; }
		RenderTextureComponent(const RenderTextureComponent&) = delete;
		RenderTextureComponent(RenderTextureComponent&&) = delete;
		RenderTextureComponent& operator=(const RenderTextureComponent&) = delete;
		RenderTextureComponent& operator=(const RenderTextureComponent&&) = delete;
	private:
		TextureObjectPtr m_Texture{};
		glm::ivec3 m_renderPos{};
	};
};