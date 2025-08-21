#include "game.hpp"
#include "globals.hpp"
#include "resources.hpp"
using namespace sf;

Night night7(0, 0, 0, 0, 7);

Texture t_sprMenu("res/img/menu.png");
Sprite sprMenu(t_sprMenu);

bool spamton = false;

void customNight(RenderWindow& window)
{
	if (spamton)
		goto SPAMTON; // y e s

	window.draw(sprMenu);

	static const float yStart = 478, yEnd = 533;
	static const rectPoint down1({ 170.f, yStart }, { 200, yEnd });
	static const rectPoint up1({ 320.f, yStart }, { 350, yEnd });

	static const rectPoint down2({ 425.f, yStart }, { 455, yEnd });
	static const rectPoint up2({ 575.f, yStart }, { 605, yEnd });

	static const rectPoint down3({ 685.f, yStart }, { 715.f, yEnd });
	static const rectPoint up3({ 835.f, yStart }, { 865.f, yEnd });

	static const rectPoint down4({ 940.f, yStart }, { 970, yEnd });
	static const rectPoint up4({ 1085.f, yStart }, { 1132, yEnd });

	static rectPoint titleButton({ 0.f, 0.f }, { 72.f, 28.f });

	static int a = 0, b = 0, c = 0, d = 0;

	Vector2i mousePosI = Mouse::getPosition(window);
	Vector2f mousePos = window.mapPixelToCoords(mousePosI);

	auto wrapValue = [](int v) {
		if (v > 20) return 0;
		if (v < 0)  return 20;
		return v;
		};

	a = wrapValue(a);
	b = wrapValue(b);
	c = wrapValue(c);
	d = wrapValue(d);


	static Text text(font);
	static const Vector2f distance = { 255.f, 0 };

	text.setPosition({ 255, 488 });
	text.setString(std::to_string(a));
	window.draw(text);

	text.setPosition(text.getPosition() + distance);
	text.setString(std::to_string(b));
	window.draw(text);

	text.setPosition(text.getPosition() + distance);
	text.setString(std::to_string(c));
	window.draw(text);

	text.setPosition(text.getPosition() + distance);
	text.setString(std::to_string(d));
	window.draw(text);

	if (!click) return;

	int val = a + b + c + d;

	if (isInsideRect(down1, mousePos)) a--;
	if (isInsideRect(up1, mousePos)) a++;

	if (isInsideRect(down2, mousePos)) b--;
	if (isInsideRect(up2, mousePos)) b++;

	if (isInsideRect(down3, mousePos)) c--;
	if (isInsideRect(up3, mousePos)) c++;

	if (isInsideRect(down4, mousePos)) d--;
	if (isInsideRect(up4, mousePos)) d++;

	//not too elegant but it's just 4 buttons

	if (a + b + c + d != val) //if change happend
		sndSelect.play();

	if (isInsideRect(titleButton, mousePos))

	{
		sndSelect.play();
		initTitle();
		game.currentState = GameState::Title;
		return;
	}
	night7.AILEVELS[0] = a;
	night7.AILEVELS[1] = b;
	night7.AILEVELS[2] = c;
	night7.AILEVELS[3] = d;


	if (isInsideRect(rectPoint({ 1017, 622 }, { 1185, 676 }), mousePos))
	{

		if (a == 1 && b == 9 && d == 7)
		{
			if (c == 9)
			{
				spamton = true;
				return;
			}
			else if (c == 8)
			{
				c = 9;
				return;
			}
		}
		else if (a == 1 && b == 2 && c == 2 && d == 5)
		{
			game.currentState = GameState::Minigame;
			return;
		}

		game.currentNight = &night7;
		startNight(window);
		game.currentState = GameState::Office;
	}

	return;

SPAMTON:
	static Vector2f velocity(240.f, 180.f);

	sprSpamton.setPosition(sprSpamton.getPosition() + Vector2f({velocity.x* deltaTime, velocity.y* deltaTime }));

	FloatRect bounds = sprSpamton.getGlobalBounds();
	if (bounds.position.x <= 0 || bounds.position.x + bounds.size.x >= SCREEN_WIDTH)
	{
		velocity.x = -velocity.x;

		Vector2f pos = sprSpamton.getPosition();
		if (pos.x < 0) pos.x = 0;
		if (pos.x + bounds.size.x > SCREEN_WIDTH) pos.x = SCREEN_WIDTH - bounds.size.x;
		sprSpamton.setPosition(pos);

		sndSpamton.play();
	}

	if (bounds.position.y <= 0 || bounds.position.y + bounds.size.y >= SCREEN_HEIGHT)
	{
		velocity.y = -velocity.y;

		Vector2f pos = sprSpamton.getPosition();
		if (pos.y < 0) pos.y = 0;
		if (pos.y + bounds.size.y > SCREEN_HEIGHT) pos.y = SCREEN_HEIGHT - bounds.size.y;
		sprSpamton.setPosition(pos);

		sndSpamton.play();
	}

	window.draw(spr1997);
	window.draw(sprSpamton);
}