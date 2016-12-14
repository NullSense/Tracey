#pragma once

using FPType = double;

// 1920 x 1080p
constexpr FPType WIDTH = 1920;
constexpr FPType HEIGHT = 1080;

// 2560 x 1440p
//constexpr FPType WIDTH = 2560;
//constexpr FPType HEIGHT = 1440;

// 3840 x 2160 4k
//constexpr FPType WIDTH = 3840;
//constexpr FPType HEIGHT = 2160;

// 7680 x 4320 8k
//constexpr FPType WIDTH = 7680;
//constexpr FPType HEIGHT = 4320;

// 7680 x 4320 16k
//constexpr FPType WIDTH = 15360;
//constexpr FPType HEIGHT = 8640;

constexpr FPType ASPECT_RATIO = WIDTH / HEIGHT;
constexpr FPType AMBIENT_LIGHT = 0.8;
constexpr FPType TOLERANCE = 0.000001;
constexpr int SUPERSAMPLING = 4;

constexpr bool REFLECTIONS_ON = false;
constexpr bool SPECULAR_ON = true;
constexpr bool SHADOWS_ON = false;
constexpr bool DIFFUSE_ON = true;
