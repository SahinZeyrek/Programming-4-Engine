#include "MoveRightCommand.h"
#include "Time.h"
namespace dae
{
	void MoveRightCommand::Execute()
	{
		auto pos = m_ObjectPtr->GetWorldPosition();
		pos.x += m_ObjectPtr->GetSpeed() * Time::deltaTime;
		m_ObjectPtr->SetPosition(pos.x, pos.y);
	}
}