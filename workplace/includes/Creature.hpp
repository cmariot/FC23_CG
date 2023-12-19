#ifndef CREATURE_HPP
# define CREATURE_HPP

class Creature
{

    public:

        int id;
        int color;
        int type;

        bool is_visible;

        // Position
        int x;
        int y;

        // Velocity
        int vx;
        int vy;

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

#endif // CREATURE_HPP
