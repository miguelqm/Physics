#pragma once

#include "SFML\Graphics.hpp"
#include "box2d/box2d.h"

float FloatB2ToSF(float f);
float FloatSFToB2(float f);

sf::Vector2f VectorB2ToSFf(b2Vec2 vec);
sf::Vector2u VectorB2ToSFu(b2Vec2 vec);
sf::Vector2i VectorB2ToSFi(b2Vec2 vec);
b2Vec2 VectorSFToB2i(sf::Vector2i vec);
b2Vec2 VectorSFToB2f(sf::Vector2f vec);
b2Vec2 VectorSFToB2u(sf::Vector2u vec);

std::vector<b2Body*> GetDynamicBodies(b2World* world);

