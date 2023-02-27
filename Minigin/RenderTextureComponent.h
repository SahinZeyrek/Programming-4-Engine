#pragma once
#include "Component.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <string>
namespace dae
{
	class Texture2D;

	class RenderTextureComponent final : public Component
	{
		using TextureObjectPtr = std::shared_ptr<Texture2D>;
	public:
		RenderTextureComponent(Component::GameObjectPtr owner, TextureObjectPtr texture);
	
		virtual ~RenderTextureComponent() override = default;
		virtual void Update()override;
		virtual void Render() override;
		void SetTexture(const std::string& filename);
		RenderTextureComponent(const RenderTextureComponent&) = delete;
		RenderTextureComponent(RenderTextureComponent&&) = delete;
		RenderTextureComponent& operator=(const RenderTextureComponent&) = delete;
		RenderTextureComponent& operator=(const RenderTextureComponent&&) = delete;
	private:
		TextureObjectPtr m_Texture{};
	};
};