#include "cmp_sprite.h"
#include "SystemRenderer.h"
#include <iostream>

ShapeComponent::ShapeComponent(Entity *p) : Component(p), _shape(std::make_shared<sf::CircleShape>()) {}

void ShapeComponent::update(double dt) {
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

}

void SpriteComponent::update(double dt) {
	_sprite->setPosition(_parent->getPosition());
}

void SpriteComponent::render() {
	Renderer::queue(_sprite.get());
}
sf::Sprite& SpriteComponent::getSprite() const {
	return *_sprite;
}

