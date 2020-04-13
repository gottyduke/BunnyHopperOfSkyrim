# BunnyHopperOfSkyrim

## Build Dependencies
* [Json2Settings](https://github.com/Ryan-rsm-McKenzie/Json2Settings)
* [CommonLibSSE](https://github.com/Ryan-rsm-McKenzie/CommonLibSSE)

## End User Dependencies
* [SKSE64](https://skse.silverlock.org/)
* [Address Library](https://www.nexusmods.com/skyrimspecialedition/mods/32444)

## Settings
Setting | Type | Default | Description
--- | --- | --- | ---
`globalSpeedMult` | float | 1.0 | Global speed multiplier
`maxSpeed` | float | 450.0 | Maximum speed allowed
`baseSpeedBoost` | float | 3.0 | Base speed gain after each consecutive jump
`baseSpeedMult` | float | 1.0 | Base speed gain multiplier
`minStrafeAngle` | float | 35.0 | Minimum profitable strafe angle threshold
`maxStrafeAngle` | float | 85.0 | Maximum profitable strafe angle cap
`strafeDeadzone` | float | 35.0 | Non-profitable strafe angle after threshold
`strafeSpeedMult` | float | 1.0 | Speed gain multiplier after each successful strafe
`minHeightLaunch` | float | 140.0 | Minimum landing height to gain a launch boost
`heightLaunchMulti` | float | 1.0 | Speed gain multiplier after each successful height launch
`crouchSpeedBoost` | float | 3.0 | Speed gain for crouching during landing
`crouchSpeedMult` | float | 1.0 | Speed gain multiplier after a successful crouch boost
`crouchBoostCooldown` | int | 6 | Number of successful jumps required to regain crouch boost
`ramDamage` | float | 5.0 | Base damage dealt when ramming objects when bhopping
`ramDamageMult` | float | 0.2 | Ram damage multiplier based on current speed
`ramSpeedThreshold` | float | 220.0 | Minimum speed required to initiate ram
`ramSpeedReduction` | float | 0.5 | Speed loss multiplier after ramming
`enableTrail` | bool | true | Enable the visiable ray trail when bhopping
`enableSimulation` | bool | fasle | Use implmented motion system to simulate force & ragdoll instead of script level fake
