#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "game.hpp"
#include "enemy.hpp"
#include "ship.hpp"
#include "result.hpp"
#include "consts.hpp"
#include <vector>
#include <fstream>
#include <string>


class IOhandler
{
public:
    void run();

private:
    std::string file_line;
    int row;
    int col;
    int num_of_round;
    std::vector<std::string> split(std::string line);
    void get_row_col(std::ifstream &myfile);
    void get_number_of_rounds(std::ifstream &myfile);
    void get_map(std::ifstream &myfile);
    void clear_additional_bullets();
    void push_normal_enemy(int x_loc,int y_loc);
    void push_super_enemy(int x_loc,int y_loc);
    void push_hostage_ships(int x_loc,int y_loc);
    void creat_game_map(Window *window);
    void creat_rounds_map(std::ifstream &myfile, Window *window);
    std::vector<Enemy> normal_enemies;
    std::vector<Super_enemy> super_enemies;
    std::vector<Hostage_ship> hostage_ships;
    std::vector<std::vector<char>> map;
    std::vector<Game> rounds;
};

#endif
