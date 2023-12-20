#include "main.hpp"

int main()
{

    Player me;
    Player foe;
    std::map<int, Creature> creatures;

    parse_creatures(creatures);

    // game loop
    while (1)
    {

        update_score(me, foe);

        me.update_saved_scans();
        foe.update_saved_scans();

        me.update_drones();
        foe.update_drones();

        update_unsaved_scans(me, foe);

        update_visible_creatures(creatures);

        update_blips(me, foe);

        // For each drone

        std::string direction = "DOWN";

        for (size_t i = 0; i < me.drones.size(); i++)
        {

            // Write an action using cout. DON'T FORGET THE "<< endl"
            // To debug: cerr << "Debug messages..." << endl;

            // if (purchased_by_enemy())
            //      runaway();
            // else if (ascending())
            //      go_up()
            // else
            //      go_down()

            // std::cout << "WAIT 1" << std::endl; // MOVE <x> <y> <light (1|0)> | WAIT <light (1|0)>



            if (me.drones.at(i).position[1] <= 500 && direction == "UP")
            {
                me.drones.at(i).direction_down();
                direction = "DOWN";
            }
            else if (me.drones.at(i).position[1] >= 9500 && direction == "DOWN")
            {
                me.drones.at(i).direction_up();
                direction = "UP";
            }



            me.drones.at(i).move();
            std::cerr << "Direction : " << direction << " this->dir = " << me.drones.at(i).direction <<  " this->position = " << me.drones.at(i).position << std::endl;
        }
    }
}
