#pragma once
#include "Color.h"

class Material: public Color
{
public:
	Material()
	{}

	Material(Color color_, FPType ambient_ = 1, FPType reflective_ = 0, FPType refractive_ = 0, FPType diffusive_ = 1, FPType special_ = 0)
		:color {color_}
		, ambient {ambient_}
		, reflective {reflective_}
		, refractive {refractive_}
		, diffusive {diffusive_}
		, special {special_}
	{}

	void SetColor(const Color &color_)
	{
		color = color_;
	}
	void SetDiffuse(const FPType diffusive_)
	{
		diffusive = diffusive_;
	}
	void SetReflection(const FPType reflective_)
	{
		reflective = reflective_;
	}
	void SetRefraction(const FPType refractive_)
	{
		refractive = refractive_;
	}
	void SetSpecial(const FPType special_)
	{
		special = special_;
	}

	Color GetColor()
	{
		return color;
	}
	FPType GetAmbient()
	{
		return ambient;
	}
	FPType GetSpecular()
	{
		return 1 - diffusive;
	}
	FPType GetDiffuse()
	{
		return diffusive;
	}
	FPType GetReflection()
	{
		return reflective;
	}
	FPType GetRefraction()
	{
		return refractive;
	}
	FPType GetSpecial()
	{
		return special;
	}

private:
	Color color;
	FPType ambient;
	FPType reflective;
	FPType refractive;
	FPType diffusive; // The more diffusive it is, the better it scatters light (phong shading radius gets wider)
	FPType glossy;
	FPType special; // Tile floor
};

