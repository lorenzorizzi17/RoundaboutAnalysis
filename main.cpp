#include <string>

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "road.hpp"
#include "functions.hpp"

int main() {
  try {
    unsigned const display_height =
        0.9 * sf::VideoMode::getDesktopMode().height;
    const double radius = 0.25 * display_height;
    const double lcar = 2*0.0991*radius;
    const double lroad = 0.8*radius;
    const double v_road = 2;
    const double v_rbout = 1.85;
    const double dist_from_rbout = 0.75;
    const double min_dist_road = 1.25*lcar/lroad;
    const double n_max_car = 3;
    int const N_ROADS = 4;
    int const rate = 15;
    int const mean_exit = 3;
    double minimum_angle = 45.;
    int const fps = 60;

    if (minimum_angle >= 360. || minimum_angle < 0.) {
      throw std::runtime_error{
          "Modificare l'angolo minimo tra gli oggetti car in rotonda."};
    }
    if ((mean_exit > N_ROADS) || (mean_exit <= 0)) {
      throw std::runtime_error{"Modificare il parametro di uscita media."};
    }

    rbout roundabout(N_ROADS, radius);

    std::vector<road> roads;
    for (int k = 0; k < roundabout.n_roads(); k++) {
      road strada_test(2 * k * M_PI / roundabout.n_roads());
      roads.push_back(strada_test);
    }

      if (roads.size() != N_ROADS) {
        throw std::runtime_error{"Modificare il numero di strade."};
      }
      sf::RenderWindow window(sf::VideoMode(display_height, display_height),
                              "Roundabout", sf::Style::Default);
      window.setFramerateLimit(fps);
      sf::Font font;
      if (!font.loadFromFile("font.ttf")) {
        throw std::runtime_error{
            "Attenzione! Il font non è stato caricato correttamente.Controlla "
            "che il file esista e sia nella giusta working directory"};
      }
      sf::Text text;
      text.setFont(font);
      text.setCharacterSize(20);
      text.setFillColor(sf::Color::Black);
      text.setPosition(0.025 * display_height, 0.01 * display_height);

      sf::Texture texture;
      if (!texture.loadFromFile("rbout.jpg", sf::IntRect(0, 0, display_height,
                                                           display_height))) {
        throw std::runtime_error{
            "Attenzione! L'immagine non è stata caricata correttamente. "
            "Controlla che il file esista e sia nella giusta working "
            "directory"};
      }
      texture.setSmooth(true);

      sf::Texture texture2;
      if (!texture2.loadFromFile("texture2.jpg", sf::IntRect(0, 0, 0, 0))) {
        throw std::runtime_error{
            "Attenzione! L'immagine non è stata caricata correttamente. "
            "Controlla che il file esista e sia nella giusta working "
            "directory"};
      }
      texture2.setSmooth(true);

      sf::Texture texturecar;
      if (!texturecar.loadFromFile("texture.jpg", sf::IntRect(0, 0, display_height,
                                                           display_height))) {
        throw std::runtime_error{
            "Attenzione! L'immagine non è stata caricata correttamente. "
            "Controlla che il file esista e sia nella giusta working "
            "directory"};
      }
      texturecar.setSmooth(true);


      sf::CircleShape cerchio1(1.15 * radius);
      sf::CircleShape cerchio2(0.85 * radius);
      cerchio1.setTexture(&texture);
      cerchio1.setPosition(0.5 * display_height - 1.15 * radius,
                           0.5 * display_height - 1.15 * radius);
      cerchio2.setPosition(0.5 * display_height - 0.85 * radius,
                           0.5 * display_height - 0.85 * radius);
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
        double l = 0.8 * radius;
        for (int i = 0; i < roundabout.n_roads(); i++) {
          sf::RectangleShape strada(sf::Vector2f(l, 0.4 * radius));
          strada.setOrigin(0.5 * l, 0.5 * 0.4 * radius);
          strada.setTexture(&texture2);
          strada.setPosition(
              0.5 * display_height +
                  (std::cos(roads[i].angle())) * (radius + 0.5 * l),
              0.5 * display_height -
                  (std::sin(roads[i].angle())) * (radius + 0.5 * l));
          strada.rotate(-roads[i].angle() * (180 / M_PI));  // in gradi
          window.draw(strada);
        }

        for (auto it = roads.begin(); it != roads.end(); ++it) {
          std::sort(roundabout.carrbout().begin(),roundabout.carrbout().end(), myfunction);
          (*it).newcar_rd(true, rate, n_max_car);
          (*it).evolve_rd(true, roundabout, minimum_angle, v_road, v_rbout, dist_from_rbout, min_dist_road);
          if (it->transfer_rd()) {
            roundabout.newcar_rbt(it->angle(), mean_exit);
          }
          it->erase_rd();
          if (roundabout.transfer_rbt(roads) > 0) {
            auto a = roundabout.transfer_rbt(roads);
            (roads[a - 1]).newcar_rd(false, rate, n_max_car);
          }
          roundabout.erase_rbt(roads);
          it->evolve_rd(false, roundabout, minimum_angle, v_road, v_rbout, dist_from_rbout, min_dist_road);

          for (car& c : it->carin()) {
            sf::RectangleShape pallino(sf::Vector2f(2*0.0416*radius,2*0.0991*radius));
            pallino.setTexture(&texturecar);
            pallino.setOrigin(0.0416*radius,0.0991*radius);
            pallino.rotate(180/M_PI *(M_PI/2-(it->angle())));
            pallino.setPosition(0.5 * display_height +
                                    radius * std::cos(it->angle() + offset) -
                                    l * std::cos(M_PI - it->angle()) +
                                    c.t() * l * std::cos(M_PI - it->angle()),
                                0.5 * display_height -
                                    radius * std::sin(it->angle() + offset) -
                                    l * std::sin(M_PI - it->angle()) +
                                    c.t() * l * std::sin(M_PI - it->angle()));
            window.draw(pallino);
          }
          for (car& c_ : it->carout()) {
            sf::RectangleShape pallino_(sf::Vector2f(2*0.0416*radius,2*0.0991*radius));
            pallino_.setTexture(&texturecar);
            pallino_.setOrigin(0.0416*radius,0.0991*radius);
            pallino_.rotate(180/M_PI *(M_PI/2-(it->angle())));
            pallino_.setPosition(
                0.5 * display_height + radius * std::cos(it->angle() - offset) - l * std::cos(M_PI - it->angle()) + c_.t() * l * std::cos(M_PI - it->angle()),
                0.5 * display_height - radius * std::sin(it->angle() - offset) -l * std::sin(M_PI - it->angle()) + c_.t() * l * std::sin(M_PI - it->angle()));
            window.draw(pallino_);
          }
          for (car& d : roundabout.carrbout()) {
            sf::RectangleShape pallino__(sf::Vector2f(2*0.0416*radius,2*0.0991*radius));
            pallino__.setTexture(&texturecar);
            double x = 0.5 * display_height + radius * std::cos(d.theta());
            double y = 0.5 * display_height - radius * std::sin(d.theta());
            pallino__.setOrigin(0.0416*radius,0.0991*radius);
            pallino__.rotate(180-d.theta()* 180/M_PI);
            pallino__.setPosition(x,y);
            window.draw(pallino__);
          }
        }
        roundabout.evolve_rbt(roads, v_rbout);
        std::string string = "Numero di macchine in rotonda: " +
                             std::to_string(roundabout.size_rbout());
        text.setString(string);
        window.draw(text);
        window.display();
      }
    }
    catch (std::runtime_error const& e) {
      std::cerr << e.what() << '\n';
    }
  }
