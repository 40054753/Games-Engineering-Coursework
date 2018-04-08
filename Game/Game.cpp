#pragma once
#include "SystemRenderer.h"
#include "Game.h"
#include "levelsystem.h"
#include "cmp_sprite.h"
#include "cmp_health.h"
#include "cmp_actor_movement.h"
#include "cmp_pickups.h"
#include "cmp_attack.h"
#include "cmp_npc.h"
#include "cmp_hud.h"
#include "cmp_char_sheet.h"
#include "cmp_enemy_attack.h"
#include "cmp_ai_steering.h"
#include "EventSystem.h"
#include <string>



using namespace sf;
using namespace std;
const int GHOSTS_COUNT = 4;
Font font;
Texture playerTexture, zombieTexture, spellsTexture, snowEffect, iconsTexture, itemsTexture;
Texture menuBg;
sf::Sprite background;
SoundBuffer buffer;
Sound sound;
RectangleShape rect;
Vector2i mousePos;
int resolution_index = 0;
bool fullscreen = false;
MenuScene::MenuScene() {
}
void MenuScene::load() {

	setID(0);
	if (!buffer.loadFromFile("res/sound/click.wav")) {
		cout << "Cannot load font!" << endl;
	}
	sound.setBuffer(buffer);
	if (!font.loadFromFile("res/fonts/font.ttf")) {
		cout << "Cannot load font!" << endl;
	}
	if (!menuBg.loadFromFile("res/img/splashScreen.png")) {
		cout << "Cannot load img!" << endl;
	}
	if (!snowEffect.loadFromFile("res/img/snow.png")) {
		cout << "Cannot load img!" << endl;
	}
	button_return.setOutlineColor(sf::Color::Black);
	button_return.setOutlineThickness(5.0f);
	button_return.setFillColor(sf::Color(79, 79, 79, 255));
	button_return.setSize({ 0.35f*WX, 0.07f * WY });
	button_return.setPosition({0.70f*WX, 0.01f * WY });
	text_return.setFont(font);
	text_return.setColor(sf::Color::Black);
	text_return.setString("Return to game");
	text_return.setOutlineColor(sf::Color::Red);
	text_return.setOutlineThickness(3.0f);
	text_return.setPosition(button_return.getPosition() + Vector2f(0.01f*WX, 0.015f*WY));

	for (int i = 0; i < 30; i++)
	{
		float scale = (float)(rand() % 10) / 50.0f;
		auto snow = make_shared<Entity>();
		auto s = snow->addComponent<StaticSpriteComponent>();
		s->getSprite().setTexture(snowEffect);
		s->getSprite().setScale({ scale,scale});
		snow->setPosition(Vector2f(rand()% ((int)WX), rand() % ((int)WY)));
		snow->addComponent<SnowComponent>();
		_ents.list.push_back(snow);
	}
	background.setTexture(menuBg);
	background.setScale(WX/1280,WY/720);
	rect.setPosition(sf::Vector2f(3.92f * WX / 5, WY / (MAX_NUMBER_OF_ITEMS)  * 2.15f));
	//rect.setScale({ 3.0f,3.0f });
	rect.setSize({ WX / 5.3f,WY / 2.8f });
	rect.setFillColor(sf::Color(1,1,1,130));

	title.setPosition(sf::Vector2f(WX / 6.0f, WY / 5.5f));
	title.setString("ICY DEAD PEOPLE");
	title.setFont(font);
	title.setCharacterSize(60.0f*WX/1280);
	title.setScale(1.0f, 2.0f);
	title.setColor(sf::Color::Black);
	//list of menu items
	menu[0].setFont(font);
	menu[0].setColor(sf::Color::Red);
	menu[0].setString("New Game");
	menu[0].setCharacterSize(30 * WX / 1280);
	menu[0].setPosition(sf::Vector2f(4*WX / 5, WY / (MAX_NUMBER_OF_ITEMS)  * 2.5f));

	menu[1].setFont(font);
	menu[1].setColor(sf::Color::White);
	menu[1].setString("Load");
	menu[1].setCharacterSize(30 * WX / 1280);
	menu[1].setPosition(sf::Vector2f(4*WX / 5, WY / (MAX_NUMBER_OF_ITEMS ) *2.75f));

	menu[2].setFont(font);
	menu[2].setColor(sf::Color::White);
	menu[2].setString("Options");
	menu[2].setCharacterSize(30 * WX / 1280);
	menu[2].setPosition(sf::Vector2f(4*WX / 5, WY / (MAX_NUMBER_OF_ITEMS) * 3.0f));

	menu[3].setFont(font);
	menu[3].setColor(sf::Color::White);
	menu[3].setString("Close");
	menu[3].setCharacterSize(30 * WX / 1280);
	menu[3].setPosition(sf::Vector2f(4*WX / 5, WY / (MAX_NUMBER_OF_ITEMS ) *3.25f));

	selectedItemIndex = 0;

	text.setPosition(sf::Vector2f(4 * WX / 5, WY / (MAX_NUMBER_OF_ITEMS) *2.25f));
	text.setString("Menu");
	text.setFont(font);
	text.setCharacterSize(30 * WX / 1280);
	text.setColor(sf::Color::Green);
}

//simple methods for moving between menu items
void MenuScene::moveUp()
{
	if (selectedItemIndex - 1 >= 0) {
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setColor(sf::Color::Red);
		sound.play();
	} 
	else
	{
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex= MAX_NUMBER_OF_ITEMS-1;
		menu[selectedItemIndex].setColor(sf::Color::Red);
		sound.play();
	}
}
void MenuScene::moveTo(int x)
{
	if (x != selectedItemIndex)
	{
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex = x;
		menu[selectedItemIndex].setColor(sf::Color::Red);
		sound.play();
	}
}
void MenuScene::moveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setColor(sf::Color::Red);
		sound.play();
	}
	else
	{
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex=0;
		menu[selectedItemIndex].setColor(sf::Color::Red);
		sound.play();
	}
}

void MenuScene::update(double dt) 
{
	EventSystem* evs = EventSystem::getInstance();

	mousePos = sf::Mouse::getPosition(Renderer::getWindow());

	moveTime -= dt;
	if(evs->isLoaded())
	if (mousePos.x >= button_return.getPosition().x  && mousePos.x <= WX)
	{
		if (mousePos.y >= button_return.getPosition().y && mousePos.y <= button_return.getPosition().y + 0.07f*WY)
		{
			
			text_return.setOutlineColor(sf::Color::Green);
			if (sf::Mouse::isButtonPressed(Mouse::Left))
			{
				activeScene = gameScene;
			}
		}
		else
		{
			text_return.setOutlineColor(sf::Color::Red);
		}
	}
	else
	{
		text_return.setOutlineColor(sf::Color::Red);
	}
	if (mousePos.x >=  0.78f * WX && mousePos.x <= 0.94f * WX )
	{
		if (moveTime <= 0 && mousePos.y >= menu[0].getPosition().y && mousePos.y <  menu[1].getPosition().y)
		{
			
			moveTo(0);
			if (sf::Mouse::isButtonPressed(Mouse::Left))
			{
				gameScene.reset(new GameScene());
				gameScene->load();
				activeScene = gameScene; //switch to game
				std::cout << "Active Scene: " + std::to_string(activeScene->getID()) << std::endl;
			}
		}
		else if (moveTime <= 0 && mousePos.y >= menu[1].getPosition().y && mousePos.y <  menu[2].getPosition().y)
		{
		
			moveTo(1);
			if (sf::Mouse::isButtonPressed(Mouse::Left))
			{
				moveTime = 0.2f;
				evs->LoadGame();
			}
		}
		else if (moveTime <= 0 && mousePos.y >= menu[2].getPosition().y && mousePos.y <  menu[3].getPosition().y)
		{
			
			moveTo(2);
			if (sf::Mouse::isButtonPressed(Mouse::Left))
			{
				moveTime = 0.2f;
				activeScene = optionsScene;
			}
		}
		else if (moveTime <= 0 && mousePos.y >= menu[3].getPosition().y && mousePos.y <  menu[3].getPosition().y+30.0f)
		{
			
			moveTo(3);
			if (sf::Mouse::isButtonPressed(Mouse::Left))
			{

				Renderer::getWindow().close();
			}
		}
	}
	//if there are menu items to move to, move to it, limit keyboard input to 0.2
	if (moveTime <= 0 && Keyboard::isKeyPressed(Keyboard::Up)) {
		moveUp();
		moveTime = 0.2f;
	}
	if (moveTime <= 0 && Keyboard::isKeyPressed(Keyboard::Down)) {
		moveDown();
		moveTime = 0.2f;
	}
	if (moveTime <= 0 && (Keyboard::isKeyPressed(Keyboard::Return) || Keyboard::isKeyPressed(Keyboard::Space)) ) {
		moveTime = 0.2f;
		if (selectedItemIndex == 0) {
			gameScene.reset(new GameScene());
			gameScene->load();
			activeScene = gameScene; //switch to game
			std::cout << "Active Scene: " + std::to_string(activeScene->getID()) << std::endl;
		}
		if (selectedItemIndex == 1) {
			moveTime = 0.2f;
			evs->LoadGame();
		}
		if (selectedItemIndex == 2) {
			activeScene = optionsScene;
		}
		if (selectedItemIndex == 3) {
			Renderer::getWindow().close();
		}
	}
	Renderer::setCenter(Vector2f(WX / 2 + 25, WY/2));
	Scene::update(dt);
	_ents.update(dt);
}
void MenuScene::render() 
{
	EventSystem* evs = EventSystem::getInstance();
	Scene::render();
	Renderer::queue(&background);
	Renderer::queue(&title);
	_ents.render();
	Renderer::queue(0,&rect);
	Renderer::queue(0,&text);
	if (evs->isLoaded())
	{
		Renderer::queue(0,&button_return);
		Renderer::queue(0,&text_return);
	}

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) { //for every menu item		
		Renderer::queue(0,&menu[i]);
	}
}
vector<shared_ptr<Entity>> ghosts;
vector<shared_ptr<Entity>> npcs;
vector<shared_ptr<Entity>> eatingEnts;
shared_ptr<Entity> player;
shared_ptr<Entity> hud;
vector<shared_ptr<Entity>> nibbles;

shared_ptr<Entity> makeNibble(const Vector2f& nl, Color col, float size)
{
	auto cherry = make_shared<Entity>();
	auto s = cherry->addComponent<ShapeComponent>();
	s->setShape<sf::CircleShape>(size);
	s->getShape().setFillColor(col);
	s->getShape().setOrigin(size, size);

	auto pickup = cherry->addComponent<PickupComponent>();
	pickup->setEntities(eatingEnts);
	cherry->setPosition(nl);
	return cherry;
}
void GameScene::respawn()
{
	for (auto n : ghosts)
	{
		n->setForDelete();
		n.reset();
	}
	ghosts.clear();
	for (auto n : npcs)
	{
		n->setForDelete();
		n.reset();
	}
	npcs.clear();


	for (int i = 0; i < GHOSTS_COUNT; ++i)
	{
		auto ghost = make_shared<Entity>();
		//ghost->addComponent<EnemyAIComponent>();
		auto s = ghost->addComponent<CharacterSpriteComponent>();
		s->getSprite().setTexture(zombieTexture);
		s->getSprite().setTextureRect({ 0,0,16,21 });
		s->getSprite().setScale({ 2.0f*WX / 1280, 2.0f*WY / 720 });
		s->getSprite().setOrigin(8.0f, 12.0f);
		ghost->addComponent<HealthComponent>();
		ghost->addComponent<EnemyHealthBarComponent>();
		auto p = ghost->addComponent<EnemyAttackComponent>();
		p->setLevel(0);
		ghost->addComponent<SteeringComponent>(player.get());
		std::cout << player.get()->getPosition().x;
		_ents.list.push_back(ghost);
		ghosts.push_back(ghost);
		//eatingEnts.push_back(ghost);       ///ghosts can eat
		
	}
	///////standing enemy
	auto ghost = make_shared<Entity>();
	auto s = ghost->addComponent<CharacterSpriteComponent>();
	s->getSprite().setTexture(zombieTexture);
	s->getSprite().setTextureRect({ 0,0,16,21 });
	s->getSprite().setScale({ 2.0f*WX / 1280, 2.0f*WY / 720 });
	s->getSprite().setOrigin(8.0f, 12.0f);
	ghost->addComponent<HealthComponent>();
	auto p = ghost->addComponent<EnemyAttackComponent>();
	p->setLevel(0);
	ghost->addComponent<EnemyHealthBarComponent>();
	_ents.list.push_back(ghost);
	ghosts.push_back(ghost);
	/////////////////////////////////////////////////////////////////EXAMPLE NPC/////////////////////////////////////
	auto npc = make_shared<Entity>();
	auto n = npc->addComponent<CharacterSpriteComponent>();
	n->getSprite().setTexture(playerTexture);
	n->getSprite().setTextureRect({ 0,0,16,21 });
	n->getSprite().setScale({ 2.0f*WX / 1280, 2.0f*WY/720 });
	n->getSprite().setOrigin(8.0f, 12.0f);
	auto d = npc->addComponent<NPCComponent>();
	d->setDialogue("HELLO THERE, ADVENTURER! HELLO THERE, \nADVENTURER! HELLO THERE, ADVENTURER! ");
	_ents.list.push_back(npc);
	npcs.push_back(npc);

	auto att = _ents.list[0]->addComponent<AttackComponent>();
	att->setEntities(ghosts);

	for (auto n : nibbles)
	{
		n->setForDelete();
		n.reset();
	}
	nibbles.clear();

	_ents.list[0]->setPosition(ls::findTiles(ls::START)[0]);

	auto ghost_spawns = ls::findTiles(ls::ENEMY);
	for (int i = 1; i < _ents.list.size(); ++i) {
		_ents.list[i]->setPosition(ghost_spawns[rand() % ghost_spawns.size()]);
	}
	
	auto nibbleLoc = ls::findTiles(ls::EMPTY);
	for (const auto &nl : nibbleLoc)
	{
		auto cherry = makeNibble(nl, Color::White, 2.0f);
		_ents.list.push_back(cherry);
		nibbles.push_back(cherry);
	}

	nibbleLoc = ls::findTiles(ls::WAYPOINT);
	for (const auto &nl : nibbleLoc)
	{
		auto cherry = makeNibble(nl, Color::Red, 3.0f);
		_ents.list.push_back(cherry);
		nibbles.push_back(cherry);
	}
	
}
void GameScene::load()
{
	setID(1);
	EventSystem* events = EventSystem::getInstance();
	events->gameLoad();
	if (!playerTexture.loadFromFile("res/img/player.png"))
	{
		cerr << "Failed to load spritesheet!" << endl;
	}
	if (!itemsTexture.loadFromFile("res/img/items.png"))
	{
		cerr << "Failed to load spritesheet!" << endl;
	}
	if (!spellsTexture.loadFromFile("res/img/spells.png"))
	{
		cerr << "Failed to load spritesheet!" << endl;
	}
	if (!zombieTexture.loadFromFile("res/img/zombie.png"))
	{
		cerr << "Failed to load spritesheet!" << endl;
	}
	if (!iconsTexture.loadFromFile("res/img/gray_icons.png")) {
		cout << "Cannot load img!" << endl;
	}
	ls::loadLevelFile("res/levels/example.txt", 25.0f * WX/1280);


	auto pl = std::make_shared<Entity>();
	pl->addComponent<CharacterSheetComponent>();
	auto mp = pl->addComponent<PlayerMovementComponent>();
	mp->setSpeed(100.0f);
	pl->addComponent<HealthComponent>();
	auto s = pl->addComponent<CharacterSpriteComponent>();
	s->getSprite().setTexture(playerTexture);
	s->getSprite().setTextureRect({ 0,0,16,21 });
	s->getSprite().setScale({ 2.0f*WX/1280, 2.0f*WY/720 });
	s->getSprite().setOrigin({ 8.0f, 12.0f });
	s->getSprite().setPosition({ 100.0f, 100.0f });
	gameScene->getEnts().push_back(pl);
	player = pl;

	auto hd = make_shared<Entity>();
	auto hb = hd->addComponent<HudComponent>();
	hud = hd;
	_ents.list.push_back(hud);

	eatingEnts.push_back(player);
	respawn();
	
}


void GameScene::update(double dt)
{
	auto health_mana = player->GetComponent<HealthComponent>();
	if (health_mana->getHealth()<=0)
	{
		health_mana->reset();
		std::cout << "Game over!" << std::endl;
		respawn();
	}
	if (Keyboard::isKeyPressed(Keyboard::Tab))
	{
		activeScene = menuScene;
		std::cout << "Active Scene: " + std::to_string(activeScene->getID()) << std::endl;
	}
	_ents.update(dt);
	Renderer::setCenter(player->getPosition());
	Scene::update(dt);
}
void GameScene::render()
{
	ls::Render(Renderer::getWindow());
	_ents.render();
	Scene::render();
}

OptionsScene::OptionsScene() {
}

void OptionsScene::load() 
{
	setID(2);
	for (int i = 0; i < 45; i++)
	{
		float scale = (float)(rand() % 10) / 50.0f;
		auto snow = make_shared<Entity>();
		auto s = snow->addComponent<StaticSpriteComponent>();
		s->getSprite().setTexture(snowEffect);
		s->getSprite().setScale({ scale,scale });
		snow->setPosition(Vector2f((rand() %(int) WX), rand() %(int) WY));
		snow->addComponent<SnowComponent>();
		_ents.list.push_back(snow);
	}
	button_return.setOutlineColor(sf::Color::Black);
	button_return.setOutlineThickness(5.0f);
	button_return.setFillColor(sf::Color(79, 79, 79, 255));
	button_return.setSize({ 0.3f*WX, 0.07f * WY });
	button_return.setPosition({ 0.03f*WX, 0.01f * WY });

	text_return.setFont(font);
	text_return.setColor(sf::Color::Black);
	text_return.setString("Return to menu");
	text_return.setOutlineColor(sf::Color::Red);
	text_return.setOutlineThickness(3.0f);
	text_return.setPosition(button_return.getPosition() + Vector2f(0.01f*WX, 0.015f*WY));

	
	background.setTexture(menuBg);
	background.setScale(WX / 1280, WY / 720);

	rect.setPosition({ 0.1f*WX, 0.1f * WY });
	rect.setSize({ 0.8f*WX,0.8f*WY });
	rect.setFillColor(sf::Color(79, 79, 79, 255));
	rect.setOutlineColor(sf::Color::Black);
	rect.setOutlineThickness(5.0f);

	title.setPosition(rect.getPosition() + Vector2f(0.01f*WX,0.01f*WY));
	title.setString("Options");
	title.setFont(font);
	title.setCharacterSize(30.0f*WY/720);
	title.setColor(sf::Color::White);
	title.setScale(WX / 1280, WY / 720);
	title.setOutlineColor(sf::Color::Black);
	title.setOutlineThickness(4.0f);

	left_list.setPosition(rect.getPosition() + Vector2f(0.01f*WX, 0.1f*WY));
	left_list.setString("Resolution\n\n\nScreen Mode\n\n\nOption3\n\n\nOption4");
	left_list.setFont(font);
	left_list.setCharacterSize(25.0f);
	left_list.setScale(WX/1280, WY/720);
	left_list.setColor(sf::Color::White);
	left_list.setOutlineColor(sf::Color::Black);
	left_list.setOutlineThickness(3.0f);

	right_list.setPosition(rect.getPosition() + Vector2f(0.41f*WX, 0.1f*WY));
	right_list.setString("Controls");
	right_list.setFont(font);
	right_list.setCharacterSize(25.0f);
	right_list.setScale(WX / 1280, WY / 720);
	right_list.setColor(sf::Color::White);
	right_list.setOutlineColor(sf::Color::Black);
	right_list.setOutlineThickness(3.0f);


	bg_resolution.setOutlineColor(sf::Color::Black);
	bg_resolution.setOutlineThickness(5.0f);
	bg_resolution.setFillColor(sf::Color(50, 50, 50, 255));
	bg_resolution.setSize({ 0.3f*WX, 0.07f * WY });
	bg_resolution.setPosition(left_list.getPosition() + Vector2f(0.0f*WX, 0.06f*WY));

	text_resolution.setFont(font);
	text_resolution.setColor(sf::Color::White);
	text_resolution.setScale(WX / 1280, WY / 720);
	text_resolution.setString(to_string((int)WX) + "x"+to_string((int)WY));
	text_resolution.setPosition(bg_resolution.getPosition() + Vector2f(0.07f*WX, 0.015f*WY));
	
	button_resolution_right = sf::CircleShape(17, 3);
	button_resolution_right.rotate(-30.0f);
	button_resolution_right.setFillColor(sf::Color(79, 79, 79, 255));
	button_resolution_right.setOutlineColor(sf::Color::White);
	button_resolution_right.setOutlineThickness(5.0f);
	button_resolution_right.setPosition(bg_resolution.getPosition() + Vector2f(0.24f*WX, 0.025f*WY));

	button_resolution_left = sf::CircleShape(17, 3);
	button_resolution_left.rotate(30.0f);
	button_resolution_left.setFillColor(sf::Color(79, 79, 79, 255));
	button_resolution_left.setOutlineColor(sf::Color::White);
	button_resolution_left.setOutlineThickness(5.0f);
	button_resolution_left.setPosition(bg_resolution.getPosition() + Vector2f(0.04f*WX, 0.0045f*WY));

	bg_screenmode.setOutlineColor(sf::Color::Black);
	bg_screenmode.setOutlineThickness(5.0f);
	bg_screenmode.setFillColor(sf::Color(50, 50, 50, 255));
	bg_screenmode.setSize({ 0.3f*WX, 0.07f * WY });
	bg_screenmode.setPosition(left_list.getPosition() + Vector2f(0.0f*WX, 0.2f*WY));

	text_screenmode.setFont(font);
	text_screenmode.setColor(sf::Color::White);
	text_screenmode.setScale(WX / 1280, WY / 720);
	text_screenmode.setString("Window");
	text_screenmode.setPosition(bg_screenmode.getPosition() + Vector2f(0.02f*WX, 0.015f*WY));

	button_screenmode_dot = sf::CircleShape(17, 8);
	button_screenmode_dot.setFillColor(sf::Color(79, 79, 79, 255));
	button_screenmode_dot.setOutlineColor(sf::Color::White);
	button_screenmode_dot.setOutlineThickness(5.0f);
	button_screenmode_dot.setPosition(bg_screenmode.getPosition() + Vector2f(0.24f*WX, 0.013f*WY));
	
}
void OptionsScene::update(double dt)
{
	EventSystem* evs = EventSystem::getInstance();
	if(!fullscreen)
	mousePos = sf::Mouse::getPosition(Renderer::getWindow());
	else
	mousePos = sf::Mouse::getPosition();
	//if(evs->isLoaded())
	if (mousePos.x >= button_return.getPosition().x  && mousePos.x <= button_return.getPosition().x + 0.3f*WX)
	{
		if (mousePos.y >= button_return.getPosition().y && mousePos.y <= button_return.getPosition().y + 0.07f*WY)
		{

			text_return.setOutlineColor(sf::Color::Green);
			if (sf::Mouse::isButtonPressed(Mouse::Left))
			{
				activeScene = menuScene;
			}
		}
		else
		{
			text_return.setOutlineColor(sf::Color::Red);
		}
	}
	else
	{
		text_return.setOutlineColor(sf::Color::Red);
	}
	if (mousePos.x >= button_resolution_right.getPosition().x- 0.013f*WX  && mousePos.x <= button_resolution_right.getPosition().x + 0.013f*WX)
	{
		if (mousePos.y >= button_resolution_right.getPosition().y - 0.025f*WY && mousePos.y <= button_resolution_right.getPosition().y + 0.025f*WY)
		{
	
			button_resolution_right.setOutlineColor(sf::Color::Green);
			if (sf::Mouse::isButtonPressed(Mouse::Left))
			{
				if (resolution_index < 2)
				{
					resolution_index++;
					menuScene.reset(new MenuScene());
					menuScene->load();
					optionsScene.reset(new OptionsScene());
					optionsScene->load();
					activeScene = menuScene;
					Renderer::resizeView();
					activeScene = optionsScene;
				}
			}
			
		}
		else
		{
			button_resolution_right.setOutlineColor(sf::Color::Red);
		}
	}
	else
	{
		button_resolution_right.setOutlineColor(sf::Color::Red);
	}
	if (mousePos.x >= button_resolution_left.getPosition().x - 0.03f*WX && mousePos.x <= button_resolution_left.getPosition().x + 0.01f*WX)
	{
		if (mousePos.y >= button_resolution_left.getPosition().y  && mousePos.y <= button_resolution_left.getPosition().y + 0.06f*WY)
		{

			button_resolution_left.setOutlineColor(sf::Color::Green);
			if (sf::Mouse::isButtonPressed(Mouse::Left))
			{
				if (resolution_index > 0)
				{
					resolution_index--;
					menuScene.reset(new MenuScene());
					menuScene->load();
					optionsScene.reset(new OptionsScene());
					optionsScene->load();
					if (evs->isLoaded())
					{
						evs->SaveGame();
						evs->LoadGame();
					}

					activeScene = menuScene;
					Renderer::resizeView();
					activeScene = optionsScene;
					
				}
			}

		}
		else
		{
			button_resolution_left.setOutlineColor(sf::Color::Red);
		}
	}
	else
	{
		button_resolution_left.setOutlineColor(sf::Color::Red);
	}
	if (mousePos.x >= button_screenmode_dot.getPosition().x - 0.03f*WX && mousePos.x <= button_screenmode_dot.getPosition().x + 0.01f*WX)
	{
		if (mousePos.y >= button_screenmode_dot.getPosition().y - 0.02f*WY && mousePos.y <= button_screenmode_dot.getPosition().y + 0.06f*WY)
		{

			button_screenmode_dot.setOutlineColor(sf::Color::Green);
			if (sf::Mouse::isButtonPressed(Mouse::Left))
			{
				
				if (!fullscreen)
				{
					Renderer::fullscreen();
					fullscreen = true;
					text_screenmode.setString("Fullscreen");
				}
				else
				{
					Renderer::not_fullscreen();
					fullscreen = false;
					text_screenmode.setString("Window");
				}
				
			}

		}
		else
		{
			button_screenmode_dot.setOutlineColor(sf::Color::Red);
		}
	}
	else
	{
		button_screenmode_dot.setOutlineColor(sf::Color::Red);
	}
	Renderer::setCenter(Vector2f(WX / 2 + 25, WY / 2));
	Scene::update(dt);
	_ents.update(dt);
}
void OptionsScene::render()
{
	Scene::render();
	Renderer::queue(&background);
	_ents.render();
	Renderer::queue(0,&rect);
	Renderer::queue(0,&title);
	Renderer::queue(0,&left_list);
	Renderer::queue(0,&bg_resolution);
	Renderer::queue(0,&text_resolution);
	Renderer::queue(0,&right_list);
	Renderer::queue(0, &button_return);
	Renderer::queue(0, &text_return);
	Renderer::queue(0, &button_resolution_right);
	Renderer::queue(0, &button_resolution_left);
	Renderer::queue(0, &bg_screenmode);
	Renderer::queue(0, &text_screenmode);
	Renderer::queue(0, &button_screenmode_dot);
	

}