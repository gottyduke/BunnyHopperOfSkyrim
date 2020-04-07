#include "Strafe.h"


auto StrafeController::GetSingleton()
-> StrafeController*
{
	static StrafeController singleton;
	return std::addressof(singleton);
}


void StrafeController::RecordChanges()
{
	auto& camera = player->GetLookingAtLocation();

	//_DMESSAGE("x %f", abs(camera.x - pos.x));
	//_DMESSAGE("y %f", abs(camera.y - pos.y));
}


void StrafeController::SetBase()
{
	auto& camera = player->GetLookingAtLocation();

	pos.x = camera.x;
	pos.y = camera.y;
}
