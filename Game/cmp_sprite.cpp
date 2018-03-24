#include "cmp_sprite.h"
#include "SystemRenderer.h"
#include <iostream>
using namespace sf;
ShapeComponent::ShapeComponent(Entity *p) : Component(p), _shape(std::make_shared<sf::CircleShape>()) {}

void ShapeComponent::update(double dt) 
{
	_shape->setPosition(_parent->getPosition());
}

void ShapeComponent::render() {
	Renderer::queue(_shape.get());
}

sf::Shape& ShapeComponent::getShape() const {
	return *_shape;
}

SpriteComponent::SpriteComponent(Entity *p) : Component(p), _sprite(std::make_shared<sf::Sprite>())
{
	frame = 0;
	walkingAnimationDown.push_back(sf::IntRect(0, 0, 16, 21));
	walkingAnimationDown.push_back(sf::IntRect(16, 0, 16, 21));
	walkingAnimationDown.push_back(sf::IntRect(32, 0, 16, 21));
	walkingAnimationDown.push_back(sf::IntRect(48, 0, 16, 21));

	walkingAnimationUp.push_back(sf::IntRect(0, 42, 16, 21));
	walkingAnimationUp.push_back(sf::IntRect(16, 42, 16, 21));
	walkingAnimationUp.push_back(sf::IntRect(32, 42, 16, 21));
	walkingAnimationUp.push_back(sf::IntRect(48, 42, 16, 21));
	
	walkingAnimationRight.push_back(sf::IntRect(0, 22, 16, 21));
	walkingAnimationRight.push_back(sf::IntRect(16, 22, 16, 21));
	walkingAnimationRight.push_back(sf::IntRect(32, 22, 16, 21));
	walkingAnimationRight.push_back(sf::IntRect(48, 22, 16, 21));

	walkingAnimationLeft.push_back(sf::IntRect(0, 65, 16, 21));
	walkingAnimationLeft.push_back(sf::IntRect(16, 65, 16, 21));
	walkingAnimationLeft.push_back(sf::IntRect(32, 65, 16, 21));
	walkingAnimationLeft.push_back(sf::IntRect(48, 65, 16, 21));
}

void SpriteComponent::update(double dt) 
{
	
	AnimationDelay -= dt;
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			if (frame > 3) frame = 0;
			if (AnimationDelay <= 0.0f)
			{
				_sprite->setTextureRect(walkingAnimationUp[frame]);
				frame++;
				AnimationDelay = 0.15f;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			if (frame > 3) frame = 0;
			if (AnimationDelay <= 0.0f)
			{
				_sprite->setTextureRect(walkingAnimationDown[frame]);
				frame++;
				AnimationDelay = 0.15f;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			if (frame > 3) frame = 0;
			if (AnimationDelay <= 0.0f)
			{
				_sprite->setTextureRect(walkingAnimationLeft[frame]);
				frame++;
				AnimationDelay = 0.15f;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			if (frame > 3) frame = 0;
			if (AnimationDelay <= 0.0f)
			{
				_sprite->setTextureRect(walkingAnimationRight[frame]);
				frame++;
				AnimationDelay = 0.15f;
			}
		}
	
	_sprite->setPosition(_parent->getPosition());
}

void SpriteComponent::render() {
	Renderer::queue(_sprite.get());
}
sf::Sprite& SpriteComponent::getSprite() const {
	return *_sprite;
}

