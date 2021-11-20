#include "Animation.h"

void CAnimation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);
	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	this->frames.push_back(frame);
}

void CAnimation::Render(Vector2D position, int nx)
{
	DWORD now = GetTickCount();

	if (!this->reverse) {
		if (this->currentFrame == -1)
		{
			this->currentFrame = 0;
			this->lastFrameTime = now;
		}
		else
		{
			DWORD t = this->frames[currentFrame]->GetTime();
			if (now - this->lastFrameTime > t)
			{
				if (this->transfer) {
					this->currentFrame++;
				}
				this->lastFrameTime = now;
				if (currentFrame == frames.size()) 
					this->currentFrame = 0;
			}

		}
	}
	else {
		if (this->currentFrame == -1)
		{
			this->currentFrame = this->frames.size() - 1;
			this->lastFrameTime = now;
		}
		else
		{
			DWORD t = this->frames[currentFrame]->GetTime();
			if (now - this->lastFrameTime > t)
			{
				if (this->transfer) {
					this->currentFrame--;
				}
				this->lastFrameTime = now;
				if (currentFrame == -1)
					this->currentFrame = this->frames.size() - 1;
			}
		}
	}

	this->frames[currentFrame]->GetSprite()->Draw(position, nx);
}

void CAnimation::SetTransfer(bool value)
{
	this->transfer = value;
}

void CAnimation::SetReverse(bool value)
{
	this->reverse = value;
}

bool CAnimation::GetTransfer()
{
	return this->transfer;
}

bool CAnimation::GetReverse()
{
	return this->reverse;
}
