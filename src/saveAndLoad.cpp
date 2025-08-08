#include "game.hpp"
#include <fstream>

using namespace std;

void Game::save()
{
	ofstream fout("res/save.png");
	fout << currentNight->num;
}

void Game::load()
{
	ifstream fin("res/save.png"); //because why not?
	int num = 0;
	fin >> num;
	if (num >= 5) { currentNight = &night5; return; }
	switch (num)
	{
	case 2: currentNight = &night2; break;
	case 3: currentNight = &night3; break;
	case 4: currentNight = &night4; break;
	default: currentNight = &night1;
	}
}