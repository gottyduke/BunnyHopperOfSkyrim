#include "Crouch.h"


auto CrouchController::GetSingleton()
-> CrouchController*
{
	static CrouchController singleton;
	return std::addressof(singleton);
}
