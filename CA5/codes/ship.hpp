#ifndef SHIP_H
#define SHIP_H

#include "bullet.hpp"
#include "consts.hpp"
#include <vector>
class Ship
{
public:
    Ship(int _x_loc, int _y_loc, int _width, int _height);
    void draw(Window *win);
    void handle_key_press(char key, Window *win);
    void update_bullets();
    void erase_bullet(int index);
    void need_to_erase_player_bullet();

    int get_bullets_size() { return bullets.size(); }
    Bullet get_bullet(int index) { return bullets[index]; }
    std::vector<Bullet> get_bullets() { return bullets; }
    int get_x_loc() { return x_loc; }
    int get_y_loc() { return y_loc; }
    int get_height() { return height; }
    int get_width() { return width; }

private:
    void move_up(Window *win);
    void move_down(Window *win);
    void move_right(Window *win);
    void move_left(Window *win);
    void shoot();

protected:
    std::vector<Bullet> bullets;
    int x_loc;
    int y_loc;
    int width;
    int height;
};

class Hostage_ship : public Ship
{
public:
    Hostage_ship(int _x_loc, int _y_loc, int _width, int _height);
    void draw(Window *win);

private:
};
#endif
