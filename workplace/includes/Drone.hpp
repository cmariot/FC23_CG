#ifndef DRONE_HPP
# define DRONE_HPP

class Drone
{

    public:

        int id;
        int x;
        int y;
        int emergency;
        int battery;
        bool light;
        std::vector<int> scaned_creatures_id;
        std::map<int, std::string> blips;

        Drone(int id, int x, int y, int emergency, int battery)
        {
            this->id = id;
            this->x = x;
            this->y = y;
            this->emergency = emergency;
            this->battery = battery;
            this->scaned_creatures_id = std::vector<int>();
            this->scaned_creatures_id.reserve(12);
            this->light = false;
            this->blips = std::map<int, std::string>();
        }

        void update_position(int x, int y)
        {
            this->x = x;
            this->y = y;
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
};

#endif // DRONE_HPP
