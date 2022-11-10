#include "Enemy.h"
#include <iostream>

Enemy::Enemy(int x, int y, int deltaX, int deltaY)
	: PlaceableActor(x, y)
	, m_currentMovementX(0)
	, m_currentMovementY(0)
	, m_directionX(0)
	, m_directionY(0)
	, m_movementInX(deltaX)
	, m_movementInY(deltaY)
{
	if (m_movementInX != 0)
	{
		m_directionX = 1;
	}
	if (m_movementInY != 0)
	{
		m_directionY = 1;
	}
}

void Enemy::Draw()
{
	std::cout << (char)153;
}

//First if checks for multiple directions and iterates through them second if group is for single direction movement
void Enemy::Update()
{
	if (m_movementInX != 0 && m_movementInY != 0)
	{
		if (m_directionX == 1 && m_directionY == 1) // Starting Position update X
		{
			this->SetPosition(m_pPosition->x + m_directionX, m_pPosition->y);
			UpdateDirection(m_currentMovementX, m_directionX, m_movementInX);			
		}
		else if (m_directionX == -1 && m_directionY == 1) // End of first side update Y
		{
			this->SetPosition(m_pPosition->x, m_pPosition->y + m_directionY);
			UpdateDirection(m_currentMovementY, m_directionY, m_movementInY);			
		}
		else if (m_directionX == -1 && m_directionY == -1) //end of second side update X
		{
			this->SetPosition(m_pPosition->x + m_directionX, m_pPosition->y);
			UpdateDirection(m_currentMovementX, m_directionX, m_movementInX);
		}
		else //end of third side return to starting point Update Y
		{
			this->SetPosition(m_pPosition->x, m_pPosition->y + m_directionY);
			UpdateDirection(m_currentMovementY, m_directionY, m_movementInY);
		}
	}
	else
	{
		if (m_movementInX != 0)
		{
			UpdateDirection(m_currentMovementX, m_directionX, m_movementInX);
		}
		if (m_movementInY != 0)
		{
			UpdateDirection(m_currentMovementY, m_directionY, m_movementInY);
		}
		this->SetPosition(m_pPosition->x + m_directionX, m_pPosition->y + m_directionY);
	}
	
}

void Enemy::UpdateDirection(int& current, int& direction, int& movement)
{
	current += direction;
	if (std::abs(current) >= movement)
	{
		current = movement * direction;
		direction *= -1;
	}
}