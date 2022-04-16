#pragma once
#include "includes.h"

namespace Game {

    using namespace sf;

    struct GameText { Text text; std::string name; IntRect rect; };
    struct Position { int x; int y; };


    class ProgrammLogic {

    public:
        ProgrammLogic();
        void loop();
        constexpr void addUser();

    private:
        template <typename... T>
        std::vector<GameText> createMenu(T&& ...args);
        
        template <typename... Args>
        void writeErrors(Args&&... args); 

        template <typename... Args>
        constexpr std::string generateString(char del, Args&&... args);


        GameText createButton(const std::string&& str, int x, int y, bool relativePosition = false);
        std::string_view getActiveItemMenu(std::vector<GameText>& menu, const RenderWindow& window);
        std::string strToLower(std::string str);
        constexpr std::string delimiter(char del = '=');

        void stringToOut(const std::string& str, std::ostream& out = std::cerr) const;
        void startGame(RenderWindow& window);
        bool readEvent(RenderWindow& window);
        void readErrors(RenderWindow& window);
        void menuDraw(RenderWindow& window, const std::vector<Game::GameText>& menu) const;
        std::string timeToString(std::time_t&& time);

        Font font_;
        std::string fontPath_;
        bool isMenu_;
        std::queue<std::string> errorQueue_;
        GameSpriteInfo heroGsi_;

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


    template<typename ...Args>
    inline void ProgrammLogic::writeErrors(Args&& ...args)
    {
        errorQueue_.push("/*");
        ((errorQueue_.push(std::forward<Args>(args))), ...);
        errorQueue_.push("*/");
    }


    template <typename... Args>
    constexpr std::string ProgrammLogic::generateString(char del, Args&&... args)
    {
        static_assert(sizeof...(args) > 0, "Template parameters must be greater than 1");
        if constexpr (sizeof...(args) > 0) {
            constexpr size_t size{ (sizeof(std::forward<Args>(args)) + ...) };
            constexpr size_t maxSize{ size };

            static_assert(maxSize <= Settings::maxLengthTextInLog
                , "The total length of the string exceeds the length at the address Settings::maxLengthTextInLog");

            return std::string{ "#"
                + std::string(1, del)
                + ((std::string(std::forward<Args>(args)) + del) + ...)
                + std::string(Settings::maxLengthTextInLog - maxSize, del)
                + "#\n" };
        }
    }


    }