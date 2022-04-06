#pragma once
#include <SFML/Graphics.hpp>

namespace Game {

	using namespace sf;

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

		Texture texture_;
		Sprite sprite_;
		GameSpriteInfo gsi_;
		bool init_;
	private:
		GameSprite() = delete;

	public:
		GameSprite(const std::string& path, const GameSpriteInfo& gsi);
		Sprite getSprite() const;
		Sprite operator() ();
	};
}
