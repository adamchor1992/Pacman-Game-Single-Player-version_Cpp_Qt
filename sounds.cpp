#include "sounds.h"

Sounds::Sounds()
{
    beginning_sound = new QMediaPlayer;
    eat_sound1 = new QMediaPlayer;
    eat_sound2 = new QMediaPlayer;
    eat_ghost_sound = new QMediaPlayer;
    pacman_death_sound = new QMediaPlayer;
    pacman_siren = new QMediaPlayer;

    beginning_sound->setMedia(QUrl("qrc:/sounds/pacman_beginning.wav"));
    eat_sound1->setMedia(QUrl("qrc:/sounds/pacman_eat.wav"));
    eat_sound2->setMedia(QUrl("qrc:/sounds/pacman_eat.wav"));
    eat_ghost_sound->setMedia(QUrl("qrc:/sounds/pacman_eatghost.wav"));
    pacman_death_sound->setMedia(QUrl("qrc:/sounds/pacman_death.wav"));
    pacman_siren->setMedia(QUrl("qrc:/sounds/pacman_siren.wav"));
}

Sounds::~Sounds()
{
    delete beginning_sound;
    delete eat_sound1;
    delete eat_sound2;
    delete eat_ghost_sound;
    delete pacman_death_sound;
    delete pacman_siren;
}
