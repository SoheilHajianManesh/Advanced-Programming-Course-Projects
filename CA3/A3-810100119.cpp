#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;


#define SEPARATOR ' '
#define TIME_SEPARATOR ':'
#define FILE_NAME "input.txt"
#define NO_TRANSLATOR "Not Found"


struct Time {
	int hh_start;
	int mm_start;
	int hh_end;
	int mm_end;
};


struct Language {
	string name;
	int num_of_translators;
	string translator_name;
};


struct Translator {
	string name;
	Time free_time;
	vector<string> languages;
	vector<Time> busy_time;
};


struct Event {
	string name;
	Time time;
	vector<Language> languages;
};


typedef vector<Translator> Translatorlist;


typedef vector<Event> Eventlist;


vector<string> split(string line) {
	vector<string> info;
	string parse;
	for (int i = 0, j = 0; i < line.size(); i++,j++) {
		if (line[i] == SEPARATOR||line[i]==TIME_SEPARATOR) {
			j = 0;
			info.push_back(parse);
			parse.clear();
			continue;
		}
		if (i == line.size() - 1){
			parse.push_back(line[i]);
			info.push_back(parse);
			parse.clear();
		}	
		parse.push_back(line[i]);
	}
	return info;
}
void set_free_time_of_translator(Translator& translator, vector<string> time) {
	translator.free_time.hh_start = stoi(time[1]);
	translator.free_time.mm_start = stoi(time[2]);
	translator.free_time.hh_end = stoi(time[3]);
	translator.free_time.mm_end = stoi(time[4]);
}
void set_language_of_translator(Translator& translator, vector<string> languages) {
	for (int i = 5; i < languages.size(); i++) {
		translator.languages.push_back(languages[i]);
	}
}
Translator translator_info(string line){
	Translator translator;
	vector<string> info = split(line);
	translator.name = info[0];
	set_free_time_of_translator(translator, info);
	set_language_of_translator(translator, info);
	return translator;
}
bool end_of_translators(string line) {
	if (line.size() == 1)
		return true;
	else
		return false;
}
Translatorlist get_translators(ifstream& myfile, string& line) {
	Translatorlist translators;
	while (1) {
		getline(myfile, line);
		if (end_of_translators(line))
			return translators;
		else
			translators.push_back(translator_info(line));
	}
}
void set_time_of_event(Event& event, vector<string> time){
	event.time.hh_start = stoi(time[1]);
	event.time.mm_start = stoi(time[2]);
	event.time.hh_end = stoi(time[3]);
	event.time.mm_end = stoi(time[4]);
}
void set_language_of_event(Event &event, vector<string> languages) {
	Language language;
	for (int i = 5; i < languages.size(); i++) {
		language.name = languages[i];
		language.num_of_translators = 0;
		event.languages.push_back(language);
	}
}
Event event_info(string line) {
	Event event;
	vector<string> info = split(line);
	event.name = info[0];
	set_time_of_event(event, info);
	set_language_of_event(event, info);
	return event;
}
Eventlist get_events(ifstream& myfile,string& line) {
	Eventlist events;
	while (getline(myfile, line)) 
		events.push_back(event_info(line));
	return events;
}
void read_file(Translatorlist &translators, Eventlist &events) {
	ifstream myfile(FILE_NAME);
	string line;
	int info_number = 0;
	getline(myfile, line);
	translators = get_translators(myfile, line);
	events = get_events(myfile, line);
	myfile.close();
}
void num_of_translators_have_language(Language &language,Translatorlist translators){
	for (int i = 0; i < translators.size(); i++) {
		for (int j = 0; j < translators[i].languages.size(); j++) {
			if (translators[i].languages[j] == language.name) {
				language.num_of_translators++;
				break;
			}
		}
	}
}
Language language_which_has_priority(Event req_event,int index) {
	for (int i = 0; i < req_event.languages.size() - 1; i++) {
		for (int j = i + 1; j < req_event.languages.size(); j++) {
			if (req_event.languages[i].num_of_translators > req_event.languages[j].num_of_translators)
				iter_swap(req_event.languages.begin()+i, req_event.languages.begin()+j);
		}
	}
	return req_event.languages[index];
}
Language order_languages(Event &req_event, Translatorlist translators,int index) {
	for (int i = 0; i<req_event.languages.size(); i++) {
		num_of_translators_have_language(req_event.languages[i], translators);
	}
    return language_which_has_priority(req_event,index);
}
int find_index_of_language(Language require_translation, vector<Language> languages) {
	int index;
	for (index = 0; index < languages.size(); index++)
		if (languages[index].name == require_translation.name)
			return index;
}
bool translator_have_that_time(Translator translator, Event event) {
	if ((translator.free_time.hh_start<event.time.hh_start && translator.free_time.hh_end>event.time.hh_end)
		|| (translator.free_time.hh_start < event.time.hh_start && translator.free_time.hh_end == event.time.hh_end && translator.free_time.mm_end >= event.time.mm_end)
		|| (translator.free_time.hh_start == event.time.hh_start && translator.free_time.mm_start <= event.time.mm_start && translator.free_time.hh_end > event.time.hh_end)
		|| (translator.free_time.hh_start == event.time.hh_start && translator.free_time.mm_start <= event.time.mm_start && translator.free_time.hh_end == event.time.hh_end && translator.free_time.mm_end >= event.time.mm_end)
		)
		return true;
	else
		return false;
}
bool not_busy_that_time(Translator translator, Event event){
	for (int k = 0; k < translator.busy_time.size(); k++) {
		if ((translator.busy_time[k].hh_end < event.time.hh_start)
			|| (translator.busy_time[k].hh_start > event.time.hh_end)
			|| (translator.busy_time[k].hh_start == event.time.hh_end && translator.busy_time[k].mm_start > event.time.mm_start)
			|| (translator.busy_time[k].hh_end == event.time.hh_start && translator.busy_time[k].mm_end < event.time.mm_start)
			)
			continue;
		else
			return false;
	}
	return true;
}
bool is_free_in_event_time(Translator translator, Event event) {
	if (translator_have_that_time(translator, event)) {
		return not_busy_that_time(translator, event);
	}
	else
		return false;
}
bool have_translator(Translatorlist usable_translators) {
	if (usable_translators.size() != 0)
		return true;
	else
		return false;
}
Translatorlist available_translators_for_event(Language language, Event event, Translatorlist translators) {///pass by reffrenco hazf kardi inja
	Translatorlist usable_translators;
	for(int i=0;i<translators.size();i++)
		for (int j = 0; j < translators[i].languages.size(); j++) {
			if (language.name == translators[i].languages[j]) {
				if (is_free_in_event_time(translators[i], event)) {
					usable_translators.push_back(translators[i]);
				}
				break;
			}
		}
	return usable_translators;
}
Translator best_choice(Translatorlist available_tr) {
	Translator best_choice = available_tr[0];
	for (int i = 1; i < available_tr.size(); i++) {
		if (available_tr[i].languages.size() < best_choice.languages.size())
			best_choice = available_tr[i];
		else if(available_tr[i].languages.size() == best_choice.languages.size())
	       	if(available_tr[i].name< best_choice.name)
				best_choice = available_tr[i];
	}
	return best_choice;
}
void increase_translator_busy_time(Event event, Translatorlist& translators,Translator right_translator) {
	int i = 0;
	while (translators[i].name != right_translator.name)
		i++;
	translators[i].busy_time.push_back(event.time);
}
void choose_translator(Language &language, Event &event, Translatorlist &translators) {
	Translator right_translator;
	Translatorlist usable_translators= available_translators_for_event(language,event,translators);
	if (have_translator(usable_translators)) {
		right_translator = best_choice(usable_translators);
		language.translator_name = right_translator.name;
		increase_translator_busy_time(event, translators, right_translator);
	}
	else 
		language.translator_name = NO_TRANSLATOR;
}
void set_translators(Translatorlist &translators, Eventlist &events) {
	for (int i = 0; i < events.size(); i++) {
	  	for (int j = 0; j<events[i].languages.size(); j++) {
			Language require_translation=order_languages(events[i], translators,j);
			int index = find_index_of_language(require_translation,events[i].languages);
			choose_translator(events[i].languages[index],events[i],translators);
		}
	}
}
void show_result(Eventlist events) {
	for (int i = 0; i < events.size(); i++) {
		cout << events[i].name << '\n';
		for (int j = 0; j < events[i].languages.size(); j++) 
			cout << events[i].languages[j].name << TIME_SEPARATOR << events[i].languages[j].translator_name << endl;
	}
}
int main(int argc, char* argv[]) {
	Translatorlist translators;
	Eventlist events;
	read_file(translators, events);
	set_translators(translators, events);
	show_result(events);
}