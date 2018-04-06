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

MenuScene::MenuScene() {
}
void MenuScene::load() {

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
	for (int i = 0; i < 50; i++)
	{
		float scale = (float)(rand() % 10) / 50.0f;
		auto snow = make_shared<Entity>();
		auto s = snow->addComponent<StaticSpriteComponent>();
		s->getSprite().setTexture(snowEffect);
		s->getSprite().setScale({ scale,scale});
		snow->setPosition(Vector2f((rand() % Renderer::gameWidth), rand() % Renderer::gameHeight));
		snow->addComponent<SnowComponent>();
		_ents.list.push_back(snow);
	}
	background.setTexture(menuBg);
	rect.setPosition(sf::Vector2f(3.92f * Renderer::gameWidth / 5, Renderer::gameHeight / (MAX_NUMBER_OF_ITEMS)  * 2.15f));
	//rect.setScale({ 3.0f,3.0f });
	rect.setSize({ Renderer::gameWidth / 5.3f,Renderer::gameHeight / 2.8f });
	rect.setFillColor(sf::Color(1,1,1,130));

	title.setPosition(sf::Vector2f(Renderer::gameWidth / 5.5f, Renderer::gameHeight / 5.5f));
	title.setString("ICY DEAD PEOPLE");
	title.setFont(font);
	title.setScale({ 2.0f,3.5f });
	title.setColor(sf::Color::Black);
	//list of menu items
	menu[0].setFont(font);
	menu[0].setColor(sf::Color::Red);
	menu[0].setString("New Game");
	menu[0].setPosition(sf::Vector2f(4*Renderer::gameWidth / 5, Renderer::gameHeight / (MAX_NUMBER_OF_ITEMS)  * 2.5f));

	menu[1].setFont(font);
	menu[1].setColor(sf::Color::White);
	menu[1].setString("Load");
	menu[1].setPosition(sf::Vector2f(4*Renderer::gameWidth / 5, Renderer::gameHeight / (MAX_NUMBER_OF_ITEMS ) *2.75f));

	menu[2].setFont(font);
	menu[2].setColor(sf::Color::White);
	menu[2].setString("Options");
	menu[2].setPosition(sf::Vector2f(4*Renderer::gameWidth / 5, Renderer::gameHeight / (MAX_NUMBER_OF_ITEMS) * 3.0f));

	menu[3].setFont(font);
	menu[3].setColor(sf::Color::White);
	menu[3].setString("Close");
	menu[3].setPosition(sf::Vector2f(4*Renderer::gameWidth / 5, Renderer::gameHeight / (MAX_NUMBER_OF_ITEMS ) *3.25f));

	selectedItemIndex = 0;

	text.setPosition(sf::Vector2f(4 * Renderer::gameWidth / 5, Renderer::gameHeight / (MAX_NUMBER_OF_ITEMS) *2.25f));
	text.setString("Menu");
	text.setFont(font);
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
	mousePos = sf::Mouse::getPosition(Renderer::getWindow());
	moveTime -= dt;
	if (mousePos.x >=  0.78f * Renderer::gameWidth && mousePos.x <= 0.94f * Renderer::gameWidth )
	{
		if (moveTime <= 0 && mousePos.y >= menu[0].getPosition().y && mousePos.y <  menu[1].getPosition().y)
		{
			
			moveTo(0);
			if (sf::Mouse::isButtonPressed(Mouse::Left))
			{
				activeScene = gameScene; //switch to game
				std::cout << "New game button has been pressed" << std::endl;
			}
		}
		else if (moveTime <= 0 && mousePos.y >= menu[1].getPosition().y && mousePos.y <  menu[2].getPosition().y)
		{
		
			moveTo(1);
			if (sf::Mouse::isButtonPressed(Mouse::Left))
			{
				moveTime = 0.2f;
				std::cout << "Load button has been pressed" << std::endl;
			}

		}
		else if (moveTime <= 0 && mousePos.y >= menu[2].getPosition().y && mousePos.y <  menu[3].getPosition().y)
		{
			
			moveTo(2);
			if (sf::Mouse::isButtonPressed(Mouse::Left))
			{
				moveTime = 0.2f;
				std::cout << "Options button has been pressed" << std::endl;
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
			activeScene = gameScene; //switch to game
			std::cout << "New game button has been pressed" << std::endl;
		}
		if (selectedItemIndex == 1) {
			std::cout << "Load button has been pressed" << std::endl;
		}
		if (selectedItemIndex == 2) {
			std::cout << "Options button has been pressed" << std::endl;
		}
		if (selectedItemIndex == 3) {
			Renderer::getWindow().close();
		}
	}
	Renderer::setCenter(Vector2f(Renderer::gameWidth / 2 + 25, Renderer::gameHeight/2));
	Scene::update(dt);
	_ents.update(dt);
}
void MenuScene::render() 
{
	Scene::render();
	Renderer::queue(&background);
	Renderer::queue(&title);
	Renderer::queue(&rect);
	Renderer::queue(&text);
	_ents.render();
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) { //for every menu item		
		Renderer::queue(&menu[i]);
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
		s->getSprite().setScale({ 2.0f, 2.0f });
		s->getSprite().setOrigin(8.0f, 12.0f);
		ghost->addComponent<HealthComponent>();
		ghost->addComponent<EnemyHealthBarComponent>();
		auto p = ghost->addComponent<EnemyAttackComponent>();
		p->setLevel(0);
		p->setPlayer(player);
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
	s->getSprite().setScale({ 2.0f, 2.0f });
	s->getSprite().setOrigin(8.0f, 12.0f);
	ghost->addComponent<HealthComponent>();
	auto p = ghost->addComponent<EnemyAttackComponent>();
	p->setLevel(0);
	p->setPlayer(player);
	ghost->addComponent<EnemyHealthBarComponent>();
	_ents.list.push_back(ghost);
	ghosts.push_back(ghost);
	/////////////////////////////////////////////////////////////////EXAMPLE NPC/////////////////////////////////////
	auto npc = make_shared<Entity>();
	auto n = npc->addComponent<CharacterSpriteComponent>();
	n->getSprite().setTexture(playerTexture);
	n->getSprite().setTextureRect({ 0,0,16,21 });
	n->getSprite().setScale({ 2.0f, 2.0f });
	n->getSprite().setOrigin(8.0f, 12.0f);
	auto d = npc->addComponent<NPCComponent>();
	d->setDialogue("HELLO THERE, ADVENTURER! HELLO THERE, \nADVENTURER! HELLO THERE, ADVENTURER! ");
	d->setEntities(player); ///////////TEMP SOLUTION /// need to update setEntities to take one entity, not vector
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
	ls::loadLevelFile("res/levels/example.txt", 25.0f);

	auto pl = make_shared<Entity>();
	pl->addComponent<CharacterSheetComponent>();
	auto mp = pl->addComponent<PlayerMovementComponent>();
	mp->setSpeed(100.0f);
	pl->addComponent<HealthComponent>();
	auto s = pl->addComponent<CharacterSpriteComponent>();
	s->getSprite().setTexture(playerTexture);
	s->getSprite().setTextureRect({ 0,0,16,21 });
	s->getSprite().setScale({ 2.0f, 2.0f });
	s->getSprite().setOrigin({8.0f, 12.0f});
	s->getSprite().setPosition({ 100.0f, 100.0f });
	_ents.list.push_back(pl);
	player = pl;

	auto hd = make_shared<Entity>();
	auto hb = hd->addComponent<HudComponent>();
	hb->setPlayer(player);
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