#include "sounds.h"

Sounds::Sounds()
{
    m_BeginningSound.setMedia(QUrl("qrc:/sounds/pacman_beginning.wav"));
    m_EatFoodballSound1.setMedia(QUrl("qrc:/sounds/pacman_eat.wav"));
    m_EatFoodballSound2.setMedia(QUrl("qrc:/sounds/pacman_eat.wav"));
    m_EatGhostSound.setMedia(QUrl("qrc:/sounds/pacman_eatghost.wav"));
    m_PacmanDeathSound.setMedia(QUrl("qrc:/sounds/pacman_death.wav"));
    m_Siren.setMedia(QUrl("qrc:/sounds/pacman_siren.wav"));
}

void Sounds::PlayBeginningSound()
{
    m_BeginningSound.play();
}

void Sounds::PlayEatFoodballSound1()
{
    if(m_EatFoodballSound1.state()==QMediaPlayer::StoppedState)
    {
        m_EatFoodballSound1.play();
    }

    if(m_EatFoodballSound1.state()==QMediaPlayer::PlayingState)
    {
        m_EatFoodballSound2.play();
    }
}

void Sounds::PlayEatGhostSound()
{
    m_EatGhostSound.play();
}

void Sounds::PlayPacmanDeathSound()
{
    m_PacmanDeathSound.play();
}

void Sounds::PlaySirenSound()
{
    m_Siren.play();
}
