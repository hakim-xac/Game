#include "ProgrammLogic.h"

namespace Game {

    void ProgrammLogic::toLog(std::string&& str)
    {
        errorQueue_.push(str);        
    }


    GameText ProgrammLogic::createButton(const std::string&& str, int x, int y, bool relativePosition)
    {
        Text text{ str, font_ };
        if(relativePosition) {

            text.setPosition(
                static_cast<float>(x)
                , static_cast<float>(y)
            );
        }
        else  {
            float width{ text.getGlobalBounds().width / 2 };
            float height{ text.getGlobalBounds().height / 2 };

            text.setPosition(
                static_cast<float>(x) - width
                , static_cast<float>(y) - height
            );
        }
        
        return { text, "", static_cast<IntRect>(text.getGlobalBounds())};
    }



    std::string ProgrammLogic::strToLower(std::string str)
    {
        std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
            return std::tolower(c);
            });
        return str;
    }

    void ProgrammLogic::delimiter(char c, std::ostream& out)
    {
        out.fill(c);
        out.width(Settings::maxLengthTextInLog);
        out << "#" << "#\n";
    }

    void ProgrammLogic::stringToOut(const std::string& str, std::ostream& out) const
    {
        std::cerr.fill(' ');
        std::cerr.width(Settings::maxLengthTextInLog);
        std::cerr << str << "#" << "\n";
    }

    void ProgrammLogic::startGame(RenderWindow& window)
    {
        GameSpriteInfo heroGsi{
            static_cast<float>((Settings::windowWidth - Settings::heroWidth) >> 1)
            , static_cast<float>((Settings::windowHeight - Settings::heroHeight) >> 1)
            , 0
            , 0
            , Settings::heroWidth
            , Settings::heroWidth
        };

        auto heroGs{ std::make_unique<GameSprite>( Settings::heroPathImage.data(), heroGsi ) };

        Sprite hero{ heroGs->getSprite() };
        
        Clock clock;
        float currentFrame{};
        Direction horizontDirection { Direction::Right };
        bool isKeyPresed;
        while (!Keyboard::isKeyPressed(Keyboard::Escape)) {  
            if (readEvent(window)) break;
            float time{ static_cast<float>(clock.getElapsedTime().asMicroseconds()) };
            time /= 800;
            clock.restart();
            float speed{ time * 0.1f };
            currentFrame += 0.01f * time;
            isKeyPresed = false;
            if (currentFrame > Settings::heroMaxFrame) currentFrame -= Settings::heroMaxFrame;

            int currentFrameInt{ static_cast<int>(currentFrame) };

            if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
                isKeyPresed = true;
                horizontDirection = Direction::Left;
                hero.move(-speed, 0);
                hero.setTextureRect(IntRect{
                    Settings::heroWidth * currentFrameInt + Settings::heroWidth, 0, -Settings::heroWidth, Settings::heroHeight
                    });
            }
            else if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
                isKeyPresed = true;
                horizontDirection = Direction::Right;
                hero.move(speed, 0);
                hero.setTextureRect(IntRect{
                    Settings::heroWidth * currentFrameInt, 0, Settings::heroWidth, Settings::heroHeight
                    });
            }
            if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) {
                isKeyPresed = true;
                switch (horizontDirection)
                {
                case Game::Direction::Left:
                    hero.setTextureRect(IntRect{
                    Settings::heroWidth * currentFrameInt + Settings::heroWidth, 0, -Settings::heroWidth, Settings::heroHeight
                        });
                    break;
                default:
                    hero.setTextureRect(IntRect{
                    Settings::heroWidth * currentFrameInt, 0, Settings::heroWidth, Settings::heroHeight
                        });
                    break;
                }
                hero.move(0, -speed);
            }
            else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) {
                isKeyPresed = true;
                switch (horizontDirection)
                {
                case Game::Direction::Left:
                    hero.setTextureRect(IntRect{
                    Settings::heroWidth * currentFrameInt + Settings::heroWidth, 0, -Settings::heroWidth, Settings::heroHeight
                        });
                    break;
                default:
                    hero.setTextureRect(IntRect{
                    Settings::heroWidth * currentFrameInt, 0, Settings::heroWidth, Settings::heroHeight
                        });
                    break;
                }
                hero.move(0, speed);
            }
            if (!isKeyPresed) {
                switch (horizontDirection)
                {
                case Game::Direction::Left:
                    hero.setTextureRect(IntRect{ Settings::heroWidth, 0, -Settings::heroWidth, Settings::heroHeight });
                    break;
                default:
                    hero.setTextureRect(IntRect{ 0, 0, Settings::heroWidth, Settings::heroHeight });
                    break;
                }                
            }
          
            window.clear();
            window.draw(hero);
            window.display();
        }
    }

    bool ProgrammLogic::readEvent(RenderWindow& window)
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
                return true;
            }
        }
        return false;
    }

    void ProgrammLogic::readErrors(RenderWindow& window)
    {
        if (!errorQueue_.empty()) {
            window.close();
            std::cerr.setf(std::ios::left, std::ios::adjustfield);
            while (!errorQueue_.empty()) {

                delimiter();
                delimiter(' ');
                stringToOut("# time: " + timeToString(std::time(nullptr)));
                stringToOut("# error: " + errorQueue_.front() + "\"");
                delimiter(' ');
                delimiter();

                errorQueue_.pop();
            }
        }
    }

    std::string ProgrammLogic::timeToString(std::time_t&& time)
    {
        std::tm tm;
        localtime_s(&tm, &time);
        std::stringstream ss;
        ss << tm.tm_mday << "." << tm.tm_mon << "." << tm.tm_year+1900 << " "
            << tm.tm_hour << ":" << tm.tm_min << ":" << tm.tm_sec;
        return ss.str();
    }

    std::unique_ptr<Sprite> ProgrammLogic::gameSprite(const std::string& path, const Position& pos, RenderWindow& window)
    {
        std::unique_ptr<Image> image{ std::make_unique<Image>(Image{}) };
        if (!image->loadFromFile(path)) return nullptr;

        std::unique_ptr<Texture> texture{ std::make_unique<Texture>(Texture{})};

        if( !texture->loadFromFile(path)) return nullptr;

        std::unique_ptr<Sprite> sprite{
            std::make_unique<Sprite>(Sprite{ *texture, IntRect{0, 0,Settings::heroWidth, Settings::heroHeight} })
        };

        return sprite;


        /*Image heroImg;
        heroImg.loadFromFile("sprites/rob2.png");
        Texture heroTexture;
        heroTexture.loadFromImage(heroImg);
        Sprite heroSprite{ heroTexture, IntRect{ 0, 0,Settings::heroWidth, Settings::heroHeight } };

        heroSprite.setPosition(
            static_cast<float>((Settings::windowWidth - Settings::heroWidth) >> 1)
            , static_cast<float>((Settings::windowHeight - Settings::heroHeight) >> 1)
        );*/
    }

    std::string_view ProgrammLogic::getActiveItemMenu(std::vector<GameText>& menu,const RenderWindow& window)
    {
        for (auto&& el : menu) {
            el.text.setFillColor(Color(128, 128, 128, 255));
            if (el.rect.contains(Mouse::getPosition(window))) {
                el.text.setFillColor(Color::Cyan);
                return el.name;
            }
        }
        return std::string_view("");
    }

    ProgrammLogic::ProgrammLogic()
        : fontPath_(Settings::fontPath)
        , isMenu_(true)
        , errorQueue_()
        , heroGsi_{
            static_cast<float>((Settings::windowWidth - Settings::heroWidth) >> 1)
            , static_cast<float>((Settings::windowHeight - Settings::heroHeight) >> 1)
            , 0
            , 0
            , Settings::heroWidth
            , Settings::heroWidth
        }
    {
        if(!font_.loadFromFile(fontPath_)) throw std::exception("Error load ttf");

    }

    void ProgrammLogic::loop()
    {
        ////////////////////////////////////////////// LOAD RESOURSE ///////////////////////////////////////////////



        RenderWindow window{ sf::VideoMode(Settings::windowWidth, Settings::windowHeight), Settings::nameWindow.data() };
       
        auto menu{ createMenu("PLAY", "EXIT")};
        while (window.isOpen())
        {

            readEvent(window);

            if (isMenu_) {

                std::string_view activeName{ getActiveItemMenu(menu, window) };

                if (Mouse::isButtonPressed(Mouse::Left)) {
                    if (activeName == "exit") {
                        window.close();
                    }
                    else if (activeName == "play") {
                        startGame(window);
                    }
                }
            }

            readErrors(window);
            
            window.clear();

            if (isMenu_) {
                for (auto&& el : menu) window.draw(el.text);
            }

            window.display();
        }

    }

    constexpr void ProgrammLogic::addUser()
    {
        //users.emplace_back(Users( Location(0, 0, 10, 10 ) ));
    }


}