#pragma once

constexpr unsigned int WIDTH = 1920;
constexpr unsigned int HEIGHT = 1080;

constexpr double AMBIENT_LIGHT = 0.6;
constexpr double GLOBAL_REFRACTION = 1;  // 1 = air / vacuum;
constexpr double BIAS = 1e-8;
constexpr unsigned SUPERSAMPLING = 1;
constexpr unsigned DEPTH =
    15;  // not checking for hall of mirrors effect try allocating more memory
constexpr unsigned FOV = 50;

constexpr bool REFRACTIONS_ON = true;
constexpr bool REFLECTIONS_ON = true;
constexpr bool SPECULAR_ON = true;
constexpr bool SHADOWS_ON = true;
constexpr bool DIFFUSE_ON = true;
constexpr bool AMBIENT_ON = true;

constexpr bool SMOOTH_SHADING = true;

// This ray tracer uses a Left hand coordinate system,
// with x pointing to the right, y up and z coming out from the screen
