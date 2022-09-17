/**************************
 * Programmer: Ben Paepke *
 * Class: CISP 400        *
 * Assignment: Chaos Game *
 * Due Date: 09/18/2022   *
 **************************/

#include <SFML/Graphics.hpp>
#include <iostream>
#include "chaosGame.h"
using namespace std;
using namespace sf;

/***********************************
 * Rectangle shape used for points *
 ***********************************/
RectangleShape Point(float x, float y)
{
  RectangleShape rect;

  rect.setSize(Vector2f(3, 3));
  rect.setPosition(x, y);

  return rect;
}
/*****************
 * Random vertex *
 *****************/
Vector2f RandVertPos(vector<RectangleShape> vertices)
{
  int randomIndex = 0 + rand() % 3;

  return vertices[randomIndex].getPosition();
}

int main()
{
  /***********************************
   * Running total number of points. *
   ***********************************/
  int count = 0;
  
  /**************************
   * Setup Video and Window *
   **************************/
  VideoMode vm(1920, 1080);
  RenderWindow window(VideoMode(1920, 1080), "Chaos Game");

  /*******************************************
   * Vectors, Variables, and RectangleShapes *
   *******************************************/
  vector<RectangleShape> vertices;
  vector<RectangleShape> points;
  RectangleShape startPoint;
  RectangleShape midPoint;
  RectangleShape prevPoint;

  Vector2i mousePos;
  Event event;

  bool MouseButtonPressed = false;

  while (window.isOpen())
  {
    /****************************************************
     * Checks if the left mouse button has been pressed *
     ****************************************************/
    MouseButtonPressed = false;
    while (window.pollEvent(event))
    {
      if (event.type == Event::MouseButtonPressed)
      {
        if (event.mouseButton.button == Mouse::Left)
        {
          MouseButtonPressed = true;
        }
      }
    }
    /*******************************
     * Outside points for triangle *
     *******************************/
    if (vertices.size() < 3)
    {
      if (MouseButtonPressed)
      {
        mousePos = Mouse::getPosition(window);
        vertices.push_back(Point(mousePos.x, mousePos.y));
      }
    }
    else
    {
      /*******************************
       * Start Sierpinski's Triangle *
       *******************************/
      if (startPoint.getPosition() == Vector2f(0, 0))
      {
        if (MouseButtonPressed)
        {
          mousePos = Mouse::getPosition(window);
          startPoint = Point(mousePos.x, mousePos.y);
          prevPoint = startPoint;
        }
      }
      else
      {
        Vector2f randVertex = RandVertPos(vertices);

        Vector2f midPointPos = Vector2f((randVertex.x + prevPoint.getPosition().x) / 2.0, (randVertex.y + prevPoint.getPosition().y) / 2.0);
        midPoint = Point(midPointPos.x, midPointPos.y);
        prevPoint = midPoint;
        points.push_back(prevPoint);
      }
    }

    /**************************************************
     * Closes the game window when Escape is pressed. *
     **************************************************/
    if (Keyboard::isKeyPressed(Keyboard::Escape))
    {
      window.close();
    }

    /************************************
     * Instructions displayed in window *
     ************************************/
    Text messageText;
    Font font;

    font.loadFromFile("fonts/KOMIKAP_.ttf");
    messageText.setFont(font);

    messageText.setString("Click 3 different points to create a triangle.\n"
                          "Click a 4th time to start.\n"
                          "Press Escape to exit.");
    messageText.setCharacterSize(20);
    messageText.setFillColor(Color::Magenta);
    messageText.setPosition(30, 30);

    /****************************
     * Color the various points *
     ****************************/
    for (unsigned int i = 0; i < vertices.size(); i++)
    {
      vertices.at(i).setFillColor(Color::Cyan);
    }
    for (unsigned int i = 0; i < points.size(); i++)
    {
      points.at(i).setFillColor(Color::Yellow);
    }
    
    /*****************
     *Draw the scene *
     *****************/
    window.clear();
    window.draw(messageText);

    for (RectangleShape vertex : vertices)
    {
      window.draw(vertex);
    }

    for (int i = 0; i < (int)points.size(); i++)
    {
      window.draw(points[i]);
      count++;
    }
    
    /***********************************
     * Display everything we just drew *
     ***********************************/ 
    window.display();
  }
  return 0;
}