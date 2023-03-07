#pragma once

// Hulp van Liam Wullaert
// UTILITY STRUCT 

struct Time final
{
	Time() = delete; // prevent construction
	static inline float deltaTime{ 0.0f }; 
	static inline const float fixedDeltaTime{ 1 / 30.f }; // update of 30 fps
	static inline constexpr float desiredFPS{ 144.f };
	static inline constexpr int frameTimeMs{ 1000 / static_cast<int>(desiredFPS) };
	
};

