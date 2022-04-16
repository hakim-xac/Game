#pragma once
#include <SFML/Graphics.hpp>
#include "Settings.h"

namespace Game {

	using namespace sf;

	enum class RespawnPosition {
		Random
		, Center
	};



	struct GameSpriteInfo {
		float posX;
		float posY;
		int left;
		int top;
		int width;
		int height;
	};


	////////////////////////////////////////////////////////////
	/// 
	///
	////////////////////////////////////////////////////////////
	class GameSprite
	{


	public:
		GameSprite(const std::string& path, const GameSpriteInfo& gsi);
		GameSprite(const std::string& path, RespawnPosition rp = RespawnPosition::Center);
		Sprite& getSprite();
		bool getIsInit() const;

	private:

		GameSprite() = delete;
		inline bool Init(const std::string& path);

		std::unique_ptr<Texture> texture_;
		std::unique_ptr<Sprite> sprite_;

		GameSpriteInfo gsi_;
		bool init_;
	};
}
