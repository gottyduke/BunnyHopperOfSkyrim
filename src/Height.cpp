#include "Height.h"


auto HeightController::GetSingleton()
-> HeightController*
{
	static HeightController singleton;
	return std::addressof(singleton);
}
