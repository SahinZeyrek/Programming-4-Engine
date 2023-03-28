#include "MoveDownCommand.h"
#include "Time.h"
namespace dae
{
	void MoveDownCommand::Execute()
	{
		auto pos = m_ObjectPtr->GetWorldPosition();
		pos.y += m_ObjectPtr->GetSpeed() * Time::deltaTime;
		m_ObjectPtr->SetPosition(pos.x, pos.y);
	}
}