#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <unordered_set>


using namespace std;

/**
 * Score points by scanning valuable fish faster than your opponent.
 **/

class Creature
{
    public:

        int id;
        int color;
        int type;

        bool is_visible;

        int x;  // x position
        int y;  // y position

        int vx; // x velocity
        int vy; // y velocity


        Creature(int id, int color, int type)
        {
            this->id = id;
            this->color = color;
            this->type = type;
            this->is_visible = false;
        }

        void update_position(int x, int y)
        {
            this->x = x;
            this->y = y;
        }

        void update_velocity(int vx, int vy)
        {
            this->vx = vx;
            this->vy = vy;
        }

        void update_visibility(bool is_visible)
        {
            this->is_visible = is_visible;
        }

        void reset_visibility(void)
        {
            this->is_visible = false;
        }

};


class Drone
{
    public:

        int id;
        int x;
        int y;
        int emergency;
        int battery;
        bool light;
        vector<int> scaned_creatures_id;

        // Store the blips of the drone
        std::map<int, std::string> blips;


        Drone(int id, int x, int y, int emergency, int battery)
        {
            this->id = id;
            this->x = x;
            this->y = y;
            this->emergency = emergency;
            this->battery = battery;
            this->scaned_creatures_id = vector<int>();
            this->scaned_creatures_id.reserve(12);
            this->light = false;
            this->blips = map<int, string>();
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

        void add_blip(const int & creature_id, const std::string & blip)
        {
            this->blips.insert(std::pair<int, std::string>(creature_id, blip));
        }

};

class Player
{
    public:

        int score;                              // current score
        std::map<int, Drone>    drones;         //
        std::unordered_set<int> saved_scans;    //


        int scan_count;         // amount of SAVED scans
        int drone_count;
        int creature_count;
        int radar_count;

        Player(void)
        {
            cin >> this->score;
            cin.ignore();
            this->drones = map<int, Drone>();
        }

        void update_drones()
        {
            int my_drone_count;
            cin >> my_drone_count;
            cin.ignore();
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
            cin >> drone_id >> drone_x >> drone_y >> emergency >> battery;
            cin.ignore();
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
            cin >> scan_count;
            cin.ignore();
            for (int i = 0; i < scan_count; i++)
            {
                int creature_id;
                cin >> creature_id;
                cin.ignore();
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

void parse_creatures(map <int, Creature> & creatures)
{

    // Number of creatures int the game zone, (will always be 12)
    int creature_count;
    cin >> creature_count;
    cin.ignore();

    for (int i = 0; i < creature_count; i++)
    {

        // Creature description
        int creature_id;    // (unique creature id)
        int color;          // (0 to 3)
        int type;           // (0 to 2)

        cin >> creature_id >> color >> type;
        cin.ignore();

        creatures.insert(pair<int, Creature>(creature_id, Creature(creature_id, color, type)));
    }
}


void update_unsaved_scans(Player & me, Player & foe)
{
    int drone_scan_count;
    cin >> drone_scan_count;
    cin.ignore();

    for (int i = 0; i < drone_scan_count; i++)
    {
        int drone_id;
        int creature_id;
        cin >> drone_id >> creature_id;
        cin.ignore();

        // If the drone_id is in the map of my drones
        if (me.drones.find(drone_id) != me.drones.end())
            me.update_unsaved_scans(drone_id, creature_id);
        else
            foe.update_unsaved_scans(drone_id, creature_id);

    }
}

void update_visible_creatures(map<int, Creature> & creatures)
{
    int visible_creature_count;
    cin >> visible_creature_count;
    cin.ignore();

    // Reset visibility of all creatures
    for (auto & creature : creatures)
        creature.second.reset_visibility();

    for (int i = 0; i < visible_creature_count; i++)
    {
        int creature_id;
        int creature_x;
        int creature_y;
        int creature_vx;
        int creature_vy;
        cin >> creature_id >> creature_x >> creature_y >> creature_vx >> creature_vy;
        cin.ignore();

        if (creatures.find(creature_id) != creatures.end())
        {
            // Creature is visible
            creatures.at(creature_id).update_position(creature_x, creature_y);
            creatures.at(creature_id).update_velocity(creature_vx, creature_vy);
            creatures.at(creature_id).update_visibility(true);
        }
    }
}


void update_blips(Player & me, Player & foe)
{
    int blip_count;
    cin >> blip_count;
    cin.ignore();

    // Restore blips ?

    for (int i = 0; i < blip_count; i++)
    {
        int drone_id;
        int creature_id;
        string blip;
        cin >> drone_id >> creature_id >> blip;
        cin.ignore();

        if (me.drones.find(drone_id) != me.drones.end())
            me.drones.at(drone_id).add_blip(creature_id, blip);
        else
            foe.drones.at(drone_id).add_blip(creature_id, blip);


    }
}
int main()
{
    map<int, Creature> creatures;

    parse_creatures(creatures);

    // game loop
    while (1)
    {

        Player me;
        Player foe;

        me.update_saved_scans();
        foe.update_saved_scans();

        me.update_drones();
        foe.update_drones();

        update_unsaved_scans(me, foe);

        update_visible_creatures(creatures);

        update_blips(me, foe);

        for (int i = 0; i < me.drones.size(); i++)
        {

            // Write an action using cout. DON'T FORGET THE "<< endl"
            // To debug: cerr << "Debug messages..." << endl;

            cout << "WAIT 1" << endl; // MOVE <x> <y> <light (1|0)> | WAIT <light (1|0)>
            cerr << "Debug messages..." << endl;
        }
    }
}