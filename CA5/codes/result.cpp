#include "result.hpp"
void show_result(int lose_or_win, Window *win)
{
    if (lose_or_win == LOSE)
    {
        win->clear();
        win->draw_img("map.jpg", Rectangle(0, 0, win->get_width(), win->get_height()));
        win->show_text("YOU LOSE!", Point(170, 200), YELLOW, "font.otf", 100);
        win->update_screen();
    }
    else
    {
        win->clear();
        win->draw_img("map.jpg", Rectangle(0, 0, win->get_width(), win->get_height()));
        win->show_text("YOU WIN!", Point(170, 200), YELLOW, "font.otf", 100);
        win->update_screen();
    }
    while (1)
    {
        Event event = win->poll_for_event();
        if (event.get_type() == Event::QUIT)
            exit(0);
    }
}