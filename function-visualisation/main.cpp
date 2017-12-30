#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <windows.h>
#include <iostream>
#include <vector>
#include <cmath>

using namespace sf;

namespace ctrl{
    namespace Keyboard{
        int KEY_LALT = VK_LMENU;
        int KEY_LCTRL = VK_LCONTROL;
        int KEY_UP = VK_UP;
        int KEY_DOWN = VK_DOWN;
        int KEY_RIGHT = VK_RIGHT;
        int KEY_LEFT = VK_LEFT;
        int KEY_SPACE = VK_SPACE;
        int KeyPressed(int key = -1){
            if(key == -1){// we must return ASCII or VK of pressed key
                short lctrl_pressed = GetKeyState(VK_LCONTROL);
                short lalt_pressed = GetKeyState(VK_LMENU);
                if(lctrl_pressed < 0) return VK_LCONTROL;
                if(lalt_pressed < 0) return VK_LCONTROL;
            }else if(key == KEY_LALT){///L_ALT
                short lalt_pressed = GetKeyState(KEY_LALT);
                if(lalt_pressed < 0) return 1;
                else return 0;
            }else if(key == KEY_LCTRL){///L_CTRL
                short lctrl_pressed = GetKeyState(KEY_LCTRL);
                if(lctrl_pressed < 0) return 1;
                else return 0;
            }else if(key == KEY_UP){
                short up_pressed = GetAsyncKeyState(KEY_UP);
                if(up_pressed < 0) return 1;
                else return 0;
            }else if(key == KEY_DOWN){
                short down_pressed = GetAsyncKeyState(KEY_DOWN);
                if(down_pressed < 0) return 1;
                else return 0;
            }else if(key == KEY_RIGHT){
                short right_pressed = GetAsyncKeyState(KEY_RIGHT);
                if(right_pressed < 0) return 1;
                else return 0;
            }else if(key == KEY_LEFT){
                short left_pressed = GetAsyncKeyState(KEY_LEFT);
                if(left_pressed < 0) return 1;
                else return 0;
            }else if(key == KEY_SPACE){
                short space_pressed = GetAsyncKeyState(KEY_SPACE);
                if(space_pressed < 0) return 1;
                else return 0;
            }
        }
    }
}

int o_val(int o_cord, int o_glob_size, int delim){
    int o_val = (o_cord - (o_glob_size / 2)) / delim;
    return o_val;
}


float func(float x, float c ){
    return sin(x) + c;
}


int main()
{
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window(VideoMode(900, 650), "f(x) = ", sf::Style::Default, settings);

    Vector2f center(window.getSize().x /2, window.getSize().y/2);

    Vertex ox[] =
    {
        Vertex(Vector2f(0, center.y)),
        Vertex(Vector2f(window.getSize().x, center.y))
    };

    Vertex oy[] =
    {
        Vertex(Vector2f(center.x, 0)),
        Vertex(Vector2f(center.x, window.getSize().y))
    };

    int delimeter = 25;
    float func_increase = 0.0;
    float c = 0.0;

    Font font;
    font.loadFromFile("resources/arial.ttf");
    float xpos = 0;
    float val = func(xpos,c);

    while (window.isOpen())
    {


        window.clear();

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed){
                window.close();
            }else if(event.type == Event::MouseWheelMoved){
                func_increase = func_increase + 0.1 * event.mouseWheel.delta;

                std::cout << event.mouseWheel.delta << std::endl;
            }

            if (event.type == Event::MouseMoved)
            {
                xpos = (Mouse::getPosition(window).x - center.x) / delimeter;
                val = func(xpos,c);
            }
        }

        std::string formula = "f(x,c) = sin(x) + c = sin(" + std::to_string(xpos) + ") +" + std::to_string((double)c) + " = " + std::to_string((double)val);
        Text value(formula, font);
        value.setCharacterSize(10);
        value.setColor(Color::White);

        window.draw(value);


        Vertex my[] =
        {
            Vertex(Vector2f(Mouse::getPosition(window).x, 0)),
            Vertex(Vector2f(Mouse::getPosition(window).x, window.getSize().y))
        };
        window.draw(my,2,Lines);


        std::cout << formula << ")\n\n";

        ///Create Oy
        window.draw(oy, 2, Lines);
        for(int i = 0; i < window.getSize().y; i++){
            if(i % delimeter == 0){
                Vertex delim[] =
                {
                    Vertex(Vector2f(center.x - 2, (window.getSize().y - i))),
                    Vertex(Vector2f(center.x + 2, (window.getSize().y - i)))
                };
                window.draw(delim, 2, Lines);


                Font font;
                font.loadFromFile("resources/arial.ttf");
                std::string py = std::to_string( o_val(i,window.getSize().y, delimeter) );
                Text value(py, font);
                value.setCharacterSize(10);
                value.setColor(Color::White);

                value.setPosition(Vector2f(delim[1].position.x + 2, delim[1].position.y - (value.getCharacterSize() / 2) - 2 ));

                if(o_val(i,window.getSize().y, delimeter) != 0) window.draw(value);
            }
        }

        if(ctrl::Keyboard::KeyPressed(ctrl::Keyboard::KEY_UP)){
            c = c + 0.1;
        }
        if(ctrl::Keyboard::KeyPressed(ctrl::Keyboard::KEY_DOWN)){
            c = c - 0.1;
        }


        window.draw(ox, 2, Lines);
        for(int i = 0; i < window.getSize().x; i++){
            if(i % delimeter == 0){
                Vertex delim[] =
                {
                    Vertex(Vector2f(window.getSize().x - i, center.y - 2)),
                    Vertex(Vector2f(window.getSize().x - i, center.y + 2))
                };
                window.draw(delim, 2, Lines);


                Font font;
                font.loadFromFile("resources/arial.ttf");
                std::string py = std::to_string( o_val(i,window.getSize().x, delimeter) * -1 );
                Text value(py, font);
                value.setCharacterSize(10);
                value.setColor(Color::White);
                if( (o_val(i,window.getSize().x, delimeter) * -1) > 0 )
                    value.setPosition(Vector2f(delim[1].position.x, delim[1].position.y - value.getCharacterSize() *2));
                else if( (o_val(i,window.getSize().x, delimeter) * -1) < 0 )
                    value.setPosition(Vector2f(delim[1].position.x, delim[1].position.y + value.getCharacterSize() / 2));
                else if( (o_val(i,window.getSize().x, delimeter) * -1) == 0 )
                    value.setPosition(center);

                window.draw(value);
            }
        }

        float plusplus = 0.5;
        for(float i = -50.0; i < 50.0; i= i + plusplus){
            float val = func(i+func_increase,c);

            CircleShape y_val(2);
            y_val.setFillColor(Color::White);
            y_val.setPosition(Vector2f( center.x + i * delimeter , center.y - val * delimeter ));



            float newval = func(i+plusplus+func_increase,c);
            Vertex line[] =
            {
                Vertex(Vector2f(y_val.getPosition().x + y_val.getRadius(), y_val.getPosition().y + y_val.getRadius())),
                Vertex(Vector2f(center.x + (i+plusplus) * delimeter + y_val.getRadius() , center.y - newval * delimeter + y_val.getRadius()))
            };

            window.draw(line, 2, Lines);


            window.draw(y_val);
        }

        window.display();
        Sleep(0);


    }

    return 0;
}
