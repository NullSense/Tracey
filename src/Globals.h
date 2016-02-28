#pragma once

using FPType = double;

// 1920 x 1080p
//extern constexpr FPType WIDTH = 1920;
//extern constexpr FPType HEIGHT = 1080;

// 2560 x 1440p
//extern constexpr FPType WIDTH = 2560;
//extern constexpr FPType HEIGHT = 1440;

// 3840 x 2160 4k
//extern constexpr FPType WIDTH = 3840;
//extern constexpr FPType HEIGHT = 2160;

// 7680 x 4320 8k

//extern constexpr FPType WIDTH = 7680;
//extern constexpr FPType HEIGHT = 4320;

// 7680 x 4320 16k (~1min for 5 spheres 1 plane)
extern constexpr FPType WIDTH = 15360;
extern constexpr FPType HEIGHT = 8640;


extern constexpr FPType ASPECTRATIO = WIDTH / HEIGHT;
extern constexpr FPType AMBIENTLIGHT = 1;
extern constexpr FPType TOLERANCE = 0.0000001;