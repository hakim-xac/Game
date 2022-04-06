#pragma once
#include "includes.h"

namespace Game {

    using namespace sf;

    struct GameText { Text text; std::string name; IntRect rect; };
    struct Position { int x; int y; };


    class ProgrammLogic {

        Font font_;
        std::string fontPath_;
        bool isMenu_;
        std::queue<std::string> errorQueue_;
        GameSpriteInfo heroGsi_;

    private:
        template <typename... T>
        std::vector<GameText> createMenu(T&& ...args);

        
        void toLog(std::string&& str);
        GameText createButton(const std::string&& str, int x, int y, bool relativePosition = false);
        std::string_view getActiveItemMenu(std::vector<GameText>& menu, const RenderWindow& window);
        std::string strToLower(std::string str);
        void delimiter(char c = '=', std::ostream& out = std::cerr);
        void stringToOut(const std::string& str, std::ostream& out = std::cerr) const;
        void startGame(RenderWindow& window);
        bool readEvent(RenderWindow& window);
        void readErrors(RenderWindow& window);
        std::string timeToString(std::time_t&& time);
        std::unique_ptr<Sprite> gameSprite(const std::string& path, const Position& pos, RenderWindow& window);
    public:
        ProgrammLogic();
        void loop();
        constexpr void addUser();

    };












    template<typename ...T>
    inline std::vector<GameText> ProgrammLogic::createMenu(T&& ...args)
    {

        std::vector<std::string> v{std::forward<T>(args)...};
        std::vector<GameText> vec;
        vec.reserve(v.size());
        size_t minLength{ v.at(0).size() };
        
        std::for_each(std::begin(v), std::end(v), [&minLength](auto&& el) {
            if (el.size() < minLength) minLength = el.size();
            });

        size_t centerWidth{ 800 >> 1 };
        size_t centerHeight{ Settings::windowHeight >> 1 };
        size_t posHeight{ centerHeight - Settings::menuTextFontSize * v.size() };

        for (size_t i{};  auto && el : v) {
            Text text{ el, font_ };
            text.setCharacterSize(Settings::menuTextFontSize);
            size_t posWidth{ centerWidth - (static_cast<size_t>(text.getGlobalBounds().width) >> 1) };
            text.setPosition(static_cast<float>(posWidth), static_cast<float>(posHeight) + (text.getCharacterSize() * i));
            vec.emplace_back( GameText{text, strToLower(el), static_cast<IntRect>(text.getGlobalBounds())});
            ++i;
        }

        return vec;
    }

}