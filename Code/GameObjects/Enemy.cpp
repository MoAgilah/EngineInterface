#include "Enemy.h"

#include "../Engine/Core/GameManager.h"

Enemy::Enemy(std::shared_ptr<IDrawable> drawable, std::shared_ptr<IBoundingVolume> volume, int maxLives)
    : DynamicGameObject(drawable, volume), m_numLives(maxLives), m_maxLives(maxLives),
    m_airTimer(0), m_resetTimer(0), m_activationTimer(0)
{
}

void Enemy::Update(float deltaTime)
{
    if (GetActive())
    {
        Animate(deltaTime);

        if (!HasLifes())
        {
            m_activationTimer.Update(deltaTime);
            if (m_activationTimer.CheckEnd())
                m_isAlive = false;
        }
    }
    else
    {
        if (!m_resetAllowed)
        {
            m_resetTimer.SetCurrTime(1);
            m_resetAllowed = true;
        }

        if (m_resetAllowed)
        {
            m_resetTimer.Update(deltaTime);
            if (m_resetTimer.CheckEnd())
            {
                // need to make generic
                /*if (GameManager::Get()->GetCamera()->CheckVerticalBounds(GetBoundingBox()))
                    Reset();*/
            }
        }
    }
}

void Enemy::OnCollisionEnter(IGameObject* obj)
{
}

void  Enemy::OnCollisionStay(IGameObject* obj)
{

}

void  Enemy::OnCollisionExit(IGameObject* obj)
{

}

void  Enemy::ResolveCollisions(float time, const Vector2f& separationVector, float relativeHitPosition)
{

}

void Enemy::Reset()
{
    DynamicGameObject::Reset();

    m_isAlive = true;
    m_numLives = m_maxLives;
    m_resetAllowed = false;
    m_invulnerable = false;

    m_resetTimer.RestartTimer();
    m_activationTimer.RestartTimer();
}

void Enemy::DecrementLife()
{
    if (--m_numLives == 0)
        Die();
}

void Enemy::SetAirTime(float time)
{
    m_airTimer.SetCurrTime(time);
}

void Enemy::SetTimeLeftActive(float time)
{
    m_activationTimer.SetCurrTime(time);
}
