#ifndef GAME_H
#define GAME_H

#include "enemy.hpp"
#include "ship.hpp"
#include "result.hpp"
#include "consts.hpp"
#include <stdlib.h>
#include <chrono>
#include <vector>
class Game
{
public:
    Game(Window *window, std::vector<Enemy> _normal_enemies, std::vector<Hostage_ship> _hostage_ships,
         std::vector<Super_enemy> _super_enemies);
    void run();

private:
    int t_start;
    std::chrono::high_resolution_clock::time_point t_last_shot = std::chrono::high_resolution_clock::now();
    bool game_running;
    void handle_events();
    void update_enemies_bullets();
    void shoot_new_bullet();
    void update_super_enemies();
    void check_enemy_killed();
    bool crash_from_right(int index_super, int index_normal);
    bool crash_from_left(int index_super, int index_normal);
    void check_enemies_crash();
    bool is_round_over();
    bool check_ship_crash_normal();
    bool check_ship_crash_super();
    bool check_crash_to_nor_bullet();
    bool check_crash_to_sup_bullet();
    bool check_shot_hostage_ship();
    bool does_player_game_over();
    void update_objects();
    void draw_enemies();
    void draw_hostage_ships();
    void draw_enemies_bullets();
    void draw_player_bullets();
    void draw_screen();
    Window *win;
    Ship ship;
    std::vector<Enemy> normal_enemies;
    std::vector<Super_enemy> super_enemies;
    std::vector<Hostage_ship> hostage_ships;
};

#endif
