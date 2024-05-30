#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#pragma warning(disable:4996)
#define START_TIME_HH 12
#define START_TIME_MM 0
#define END_TIME_HH 20
#define END_TIME_MM 0
#define ONE_HOUR 1
#define ONE_HOUR_MINUTE 60
#define END_GET_COURSES 0
using namespace std;
void print_time(int time) {
	if (time < 10)
		cout << "0" << time;
	else
		cout << time;
}
void printcolon() {
	cout << ":";
}
void printdash() {
	cout << "-";
}
struct Time {
	int hh_start;
	int mm_start;
	int hh_end;
	int mm_end;
};
struct Task {
	int duration;
	int free_time_period;
	Time free_time_used;
};
struct Period {
	int number;
	Time time;
};
Time get_time() {
	Time course_time;
	char colon,hyphen;
	cin>>course_time.hh_start>>colon>>course_time.mm_start>>hyphen>> course_time.hh_end>>colon>>course_time.mm_end;
	return course_time;
}
void clear_cin_cache() {
	cin.clear();
	cin.ignore(256,'\n');
}
Task get_input() {
	Task temp_task;
	cin >> temp_task.duration >> temp_task.free_time_period;
	return temp_task;
}
void get_courses(vector<Time> &courses) {
	while (1) {
		courses.push_back(get_time());
		if (courses[courses.size() - 1].hh_start == END_GET_COURSES) {
			courses.pop_back();
			break;
		}
	}
	clear_cin_cache();
}
void get_duty(vector<Task> &duty) {
	while (1) {
		duty.push_back(get_input());
		if (cin.eof())
			break;
	}
	duty.pop_back();
}
void set_period_type1(vector<Period>& periods, vector<Time>courses) {
	Period temp_period;
	for (int i = 0; i < courses.size(); i++) {
		if (courses[i].hh_end >= 20)
			break;
		temp_period.time.hh_start = courses[i].hh_end;
		temp_period.time.mm_start = courses[i].mm_end;
		if (i == courses.size() - 1) {
			temp_period.time.hh_end = END_TIME_HH;
			temp_period.time.mm_end = END_TIME_MM;
		}
		else {
			temp_period.time.hh_end = courses[i + 1].hh_start;
			temp_period.time.mm_end = courses[i + 1].mm_start;
		}
		temp_period.number = i+1;
		periods.push_back(temp_period);
	}
}
void set_period_type2(vector<Period>& periods, vector<Time>courses) {
	Period temp_period;
	for (int i = 0; i < courses.size(); i++) {
		if (i == 0) {
			temp_period.time.hh_start = START_TIME_HH;
			temp_period.time.mm_start = START_TIME_MM;
		}
		else {
			temp_period.time.hh_start = courses[i - 1].hh_end;
			temp_period.time.mm_start = courses[i - 1].mm_end;
		}
		temp_period.time.hh_end = courses[i].hh_start;
		temp_period.time.mm_end = courses[i].mm_start;
		temp_period.number = i + 1;
		periods.push_back(temp_period);
	}
	if (courses[courses.size() - 1].hh_end < 20) {
		temp_period.time.hh_start = courses.back().hh_end;
		temp_period.time.mm_start = courses.back().mm_end;
		temp_period.time.hh_end = END_TIME_HH;
		temp_period.time.mm_end = END_TIME_MM;
		temp_period.number = courses.size() + 1;
		periods.push_back(temp_period);
	}
}
void organize_periods(vector<Period> &periods, vector<Time>courses) {
	if (courses[0].hh_start == START_TIME_HH && courses[0].mm_start == START_TIME_MM)
		set_period_type1(periods, courses);
	else
		set_period_type2(periods, courses);
}
void set_timetable(Task& duty, Period &relevant_period) {
	duty.free_time_used.hh_start = relevant_period.time.hh_start;
	duty.free_time_used.hh_end = relevant_period.time.hh_start;
	duty.free_time_used.mm_start = relevant_period.time.mm_start;
	duty.free_time_used.mm_end = duty.free_time_used.mm_start + duty.duration;
	while (duty.free_time_used.mm_end >= ONE_HOUR_MINUTE) {
		duty.free_time_used.hh_end += ONE_HOUR;
		duty.free_time_used.mm_end -= ONE_HOUR_MINUTE;
	}
	relevant_period.time.hh_start = duty.free_time_used.hh_end;
	relevant_period.time.mm_start = duty.free_time_used.mm_end;
}
void organize_works_timetable(vector<Period> periods,vector<Task> &duty){
	int j;
	for (int i = 0; i < duty.size(); i++) {
		for (j = 0; j < periods.size(); j++) {
			if (periods[j].number == duty[i].free_time_period)
				break;
		}
			set_timetable(duty[i],periods[j]);
	}
}
void show_final_timetable(vector<Task> duty) {
	for (int i = 0; i < duty.size(); i++) {
		cout << i+1 <<' ';
		print_time(duty[i].free_time_used.hh_start);
		printcolon();
		print_time(duty[i].free_time_used.mm_start);
		printdash();
		print_time(duty[i].free_time_used.hh_end);
		printcolon();
		print_time(duty[i].free_time_used.mm_end);
		cout << endl;
	}
}
int main()
{
	vector<Time> courses;
	vector<Task> duty;
	vector<Period> periods;
	get_courses(courses);
	get_duty(duty);
	organize_periods(periods,courses);
	organize_works_timetable(periods, duty);
	show_final_timetable(duty);
	return 0;
}