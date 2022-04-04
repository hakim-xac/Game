#include "ProgrammLogic.h"

namespace Game {

    void ProgrammLogic::toLog(std::string&& str)
    {
        errorQueue_.push(currentDateTime());
        errorQueue_.push(str);
    }

    std::string ProgrammLogic::currentDateTime()
    {
        return "";              //TODO
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

    void ProgrammLogic::startGame(RenderWindow& window)
    {
        auto [hero, isCreateHero] = gameSprite( "sprites/rob2.png", Position{Settings::heroWidth, Settings::heroHeight }) ;
        if (!isCreateHero) {
            toLog("--------------------------------------------------------------------------------------");
            toLog("FileNotFound");
            toLog("gameSprite(\"sprites /rob2.png\", Position{Settings::heroWidth, Settings::heroHeight})");
            toLog("--------------------------------------------------------------------------------------");
        }
        Image heroImg;
        heroImg.loadFromFile("sprites/rob2.png");
        Texture heroTexture;
        heroTexture.loadFromImage(heroImg);
        Sprite heroSprite{ heroTexture, IntRect{ 0, 0,Settings::heroWidth, Settings::heroHeight } };

        heroSprite.setPosition(
            static_cast<float>((Settings::windowWidth - Settings::heroWidth) >> 1)
            , static_cast<float>((Settings::windowHeight - Settings::heroHeight) >> 1)
        );
        
        Clock clock;
        float currentFrame{};
        Direction horizontDirection { Direction::Right };
        bool isKeyPresed;
        while (!Keyboard::isKeyPressed(Keyboard::Escape)) {  
            if (readEvent(window)) break;
            float time{ static_cast<float>(clock.getElapsedTime().asMicroseconds()) };
            time /= 300;
            clock.restart();
            float speed{ time * 0.1f };
            currentFrame += 0.005f * time;
            isKeyPresed = false;
            if (currentFrame > Settings::heroMaxFrame) currentFrame -= Settings::heroMaxFrame;

            int currentFrameInt{ static_cast<int>(currentFrame) };

            if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
                isKeyPresed = true;
                horizontDirection = Direction::Left;
                heroSprite.move(-speed, 0);
                heroSprite.setTextureRect(IntRect{
                    Settings::heroWidth * currentFrameInt + Settings::heroWidth, 0, -Settings::heroWidth, Settings::heroHeight
                    });
            }
            else if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
                isKeyPresed = true;
                horizontDirection = Direction::Right;
                heroSprite.move(speed, 0);
                heroSprite.setTextureRect(IntRect{
                    Settings::heroWidth * currentFrameInt, 0, Settings::heroWidth, Settings::heroHeight
                    });
            }
            if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) {
                isKeyPresed = true;
                switch (horizontDirection)
                {
                case Game::Direction::Left:
                    heroSprite.setTextureRect(IntRect{
                    Settings::heroWidth * currentFrameInt + Settings::heroWidth, 0, -Settings::heroWidth, Settings::heroHeight
                        });
                    break;
                default:
                    heroSprite.setTextureRect(IntRect{
                    Settings::heroWidth * currentFrameInt, 0, Settings::heroWidth, Settings::heroHeight
                        });
                    break;
                }
                heroSprite.move(0, -speed);
            }
            else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) {
                isKeyPresed = true;
                switch (horizontDirection)
                {
                case Game::Direction::Left:
                    heroSprite.setTextureRect(IntRect{
                    Settings::heroWidth * currentFrameInt + Settings::heroWidth, 0, -Settings::heroWidth, Settings::heroHeight
                        });
                    break;
                default:
                    heroSprite.setTextureRect(IntRect{
                    Settings::heroWidth * currentFrameInt, 0, Settings::heroWidth, Settings::heroHeight
                        });
                    break;
                }
                heroSprite.move(0, speed);
            }
            if (!isKeyPresed) {
                switch (horizontDirection)
                {
                case Game::Direction::Left:
                    heroSprite.setTextureRect(IntRect{ Settings::heroWidth, 0, -Settings::heroWidth, Settings::heroHeight });
                    break;
                default:
                    heroSprite.setTextureRect(IntRect{ 0, 0, Settings::heroWidth, Settings::heroHeight });
                    break;
                }                
            }
          
            window.clear();
            window.draw(heroSprite);
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

    std::pair<Sprite, bool> ProgrammLogic::gameSprite(const std::string& path, const Position& pos)
    {
        Image img;
        if (!img.loadFromFile(path)) return std::make_pair(Sprite(), false);

        Texture texture;
        if( !texture.loadFromFile(path)) return std::make_pair(Sprite(), false);
        Sprite sprite{ texture, IntRect{ 0, 0,Settings::heroWidth, Settings::heroHeight } };
        return std::make_pair(sprite, true);


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
        : fontPath_("fonts/arial.ttf")
        , isMenu_(true)
        , errorQueue_()
    {
        if(!font_.loadFromFile(fontPath_)) throw std::exception("Error load ttf");

    }

    void ProgrammLogic::loop()
    {
        ////////////////////////////////////////////// LOAD RESOURSE ///////////////////////////////////////////////



        RenderWindow window(sf::VideoMode(Settings::windowWidth, Settings::windowHeight), Settings::nameWindow.data());
       
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
            if (!errorQueue_.empty()) {
                window.close();
                while (!errorQueue_.empty()) {
                    std::cerr << errorQueue_.front() << "\n";
                    errorQueue_.pop();
                }
            }
            
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