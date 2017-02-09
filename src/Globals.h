#pragma once

using FPType = double;

//constexpr unsigned WIDTH = 500;
//constexpr unsigned HEIGHT = 500;

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

// 15360 x 8640 16k
//constexpr FPType WIDTH = 15360;
//constexpr FPType HEIGHT = 8640;



// ULTRAWIDE

// 2560x1080 (1080p)
//constexpr FPType WIDTH = 2560;
//constexpr FPType HEIGHT = 1080;

// 3440x1440 (1440p)
//constexpr FPType WIDTH = 3440;
//constexpr FPType HEIGHT = 1440;

// 5120x2160 (4k)
//constexpr FPType WIDTH = 5120;
//constexpr FPType HEIGHT = 2160;

// 6880x2880
//constexpr FPType WIDTH = 6880;
//constexpr FPType HEIGHT = 2880;

constexpr FPType ASPECT_RATIO = WIDTH / HEIGHT;
constexpr FPType AMBIENT_LIGHT = 0.7;
constexpr FPType GLOBAL_REFRACTION = 1; // 1 = air / vacuum;
constexpr FPType BIAS = 1e-8;
constexpr unsigned SUPERSAMPLING = 1;
constexpr unsigned DEPTH = 8;
constexpr unsigned FOV = 90;

constexpr bool REFRACTIONS_ON = false;
constexpr bool REFLECTIONS_ON = true;
constexpr bool SHADOWS_ON = true;
constexpr bool SPECULAR_ON = true;
constexpr bool DIFFUSE_ON = true;
constexpr bool AMBIENT_ON = true;

// This ray tracer uses a Left hand coordinate system,
// with x pointing to the right, y up and z coming out from the screen