#include "GameSprite.h"

namespace Game {


	inline bool GameSprite::Init(const std::string& path)
	{
		init_ = texture_->loadFromFile(path);
		if (init_) {
			sprite_->setTexture(*texture_);
			sprite_->setTextureRect(IntRect{ gsi_.left, gsi_.top, gsi_.width, gsi_.height });
			sprite_->setPosition(
				static_cast<float>(gsi_.posX)
				, static_cast<float>(gsi_.posY)
			);
			return true;
		}
		return false;
	}


	GameSprite::GameSprite(const std::string& path, const GameSpriteInfo& gsi)
		: texture_(std::make_unique<Texture>())
		, sprite_(std::make_unique<Sprite>())
		, gsi_(gsi)
	{
		Init(path);		
	}

	GameSprite::GameSprite(const GameSprite& gs) noexcept
		: texture_(new Texture(*gs.texture_.get()))
		, sprite_(new Sprite(*gs.sprite_.get()))
		, gsi_(gs.gsi_)
		, init_(gs.init_) {}


	GameSprite::GameSprite(const std::string& path, RespawnPosition rp)
		: texture_(std::make_unique<Texture>())
		, sprite_(std::make_unique<Sprite>())
	{
		float posX{};
		float posY{};
		switch (rp) {
		case RespawnPosition::Center:
			posX = (Settings::windowWidth - Settings::heroWidth) >> 1;
			posY = (Settings::windowHeight - Settings::heroHeight) >> 1;
			break;

		case RespawnPosition::Random:
			/// <summary>
			/// ////////////	TODO
			/// </summary>
			/// <param name="path"></param>
			/// <param name="rp"></param>
			break;
		default:
			posX = (Settings::windowWidth - Settings::heroWidth) >> 1;
			posY = (Settings::windowHeight - Settings::heroHeight) >> 1;
		}

		gsi_ = GameSpriteInfo{
			posX
			, posY
			, 0
			, 0
			, Settings::heroWidth
			, Settings::heroWidth
		};

		Init(path);
	}


	Sprite& GameSprite::getSprite()
	{
		return *sprite_;
	}


	bool GameSprite::getIsInit() const
	{
		return init_;
	}
}