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
#include <string>




using namespace sf;
using namespace std;
const int GHOSTS_COUNT = 4;
Font font;
Texture playerTexture, zombieTexture, spellsTexture;
Texture menuBg;
sf::Sprite background;
RectangleShape rect;
MenuScene::MenuScene() {
}
void MenuScene::load() {
	if (!font.loadFromFile("res/fonts/leadcoat.ttf")) {
		cout << "Cannot load font!" << endl;
	}
	if (!menuBg.loadFromFile("res/img/splashScreen.png")) {
		cout << "Cannot load img!" << endl;
	}
	background.setTexture(menuBg);
	rect.setPosition(sf::Vector2f(3.8f * Renderer::gameWidth / 5, Renderer::gameHeight / (MAX_NUMBER_OF_ITEMS)  * 2.15f));
	//rect.setScale({ 3.0f,3.0f });
	rect.setSize({ Renderer::gameWidth / 5.7f,Renderer::gameHeight / 2.8f });
	rect.setFillColor(sf::Color(1,1,1,130));

	title.setPosition(sf::Vector2f(Renderer::gameWidth / 5.5f, Renderer::gameHeight / 5.5f));
	title.setString("ICY DEAD PEOPLE");
	title.setFont(font);
	title.setScale({ 3.5f,3.5f });
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
	} 
	else
	{
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex= MAX_NUMBER_OF_ITEMS-1;
		menu[selectedItemIndex].setColor(sf::Color::Red);
	}
}
void MenuScene::moveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setColor(sf::Color::Red);
	}
	else
	{
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex=0;
		menu[selectedItemIndex].setColor(sf::Color::Red);
	}
}

void MenuScene::update(double dt) {
	static float moveTime = 0.0f;
	moveTime -= dt;
	//if there are menu items to move to, move to it, limit keyboard input to 0.2
	if (moveTime <= 0 && Keyboard::isKeyPressed(Keyboard::Up)) {
		moveUp();
		moveTime = 0.2f;
	}
	if (moveTime <= 0 && Keyboard::isKeyPressed(Keyboard::Down)) {
		moveDown();
		moveTime = 0.2f;
	}
	if (moveTime <= 0 && Keyboard::isKeyPressed(Keyboard::Return)) {
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
		ghost->addComponent<EnemyAIComponent>();

		auto s = ghost->addComponent<CharacterSpriteComponent>();
		s->getSprite().setTexture(zombieTexture);
		s->getSprite().setTextureRect({ 0,0,16,21 });
		s->getSprite().setScale({ 2.0f, 2.0f });
		s->getSprite().setOrigin(8.0f, 12.0f);
		auto h = ghost->addComponent<HealthComponent>();
		_ents.list.push_back(ghost);
		ghosts.push_back(ghost);
		//eatingEnts.push_back(ghost);       ///ghosts can eat
		
	}
	///////stanting enemy
	auto ghost = make_shared<Entity>();
	auto s = ghost->addComponent<CharacterSpriteComponent>();
	s->getSprite().setTexture(zombieTexture);
	s->getSprite().setTextureRect({ 0,0,16,21 });
	s->getSprite().setScale({ 2.0f, 2.0f });
	s->getSprite().setOrigin(8.0f, 12.0f);
	auto h = ghost->addComponent<HealthComponent>();
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
	d->setEntities(eatingEnts); ///////////TEMP SOLUTION /// need to update setEntities to take one entity, not vector
	_ents.list.push_back(npc);
	npcs.push_back(npc);

	auto att = _ents.list[0]->addComponent<AttackComponent>();
	att->setEntities(ghosts);
	att->damageText.setFont(font);

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
	if (!spellsTexture.loadFromFile("res/img/spells.png"))
	{
		cerr << "Failed to load spritesheet!" << endl;
	}
	if (!zombieTexture.loadFromFile("res/img/zombie.png"))
	{
		cerr << "Failed to load spritesheet!" << endl;
	}
	ls::loadLevelFile("res/levels/example.txt", 25.0f);

	auto pl = make_shared<Entity>();
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
	hud = hd;


	eatingEnts.push_back(player);
	respawn();
	
}


void GameScene::update(double dt)
{
	auto health_mana = player->GetComponent<HealthComponent>();
	auto hudobject = hud->GetComponent<HudComponent>();
	hudobject->set(health_mana->getHealth(), health_mana->getMaxHealth(), health_mana->getMana(), health_mana->getMaxMana());
	hudobject->setText();
	if (health_mana->getHealth()<=0)
	{
		health_mana->reset();
		std::cout << "Game over!" << std::endl;
		respawn();
	}
	Renderer::setCenter(player->getPosition());
	if (Keyboard::isKeyPressed(Keyboard::Tab))
	{
		activeScene = menuScene;
	}
	
	for (auto &g : ghosts) 
	{
		if (!g->is_forDeletion())
		{
			auto hp = g->GetComponent<HealthComponent>();
			if (hp->getHealth() <= 0) g->setForDelete();
			if (length(g->getPosition() - player->getPosition()) < 20.0f)
			{
				auto d = player->GetComponent<PlayerMovementComponent>();
				d->move((player->getPosition() - g->getPosition())*3.0f);
				health_mana->reduceHealth(30);

			}
		}
	}

	hudobject->setPosition(Vector2f(player->getPosition().x - Renderer::gameWidth/2, player->getPosition().y - Renderer::gameHeight / 2));
	hudobject->render();
	_ents.update(dt);
	Scene::update(dt);
}
void GameScene::render()
{
	ls::Render(Renderer::getWindow());
	_ents.render();
	Scene::render();
}