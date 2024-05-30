#include "bullet.hpp"

using namespace std;

Bullet::Bullet(int _x_loc, int _y_loc, int _width, int _height)
{
    x_loc = _x_loc;
    y_loc = _y_loc;
    width = _width;
    height = _height;
}

void Bullet::move_up()
{
    y_loc -= BULLETS_SPEED;
}

void Bullet::draw(Window *win)
{
    win->draw_img("friendly-bullet.png",Rectangle(x_loc,y_loc,width,height));
}

Enemy_bullet::Enemy_bullet(int _x_loc, int _y_loc, int _width,int _height)
    : Bullet(_x_loc, _y_loc, _width,_height)
{
}

void Enemy_bullet::draw(Window *win)
{
    win->draw_img("enemy-bullet.png",Rectangle(x_loc,y_loc,width,height));
}
void Enemy_bullet::move_down()
{
    y_loc += BULLETS_SPEED;
}