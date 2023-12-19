#ifndef PLAYER_HPP
# define PLAYER_HPP

#include <map>
#include <iostream>
#include <unordered_set>

#include "Drone.hpp"


class Player
{
    public:
        int score;                           // current score
        std::map<int, Drone> drones;         //
        std::unordered_set<int> saved_scans; //

        int scan_count; // amount of SAVED scans
        int drone_count;
        int creature_count;
        int radar_count;

        Player(void)
        {
            std::cin >> this->score;
            std::cin.ignore();
            this->drones = std::map<int, Drone>();
        }

        void update_drones()
        {
            int my_drone_count;
            std::cin >> my_drone_count;
            std::cin.ignore();
            for (int i = 0; i < my_drone_count; i++)
                this->addDrone();
        }

        void addDrone(void)
        {
            int drone_id;
            int drone_x;
            int drone_y;
            int emergency;
            int battery;
            std::cin >> drone_id >> drone_x >> drone_y >> emergency >> battery;
            std::cin.ignore();
            this->drones.insert(std::pair<int, Drone>(drone_id, Drone(
                                                                    drone_id,
                                                                    drone_x,
                                                                    drone_y,
                                                                    emergency,
                                                                    battery)));
        }

        void update_saved_scans()
        {
            int scan_count;
            std::cin >> scan_count;
            std::cin.ignore();
            for (int i = 0; i < scan_count; i++)
            {
                int creature_id;
                std::cin >> creature_id;
                std::cin.ignore();
                this->saved_scans.insert(creature_id);
            }
        }

        void update_unsaved_scans(int drone_id, int creature_id)
        {
            this->drones.at(drone_id).scaned_creatures_id.push_back(creature_id);
        }

        void moveDrone(int drone_id, int x, int y, bool light)
        {
            this->drones.at(drone_id).x = x;
            this->drones.at(drone_id).y = y;
            this->drones.at(drone_id).light = light;

            if (light)
                this->drones.at(drone_id).battery -= 1;
            else
                this->drones.at(drone_id).battery -= 2;
        }
};

#endif // PLAYER_HPP