#include <iostream>
#include <string>
using namespace std;
bool is_fix(string str, string sub1, string sub2) {
	if (sub1 == "" && sub2 == "")
		return true;
    if (str == "")
		return false;
	if (sub2[0] == str[0] && sub1[0] == str[0]) {
		for (int i = 1; sub1[i] != '\0' && sub2[i] != '\0'; i++) {
			if (str[i] == sub1[i] && str[i] != sub2[i])
				return is_fix(str.substr(1), sub1.substr(1), sub2);
			if (str[i] != sub1[i] && str[i] == sub2[i])
				return is_fix(str.substr(1), sub1, sub2.substr(1));
		}	
	}
    if (sub1[0] == str[0])
		return is_fix(str.substr(1), sub1.substr(1),sub2);
	if (sub2[0] == str[0])
		return is_fix(str.substr(1), sub1, sub2.substr(1));
	else
		return false;
}
void show_result(int true_or_false) {
	if(true_or_false==true)
		cout << "Interleaving" << endl;
	else
		cout << "Not Interleaving" << endl;
}
int main() {
	string str, sub1, sub2;
	cin >> sub1 >> sub2 >> str;
	show_result(is_fix(str, sub1, sub2));
}