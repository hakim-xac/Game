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
        void writeToLog(Args&&... args);


        template <typename... Args>
        void writeReadToLog(RenderWindow& window, IsClosedWindow isw, Args&&... args);

        template <typename... Args>
        constexpr std::string generateString(char del, Args&&... args);

        template <typename... Args>
        constexpr std::pair<bool, bool> addToResourseVec(Args&&... args);


        GameText createButton(const std::string&& str, int x, int y, bool relativePosition = false);
        std::string_view getActiveItemMenu(std::vector<GameText>& menu, const RenderWindow& window);
        std::string strToLower(std::string str);
        constexpr std::string delimiter(char del = '=');

        void stringToOut(const std::string& str, std::ostream& out = std::cerr) const;
        void startGame(RenderWindow& window);
        bool readEvent(RenderWindow& window);
        void readInLog(RenderWindow& window, IsClosedWindow isw = IsClosedWindow::YES);
        void menuDraw(RenderWindow& window, const std::vector<Game::GameText>& menu) const;
        std::string timeToString(std::time_t&& time);

        Font font_;
        std::string fontPath_;
        bool isMenu_;
        std::queue<std::string> errorQueue_;
        GameSpriteInfo heroGsi_;

    };












    template<typename ...T>
    inline std::vector<GameText> ProgrammLogic
        ::createMenu(T&& ...args)
    {

        std::vector<std::string> v{std::forward<T>(args)...};
        std::vector<GameText> vec;
        vec.reserve(v.size());
        size_t minLength{ v.at(0).size() };
        
        std::for_each(std::begin(v), std::end(v), [&minLength](auto&& el) {
            if (el.size() < minLength) minLength = el.size();
            });

        size_t centerWidth{ Settings::windowWidth >> 1 };
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
    inline void ProgrammLogic
        ::writeToLog(Args&& ...args)
    {
        static_assert(sizeof...(args) > 0
            , "Template parameters must be greater than 1");

        errorQueue_.push("/*");
        ((errorQueue_.push(std::forward<Args>(args))), ...);
        errorQueue_.push("*/");
    }


    template<typename ...Args>
    inline void ProgrammLogic
        ::writeReadToLog(RenderWindow& window, IsClosedWindow isw, Args&& ...args)
    {
        static_assert(sizeof...(args) > 0
            , "Template parameters must be greater than 1");
        writeToLog(std::forward<Args>(args)...);
        readInLog(window, isw);
    }


    template <typename... Args>
    constexpr std::string ProgrammLogic
        ::generateString(char del, Args&&... args)
    {
        static_assert(sizeof...(args) > 0
            , "Template parameters must be greater than 1");

        if constexpr (sizeof...(args) > 0) {

            static_assert((std::is_same_v<std::decay_t<Args>, std::string> && ...)
                , "All arguments must be of type std::string");
            std::array<std::string, sizeof...(args)> array{ std::forward<Args>(args)... };

            size_t size{ std::accumulate(array.begin(), array.end(), size_t(0),[](size_t lhs, auto rhs) {
                return lhs + rhs.size() + 1;
                }) + 4 };

            assert(size <= Settings::maxLengthTextInLog);

            std::string tmp{"# "};
            for (auto&& elem: array) {
                tmp += elem + " ";
            }
            tmp += std::string(Settings::maxLengthTextInLog - tmp.size() - 2, del);
            tmp += "#\n";
            assert(tmp.size() <= Settings::maxLengthTextInLog);
            return tmp;
        }
    }


    template <typename... Args>
    inline constexpr std::pair<bool, bool> ProgrammLogic
        ::addToResourseVec(Args&& ...args)
    {
        /*static_assert((std::is_same_v<std::decay_t<Args>, GameSprite> && ...)
            , "All arguments must be of type std::unique_ptr<GameSprite>");*/

       // std::vector<std::unique_ptr<GameSprite>> vec = { std::forward<Args>(args)... };
        

        return { false, false };
    }


    }