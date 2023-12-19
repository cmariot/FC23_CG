#ifndef MAIN_HPP
# define MAIN_HPP


# include <iostream>
# include <string>
# include <vector>
# include <map>
# include <algorithm>
# include <unordered_set>

# include "Creature.hpp"
# include "Drone.hpp"
# include "Player.hpp"

void parse_creatures(std::map<int, Creature> &creatures);
void update_unsaved_scans(Player &me, Player &foe);
void update_visible_creatures(std::map<int, Creature> &creatures);
void update_blips(Player &me, Player &foe);


#endif // MAIN_HPP