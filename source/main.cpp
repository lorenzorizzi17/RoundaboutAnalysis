#include <string>

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <fstream>
#include<algorithm>

#include "road.hpp"
#include "functions.hpp"

// per l'offset, ho che tan(alfa) = (0.5*widthRoad)/((radius+widthRoundabout-0.1*radius))
int main() {
  try {
    //graphic constants
    unsigned const display_height = 0.95 * sf::VideoMode::getDesktopMode().height; //=768
    int const fps = 60;
    //geometric constants
    const double radius = 0.2 * display_height;
    const double lenghtCar = 4*0.0991*radius;
    const double widthCar = 4*0.0416*radius;
    const double lenghtRoad = 1.2*radius;
    const double widthRoad = 0.8*radius ;
    const double widthRoundabout = 0.25*radius;
    const double x = 0.25;
    const double offset = std::atan(((0.3*widthRoad))/((radius+widthRoundabout-x*radius)));
    
    //simulation parameters
    int const N_ROADS = 4;
    const double rates[N_ROADS] = {14,14,14,14};  //calcola flusso di ingresso
    const double amplificationTransfer = 1.2;
    const double v_road = 3;
    const double v_rbout = 2.85;
    const double dist_from_rbout = (radius -lenghtCar)/radius;
    const double min_dist_road = 1.2*(lenghtCar/lenghtRoad);
    const double n_max_car = 200;
    const double minimum_angle_behind = 50;
    const double minimum_angle_ahead = 25;
//sumo

    rbout roundabout(N_ROADS, radius);
    std::vector<road> roads;

    std::ofstream roadsfile[N_ROADS];
    std::ofstream myfile2;
    for(int i{0};i < N_ROADS;i++){
      std::string name = "/home/lorenzo17/Roundabout2/data/road" + std::to_string(i) + ".dat";
      roadsfile[i].open(name);
    }


    for (int k = 0; k < roundabout.n_roads(); k++) {
      road strada_test(2 * k * M_PI / roundabout.n_roads(), rates[k]);
      roads.push_back(strada_test);
    }

      if (roads.size() != N_ROADS) {
        throw std::runtime_error{"Modificare il numero di strade."};
      }
      sf::RenderWindow window(sf::VideoMode(display_height, display_height),
                              "Roundabout", sf::Style::Default);
      window.setFramerateLimit(fps);
      sf::Font font;
      if (!font.loadFromFile("graphics/font.ttf")) {
        throw std::runtime_error{
            "Attenzione! Il font non è stato caricato correttamente.Controlla "
            "che il file esista e sia nella giusta directory (./graphics)"};
      }
      sf::Text text;
      text.setFont(font);
      text.setCharacterSize(20);
      text.setFillColor(sf::Color::Black);
      text.setPosition(0.025 * display_height, 0.01 * display_height);

      sf::Texture texture;
      if (!texture.loadFromFile("graphics/rbout.jpg", sf::IntRect(0, 0, display_height,
                                                           display_height))) {
        throw std::runtime_error{
            "Attenzione! L'immagine non è stata caricata correttamente. "
            "Controlla che il file esista e sia nella giusta working "
            "directory"};
      }
      texture.setSmooth(true);

      sf::Texture texture2;
      if (!texture2.loadFromFile("graphics/texture2.jpg", sf::IntRect(0, 0, 0, 0))) {
        throw std::runtime_error{
            "Attenzione! L'immagine non è stata caricata correttamente. "
            "Controlla che il file esista e sia nella giusta working "
            "directory"};
      }
      texture2.setSmooth(true);

      sf::Texture texturecar;
      if (!texturecar.loadFromFile("graphics/texture.jpg", sf::IntRect(0, 0, display_height,
                                                           display_height))) {
        throw std::runtime_error{
            "Attenzione! L'immagine non è stata caricata correttamente. "
            "Controlla che il file esista e sia nella giusta working "
            "directory"};
      }
      texturecar.setSmooth(true);


      sf::CircleShape cerchio1(radius+widthRoundabout);
      sf::CircleShape cerchio2(radius-widthRoundabout);
      cerchio1.setTexture(&texture);
      cerchio1.setPosition(0.5 * display_height - radius-widthRoundabout,
                           0.5 * display_height - radius-widthRoundabout);
      cerchio2.setPosition(0.5 * display_height - radius+widthRoundabout,
                           0.5 * display_height - radius+widthRoundabout);



      int b = 0;
      while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
          if (event.type == sf::Event::Closed) {
            window.close();
          }
        }
        window.clear(sf::Color::White);
        window.draw(cerchio1);
        window.draw(cerchio2);
        for (int i = 0; i < roundabout.n_roads(); i++) {
          sf::RectangleShape strada(sf::Vector2f(lenghtRoad, widthRoad));
          strada.setOrigin(0.5 * lenghtRoad, 0.5 * widthRoad);
          strada.setTexture(&texture2);
          strada.setPosition(
              0.5 * display_height +
                  (std::cos(roads[i].angle())) * ((radius+widthRoundabout-x*radius) + 0.5 * lenghtRoad),
              0.5 * display_height -
                  (std::sin(roads[i].angle())) * ((radius+widthRoundabout-x*radius) + 0.5 * lenghtRoad));
          strada.rotate(-roads[i].angle() * (180 / M_PI));  // in gradi
          window.draw(strada);
        }
        int number_current_road = 1;
        for (auto it = roads.begin(); it != roads.end(); ++it) {
          //std::sort(roundabout.carrbout().begin(),roundabout.carrbout().end(), compareCarDistance);
          it->newcar_rd(true, it->rate(), n_max_car, offset);
          it->evolve_rd(true, roundabout, minimum_angle_ahead, minimum_angle_behind, v_road, dist_from_rbout, min_dist_road, offset, amplificationTransfer);
          if (it->transfer_rd()) {
            roundabout.newcar_rbt(it->angle(), offset, number_current_road);
          }
          it->erase_rd();
          it->evolve_rd(false, roundabout, 0,0, v_road, dist_from_rbout, min_dist_road, offset, amplificationTransfer);
          roadsfile[number_current_road-1] << (it->carin()).size() << std::endl;
          for (car& c : it->carin()) {
            sf::RectangleShape pallino(sf::Vector2f(widthCar,lenghtCar));
            pallino.setTexture(&texturecar);
            pallino.setOrigin(0.0416*radius,0.0991*radius);
            pallino.rotate(180/M_PI *(M_PI/2-(it->angle())));
            pallino.setPosition(0.5 * display_height +
                                    radius * std::cos(it->angle() + offset) -
                                    lenghtRoad * std::cos(M_PI - it->angle()) +
                                    c.t() * lenghtRoad * std::cos(M_PI - it->angle()),
                                0.5 * display_height -
                                    radius * std::sin(it->angle() + offset) -
                                    lenghtRoad * std::sin(M_PI - it->angle()) +
                                    c.t() * lenghtRoad * std::sin(M_PI - it->angle()));
            window.draw(pallino);
          }
          for (car& c_ : it->carout()) {
            sf::RectangleShape pallino_(sf::Vector2f(widthCar,lenghtCar));
            pallino_.setTexture(&texturecar);
            pallino_.setOrigin(0.0416*radius,0.0991*radius);
            pallino_.rotate(180/M_PI *(M_PI/2-(it->angle())));
            pallino_.setPosition(
                0.5 * display_height + radius * std::cos(it->angle() - offset) - lenghtRoad * std::cos(M_PI - it->angle()) + c_.t() * lenghtRoad * std::cos(M_PI - it->angle()),
                0.5 * display_height - radius * std::sin(it->angle() - offset) - lenghtRoad * std::sin(M_PI - it->angle()) + c_.t() * lenghtRoad * std::sin(M_PI - it->angle()));
            window.draw(pallino_);
          }
          for (car& d : roundabout.carrbout()) {
            sf::RectangleShape pallino__(sf::Vector2f(widthCar,lenghtCar));
            pallino__.setTexture(&texturecar);
            double x = 0.5 * display_height + radius * std::cos(d.theta());
            double y = 0.5 * display_height - radius * std::sin(d.theta());
            pallino__.setOrigin(0.0416*radius,0.0991*radius);
            pallino__.rotate(180-d.theta()* 180/M_PI);
            pallino__.setPosition(x,y);
            window.draw(pallino__);
          }
          number_current_road++;
        }
        if (roundabout.transfer_rbt(roads, offset) > 0) {
            auto a = roundabout.transfer_rbt(roads, offset);
            (roads[a - 1]).newcar_rd(false, 0, n_max_car, offset);
          }
          roundabout.erase_rbt(roads, offset);
        roundabout.evolve_rbt(roads, v_rbout);
        std::string string = "Numero di macchine in rotonda: " +
                             std::to_string(roundabout.size_rbout());
        
        text.setString(string);
        
        double mean{0};
        for (auto it = roads.begin(); it != roads.end(); it++)
        {
          std::cerr << "Macchine nella strada a " << (it->angle())*180/M_PI << " gradi: " << (it->carin()).size() << '\n';
          mean += (it->carin()).size();
        }
        std::cerr <<'\n';
        window.draw(text);
        window.display();
        b++;
      }
      for(int i=0;i < N_ROADS; i++){
        roadsfile[i].close();
      }
    }
    catch (std::runtime_error const& e) {
      std::cerr << e.what() << '\n';
    }
  }
