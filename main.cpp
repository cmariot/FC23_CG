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

        Creature(int id, int color, int type)
        {
            this->id = id;
            this->color = color;
            this->type = type;
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
        vector<int> scaned_creatures_id;

        Drone(int id, int x, int y, int emergency, int battery)
        {
            this->id = id;
            this->x = x;
            this->y = y;
            this->emergency = emergency;
            this->battery = battery;
            this->scaned_creatures_id = vector<int>();
        }
};

class Player
{
    public:

        int score;                      // current score
        std::map<int, Drone>    drones;         //
        std::unordered_set<int> saved_scans;    //


        int scan_count;                 // amount of SAVED scans
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

        int drone_scan_count;
        cin >> drone_scan_count;
        cin.ignore();
        for (int i = 0; i < drone_scan_count; i++)
        {
            int drone_id;
            int creature_id;
            cin >> drone_id >> creature_id;
            cin.ignore();

            // TODO : use it
            for (int j = 0; j < me.drones.size(); j++)
                if (me.drones.at(j).id == drone_id)
                    me.drones.at(j).scaned_creatures_id.push_back(creature_id);

            // idk if it can be foe scans
            for (int j = 0; j < foe.drones.size(); j++)
                if (foe.drones.at(j).id == drone_id)
                    foe.drones.at(j).scaned_creatures_id.push_back(creature_id);

        }

        int visible_creature_count;
        cin >> visible_creature_count;
        cin.ignore();
        for (int i = 0; i < visible_creature_count; i++)
        {
            int creature_id;
            int creature_x;
            int creature_y;
            int creature_vx;
            int creature_vy;
            cin >> creature_id >> creature_x >> creature_y >> creature_vx >> creature_vy;
            cin.ignore();
            // TODO : store visible creature
        }

        int radar_blip_count;
        cin >> radar_blip_count;
        cin.ignore();
        for (int i = 0; i < radar_blip_count; i++)
        {
            int drone_id;
            int creature_id;
            string radar;
            cin >> drone_id >> creature_id >> radar;
            cin.ignore();
            // TODO : store radar blip
        }

        for (int i = 0; i < my_drone_count; i++)
        {

            // Write an action using cout. DON'T FORGET THE "<< endl"
            // To debug: cerr << "Debug messages..." << endl;

            cout << "WAIT 1" << endl; // MOVE <x> <y> <light (1|0)> | WAIT <light (1|0)>
            cerr << "Debug messages..." << endl;
            // Print on cerr the id of the drones
            auto it = me.drones.begin();
            auto it2 = foe.drones.begin();
            while (it != me.drones.end())
            {
                cerr << "ID:  " << it->first << endl;
                cerr << "ID2: " << it2->first << endl;
                ++it;
                ++it2;
            }
        }
    }
}