#include "resources.hpp"

using namespace sf;
Texture t_sprTitle("res/img/title.png");
Sprite sprTitle(t_sprTitle);

Texture t_sprSelect("res/img/select.png");
Sprite sprSelect(t_sprSelect);

Texture t_sprOffice("res/img/office.png");
Sprite sprOffice(t_sprOffice);

SoundBuffer sndBfrTitle("res/snd/title.wav");
Sound sndTitle(sndBfrTitle);

SoundBuffer sndBfrSelect("res/snd/select.wav");
Sound sndSelect(sndBfrSelect);

SoundBuffer sndBfrBoop("res/snd/boop.wav");
Sound sndBoop(sndBfrBoop);