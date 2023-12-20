#ifndef DRONE_HPP
# define DRONE_HPP

#include "main.hpp"

#include <iostream>

class Drone
{

    public:

        int id;
        ft::Vector<int> position;
        ft::Vector<int> direction;
        int max_move;

        int emergency;
        int battery;
        bool light;

        std::vector<int> scaned_creatures_id;
        std::map<int, std::string> blips;

        Drone(int id, int x, int y, int emergency, int battery)
        {
            this->id = id;

            // position
            this->position = ft::Vector<int>(2);
            this->position[0] = x;
            this->position[1] = y;

            // direction
            this->direction = ft::Vector<int>(2);
            direction_down();

            this->emergency = emergency;
            this->battery = battery;
            this->scaned_creatures_id = std::vector<int>();
            this->scaned_creatures_id.reserve(12);
            this->light = false;
            this->blips = std::map<int, std::string>();
        }

        void update_position(int x, int y)
        {
            this->position[0] = x;
            this->position[1] = y;
        }

        void update_emergency(int emergency)
        {
            this->emergency = emergency;
        }

        void update_battery(int battery)
        {
            this->battery = battery;
        }

        void update_light(bool light)
        {
            this->light = light;
        }

        void add_blip(const int &creature_id, const std::string &blip)
        {
            this->blips.insert(std::pair<int, std::string>(creature_id, blip));
        }

        void direction_down()
        {
            this->direction[0] = 0;
            this->direction[1] = 1;
        }

        void direction_left()
        {
            this->direction[0] = -1;
            this->direction[1] = 0;
        }

        void direction_right()
        {
            this->direction[0] = 1;
            this->direction[1] = 0;
        }

        void direction_up()
        {
            this->direction[0] = 0;
            this->direction[1] = -1;
        }

        void move()
        {
            this->position[0] += (600 * this->direction[0]);
            this->position[1] += (600 * this->direction[1]);
            std::cout << "MOVE " << this->position[0] << " " << this->position[1] << " " << (int)this->light << std::endl;
        }


};

#endif // DRONE_HPP
