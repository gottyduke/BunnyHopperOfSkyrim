#pragma once

#include "RE/Skyrim.h"


template <class T>
class IController
{
public:
	struct NiPoint3
	{
		float x;
		float y;
		float z;
	};
	STATIC_ASSERT(sizeof(NiPoint3) == 0xc);

	virtual void Halt() noexcept = 0;


	IController(const IController&) = delete;
	IController(IController&&) = delete;

	IController& operator=(const IController&) = delete;
	IController& operator=(IController&&) = delete;

	T* operator->() { return singleton; }
	T& operator*() { return *singleton; }
	const T* operator->() const { return singleton; }
	const T& operator*() const { return *singleton; }
	
protected:
	IController() = default;
	virtual ~IController() = default;

	virtual void Reset() noexcept = 0;
	virtual void Update() noexcept = 0;

	RE::PlayerCharacter* player = RE::PlayerCharacter::GetSingleton();
	RE::PlayerCamera* camera = RE::PlayerCamera::GetSingleton();
	RE::bhkCharacterController* bhk = player->GetCharController();

private:
	static T* singleton;
};


template <class T>
T* IController<T>::singleton;