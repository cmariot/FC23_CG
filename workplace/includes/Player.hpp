#ifndef PLAYER_HPP
# define PLAYER_HPP

class Player
{

    public:

        int score;                              // current score
        std::map<int, Drone> drones;            // map of drones, key is drone_id
        std::unordered_set<int> saved_scans;    // set of saved scans, key is creature_id

        int scan_count;                         // amount of SAVED scans
        int drone_count;                        // amount of drones
        int creature_count;                     // amount of creatures
        int radar_count;                        // amount of radars

        Player(void)
        {
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


            if (this->drones.find(drone_id) == this->drones.end())
            {
                this->drones.insert(
                    std::pair<int, Drone>(
                        drone_id, Drone(drone_id, drone_x, drone_y, emergency, battery)
                    )
                );
            }
            else
            {
                // this->drones.at(drone_id).update_position(drone_x, drone_y);
                this->drones.at(drone_id).update_emergency(emergency);
                this->drones.at(drone_id).update_battery(battery);
            }
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
            this->drones.at(drone_id).update_position(x, y);
            this->drones.at(drone_id).light = light;

            if (light)
                this->drones.at(drone_id).battery -= 5;
            else
                this->drones.at(drone_id).battery += 1;
        }

        void update_score(const int & new_score)
        {
            this->score = new_score;
        }

};

#endif // PLAYER_HPP
