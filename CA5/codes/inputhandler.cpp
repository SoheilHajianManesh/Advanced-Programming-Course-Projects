#include "inputhandler.hpp"

using namespace std;

vector<string> IOhandler::split(string line)
{
    vector<string> info;
    string parse;
    for (int i = 0, j = 0; i < line.size(); i++, j++)
    {
        if (line[i] == SEPARATOR)
        {
            j = 0;
            info.push_back(parse);
            parse.clear();
            continue;
        }
        if (i == line.size() - 1)
        {
            parse.push_back(line[i]);
            info.push_back(parse);
            parse.clear();
        }
        parse.push_back(line[i]);
    }
    return info;
}
void IOhandler::get_row_col(ifstream &myfile)
{
    getline(myfile, file_line);
    vector<string> info = split(file_line);
    row = stoi(info[0]);
    col = stoi(info[1]);
}
void IOhandler::get_number_of_rounds(ifstream &myfile)
{
    getline(myfile, file_line);
    num_of_round = stoi(file_line);
}
void IOhandler::push_normal_enemy(int x_loc, int y_loc)
{
    Enemy new_enemy(PER_SIDE_SIZE * x_loc + (PER_SIDE_SIZE-SHIP_WIDTH)/2, PER_SIDE_SIZE * y_loc + SHIP_HEIGHT, SHIP_WIDTH,SHIP_HEIGHT);
    normal_enemies.push_back(new_enemy);
}
void IOhandler::push_super_enemy(int x_loc, int y_loc)
{
    Super_enemy new_super_enemy(PER_SIDE_SIZE * x_loc + (PER_SIDE_SIZE-SHIP_WIDTH)/2, PER_SIDE_SIZE * y_loc + SHIP_HEIGHT, SHIP_WIDTH, SHIP_HEIGHT);
    super_enemies.push_back(new_super_enemy);
}
void IOhandler::push_hostage_ships(int x_loc, int y_loc)
{
    Hostage_ship new_hostage_ship(PER_SIDE_SIZE * x_loc + (PER_SIDE_SIZE-SHIP_WIDTH)/2, PER_SIDE_SIZE * y_loc + SHIP_HEIGHT, SHIP_WIDTH, SHIP_HEIGHT);
    hostage_ships.push_back(new_hostage_ship);
}
void IOhandler::clear_additional_bullets()
{
    for (int i = 0; i < normal_enemies.size(); i++)
        normal_enemies[i].clear_bullets();
    for (int i = 0; i < super_enemies.size(); i++)
        super_enemies[i].clear_bullets();
}
void IOhandler::creat_game_map(Window *window)
{
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
        {
            if (map[i][j] == NORMAL_ENEMY)
                push_normal_enemy(j, i);
            if (map[i][j] == SUPER_ENEMY)
                push_super_enemy(j, i);
            else if (map[i][j] == HOSTAGE_SHIP)
                push_hostage_ships(j, i);
        }
    clear_additional_bullets();
    rounds.push_back(Game(window, normal_enemies, hostage_ships, super_enemies));
}
void IOhandler::get_map(std::ifstream &myfile)
{
    map.resize(row, vector<char>(col));
    for (int i = 0; i < row; i++)
    {
        getline(myfile, file_line);
        for (int j = 0; j < file_line.size(); j++)
            map[i][j] = file_line[j];
    }
}
void IOhandler::creat_rounds_map(ifstream &myfile, Window *window)
{
    for (int k = 0; k < num_of_round; k++)
    {
        get_map(myfile);
        creat_game_map(window);
        getline(myfile, file_line);
        normal_enemies.clear();
    }
}
void IOhandler::run()
{
    ifstream myfile(FILE_NAME);
    get_row_col(myfile);
    Window win = Window(col * 200, row * 200, "STAR WARS");
    get_number_of_rounds(myfile);
    creat_rounds_map(myfile, &win);
    for (int i = 0; i < num_of_round; i++)
        rounds[i].run();
    show_result(WIN, &win);
}
