#pragma once

#include "FNV1A.h"  // hash_64_fnv1a_const, hash_64_fnv1a

#include "RE/Skyrim.h"


enum class Anim : std::uint64_t
{
	kUp = hash_64_fnv1a_const("jumpup"),
	kFall = hash_64_fnv1a_const("jumpfall"),
	kFallDirectional = hash_64_fnv1a_const("jumpfalldirectional"),
	kLandEnd = hash_64_fnv1a_const("jumplandend"),
	kDown = hash_64_fnv1a_const("jumpdown"),
	kFootLeft = hash_64_fnv1a_const("footleft"),
	kFootRight = hash_64_fnv1a_const("footright"),
	kGraphDeleting = hash_64_fnv1a_const("graphdeleting")
};


Anim HashAnimation(const char* a_str, std::uint32_t a_len);
Anim HashAnimation(const RE::BSFixedString& a_str);
