#include "Strafe.h"


StrafeController::StrafeController()
{
	
}


void StrafeController::Reset() noexcept
{
	
}


void StrafeController::Update() noexcept
{
	
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
