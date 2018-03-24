#pragma once
#include "SystemRenderer.h"
#include "Game.h"
#include "levelsystem.h"
#include "cmp_sprite.h"
#include "cmp_actor_movement.h"
#include "cmp_pickups.h"
#include "cmp_attack.h"

#define MAX_NUMBER_OF_ITEMS 3 //number of main menu options

using namespace sf;
using namespace std;
const int GHOSTS_COUNT = 4;
Font font;
Texture spritesheet;
MenuScene::MenuScene() {
}
void MenuScene::load() {
	if (!font.loadFromFile("res/fonts/leadcoat.ttf")) {
		cout << "Cannot load font!" << endl;
	}

	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		activeScene = gameScene;
	}

	//list of menu items
	menu[0].setFont(font);
	menu[0].setColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setPosition(sf::Vector2f(Renderer::gameWidth / 2, Renderer::gameHeight / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setColor(sf::Color::White);
	menu[1].setString("Options");
	menu[1].setPosition(sf::Vector2f(Renderer::gameWidth / 2, Renderer::gameHeight / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setColor(sf::Color::White);
	menu[2].setString("Close");
	menu[2].setPosition(sf::Vector2f(Renderer::gameWidth / 2, Renderer::gameHeight / (MAX_NUMBER_OF_ITEMS + 1) * 3));

	selectedItemIndex = 0;

	text.setPosition(Vector2f((1280* 0.5f) - (text.getLocalBounds().width * 0.5f), 0));
	text.setString("Main Menu");
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
}
void MenuScene::moveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex++;
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
			std::cout << "Play button has been pressed" << std::endl;
		}
		if (selectedItemIndex == 1) {
			std::cout << "Options button has been pressed" << std::endl;
		}
		if (selectedItemIndex == 2) {
			std::cout << "Close button has been pressed" << std::endl;
		}
	}
	Renderer::setCenter(Vector2f(Renderer::gameWidth / 2 + 25, Renderer::gameHeight/2));
	Scene::update(dt);
	_ents.update(dt);
}
void MenuScene::render() {
	Scene::render();
	_ents.render(); 
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) { //for every menu item
		Renderer::queue(&text);
		Renderer::queue(&menu[i]);
	}
}
vector<shared_ptr<Entity>> ghosts;
vector<shared_ptr<Entity>> eatingEnts;
shared_ptr<Entity> player;
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
const sf::Color ghost_cols[]{ { 208, 62, 25 },
{ 219, 133, 28 },
{ 70, 191, 238 },
{ 234, 130, 229 } };
void GameScene::respawn()
{
	for (auto n : ghosts)
	{
		n->setForDelete();
		n.reset();
	}
	ghosts.clear();

	Vector2f pos = Vector2f{ 300.0f, 300.0f };
	for (int i = 0; i < GHOSTS_COUNT; ++i)
	{
		auto ghost = make_shared<Entity>();
		ghost->addComponent<EnemyAIComponent>();

		auto s = ghost->addComponent<ShapeComponent>();
		s->setShape<sf::CircleShape>(10.0f);
		s->getShape().setFillColor(ghost_cols[i % 4]);
		s->getShape().setOrigin(Vector2f(10.f, 10.f));

		_ents.list.push_back(ghost);
		ghosts.push_back(ghost);
		pos += Vector2f(70.0f, 0);
	}

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
	if (!spritesheet.loadFromFile("res/img/player.png"))
	{
		cerr << "Failed to load spritesheet!" << endl;
	}
	ls::loadLevelFile("res/levels/example.txt", 25.0f);

	auto pl = make_shared<Entity>();
	auto mp = pl->addComponent<PlayerMovementComponent>();
	mp->setSpeed(100.0f);
	auto s = pl->addComponent<SpriteComponent>();
	s->getSprite().setTexture(spritesheet);	
	s->getSprite().setTextureRect({ 0,0,16,21 });
	s->getSprite().setScale({ 2.0f, 2.0f });
	s->getSprite().setOrigin({8.0f, 8.0f});
	s->getSprite().setPosition({ 100.0f, 100.0f });

	/*s->setShape<sf::CircleShape>(10.0f);
	s->getShape().setFillColor(Color::Yellow);
	s->getShape().setOrigin(10.0f, 10.0f);
	s->getShape().setPosition({ 100.0f, 100.0f});*/
	_ents.list.push_back(pl);
	player = pl;
	eatingEnts.push_back(player);
	respawn();
	
}
void GameScene::update(double dt)
{
	Renderer::setCenter(player->getPosition());
	if (Keyboard::isKeyPressed(Keyboard::Tab))
	{
		activeScene = menuScene;
	}
	
	for (auto &g : ghosts) 
	{
		if(!g->is_forDeletion())
		if (length(g->getPosition() - player->getPosition()) < 15.0f) 
		{
			std::cout << "Game over!" << std::endl;
			respawn();
		}
	}
	_ents.update(dt);
	Scene::update(dt);
}
void GameScene::render()
{
	ls::Render(Renderer::getWindow());
	_ents.render();
	Scene::render();
}