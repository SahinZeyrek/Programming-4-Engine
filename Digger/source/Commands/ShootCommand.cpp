#include "ShootCommand.h"
#include "ProjectileComponent.h"
namespace dae
{
	void ShootCommand::Execute()
	{
		m_Target->GetComponent<ProjectileComponent>()->Shoot();
	}

	ShootCommand::ShootCommand(GameObject* target) : m_Target(target)
	{
	}
}

