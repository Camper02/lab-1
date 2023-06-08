#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <chrono>
#include <windows.h>
#include <sstream>


class AnimatedText
{
private:
    double duration = 0;
    std::string text;

public:
    AnimatedText(const double& d, std::string t)
    {
        duration = d;
        text = t;
    }
    ~AnimatedText()
    {
    }
    double time()
    {
        return duration / size(text);
    }

    double GetDuration()
    {
        return duration;
    }

    std::string update(float t)
    {
        std::string out_text;
        for (int i = 0; i <= t / time(); i++)
        {
            out_text += text[i];
        }
        return out_text;
    }
};

bool check(float tim, double dur)
{
    if (tim > dur)
    {
        Sleep(500);
        exit(0);
    }
}

int main()
{
    sf::Font font;
    font.loadFromFile("Arialmt.ttf");
    sf::Text Font("", font, 40);
    Font.setStyle(sf::Text::Bold);

    double dur;
    std::cin >> dur;
    std::string txt;
    std::cin >> txt;
    AnimatedText Main_text(dur, txt);

    sf::RenderWindow window(sf::VideoMode(640, 480), "lab_1");
    sf::Clock clock_main;
    sf::Clock clock_restart;
    
    while (window.isOpen())
    {

        float timer = clock_main.getElapsedTime().asMicroseconds();
        float timer_restart = clock_restart.getElapsedTime().asMicroseconds();
        timer = timer / 800 / 1000 ;
        timer_restart = timer_restart / 800 / 1000;

        std::ostringstream AnimationOfText;
        AnimationOfText << Main_text.update(timer);
        Font.setString("Text: " + AnimationOfText.str());

        Font.setPosition(50, 150);
        window.draw(Font);
        check(timer, Main_text.GetDuration());

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(Font);
        window.display();
    }
    return 0;
}
