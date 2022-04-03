#include "ProgrammLogic.h"

namespace Game {


    GameText ProgrammLogic::createButton(const std::string&& str, int x, int y, bool relativePosition)
    {
        Text text{ str, font_ };
        if(relativePosition) {
            text.setPosition(static_cast<float>(x), static_cast<float>(y));
        }
        else  {
            float width{ text.getGlobalBounds().width / 2 };
            float height{ text.getGlobalBounds().height / 2 };
            text.setPosition(static_cast<float>(x) - width, static_cast<float>(y) - height);
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
        while (!Keyboard::isKeyPressed(Keyboard::Escape)) {            
            window.clear();

            window.display();
        }
        isMenu_ = true;
        /* float time{ static_cast<float>(clock.getElapsedTime().asMicroseconds()) };
             clock.restart();
             time /= 300;
             float speed{ SPEED_DEFAULT * time };
             currentFrame += 0.005f * time;
             if (currentFrame > maxFrame) currentFrame -= maxFrame;
             int currentFrameInt{ static_cast<int>(currentFrame) };

             switch (direction)
             {
             case Directions::LEFT:
                 rob_sp.setTextureRect(IntRect(FrameWidth, 0, -FrameWidth, FrameHeight));
                 break;
             default:
                 rob_sp.setTextureRect(IntRect(0, 0, FrameWidth, FrameHeight));
                 break;
             }*/


             /*if (Keyboard::isKeyPressed(Keyboard::Left)
                 || Keyboard::isKeyPressed(Keyboard::A)) {
                 direction = Directions::LEFT;
                 rob_sp.move(-speed, 0);
                 rob_sp.setTextureRect(IntRect(currentFrameInt * FrameWidth + FrameWidth, 0, -FrameWidth, FrameHeight));

             }
             else if (Keyboard::isKeyPressed(Keyboard::Right)
                 || Keyboard::isKeyPressed(Keyboard::D)) {
                 direction = Directions::RIGHT;
                 rob_sp.move(speed, 0);
                 rob_sp.setTextureRect(IntRect(currentFrameInt * FrameWidth, 0, FrameWidth, FrameHeight));
             }

             if (Keyboard::isKeyPressed(Keyboard::Up)
                 || Keyboard::isKeyPressed(Keyboard::W)) {
                 rob_sp.move(0, -speed);
             }
             else if (Keyboard::isKeyPressed(Keyboard::Down)
                 || Keyboard::isKeyPressed(Keyboard::S)) {
                 rob_sp.move(0, speed);
             }*/
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
    {
        if(!font_.loadFromFile(fontPath_)) throw std::exception("Error load ttf");

    }

    void ProgrammLogic::loop()
    {
        ////////////////////////////////////////////// LOAD RESOURSE ///////////////////////////////////////////////

        auto menu{ createMenu("PLAY", "EXIT", "test")};


        RenderWindow window(sf::VideoMode(Settings::windowWidth, Settings::windowHeight), Settings::nameWindow.data());
       
        while (window.isOpen())
        {
            Event event;
            std::string_view activeName{};
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }

            if (isMenu_) {

                activeName = getActiveItemMenu(menu, window);

                if (Mouse::isButtonPressed(Mouse::Left)) {
                    if (activeName == "exit") {
                        window.close();
                    }
                    else if (activeName == "play") {
                        isMenu_ = false;
                        startGame(window);
                    }
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