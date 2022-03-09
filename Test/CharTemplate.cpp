#include "CharTemplate.h"

void CharTemplate::moveToSomeSide(CurrentDirection const& dir)
{
	if (dir == CurrentDirection::LEFT)
	{
		for (CurrentDirection dir : lockDirections)
		{
			if (dir == CurrentDirection::LEFT)
				return;
		}

		curDir = dir;
		curXLocation -= stepLength;




		if (curAnim != CurrentAnimation::ATTACK && curAnim != CurrentAnimation::JUMP)
			setAnimation(CurrentAnimation::RUN);
	}
	else if (dir == CurrentDirection::RIGHT)
	{
		for (CurrentDirection dir : lockDirections)
		{
			if (dir == CurrentDirection::RIGHT)
				return;
		}

		curDir = dir;
		curXLocation += stepLength;



		if (curAnim != CurrentAnimation::ATTACK && curAnim != CurrentAnimation::JUMP)
			setAnimation(CurrentAnimation::RUN);
	}
	else if (dir == CurrentDirection::STAY)
	{
		setAnimation(CurrentAnimation::IDLE);
	}
}

void CharTemplate::jump(CurrentDirection const& dir, int const& pressRealise)
{
	if (pressRealise)
	{
		
		if ((currentJumpHeight * (-1)) >= maxJumpHeight)
		{
			toFall = true;
			return;
		}

		if (toFall && (currentJumpHeight * (-1)) < 1)
		{
			toFall = false;
			curAnim = CurrentAnimation::IDLE;
			return;
		}

		if (toFall)
		{
			currentJumpHeight += jumpStep;
			curYLocation += jumpStep;
			return;
		}

		curAnim = CurrentAnimation::JUMP;
		currentJumpHeight -= jumpStep;
		curYLocation -= jumpStep;

		return;
		
	}
	else
	{
		toFall = true;
	}
}

void CharTemplate::toFallCont()
{
	if (toFall)
	{
		for (CurrentDirection dir : lockDirections)
		{
			if (dir == CurrentDirection::BOT)
			{
				toFall = false;
				firstFall = false;
				curAnim = CurrentAnimation::IDLE;
				return;
			}
		}

		
		if (!firstFall)
		{
			curYLocation += jumpStep;
			currentJumpHeight += jumpStep;
			return;
		}
		curYLocation += jumpStep;
		return;
		
	}
	
}



