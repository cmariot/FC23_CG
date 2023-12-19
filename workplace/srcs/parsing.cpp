#include "main.hpp"

void parse_creatures(std::map<int, Creature> &creatures)
{

    // Number of creatures int the game zone, (will always be 12)
    int creature_count;
    std::cin >> creature_count;
    std::cin.ignore();

    for (int i = 0; i < creature_count; i++)
    {

        // Creature description
        int creature_id; // (unique creature id)
        int color;       // (0 to 3)
        int type;        // (0 to 2)

        std::cin >> creature_id >> color >> type;
        std::cin.ignore();

        creatures.insert(std::pair<int, Creature>(creature_id, Creature(creature_id, color, type)));
    }
}

void update_unsaved_scans(Player &me, Player &foe)
{
    int drone_scan_count;
    std::cin >> drone_scan_count;
    std::cin.ignore();

    for (int i = 0; i < drone_scan_count; i++)
    {
        int drone_id;
        int creature_id;
        std::cin >> drone_id >> creature_id;
        std::cin.ignore();

        // If the drone_id is in the map of my drones
        if (me.drones.find(drone_id) != me.drones.end())
            me.update_unsaved_scans(drone_id, creature_id);
        else
            foe.update_unsaved_scans(drone_id, creature_id);
    }
}

void update_visible_creatures(std::map<int, Creature> &creatures)
{
    int visible_creature_count;
    std::cin >> visible_creature_count;
    std::cin.ignore();

    // Reset visibility of all creatures
    for (auto &creature : creatures)
        creature.second.reset_visibility();

    for (int i = 0; i < visible_creature_count; i++)
    {
        int creature_id;
        int creature_x;
        int creature_y;
        int creature_vx;
        int creature_vy;
        std::cin >> creature_id >> creature_x >> creature_y >> creature_vx >> creature_vy;
        std::cin.ignore();

        if (creatures.find(creature_id) != creatures.end())
        {
            // Creature is visible
            creatures.at(creature_id).update_position(creature_x, creature_y);
            creatures.at(creature_id).update_velocity(creature_vx, creature_vy);
            creatures.at(creature_id).update_visibility(true);
        }
    }
}

void update_blips(Player &me, Player &foe)
{
    int blip_count;
    std::cin >> blip_count;
    std::cin.ignore();

    // Restore blips ?

    for (int i = 0; i < blip_count; i++)
    {
        int drone_id;
        int creature_id;
        std::string blip;
        std::cin >> drone_id >> creature_id >> blip;
        std::cin.ignore();

        if (me.drones.find(drone_id) != me.drones.end())
            me.drones.at(drone_id).add_blip(creature_id, blip);
        else
            foe.drones.at(drone_id).add_blip(creature_id, blip);
    }
}
