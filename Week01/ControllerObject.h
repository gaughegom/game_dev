#pragma once
#ifndef _CONTROLLER_OBJECT_H
#define _CONTROLLER_OBJECT_H

#include "GameObject.h"

class CControllerObject
{
private:
	bool selected = false;

public:
	void Select(bool value);
	void AlterSelect(); // toggle selected
	bool IsSelected();
};

#endif // !_CONTROLLER_OBJECT_H
