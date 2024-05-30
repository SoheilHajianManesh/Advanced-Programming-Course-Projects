#include "game.hpp"
#include "rsdl.hpp"
using namespace std;

Game::Game(Window *window, vector<Enemy> _normal_enemies, vector<Hostage_ship> _hostage_ships,
           vector<Super_enemy> _super_enemies)
    : ship(rand() % window->get_width(), window->get_height() - SHIP_HEIGHT, SHIP_WIDTH, SHIP_HEIGHT)
{
    win = window;
    normal_enemies = _normal_enemies;
    super_enemies = _super_enemies;
    hostage_ships = _hostage_ships;
    t_start = 0;
}

void Game::handle_events()
{
    while (win->has_pending_event())
    {
        Event event = win->poll_for_event();
        switch (event.get_type())
        {
        case Event::QUIT:
            exit(0);
            break;
        case Event::KEY_PRESS:
            ship.handle_key_press(event.get_pressed_key(), win);
            break;
        }
    }
}
void Game::update_enemies_bullets()
{
    for (int i = 0; i < normal_enemies.size(); i++)
        normal_enemies[i].update_enemy_bullet();
    for (int i = 0; i < super_enemies.size(); i++)
        super_enemies[i].update_enemy_bullet();
}
void Game::shoot_new_bullet()
{
    if (t_start == 0)
    {
        for (int i = 0; i < normal_enemies.size(); i++)
            normal_enemies[i].shoot_bullets();
        for (int i = 0; i < super_enemies.size(); i++)
            super_enemies[i].shoot_bullets();
        t_start++;
    }
    auto t_end = std::chrono::high_resolution_clock::now();
    if (std::chrono::duration<double, std::milli>(t_end - t_last_shot).count() >= DURATION_BETWEEN_TWO_SHOT && normal_enemies.size() != 0)
    {
        for (int i = 0; i < normal_enemies.size(); i++)
            normal_enemies[i].shoot_bullets();
        for (int i = 0; i < super_enemies.size(); i++)
            super_enemies[i].shoot_bullets();
        t_last_shot = t_end;
    }
}
void Game::update_super_enemies()
{
    for (int i = 0; i < super_enemies.size(); i++)
        super_enemies[i].movement(win);
}
void Game::check_enemy_killed()
{
    for (int j = 0; j < normal_enemies.size(); j++)
        for (int i = 0; i < ship.get_bullets_size(); i++)
            if (ship.get_bullet(i).get_x_loc() > normal_enemies[j].get_x_loc() - ship.get_bullet(i).get_width() &&
                ship.get_bullet(i).get_x_loc() < normal_enemies[j].get_x_loc() + normal_enemies[j].get_width() &&
                ship.get_bullet(i).get_y_loc() < normal_enemies[j].get_y_loc() + normal_enemies[j].get_height())
            {
                normal_enemies.erase(normal_enemies.begin() + j);
                ship.erase_bullet(i);
                break;
            }
    for (int j = 0; j < super_enemies.size(); j++)
        for (int i = 0; i < ship.get_bullets_size(); i++)
            if (ship.get_bullet(i).get_x_loc() > super_enemies[j].get_x_loc() - ship.get_bullet(i).get_width() &&
                ship.get_bullet(i).get_x_loc() < super_enemies[j].get_x_loc() + super_enemies[j].get_width() &&
                ship.get_bullet(i).get_y_loc() < super_enemies[j].get_y_loc() + super_enemies[j].get_height())
            {
                super_enemies.erase(super_enemies.begin() + j);
                ship.erase_bullet(i);
                break;
            }
}
bool Game::crash_from_left(int index_super, int index_normal)
{
    if (super_enemies[index_super].get_x_loc() <= normal_enemies[index_normal].get_x_loc() + normal_enemies[index_normal].get_width() &&
        super_enemies[index_super].get_x_loc() + 10 >= normal_enemies[index_normal].get_x_loc() + normal_enemies[index_normal].get_width() &&
        super_enemies[index_super].get_y_loc() == normal_enemies[index_normal].get_y_loc())
        return true;
    return false;
}
bool Game::crash_from_right(int index_super, int index_normal)
{
    if (super_enemies[index_super].get_x_loc() >= normal_enemies[index_normal].get_x_loc() &&
        super_enemies[index_super].get_x_loc() - 10 <= normal_enemies[index_normal].get_x_loc() &&
        super_enemies[index_super].get_y_loc() == normal_enemies[index_normal].get_y_loc())
        return true;
    return false;
}
void Game::check_enemies_crash()
{
    for (int i = 0; i < super_enemies.size(); i++)
        for (int j = 0; j < normal_enemies.size(); j++)
        {
            if (crash_from_left(i, j))
                super_enemies[i].turn_to_right();
            else if (crash_from_right(i, j))
                super_enemies[i].turn_t_left();
        }
}
bool Game::is_round_over()
{
    if (normal_enemies.size() == 0 && super_enemies.size() == 0)
        return true;
    return false;
}
bool Game::check_ship_crash_normal()
{
    for (int i = 0; i < normal_enemies.size(); i++)
        if (ship.get_x_loc() > normal_enemies[i].get_x_loc() - ship.get_width() &&
            ship.get_x_loc() < normal_enemies[i].get_x_loc() + normal_enemies[i].get_width() &&
            ship.get_y_loc() > normal_enemies[i].get_y_loc() - ship.get_height() &&
            ship.get_y_loc() < normal_enemies[i].get_y_loc() + normal_enemies[i].get_height())
            return true;
    return false;
}
bool Game::check_ship_crash_super()
{
    for (int i = 0; i < super_enemies.size(); i++)
        if (ship.get_x_loc() > super_enemies[i].get_x_loc() - ship.get_width() &&
            ship.get_x_loc() < super_enemies[i].get_x_loc() + super_enemies[i].get_width() &&
            ship.get_y_loc() > super_enemies[i].get_y_loc() - ship.get_height() &&
            ship.get_y_loc() < super_enemies[i].get_y_loc() + super_enemies[i].get_height())
            return true;
    return false;
}
bool Game::check_crash_to_nor_bullet()
{
    for (int i = 0; i < normal_enemies.size(); i++)
        for (int j = 0; j < normal_enemies[i].get_bullets_size(); j++)
            if (normal_enemies[i].get_bullet(j).get_x_loc() > ship.get_x_loc() &&
                normal_enemies[i].get_bullet(j).get_x_loc() + normal_enemies[i].get_bullet(j).get_width() < ship.get_x_loc() + ship.get_width() &&
                normal_enemies[i].get_bullet(j).get_y_loc() > ship.get_y_loc() &&
                normal_enemies[i].get_bullet(j).get_y_loc() < ship.get_y_loc() + ship.get_height())
                return true;
    return false;
}
bool Game::check_crash_to_sup_bullet()
{
    for (int i = 0; i < super_enemies.size(); i++)
        for (int j = 0; j < super_enemies[i].get_bullets_size(); j++)
            if (super_enemies[i].get_bullet(j).get_x_loc() > ship.get_x_loc() &&
                super_enemies[i].get_bullet(j).get_x_loc() + super_enemies[i].get_bullet(j).get_width() < ship.get_x_loc() + ship.get_width() &&
                super_enemies[i].get_bullet(j).get_y_loc() > ship.get_y_loc() &&
                super_enemies[i].get_bullet(j).get_y_loc() < ship.get_y_loc() + ship.get_height())
                return true;
    return false;
}
bool Game::check_shot_hostage_ship()
{
    for (int j = 0; j < hostage_ships.size(); j++)
        for (int i = 0; i < ship.get_bullets_size(); i++)
            if (ship.get_bullet(i).get_x_loc() > hostage_ships[j].get_x_loc() - ship.get_bullet(i).get_width() &&
                ship.get_bullet(i).get_x_loc() < hostage_ships[j].get_x_loc() + hostage_ships[j].get_width() &&
                ship.get_bullet(i).get_y_loc() < hostage_ships[j].get_y_loc() + hostage_ships[j].get_height())
                return true;
    return false;
}
bool Game::does_player_game_over()
{
    if (check_ship_crash_normal())
        return true;
    if (check_ship_crash_super())
        return true;
    if (check_crash_to_nor_bullet())
        return true;
    if (check_crash_to_sup_bullet())
        return true;
    if (check_shot_hostage_ship())
        return true;
    return false;
}
void Game::update_objects()
{
    ship.update_bullets();
    ship.need_to_erase_player_bullet();
    update_enemies_bullets();
    update_super_enemies();
    shoot_new_bullet();
    check_enemy_killed();
    if (is_round_over())
        game_running = false;
    if (does_player_game_over())
    {
        game_running = false;
        show_result(LOSE, win);
    };
    check_enemies_crash();
}
void Game::draw_enemies()
{
    for (int i = 0; i < normal_enemies.size(); i++)
        normal_enemies[i].draw(win);
    for (int i = 0; i < super_enemies.size(); i++)
        super_enemies[i].draw(win);
}
void Game::draw_hostage_ships()
{
    for (int i = 0; i < hostage_ships.size(); i++)
        hostage_ships[i].draw(win);
}
void Game::draw_enemies_bullets()
{
    for (int i = 0; i < normal_enemies.size(); i++)
        normal_enemies[i].draw_bullets(win);
    for (int i = 0; i < super_enemies.size(); i++)
        super_enemies[i].draw_bullets(win);
}
void Game::draw_player_bullets()
{
    for (int j = 0; j < ship.get_bullets_size(); j++)
        ship.get_bullet(j).draw(win);
}
void Game::draw_screen()
{
    win->clear();
    win->draw_img("map.jpg", Rectangle(0, 0, win->get_width(), win->get_height()));
    ship.draw(win);
    draw_enemies();
    draw_hostage_ships();
    draw_player_bullets();
    draw_enemies_bullets();
    win->update_screen();
}
void Game::run()
{
    game_running = true;
    while (game_running)
    {
        handle_events();
        update_objects();
        draw_screen();
        delay(100);
    }
}