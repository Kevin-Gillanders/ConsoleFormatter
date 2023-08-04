#pragma once

struct ColourStruct
{
	int r;
	int g;
	int b;

	ColourStruct() {}
	ColourStruct(int r, int g, int b)
		: r(r), g(g), b(b)
	{
	}
};