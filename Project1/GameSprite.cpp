#include "GameSprite.h"

namespace Game {

	GameSprite::GameSprite(const std::string& path, const GameSpriteInfo& gsi)
		: texture_()
		, sprite_()
		, gsi_(gsi)
		, init_()
	{
		init_ = texture_.loadFromFile(path);
		if (init_) {
			sprite_.setTexture(texture_);
			sprite_.setTextureRect(IntRect{ gsi_.left, gsi_.top, gsi_.width, gsi_.height });
			sprite_.setPosition(gsi_.posX, gsi_.posY);
		}

	}


	Sprite GameSprite::getSprite() const
	{
		return sprite_;
	}


	Sprite GameSprite::operator() () {
		return sprite_;
	}
}