#include "SophiaStateMoveBackward.h"

void CSophiaStateMoveBackward::Render(CSophia& sophia)
{
	std::unordered_map<int, LPANIMATION> animations = sophia.GetAnimations();
	LPANIMATION left_wheel = animations.at(LEFT_WHEEL);
	LPANIMATION right_wheel = animations.at(RIGHT_WHEEL);

	left_wheel->SetReverse(false);
	right_wheel->SetReverse(false);

	left_wheel->SetTransfer(true);
	right_wheel->SetTransfer(true);
}
