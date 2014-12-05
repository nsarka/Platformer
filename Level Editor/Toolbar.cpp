#include "Toolbar.h"

Toolbar::Toolbar(int xpos, int ypos, int width, int height, int r, int g, int b, int a)
{
	bounds.x = xpos;
	bounds.y = ypos;
	bounds.w = width;
	bounds.h = height;

	barColor.r = r;
	barColor.g = g;
	barColor.b = b;
	barColor.a = a;
}

void Toolbar::AddItem()
{

}

void Toolbar::RemoveItem()
{

}

Toolbar::~Toolbar()
{

}