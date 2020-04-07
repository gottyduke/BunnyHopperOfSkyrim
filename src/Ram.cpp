#include "Ram.h"


auto RamController::GetSingleton()
-> RamController*
{
	static RamController singleton;
	return std::addressof(singleton);
}


