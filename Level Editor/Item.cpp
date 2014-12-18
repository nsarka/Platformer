#include "Item.h"


Item::Item(int xpos, int ypos, int width, int height)
{
	toolbarBounds.x = xpos;
	toolbarBounds.y = ypos;
	toolbarBounds.w = width;
	toolbarBounds.h = height;
}


Item::~Item()
{

}
