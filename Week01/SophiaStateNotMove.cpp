#include "SophiaStateNotMove.h"

void CSophiaStateNotMove::Render(CSophia& sophia)
{
	std::unordered_map<int, LPANIMATION> animations = sophia.GetAnimations();
	LPANIMATION left_wheel = animations.at(LEFT_WHEEL);
	LPANIMATION right_wheel = animations.at(RIGHT_WHEEL);

	left_wheel->SetWait(true);
	right_wheel->SetWait(true);
}
