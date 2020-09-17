#pragma once
#include<iostream>
#include <unordered_map> 
#include<fstream>
using namespace std;

class ofstr
{
private:
	string work_path;
public:
	ofstr(string path);
	void write_data(unordered_map<string, int>& map_user_event, unordered_map<string, int>& map_repo_event,
		unordered_map<string, int>& map_user_repo_event);
};

