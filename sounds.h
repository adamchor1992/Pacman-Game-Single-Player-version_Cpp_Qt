#pragma once

#include <QMediaPlayer>

class Sounds
{
public:
    Sounds();
    void PlayBeginningSound();
    void PlayEatFoodballSound1();
    void PlayEatGhostSound();
    void PlayPacmanDeathSound();
    void PlaySirenSound();

private:
    QMediaPlayer m_BeginningSound;
    QMediaPlayer m_EatFoodballSound1;
    QMediaPlayer m_EatFoodballSound2;
    QMediaPlayer m_EatGhostSound;
    QMediaPlayer m_PacmanDeathSound;
    QMediaPlayer m_Siren;
};
