#pragma once
#include "Color.h"

class Material: public Color
{
public:
	Material()
	{}

	Material(Color color_, FPType diffusion_ = 0, FPType reflection_ = 0, FPType special_ = 0)
		:color {color_}
		, diffusion {diffusion_}
		, reflection {reflection_}
		, special {special_}
	{}

	void SetColor(Color& color_)
	{
		color = color_;
	}
	void SetDiffuse(FPType diffusion_)
	{
		diffusion = diffusion_;
	}
	void SetReflection(FPType reflection_)
	{
		reflection = reflection_;
	}
	void SetSpecial(FPType special_)
	{
		special = special_;
	}

	Color GetColor()
	{
		return color;
	}
	FPType GetSpecular()
	{
		return 1 - diffusion;
	}
	FPType GetDiffuse()
	{
		return diffusion;
	}
	FPType GetReflection()
	{
		return reflection;
	}
	FPType GetSpecial()
	{
		return special;
	}
private:
	Color color;
	FPType reflection;
	FPType diffusion; // The more diffusive it is, the better it scatters light (phong shading radius gets wider)
	FPType special; // Tile floor
};

