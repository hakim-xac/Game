#pragma once
#include "includes.h"

namespace Game {

    using namespace sf;

    struct GameText { Text text; std::string name; IntRect rect; };


    class ProgrammLogic {

        Font font_;
        std::string fontPath_;
        bool isMenu_;

    private:
        GameText createButton(const std::string&& str, int x, int y, bool relativePosition = false);
        template <typename... T>
        std::vector<GameText> createMenu(T&& ...args);
        std::string strToLower(std::string str);
        void startGame(RenderWindow& window);
        std::string_view getActiveItemMenu(std::vector<GameText>& menu, const RenderWindow& window);
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
        size_t indent{ 40 };
        size_t minLength{ v.at(0).size() };
        
        std::for_each(std::begin(v), std::end(v), [&minLength](auto&& el) {
            if (el.size() < minLength) minLength = el.size();
            });

        size_t centerWidth{ Settings::windowWidth >> 1 };
        size_t centerHeight{ Settings::windowHeight >> 1 };
        size_t posHeight{ centerHeight - indent * v.size() };

        for (size_t i{};  auto && el : v) {
            Text text{ el, font_ };
            size_t posWidth{ centerWidth - (static_cast<size_t>(text.getGlobalBounds().width) >> 1) };
            text.setPosition(static_cast<float>(posWidth), static_cast<float>(posHeight) + (indent * i));
            vec.emplace_back( GameText{text, strToLower(el), static_cast<IntRect>(text.getGlobalBounds())});
            ++i;
        }

        return vec;
    }

}