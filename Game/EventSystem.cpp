
#include "EventSystem.h"
#include "cmp_char_sheet.h"
#include "Game.h"
#include "ItemGenerator.h"
#include <iostream>
#include <fstream>
#include "cmp_actor_movement.h"
#include "cmp_health.h"
#include "cmp_hud.h"
#include <sstream>

EventSystem* EventSystem::instance;
ItemGenerator* itemGenerator = ItemGenerator::getInstance();
EventSystem::EventSystem()
{
	
}
EventSystem* EventSystem::getInstance()
{
	if (instance == 0)
	{
		instance = new EventSystem();
	}

	return instance;
}
EventSystem::~EventSystem()
{
}

void EventSystem::LoadGame()
{
	gameScene.reset(new GameScene());
	gameScene->load();
	std::vector<int> location;
	std::vector<int> levels;
	std::vector<int> experience;
	std::vector<int> items;
	auto character = player->GetComponent<CharacterSheetComponent>();
	std::ifstream save("save.txt");
	if (save.good())
	{
		std::string line;
		int line_number = 0;
		while (std::getline(save, line))
		{
			std::stringstream ss(line);
			int i;
			while (ss >> i)
			{
				if (line_number == 0)
					location.push_back(i);
				else if (line_number == 1)
					levels.push_back(i);
				else if (line_number == 2)
					experience.push_back(i);
				else if (line_number == 3)
					items.push_back(i);

				if (ss.peek() == ',')
					ss.ignore();
			}
			line_number++;
		}

		activeScene = gameScene;
		player->setPosition({ (float)location[1],(float)location[2] });
		character->setLevels(levels[0], levels[1], levels[2], levels[3], levels[4]);
		character->setExperience(experience[0], experience[1], experience[2], experience[3], experience[4]);
		for (int i = 0; i < items.size(); i += 2)
		{
			itemGenerator->load(items[i], (bool)items[i + 1]);
		}
		auto x = player->GetComponent<HudComponent>();
		x->reload();

	}
	
}
void EventSystem::SaveGame()
{
	auto character = player->GetComponent<CharacterSheetComponent>();
	std::ofstream save("save.txt");
	if (save.is_open())
	{
		save << character->saveLocation() + "\n";
		save << character->saveLevels() + "\n";
		save << character->saveExperience() + "\n";
		save << character->saveItems() + "\n";
		save.close();
	}
	else std::cout << "Unable to open file";
}
void EventSystem::addExp(int a, float b)
{
	auto exp = player->GetComponent<CharacterSheetComponent>();
	exp->addEXP(a, b);
}