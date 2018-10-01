#pragma once
#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>

class DrawableGroup: public sf::Drawable
{
private:
	std::vector<std::unique_ptr<sf::Drawable>> objectElements_;
public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (auto& el : objectElements_)
			target.draw(*el);
	}
	DrawableGroup();
	~DrawableGroup();
};

