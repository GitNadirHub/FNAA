#include "camera.hpp"
#include "globals.hpp"
#include "resources.hpp"
#include <map>

using namespace sf;

struct Room
{
	Room* adjRoom[2];
	uint8_t occupants = 0;

	void addLink(Room* r0 = nullptr, Room* r1 = nullptr, Room* r2 = nullptr)
	{
		adjRoom[0] = r0;
		adjRoom[1] = r1;
	}

	void calculateOccupants();
};

Room Garage, Exterior, Shop, Bedroom, Hall, Garden, Bathroom, SWRoom;

Room* currentRoom = &Bedroom;

struct FloweyStruct {
	uint8_t AILEVEL = 0;
	Room* location = &Bedroom;
	void update()
	{

	}
};

struct AsgoreStruct {
	uint8_t AILEVEL = 0;
	Room* location = &Bedroom;
	void update()
	{

	}
};
struct StarwalkerStruct {
	uint8_t AILEVEL = 0;
	Room* location = &SWRoom;
	void update()
	{

	}
};

FloweyStruct Flowey;
AsgoreStruct Asgore;
StarwalkerStruct Starwalker;

void Room::calculateOccupants()
{
	occupants = Flowey.location == this | (Starwalker.location == this) << 1 | (Asgore.location == this) << 2;
}

/*
	occupants = Flowey << 0 | Asgore << 1 | Starwalker << 2;
*/

Texture t_sprBedroom[3];

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
	window.draw(sprShop); 
}
void drawHall(RenderWindow& window) 
{ 
	window.draw(sprHall); 
}
void drawExterior(RenderWindow& window) 
{
	window.draw(sprExterior);
}
void drawGarage(RenderWindow& window) 
{
	window.draw(sprGarage); 
}
void drawGarden(RenderWindow& window)
{
	window.draw(sprGarden); 
}
void drawBathroom(RenderWindow& window) 
{
	window.draw(sprBathroom); 
}
void drawSWRoom(RenderWindow& window)
{ 
	//nothing for now
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


GameState updateCamera()
{
	Vector2i mousePos = Mouse::getPosition();
	Vector2f mousePosF = { mousePos.x * 1.f, mousePos.y * 1.f };

	static rectPoint lancerBounds({ 1150.f, 600 }, { SCREEN_WIDTH, SCREEN_HEIGHT });

	if (Mouse::isButtonPressed(Mouse::Button::Left))
	{	
		if (isInsideRect(lancerBounds, mousePosF))
		{
			sndCamClose.play();
			return GameState::Office;
		}
		switchCameraLogic(mousePosF);
	}

	return GameState::Camera;
}

void renderCamera(RenderWindow& window)
{
	window.draw(sprCamera);

	roomDrawFunctions[currentRoom](window);

}