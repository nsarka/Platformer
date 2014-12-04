#include "Item.h"


Item::Item(int xpos, int ypos, int width, int height)
{
	bounds.x = xpos;
	bounds.y = ypos;
	bounds.w = width;
	bounds.h = height;
}


Item::~Item()
{

}
