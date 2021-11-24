#include "ControllerObject.h"

void CControllerObject::Select(bool value)
{
	this->selected = value;
}

void CControllerObject::AlterSelect()
{
	this->selected = !this->selected;
}

bool CControllerObject::IsSelected()
{
	return this->selected;
}
