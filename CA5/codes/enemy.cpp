#include "enemy.hpp"
using namespace std;
Enemy::Enemy(int _x_loc, int _y_loc, int _width, int _height)
    : Ship(_x_loc, _y_loc, _width, _height)
{
}
void Enemy::draw_bullets(Window *win)
{
    for (int k = 0; k < bullets.size(); k++)
        bullets[k].draw(win);
}
void Enemy::shoot_bullets()
{
    Enemy_bullet new_bullet(x_loc + (width - BULLET_WIDTH) / 2, y_loc + height, BULLET_WIDTH, BULLET_HEIGHT);
    bullets.push_back(new_bullet);
}
void Enemy::update_enemy_bullet()
{
    for (int i = 0; i < bullets.size(); i++)
        bullets[i].move_down();
}
void Enemy::clear_bullets()
{
    bullets.clear();
}
void Enemy::draw(Window *win)
{
    win->draw_img("enemy.png", Rectangle(x_loc, y_loc, width, height));
}
Super_enemy::Super_enemy(int _x_loc, int _y_loc, int _width, int _height)
    : Enemy(_x_loc, _y_loc, _width, _height)
{
    direct = RIGHT;
}
void Super_enemy::draw(Window *win)
{
    win->draw_img("super-enemy.png", Rectangle(x_loc, y_loc, width, height));
}
void Super_enemy::movement(Window *win)
{
    if (direct == RIGHT)
    {
        x_loc += SHIPS_SPEED;
        if (x_loc > win->get_width() - width)
            direct = LEFT;
    }
    if (direct == LEFT)
    {
        x_loc -= SHIPS_SPEED;
        if (x_loc < 0)
            direct = RIGHT;
    }
}
