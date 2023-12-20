#ifndef MAIN_HPP
# define MAIN_HPP

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <unordered_set>

class Creature;
class Player;
namespace ft
{
    template <typename T>
    class Vector;
}

# include "vector.hpp"
# include "Creature.hpp"
# include "Drone.hpp"
# include "Player.hpp"

void update_score(Player &me, Player &foe);
void parse_creatures(std::map<int, Creature> &creatures);
void update_unsaved_scans(Player &me, Player &foe);
void update_visible_creatures(std::map<int, Creature> &creatures);
void update_blips(Player &me, Player &foe);


#endif // MAIN_HPP
