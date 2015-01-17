
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>

#include "TestApplication.h"
#include "BulletTest.h"

const sf::Time TestApplication::TimePerFrame = sf::seconds(1.f/60.f);

TestApplication::TestApplication()
    : mWindow(sf::VideoMode(1920, 1280), "Box2D Testbed") {
    mWindow.setFramerateLimit(60);
    mView = mWindow.getDefaultView();
    
    mFont.loadFromFile("./assets/font/arial.ttf");
    std::stringstream  sstr;
    sstr << "Keys: \n"
         << "Return, quote: switch demo\n"
         << "Arrow Keys: move camera\n"
         << "a,s,d,w,q,l,m: optionally implemented\n";
    mDirections.setFont(mFont);
    mDirections.setCharacterSize(40);
    mDirections.setColor(sf::Color::Black);
    mDirections.setString(sstr.str());
    
    
    mTitle.setFont(mFont);
    mTitle.setCharacterSize(40);
    mTitle.setColor(sf::Color::Black);
    mTitle.setStyle(sf::Text::Bold);
    mTitle.setString(g_testEntries[mTestEntryIndex].name);
        
    
    mTestEntryIndex = 0;
    
    mTest.reset(g_testEntries[mTestEntryIndex].createFcn(mWindow));

}

TestApplication::~TestApplication() { }

void TestApplication::processInput() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
    
        if (event.type == sf::Event::KeyPressed) {
        
            switch (event.key.code) {
                case sf::Keyboard::Left:
                    mViewPos.x -= 30.0f;
                    break;
                case sf::Keyboard::Right:
                    mViewPos.x += 30.0f;
                    break;
                case sf::Keyboard::Up:
                    mViewPos.y -= 30.0f;
                    break;
                case sf::Keyboard::Down:
                    mViewPos.y += 30.0f;
                    break;
                case sf::Keyboard::Quote:
                    mTestEntryIndex  = (mTestEntryIndex - 1 < 0) ? g_testEntries.size() - 1 : mTestEntryIndex - 1;
                    mTest.reset(g_testEntries[mTestEntryIndex].createFcn(mWindow));
                    mTitle.setString(g_testEntries[mTestEntryIndex].name);
                    break;
                case sf::Keyboard::Return:
                    mTestEntryIndex  = (mTestEntryIndex + 1) % g_testEntries.size();
                    mTest.reset(g_testEntries[mTestEntryIndex].createFcn(mWindow));
                    mTitle.setString(g_testEntries[mTestEntryIndex].name);
                    break;
                default:
                    mTest->Keyboard(event.key.code);
                    break;
            }
            

        } else if (event.type == sf::Event::KeyReleased) {
            mTest->KeyboardUp(event.key.code);
        } else if (event.type == sf::Event::Closed) {
            mWindow.close();
        }
        
    }
}

//  not currently needed
void TestApplication::update(sf::Time dt) {}

void TestApplication::render() {
    mWindow.clear(sf::Color::White);
    mView.setCenter(mViewPos.x, mViewPos.y);

    mWindow.setView(mView);
    mTest->Step(&mSettings);

    sf::Vector2f top_left, top_right;
    top_left.x = mView.getCenter().x - (mView.getSize().x / 2.);
    top_left.y = mView.getCenter().y - (mView.getSize().y / 2.);

    top_right.y = top_left.y;
    top_right.x = top_left.x + mView.getSize().x - 400;
    mDirections.setPosition(top_left);
    mTitle.setPosition(top_right);

    mWindow.draw(mDirections);
    mWindow.draw(mTitle);
    
    mWindow.display();
}

void TestApplication::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen()) {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;
        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            processInput();
            update(TimePerFrame);
        }
        render();
    }
}

sf::RenderWindow& TestApplication::getWindow() {
    return mWindow;
}


