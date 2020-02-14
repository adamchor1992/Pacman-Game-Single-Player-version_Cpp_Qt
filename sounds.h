#ifndef SOUNDS_H
#define SOUNDS_H

#include <QMediaPlayer>

struct Sounds
{
    Sounds();

    QMediaPlayer m_BeginningSound;
    QMediaPlayer m_EatSound1;
    QMediaPlayer m_EatSound2;
    QMediaPlayer m_EatGhostSound;
    QMediaPlayer m_PacmanDeathSound;
    QMediaPlayer m_PacmanSiren;
};

#endif // SOUNDS_H
