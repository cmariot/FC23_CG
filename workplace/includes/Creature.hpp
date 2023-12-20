#ifndef CREATURE_HPP
# define CREATURE_HPP

#include "vector.hpp"
class Creature
{

    public:

        int id;
        int color;
        int type;

        bool is_visible;

        // Position
        ft::Vector<int> position;

        // Velocity
        ft::Vector<int> velocity;

        Creature(int id, int color, int type)
        {
            this->id = id;
            this->color = color;
            this->type = type;
            this->is_visible = false;
        }

        void update_position(int x, int y)
        {
            this->position[0] = x;
            this->position[1] = y;
        }

        void update_velocity(int vx, int vy)
        {
            this->velocity[0] = vx;
            this->velocity[1] = vy;
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

#endif // CREATURE_HPP
