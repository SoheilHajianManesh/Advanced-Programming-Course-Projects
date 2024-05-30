#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <algorithm>
#define FIRST_MONEY 1000
#define FIRST_HEALTH 100
#define MAX_MONEY 10000
#define SEPARATOR ' '
#define TERRORIST 0
#define COUNTER_TERRORIST 1
#define MATCH_NOT_START 0
#define MATCH_STARTED 1
#define ATK_MODE 0
#define AFK_MODE 1
#define ALIVE 0
#define DEAD 1
#define ROUND_WINNER_BONUS 2700
#define ROUND_LOSER_BONUS 2400
using namespace std;


class Player;

typedef vector<Player> Player_list;


class Gun {
public:
	Gun(string gun_name, int gun_price, int gun_damage, int gun_reward);
	Gun();
	string get_name() { return name; }
	int get_price() { return price; }
	int get_damage() { return damage; }
	int get_reward() { return reward; }
private:
	string name;
	int price;
	int damage;
	int reward;
};


class Player {
public:
	Player();
	Player(string name, int user_money, int user_health, int user_side,Gun default_gun,int free_to_atk,int alive_,int kill_,int death_);
	void show_money_to_player(Player_list players,string name);
	void show_health_to_player(Player_list players,string name);
	void go_afk(Player_list &players,string name);
	void go_atk(Player_list &players,string name);
	void add_gun(Gun req_gun);
	void decrease_money(int decrease_amount);
	void increase_money(int increase_amount);
	void decrease_health(int decrease_amount);
	void increase_death();
	void increase_kill();
	void set_health_to_defualt();
	bool check_weapon_not_duplicate(Gun gun);
	bool check_player_have_a_gun(string gun_name);
	bool are_players_in_same_teams(Player attacked);
	bool is_money_enough(int wanted_money);


	string get_name() { return username; }
	int get_money() { return money; }
	int get_health() { return health; }
	int get_side() { return side; }
	int get_mode() { return can_atk; }
	vector<Gun> get_gun() { return guns; }
	int get_alive() { return alive; }
	int get_kill() { return kill; }
	int get_death() { return death; }


private:
	string username;
	int money;
	int health;
	vector<Gun> guns;
	int side;
	int can_atk;
	int alive;
	int kill;
	int death;
};
class Interface {
public:
	Interface(int number_of_round_) {
		number_of_round = number_of_round_;
	}
	int start();
	Player add_user(vector<string> info);
	Gun find_a_gun_from_list(string gun_name);
	int  find_a_player_from_list(string name);
	int number_of_alive_player(int side);
	bool check_player_available(string player_name);
	bool check_gun_available(string name);
	bool check_players_alive_for_shoot(int attacker_index, int attacked_index);
	bool is_game_start(int check_game_start, string shoot_or_buy);
	void order_base_on_kill();
	void order_base_on_death();
	void order_base_on_alphabet();
	Player_list order_list(int side);
	void buy(string gun_name, string player_name, int check_game_start);
	void shoot_player(int attacker_index, int attacked_index, Gun gun);
	void shoot(int check_game_start, string attacker_name, string attacked_name, string gun_name);
	void show_team_result(Player_list team, string team_name);
	void score_board();
	void show_result_of_a_round();
	void set_player_to_defualt(int winner_side, int loser_side);
	void get_command();
	void start_get_command();
private:
	Player_list players;
	int number_of_round;
	int number_of_command_in_a_round;
	vector<string> command;
};


Gun HEAVY("heavy", 3000, 45, 100);


Gun PISTOL("pistol", 400, 20, 200);


Gun KNIFE("knife", 0, 35, 500);


vector<string> split(string line) {
	vector<string> info;
	string parse;
	for (int i = 0, j = 0; i < line.size(); i++, j++) {
		if (line[i] == SEPARATOR) {
			j = 0;
			info.push_back(parse);
			parse.clear();
			continue;
		}
		if (i == line.size() - 1) {
			parse.push_back(line[i]);
			info.push_back(parse);
			parse.clear();
		}
		parse.push_back(line[i]);
	}
	return info;
}
void clear_cin_cache() {
	cin.clear();
	cin.ignore(256, '\n');
}
int get_number_of_round() {
	int rounds;
	cin >> rounds;
	clear_cin_cache();
	return rounds;
}
Gun::Gun(string gun_name, int gun_price, int gun_damage, int gun_reward) {
	name = gun_name;
	price = gun_price;
	damage = gun_damage;
	reward = gun_reward;
}
Gun::Gun() {
	Gun("empty", 0, 0, 0);
}
Player::Player(string name, int user_money, int user_health, int user_side,Gun default_gun,int free_to_atk,int alive_,int kill_,int death_) {
	username = name;
	money = user_money;
	health = user_health;
	side = user_side;
	guns.push_back(default_gun);
	can_atk = free_to_atk;
	alive = alive_;
	kill = kill_;
	death = death_;
}

Player::Player() {
	Player("empty", 0, 0, 0, KNIFE,ATK_MODE,ALIVE,0,0);
}
void Player::go_afk(Player_list &players,string name) {
	for (int i = 0;i < players.size();i++)
		if (players[i].get_name() == name)
			players[i].can_atk = AFK_MODE;
	cout << "ok\n";
}
void Player::go_atk(Player_list &players,string name) {
	for (int i = 0;i < players.size();i++)
		if (players[i].get_name() == name)
			players[i].can_atk = ATK_MODE;
	cout << "ok\n";
}
void Player::show_money_to_player(Player_list players,string name) {
	int i = 0;
	for (i;i < players.size();i++)
		if (players[i].get_name() == name)
			break;
	cout << players[i].get_money()<<endl;
} 
void Player::show_health_to_player(Player_list players, string name) {
	int i = 0;
	for (i;i < players.size();i++)
		if (players[i].get_name() == name)
			break;
	cout << players[i].get_health() << endl;
} 
void Player::add_gun(Gun req_gun) {
	guns.push_back(req_gun);
}
void Player::set_health_to_defualt() {
    health=FIRST_HEALTH;
	alive=ALIVE;
}
void Player::decrease_money(int decrease_amount) {
	money-= decrease_amount;
}
void Player::increase_money(int increase_amount) {
	money += increase_amount;
	if (money > MAX_MONEY)
		money = MAX_MONEY;
}
void Player::increase_death() {
	alive = DEAD;
	death += 1;
	guns.clear();
	guns.push_back(KNIFE);
}
void Player::increase_kill() {
	kill += 1;
}
void Player::decrease_health(int decrease_amount) {
	health -= decrease_amount;
	if (health < 0)
		health = 0;
}
bool Player::check_weapon_not_duplicate(Gun gun) {
	for (int i = 0;i < guns.size();i++)
		if (guns[i].get_name() == gun.get_name()) {
			cout << "you already have this weapon\n";
			return false;
		}
	return true;
}
bool Player::check_player_have_a_gun(string gun_name) {
	for (int i = 0;i < guns.size();i++)
		if (guns[i].get_name() == gun_name)
			return true;
	cout << "attacker doesn't have this gun\n";
	return false;
}
bool Player::is_money_enough(int wanted_money) {
	if (money < wanted_money) {
		cout << "insufficient money\n";
		return false;
	}
	return true;
}
bool Player::are_players_in_same_teams(Player attacked) {
	if (side == attacked.side) {
		cout << "you can't shoot this player\n";
		return true;
	}
	else
		cout << "nice shot\n";
	return false;
}
int  Interface::start() {
	cout << "fight" << '\n';
	return MATCH_STARTED;
}
Player Interface::add_user(vector<string> info) {
	int player_side;
	if (info[2] == "terrorist")
		player_side = TERRORIST;
	else 
		player_side = COUNTER_TERRORIST;
	cout << "ok" << '\n';
	return Player(info[1], FIRST_MONEY, FIRST_HEALTH, player_side, KNIFE, ATK_MODE,ALIVE,0,0);
}
Gun Interface::find_a_gun_from_list(string gun_name) {
	if (gun_name == "knife")
		return KNIFE;
	if (gun_name == "heavy")
		return HEAVY;
	if (gun_name == "pistol")
		return PISTOL;
}
int Interface::find_a_player_from_list(string name) {
	for (int i = 0;i < players.size();i++)
		if (players[i].get_name() == name)
			return i;
}
int Interface::number_of_alive_player(int side) {
	int number = 0;
	if (side == TERRORIST)
		for (int i = 0;i < players.size();i++)
			if (players[i].get_side() == TERRORIST && players[i].get_alive() == ALIVE && players[i].get_mode() == ATK_MODE)
				number++;
	if (side == COUNTER_TERRORIST)
		for (int i = 0;i < players.size();i++)
			if (players[i].get_side() == COUNTER_TERRORIST && players[i].get_alive() == ALIVE && players[i].get_mode() == ATK_MODE)
				number++;
	return number;
}
bool Interface::check_player_available(string player_name) {
	for (int i = 0;i < players.size();i++)
		if (players[i].get_name() == player_name)
			if (players[i].get_mode() == ATK_MODE)
				return true;
	cout << "user not available\n";
	return false;
}
bool Interface::check_gun_available(string name) {
	if (name != "knife" && name != "pistol" && name != "heavy") {
		cout << "weapon not available\n";
		return false;
	}
	return true;
}
bool Interface::check_players_alive_for_shoot(int attacker_index, int attacked_index) {
	if (players[attacker_index].get_alive()==DEAD) {
		cout << "attacker is dead\n";
		return false;
	}
	if (players[attacked_index].get_alive()==DEAD) {
		cout << "attacked is dead\n";
		return false;
	}
	return true;
}
bool Interface::is_game_start(int check_game_start, string shoot_or_buy) {
	if (shoot_or_buy == "buy") {
		if (check_game_start == MATCH_STARTED) {
			cout << "you can't buy weapons anymore\n";
			return true;
		}
		else return false;
	}
	else if (shoot_or_buy == "shoot") {
		if (check_game_start == MATCH_NOT_START) {
			cout << "the game hasn't started yet\n";
			return false;
		}
		else return true;
	}
}
void Interface::order_base_on_kill(){
	for (int i = 0;i < players.size() - 1;i++)
		for (int j = i + 1;j < players.size();j++) 
			if (players[j].get_kill() > players[i].get_kill())
				iter_swap(players.begin() + i, players.begin() + j);
}
void Interface::order_base_on_death() {
	for (int i = 0;i < players.size() - 1;i++)
		for (int j = i + 1;j < players.size();j++) 
			if (players[j].get_kill() == players[i].get_kill()&&players[j].get_death() < players[i].get_death())
				iter_swap(players.begin() + i, players.begin() + j);
}
void Interface::order_base_on_alphabet() {
	for (int i = 0;i < players.size() - 1;i++)
		for (int j = i + 1;j < players.size();j++) 
			if (players[j].get_kill() == players[i].get_kill() && players[j].get_death() == players[i].get_death()&&
				   players[j].get_name() < players[i].get_name())
			   iter_swap(players.begin() + i, players.begin() + j);
}
Player_list Interface::order_list(int side) {
	Player_list terrorist_users, counter_terrorist_users;
	order_base_on_kill();
	order_base_on_death();
	order_base_on_alphabet();
	for (int k = 0;k < players.size();k++) {
		if (players[k].get_side() == TERRORIST)
			terrorist_users.push_back(players[k]);
		else
			counter_terrorist_users.push_back(players[k]);
	}
	if (side == TERRORIST)
		return terrorist_users;
	if (side == COUNTER_TERRORIST)
		return counter_terrorist_users;
}
void Interface::buy(string gun_name, string player_name, int check_game_start) {
	Gun wanted_gun;
	int player_index = find_a_player_from_list(player_name);
	if (is_game_start(check_game_start, "buy"))
		return;
	if (!check_player_available(players[player_index].get_name()))
		return;
	if (!check_gun_available(gun_name))
		return;
	wanted_gun = find_a_gun_from_list(gun_name);
	if (!players[player_index].is_money_enough(wanted_gun.get_price()))
		return;
	if (!players[player_index].check_weapon_not_duplicate(wanted_gun))
		return;
	players[player_index].add_gun(wanted_gun);
	players[player_index].decrease_money(wanted_gun.get_price());
	cout << "weapon bought successfully\n";
}
void Interface::shoot_player(int attacker_index, int attacked_index, Gun gun) {
	players[attacked_index].decrease_health(gun.get_damage());
	if (players[attacked_index].get_health() == 0) {
		players[attacker_index].increase_money(gun.get_reward());
		players[attacker_index].increase_kill();
		players[attacked_index].increase_death();
	}
}
void Interface::shoot(int check_game_start, string attacker_name, string attacked_name, string gun_name) {
	if (!is_game_start(check_game_start, "shoot"))
		return;
	int attacker_index = find_a_player_from_list(attacker_name);
	int attacked_index = find_a_player_from_list(attacked_name);
	if (!check_player_available(attacker_name) || !check_player_available(attacked_name))
		return;
	if (!check_players_alive_for_shoot(attacker_index, attacked_index))
		return;
	if (!players[attacker_index].check_player_have_a_gun(gun_name))
		return;
	if (players[attacker_index].are_players_in_same_teams(players[attacked_index]))
		return;
	Gun wanted_gun = find_a_gun_from_list(gun_name);
	shoot_player(attacker_index, attacked_index, wanted_gun);
}
void Interface::show_team_result(Player_list team, string team_name) {
	cout << team_name << " players:\n";
	for (int i = 0;i < team.size();i++)
		cout << team[i].get_name() << " " << team[i].get_kill() << " " << team[i].get_death() << endl;
}
void Interface::score_board() {
	Player_list terrorist = order_list(TERRORIST);
	Player_list counter_terrorist = order_list(COUNTER_TERRORIST);
	show_team_result(counter_terrorist, "counter-terrorist");
	show_team_result(terrorist, "terrorist");
}
void Interface::show_result_of_a_round() {
	int num_of_terrorist_alive = number_of_alive_player(TERRORIST);
	int num_of_counter_terrorist_alive = number_of_alive_player(COUNTER_TERRORIST);
	if (num_of_counter_terrorist_alive == 0) {
		cout << "terrorist won\n";
		set_player_to_defualt(TERRORIST, COUNTER_TERRORIST);
	}
	else {
		cout << "counter-terrorist won\n";
		set_player_to_defualt(COUNTER_TERRORIST,TERRORIST);
	}
}
void Interface::set_player_to_defualt(int winner_side, int loser_side) {
	for (int i = 0;i < players.size();i++) {
		players[i].set_health_to_defualt();
		if (players[i].get_side() == winner_side)
			players[i].increase_money(ROUND_WINNER_BONUS);
		else if (players[i].get_side() == loser_side)
			players[i].increase_money(ROUND_LOSER_BONUS);
	}
}
void Interface::get_command() {
	while (1) {
		string line;
		getline(cin, line);
		command = split(line);
		if(command.size()==0)
			break;
		else if (command[0] == "round") {
			number_of_command_in_a_round = stoi(command[1]);
			break;
		}
		else if (command[0] == "add-user")
			players.push_back(add_user(command));
		else if (command[0] == "score-board")
			score_board();
	}
}
void Interface::start_get_command() {
	while (1) {
		get_command();
		if (command.size()==0)
			break;
		int i = 1;
		int check_game_start = MATCH_NOT_START;
		Player wanted_player;
		while (i <= number_of_command_in_a_round) {
			string line;
			getline(cin, line);
			command = split(line);
			if (command[0] == "start")
				check_game_start = start();
			else if (command[0] == "get-money")
				wanted_player.show_money_to_player(players, command[1]);
			else if (command[0] == "get-health")
				wanted_player.show_health_to_player(players, command[1]);
			else if (command[0] == "go-afk")
				wanted_player.go_afk(players, command[1]);
			else if (command[0] == "go-atk")
				wanted_player.go_atk(players, command[1]);
			else if (command[0] == "buy")
				buy(command[2], command[1], check_game_start);
			else if (command[0] == "shoot")
				shoot(check_game_start, command[1], command[2], command[3]);
			else if (command[0] == "score-board")
				score_board();
			i++;
		}
		show_result_of_a_round();
	}
}
int main() {
	Interface interface(get_number_of_round());
	interface.start_get_command();
}