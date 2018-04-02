#pragma once
#include "Scene.h"
#define MAX_NUMBER_OF_ITEMS 3

extern std::shared_ptr<Scene> gameScene;
extern std::shared_ptr<Scene> menuScene;
extern std::shared_ptr<Scene> activeScene;
extern sf::Texture playerTexture;
extern sf::Texture zombieTexture;
extern sf::Texture spellsTexture;
extern sf::Font font;
class MenuScene : public Scene
{
private:
	int selectedItemIndex;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	sf::Text text;
public:
	MenuScene();
	void update(double dt) override;
	void render() override;
	void load() override;
	void moveUp();
	void moveDown();
};

class GameScene : public Scene
{
private:
	sf::Clock scoreClock;
	sf::Text text;
	void respawn();
public:
	GameScene() = default;
	void update(double dt) override;
	void render() override;
	void load() override;
};