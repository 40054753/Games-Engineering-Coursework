#pragma once
#include "Scene.h"
#include "SFML\Audio.hpp"





enum ITEM_TYPE { WEAPON, SHIELD, HELMET, ARMOUR, BOOTS, POTION, POWERUP, KEYITEM };
extern int resolution_index;
extern std::shared_ptr<Scene> gameScene;
extern std::shared_ptr<Scene> menuScene;
extern std::shared_ptr<Scene> optionsScene;
extern std::shared_ptr<Scene> activeScene;
extern sf::Texture playerTexture;
extern sf::Texture zombieTexture;
extern sf::Texture spellsTexture;
extern sf::Texture animatedSpellsTexture;
extern sf::Texture iconsTexture;
extern sf::Texture itemsTexture;
extern sf::Texture spell_icons;
extern sf::Texture tile_textures;
extern sf::Texture swordSwingTexture;
extern std::shared_ptr<Entity> player;
extern sf::SoundBuffer buffer;
extern sf::Sound sound;
extern sf::Texture snowEffect;
extern sf::Font font;
extern sf::Vector2i mousePos;
extern bool fullscreen;
#define MAX_NUMBER_OF_ITEMS 4
#define WX  1.0f*Renderer::gameWidth[resolution_index]
#define WY 1.0f*Renderer::gameHeight[resolution_index]

extern std::string codes[101];
extern sf::Keyboard::Key controls[13];
class MenuScene : public Scene
{
private:
	float moveTime=0.0f;
	int selectedItemIndex;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	sf::Text text;
	sf::RectangleShape button_return;
	sf::Text text_return;
	sf::Text title;
public:
	MenuScene();
	void update(double dt) override;
	void render() override;
	void load() override;
	void moveUp();
	void moveDown();
	void moveTo(int x);
};

class GameScene : public Scene
{
private:	
	bool start_blackout = false;
	bool stop_blackout = false;
	float blackout_slider=0;
	sf::RectangleShape blackout;
	sf::Text text;
	void respawn_interior0();
	void respawn_village0();
public:
	GameScene() { }
	void update(double dt) override;
	void render() override;
	void load() override;
};

class OptionsScene : public Scene
{
private:
	sf::CircleShape button_resolution_right;
	sf::CircleShape button_resolution_left;
	sf::RectangleShape button_return;
	sf::Text text_resolution;
	sf::RectangleShape bg_resolution;
	sf::Text text_screenmode;
	sf::RectangleShape bg_screenmode;
	sf::CircleShape button_screenmode_dot;
	sf::Text text_move_up;
	sf::RectangleShape bg_move_up;
	sf::RectangleShape rect;
	sf::Text text_return;
	sf::Text title;
	sf::Text left_list;
	sf::Text right_list;
	sf::Text right_list2;
	sf::Text control_labels[13];
	float delay = 0.2f;
	bool keySelected[13] = { false,false,false,false,false,false,false,false,false,false,false,false,false };
	bool anyKeySelected=false;
	int selectedKey = 0;

public:
	OptionsScene();
	void update(double dt) override;
	void render() override;
	void load() override;
};