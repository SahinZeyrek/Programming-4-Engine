#include "KillCommand.h"
#include "HealthComponent.h"
namespace dae
{
	void KillCommand::Execute()
	{
		m_Target->GetComponent<HealthComponent>()->TakeDamage(999);
	}

}

