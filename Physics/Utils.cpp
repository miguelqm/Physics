#include "Settings.h"
#include "Utils.h"

float FloatB2ToSF(float f) {
	return f * PTM_RATIO;
}

float FloatSFToB2(float f) {
	return f / PTM_RATIO;
}

sf::Vector2f VectorB2ToSFf(b2Vec2 vec) {
	return sf::Vector2f(vec.x * PTM_RATIO, vec.y * PTM_RATIO);
}

sf::Vector2u VectorB2ToSFu(b2Vec2 vec) {
	return sf::Vector2u(vec.x * PTM_RATIO, vec.y * PTM_RATIO);
}

sf::Vector2i VectorB2ToSFi(b2Vec2 vec) {
	return sf::Vector2i(vec.x * PTM_RATIO, vec.y * PTM_RATIO);
}

b2Vec2 VectorSFToB2i(sf::Vector2i vec) {
	return b2Vec2(vec.x / PTM_RATIO, vec.y / PTM_RATIO);
}

b2Vec2 VectorSFToB2f(sf::Vector2f vec) {
	return b2Vec2(vec.x / PTM_RATIO, vec.y / PTM_RATIO);
}

b2Vec2 VectorSFToB2u(sf::Vector2u vec) {
	return b2Vec2(vec.x / PTM_RATIO, vec.y / PTM_RATIO);
}

std::vector<b2Body*> GetDynamicBodies(b2World* world)
{
	std::vector<b2Body*> bodies;
	b2Body* body;

	for (body = world->GetBodyList(); body != NULL; body = body->GetNext())
		if (body->GetType() == b2BodyType::b2_dynamicBody)
			bodies.push_back(body);

	return bodies;
}