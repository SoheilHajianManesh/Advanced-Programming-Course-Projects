#include <iostream>
#include <vector>
using namespace std;
void push_back_number(vector<int>& number, int first, int second) {
	number.push_back(first);
	number.push_back(second);
	number.erase(number.begin());
}
void change_zero_or_one(vector<int>& number, int element, int index, int number_size) {
	if (index == number_size)
		return;
	if (element == 0)
		push_back_number(number, 1, 0);
	else if (element == 1)
		push_back_number(number, 0, 1);
	change_zero_or_one(number, number[0], index + 1, number_size);
}
void change_system(vector<int> &number,int time) {
	if (time == 1)
		return;
	else {
		change_zero_or_one(number, number[0], 0, number.size());
	}
	change_system(number, time - 1);
}
void show_result(vector<int> number,int index) {
	cout << number[number.size() - index] << endl;
}
int main()
{
	vector<int> number = { 0 };
	int time,index;
	cin >> time >> index;
	change_system(number, time);
	show_result(number, index);
}