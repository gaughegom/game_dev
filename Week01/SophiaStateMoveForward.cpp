#include "SophiaStateMoveForward.h"

void CSophiaStateMoveForward::Render(CSophia& sophia)
{
	auto left_wheel = sophia.GetAnimations().at(LEFT_WHEEL);
	auto right_wheel = sophia.GetAnimations().at(RIGHT_WHEEL);
	
	left_wheel->SetReverse(true);
	right_wheel->SetReverse(true);

	left_wheel->SetWait(false);
	right_wheel->SetWait(false);
}
