#include "main.hpp"

int main()
{
    std::map<int, Creature> creatures;

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

        for (size_t i = 0; i < me.drones.size(); i++)
        {

            // Write an action using cout. DON'T FORGET THE "<< endl"
            // To debug: cerr << "Debug messages..." << endl;

            std::cout << "WAIT 1" << std::endl; // MOVE <x> <y> <light (1|0)> | WAIT <light (1|0)>
            std::cerr << "Debug messages..." << std::endl;
        }
    }
}