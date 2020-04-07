#include "Strafe.h"


auto StrafeController::GetSingleton()
-> StrafeController*
{
	static StrafeController singleton;
	return std::addressof(singleton);
}


void StrafeController::RecordChanges()
{
}
