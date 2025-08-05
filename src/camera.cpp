#include "camera.hpp"
#include "globals.hpp"
#include "resources.hpp"
#include "animatronics.hpp"
#include "sound.hpp"
#include "static.hpp"
#include <map>
#include "drink.hpp"

using namespace sf;


Room Garage(0), Exterior(1), Shop(2), Bedroom(3), Hall(4), Garden(5), Bathroom(6), SWRoom(7), You(8);

Room* currentRoom = &Bedroom;

void Room::calculateOccupants()
{
	occupants = Flowey.location == this | (Starwalker.location == this) << 1 | (Asgore.location == this) << 2;
}

/*
	occupants = Flowey << 0 | Asgore << 1 | Starwalker << 2;
*/

void drawBedroom(RenderWindow& window) 
{ 
	Bedroom.calculateOccupants();

	static Texture textures[8] = {
		Texture("res/img/Bedroom/bedroom000.png"),
		Texture("res/img/Bedroom/bedroom001.png"),
		Texture("res/img/Bedroom/bedroom010.png"),
		Texture("res/img/Bedroom/bedroom011.png"),
		Texture("res/img/Bedroom/bedroom100.png"),
		Texture("res/img/Bedroom/bedroom101.png"),
		Texture("res/img/Bedroom/bedroom110.png"),
		Texture("res/img/Bedroom/bedroom111.png")
	};

	sprBedroom.setTexture(textures[Bedroom.occupants]);

	window.draw(sprBedroom);
}
void drawShop(RenderWindow& window)
{
	Shop.calculateOccupants();

	static Texture textures[8] = {
		Texture("res/img/Shop/shop000.png"),
		Texture("res/img/Shop/shop001.png"),
		Texture("res/img/Shop/shop010.png"),
		Texture("res/img/Shop/shop011.png"),
		Texture("res/img/Shop/shop100.png"),
		Texture("res/img/Shop/shop101.png"),
		Texture("res/img/Shop/shop110.png"),
		Texture("res/img/Shop/shop111.png")
	};

	sprShop.setTexture(textures[Shop.occupants]);

	window.draw(sprShop);
}

void drawHall(RenderWindow& window)
{
	Hall.calculateOccupants();

	int occ = Hall.occupants;
	occ >>= 1;

	static Texture textures[4] = {
		Texture("res/img/Hall/hall00.png"),
		Texture("res/img/Hall/hall01.png"),
		Texture("res/img/Hall/hall10.png"),
		Texture("res/img/Hall/hall11.png")
	};

	sprHall.setTexture(textures[occ]);

	window.draw(sprHall);
}

void drawExterior(RenderWindow& window)
{
	Exterior.calculateOccupants();

	static Texture textures[8] = {
		Texture("res/img/Exterior/exterior000.png"),
		Texture("res/img/Exterior/exterior001.png"),
		Texture("res/img/Exterior/exterior010.png"),
		Texture("res/img/Exterior/exterior011.png"),
		Texture("res/img/Exterior/exterior100.png"),
		Texture("res/img/Exterior/exterior101.png"),
		Texture("res/img/Exterior/exterior110.png"),
		Texture("res/img/Exterior/exterior111.png")
	};

	sprExterior.setTexture(textures[Exterior.occupants]);

	window.draw(sprExterior);
}

void drawGarage(RenderWindow& window)
{
	Garage.calculateOccupants();

	static Texture textures[4] = {
		Texture("res/img/Garage/garage000.png"),
		Texture("res/img/Garage/garage001.png"),
		Texture("res/img/Garage/garage010.png"),
		Texture("res/img/Garage/garage011.png")
	};

	sprGarage.setTexture(textures[Garage.occupants]);

	window.draw(sprGarage);
}

void drawGarden(RenderWindow& window)
{
	Garden.calculateOccupants();

	int occ = Garden.occupants;

	occ >>= 1; //shift right to get rid of Flowey, as he is not here ever

	static Texture textures[4] = {
		Texture("res/img/Garden/garden00.png"),
		Texture("res/img/Garden/garden01.png"),
		Texture("res/img/Garden/garden10.png"),
		Texture("res/img/Garden/garden11.png")
	};

	sprGarden.setTexture(textures[occ]);

	window.draw(sprGarden);
}


void drawBathroom(RenderWindow& window)
{
	Bathroom.calculateOccupants();

	int occ = Bathroom.occupants;

	occ >>= 1;

	static Texture textures[4] = {
		Texture("res/img/Bathroom/bathroom00.png"),
		Texture("res/img/Bathroom/bathroom01.png"),
		Texture("res/img/Bathroom/bathroom10.png"),
		Texture("res/img/Bathroom/bathroom11.png")
	};

	sprBathroom.setTexture(textures[occ]);

	window.draw(sprBathroom);
}

void drawSWRoom(RenderWindow& window)
{ 
	static Texture t("res/img/swroom.png");
	static Sprite sprSWRoom(t);
	window.draw(sprSWRoom);
}

std::map<Room*, void(*)(RenderWindow&)> roomDrawFunctions = {
	{ &Bedroom, drawBedroom },
	{ &Shop, drawShop },
	{ &Hall, drawHall },
	{ &Exterior, drawExterior },
	{ &Garage, drawGarage },
	{ &Garden, drawGarden },
	{ &Bathroom, drawBathroom },
	{ &SWRoom, drawSWRoom },
};


void switchCameraLogic(const Vector2f& mousePosF)
{
	static rectPoint bedroomRect({ 920.f, 232.f }, { 1010.f, 313.f }),
					 shopArea({ 920.f, 142.f }, { 1010.f, 230.f }),
					 hallArea({ 920.f, 325.f }, { 1010.f, 360.f }),
					 exteriorArea({ 920.f, 90.f }, { 1120.f, 132.f }),
					 garageArea({ 1020.f, 150.f }, { 1121.f, 245.f }),
					 gardenArea({ 1020.f, 290.f }, { 1130.f, 360.f }),
					 bathroomArea({ 1131.f, 295.f }, { 1256.f, 360.f }),
					 SWRoomArea({ 1131.f, 50.f }, { 1256.f, 292.f });

	//bad programming maybe but im lazy for now, and im not planning to scale the amount
			//of rooms soooooo...

	Room* roomToSwitchTo = currentRoom;

	if (isInsideRect(bedroomRect, mousePosF))
		roomToSwitchTo = &Bedroom;
	else if (isInsideRect(shopArea, mousePosF))
		roomToSwitchTo = &Shop;
	else if (isInsideRect(hallArea, mousePosF))
		roomToSwitchTo = &Hall;
	else if (isInsideRect(exteriorArea, mousePosF))
		roomToSwitchTo = &Exterior;
	else if (isInsideRect(garageArea, mousePosF))
		roomToSwitchTo = &Garage;
	else if (isInsideRect(gardenArea, mousePosF))
		roomToSwitchTo = &Garden;
	else if (isInsideRect(bathroomArea, mousePosF))
		roomToSwitchTo = &Bathroom;
	else if (isInsideRect(SWRoomArea, mousePosF))
		roomToSwitchTo = &SWRoom;

	if (roomToSwitchTo == currentRoom)
		return;
	
	currentRoom = roomToSwitchTo;
}

bool G = false;

GameState updateCamera()
{
	Vector2i mousePos = Mouse::getPosition();
	Vector2f mousePosF = { mousePos.x * 1.f, mousePos.y * 1.f };

	static rectPoint lancerBounds({ 1150.f, 600 }, { SCREEN_WIDTH, SCREEN_HEIGHT });

	if (sndStatic.getStatus()!=Sound::Status::Playing)
	{
		sndStatic.play();
		sndStatic.setLooping(true);
		sndStatic.setVolume(50.f);
	}

	if (click)
	{	
		if (isInsideRect(lancerBounds, mousePosF))
		{
			FUN = randRange(0, 100);
			if (FUN == 66 && randRange(0, 10) == 6 && randRange(-66, 66) == 6) G = true;
			sndStatic.pause();
			sndCamClose.play();
			return GameState::Office;
		}
		switchCameraLogic(mousePosF);
	}

	Flowey.update();
	Starwalker.update();
	Asgore.update();
	if (game.currentState != GameState::Camera)
	{
		sndStatic.stop();
		return game.currentState;
	}
	ambienceSound();
	return GameState::Camera;
}

void renderCamera(RenderWindow& window)
{
	static auto lastRoom = currentRoom;
	static auto lastOccupants = currentRoom->occupants;

	window.draw(sprCamera);

	roomDrawFunctions[currentRoom](window);

	for (auto& drink : drinks)
	{
		if (drink.active && drink.room && drink.room == currentRoom) //check if nullptr
		{
			if (currentRoom == &Hall)
				sprDrink.setPosition(drink.position + sprHall.getPosition());
			else
				sprDrink.setPosition(drink.position);
			window.draw(sprDrink);

			if (click && sprDrink.getGlobalBounds().contains({ Mouse::getPosition(window).x * 1.f, Mouse::getPosition(window).y * 1.f }))
			{
				sndPop.play();
				drink.active = false;
				drinkCount--;
			}

		}
	}

	static bool staticShouldPlay = false; //to clarify, on switching states

	if (lastRoom != currentRoom || lastOccupants != currentRoom->occupants)
	{
		staticShouldPlay = true;
		sndStaticFlash.play();
		sndStaticFlash.setPitch(randRange(50, 150) / 100.f);
	}
	if (staticShouldPlay)
	{
		staticShouldPlay = renderStaticOnUpdate(window);
	}
	else if (currentRoom != &SWRoom)
	{
		sndStaticFlash.stop();
		renderGeneralStatic(window);
	}

	lastRoom = currentRoom;
	lastOccupants = currentRoom->occupants;

	static SoundBuffer sndBfrCooking("res/snd/cooking.wav");
	static Sound sndCooking(sndBfrCooking);

	if (currentRoom == &SWRoom)
	{
		if (Starwalker.location == &SWRoom)
		{
			if (sndCooking.getStatus() != Sound::Status::Playing) sndCooking.play();
		}
		else sndCooking.stop();
	}
	else sndCooking.pause();

	static Texture t_sprCover("res/img/cover.png");
	static Sprite sprCover(t_sprCover);

	window.draw(sprCover);
}