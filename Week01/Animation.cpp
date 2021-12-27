#include "Animation.h"

CAnimation::CAnimation()
{
}

void CAnimation::Add(std::string spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);
	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	this->frames.push_back(frame);
}

void CAnimation::Render(Vector2D position, int nx, D3DCOLOR color, int layer, float rotate)
{
	DWORD now = GetTickCount64();

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
				if (!this->wait) {
					this->currentFrame++;
				}
				this->lastFrameTime = now;
				if (currentFrame == frames.size()) {
					if (this->loop == true) {
						this->currentFrame = 0;
					}
					else {
						this->finish = true;
						this->currentFrame--;
					}
				}
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
				if (!this->wait) {
					this->currentFrame--;
				}
				this->lastFrameTime = now;
				if (currentFrame == -1) {
					if (this->loop == true) {
						this->currentFrame = this->frames.size() - 1;
					}
					else {
						this->finish = true;
						this->currentFrame++;
					}
				}
			}
		}
	}

	this->frames[currentFrame]->GetSprite()->Draw(position, nx, color, layer, rotate);
}

void CAnimation::SetWait(bool value)
{
	this->wait = value;
}

void CAnimation::SetReverse(bool value)
{
	this->reverse = value;
}

bool CAnimation::IsWait()
{
	return this->wait;
}

bool CAnimation::IsReverse()
{
	return this->reverse;
}
