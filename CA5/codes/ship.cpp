#include "ship.hpp"
using namespace std;
Ship::Ship(int _x_loc, int _y_loc, int _width, int _height)
{
    x_loc = _x_loc;
    y_loc = _y_loc;
    width = _width;
    height = _height;
}
void Ship::draw(Window *win)
{
    win->draw_img("ship.png", Rectangle(x_loc, y_loc, width, height));
}
void Ship::move_up(Window *win)
{
    y_loc -= SHIPS_SPEED;
    if (y_loc < 0)
        y_loc = 0;
}
void Ship::move_down(Window *win)
{
    y_loc += SHIPS_SPEED;
    if (y_loc > win->get_height() - height)
        y_loc = win->get_height() - height;
}
void Ship::move_right(Window *win)
{
    x_loc += SHIPS_SPEED;
    if (x_loc > win->get_width() - width)
        x_loc = win->get_width() - width;
}
void Ship::move_left(Window *win)
{
    x_loc -= SHIPS_SPEED;
    if (x_loc < 0)
        x_loc = 0;
}
void Ship::shoot()
{
    Bullet new_bullet(x_loc + (width - BULLET_WIDTH) / 2, y_loc - 20, BULLET_WIDTH, BULLET_HEIGHT);
    bullets.push_back(new_bullet);
}
void Ship::update_bullets()
{
    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[i].move_up();
    }
}
void Ship::erase_bullet(int index)
{
    bullets.erase(bullets.begin() + index);
}
void Ship::need_to_erase_player_bullet()
{
    for (int i = 0; i < bullets.size(); i++)
    {
        if (bullets[i].get_y_loc() + bullets[i].get_height() < 0)
            bullets.erase(bullets.begin() + i);
    }
}
void Ship::handle_key_press(char key, Window *win)
{
    switch (key)
    {
    case 'd':
        move_right(win);
        break;
    case 'a':
        move_left(win);
        break;
    case 'w':
        move_up(win);
        break;
    case 's':
        move_down(win);
        break;
    case ' ':
        shoot();
        break;
    }
}
Hostage_ship::Hostage_ship(int _x_loc, int _y_loc, int _width, int _height)
    : Ship(_x_loc, _y_loc, _width, _height)
{
}
void Hostage_ship::draw(Window *win){
        win->draw_img("hostage-ship.png", Rectangle(x_loc, y_loc, width, height));
}