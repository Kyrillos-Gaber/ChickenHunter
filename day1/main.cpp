#include <SFML/Graphics.hpp>
#include <time.h>
#include <SFML/Audio.hpp>
#include<bits/c++io.h>
#include<sstream>
#include<string>

#include<iostream>
using namespace sf;
using namespace std;
struct point
{ int x,y;};

int main()
{
    int c=0;
    srand(time(0));

    RenderWindow app(VideoMode(400, 533), "Doodle Game!");
    app.setFramerateLimit(60);

    stringstream stream;
    string str;
    str=to_string(c);
    Text text;
    Font font;
    font.loadFromFile("arial.ttf");

    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);

text.setStyle(sf::Text::Bold | sf::Text::Underlined);


    Text textgo;
    textgo.setFont(font);
    textgo.setString("GAME OVER !");
    textgo.setCharacterSize(30);
    textgo.setFillColor(sf::Color::Black);

    textgo.setStyle(sf::Text::Bold | sf::Text::Underlined);
    textgo.setOrigin(textgo.getGlobalBounds().width/2,textgo.getGlobalBounds().height/2);
    textgo.setPosition(Vector2f(app.getSize().x/2,app.getSize().y/2));
    Texture t1,t2,t3;
    SoundBuffer buffer;
    if(!buffer.loadFromFile("jump.wav"))
        return -1;
    Sound sound;
    sound.setBuffer(buffer);


    Music music;
    music.openFromFile("jump.wav");
    music.setLoop(true);
    Music musicback;
    musicback.openFromFile("background.wav");
    musicback.setLoop(true);
    musicback.play();

    t1.loadFromFile("images/background.png");
    t2.loadFromFile("images/platform.png");
    t3.loadFromFile("images/doodle.png");
    Sprite sBackground(t1), sPlat(t2), sPers(t3);
    float f=50;
    point plat[20];

    for (int i=0;i<10;i++)
      {
       plat[i].x=rand()%400;
       plat[i].y=rand()%533;
      }

    int x=app.getSize().x/2,y=app.getSize().y-100,h=200;
    float dx=0,dy=0;

    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
        }

    if (Keyboard::isKeyPressed(Keyboard::Right)) x+=3;
    if (Keyboard::isKeyPressed(Keyboard::Left)) x-=3;
    if (Keyboard::isKeyPressed(Keyboard::U)) if(f<100)musicback.setVolume(f+=1.f);
    if (Keyboard::isKeyPressed(Keyboard::D)) if(f>0)musicback.setVolume(f-=1.f);
    if (Keyboard::isKeyPressed(Keyboard::M)) {if(f!=0) f=0;
                                                else f=100;
                                                musicback.setVolume(f);}
    //dy+=0.2;
    y+=dy;
    if (y>500) { ;

        sound.play();
              c--;
        str=to_string(c);
        text.setString(str);
    }





    for (int i=0;i<10;i++)
    {

      plat[i].y=plat[i].y+2;
      if (plat[i].y>533) {plat[i].y=0; plat[i].x=rand()%400;}
    }

    for (int i=0;i<10;i++)
     if ((x+50>plat[i].x) && (x+20<plat[i].x+68)
      && (y+70>plat[i].y) && (y+70<plat[i].y+14) && (dy>0))  {
      c++;
    str=to_string(c);
        text.setString(str);
      sound.play();

      }

    sPers.setPosition(x,y);

    app.draw(sBackground);
    app.draw(sPers);
    app.draw(text);
    for (int i=0;i<10;i++)
    {
    sPlat.setPosition(plat[i].x,plat[i].y);
    app.draw(sPlat);
    }
    if(c<0){
        app.draw(sBackground);
        app.draw(textgo);
        musicback.pause();
        sound.pause();
            }

    app.display();

}

    return 0;
}
