#ifndef ENEMY_H
#define ENEMY_H

#include "consts.hpp"
#include "ship.hpp"
#include "bullet.hpp"


class Enemy : public Ship
{
public:
    Enemy(int _x_loc, int _y_loc, int _width, int _height);
    void shoot_bullets();
    void update_enemy_bullet();
    void draw_bullets(Window *win);
    void clear_bullets();
    void draw(Window *win);

    int get_bullets_size() { return bullets.size(); }
    Enemy_bullet get_bullet(int index) { return bullets[index]; }

protected:
    std::vector<Enemy_bullet> bullets;
};

class Super_enemy : public Enemy
{
public:
    Super_enemy(int _x_loc, int _y_loc, int _width, int _height);
    void draw(Window *win);
    void movement(Window *win);

    int get_direct() { return direct; }
    void turn_to_right() { direct -= 1; }
    void turn_t_left() { direct += 1; }

private:
    int direct;
};

#endif
