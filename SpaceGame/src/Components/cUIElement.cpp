#include "cUIElement.h"


cUIElement::cUIElement(const char* text)
{
	sprintf_s(_text, text);
}

cUIElement::~cUIElement()
{

}