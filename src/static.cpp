#include "static.hpp"
#include "globals.hpp"
using namespace sf;

sf::Clock clocky; //because u cant name it "clock"

constexpr auto updateFrame = 15;
int frameCounter = 0; // ONLY UPDATE EVERY 15 FRAMES

bool shouldUpdate()
{
	if (frameCounter++ == updateFrame)
	{
		frameCounter = 0;
		return true;
	}
	return false;
}

static const int width = 886>>1, height = 720>>1; // actually just use half of the thingies provided, but scale the thing later

void renderGeneralStatic(RenderWindow& window)
{

	static Image img;
	static bool init = false;
	static Texture texture;

	static Sprite* ptrSpr = nullptr;

	if (!init)
	{
		init = true;
		img.resize({ width, height });
		texture.loadFromImage(img);
	}
	if (shouldUpdate())
	{
		static Sprite spr(texture);
		static bool initSpr = true;
		if (initSpr)
		{
			spr.setScale({ 2.f, 2.f });
			initSpr = true;
			ptrSpr = &spr;
		}
		for (uint16_t i = 0; i < width; ++i)
			for (uint16_t j = 0; j < height; ++j)
			{
				img.setPixel({ i, j }, sf::Color(randRange(0, 255), randRange(0, 255), randRange(0, 255), randRange(0, 100)));
			}
		texture.update(img);
	}
	if (ptrSpr) window.draw(*ptrSpr);
}

bool renderStaticOnUpdate(RenderWindow& window)
{
    static Image img;
    static bool playing = false;
    static bool init = false;
    static Texture texture;
    static Sprite* ptrSpr = nullptr;

    if (!init)
    {
        init = true;
        img.resize({ width, height });
        texture.loadFromImage(img);
    }

    if (!playing)
    {
        playing = true;
        clocky.restart();
    }

    if (clocky.getElapsedTime().asSeconds() > 0.3f)
    {
        playing = false;
        return false;
    }

    if (shouldUpdate())
    {
        static Sprite spr(texture);
        static bool initSpr = true;
        if (initSpr)
        {
            spr.setScale({ 2.f, 2.f });
            initSpr = false;
            ptrSpr = &spr;
        }
        for (uint16_t i = 0; i < width; ++i)
            for (uint16_t j = 0; j < height; ++j)
            {
               // uint8_t binaryColor = randRange(0, 1) == 0 ? 0 : 255; // BINARY
                uint8_t binaryColor = randRange(0, 255); //GRAYSCALE, STILL CALLED BINARY CUZ IM LAZY
                img.setPixel({ i, j }, sf::Color(binaryColor, binaryColor, binaryColor));
            }
        texture.update(img);
    }

    if (ptrSpr) window.draw(*ptrSpr);
    return true;
}
