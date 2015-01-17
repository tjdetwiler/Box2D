#ifndef TestApplication_H
#define TestApplication_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>

#include "Test.h"

class TestApplication {
 public:
    TestApplication();
    ~TestApplication();
    void run();
    sf::RenderWindow& getWindow();

 private:
    void processInput();
    void update(sf::Time dt);
    void render();

    static const sf::Time TimePerFrame;
    sf::RenderWindow mWindow;
    std::unique_ptr<Test> mTest;
    Settings mSettings;
    sf::View mView;
    sf::Vector2f mViewPos;
    int mTestEntryIndex;
    sf::Text mDirections;
    sf::Text mTitle;
    sf::Font mFont;
    
};

#endif // TestApplication_H
