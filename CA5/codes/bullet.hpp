#ifndef BULLET_H
#define BULLET_H

#include "rsdl.hpp"
#include "consts.hpp"

class Bullet
{
public:
    Bullet(int _x_loc, int _y_loc, int _width, int _height);
    void draw(Window *win);
    void move_up();

    int get_y_loc() { return y_loc; }
    int get_x_loc() { return x_loc; }
    int get_width() { return width; }
    int get_height() { return height; }

protected:
    int x_loc;
    int y_loc;
    int width;
    int height;
};

class Enemy_bullet : public Bullet
{
public:
    Enemy_bullet(int _x_loc, int _y_loc, int _width, int _height);
    void draw(Window *win);
    void move_down();

private:
};

#endif
