
#include "ofstr.h"

using namespace std;

void ofstr:: write_data(unordered_map<string, int>& map_user_event, unordered_map<string, int>& map_repo_event, unordered_map<string, int>& map_user_repo_event)
{
	ofstream ofile;
	ofile.open(work_path + "\\1.json");
	unordered_map<string, int>::iterator iter;
	iter = map_user_event.begin();
	if (iter != map_user_event.end())
	{
		ofile << "{\"" << iter->first << "\":" << iter->second;
		iter++;
	}
	for (; iter != map_user_event.end(); iter++)
	{
		ofile << ",\"" << iter->first << "\":" << iter->second;
	}
	ofile << "}";
	ofile.close();
	ofile.open(work_path + "\\2.json");
	iter = map_repo_event.begin();
	if (iter != map_repo_event.end())
	{
		ofile << "{\"" << iter->first << "\":" << iter->second;
		iter++;
	}
	for (; iter != map_repo_event.end(); iter++)
	{
		ofile << ",\"" << iter->first << "\":" << iter->second;
	}
	ofile << "}";
	ofile.close();
	ofile.open(work_path + "\\3.json");
	iter = map_user_repo_event.begin();
	if (iter != map_user_repo_event.end())
	{
		ofile << "{\"" << iter->first << "\":" << iter->second;
		iter++;
	}
	for (; iter != map_user_repo_event.end(); iter++)
	{
		ofile << ",\"" << iter->first << "\":" << iter->second;
	}
	ofile << "}";
	ofile.close();
}

ofstr::ofstr(string path)
{
	work_path = path;
}
