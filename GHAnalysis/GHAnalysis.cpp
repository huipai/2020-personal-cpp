// GHAnalysis.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include<iostream>
#include <string> 
#include <fstream> 
#include <io.h>
#include<map>
#include <stdlib.h>
#include <direct.h>
#include <sstream>
#include<vector>
#include <unordered_map> 

#include"xgetopt.h"
#include"cJSON.h"

using namespace std;

/*void GetLineAndSave(string in_path, string work_path, string fileinfo_name,
	unordered_map<string, int>& map_user_event, unordered_map<string, int>& map_repo_event, unordered_map<string, int>& map_user_repo_event);
int search(int type, string actor_login, string repo_name, string  event_type);
string get_work_path();*/
void initFile(char* argv[]);
int main(int argc, char* argv[])
{
	string actor_login;
	string repo_name;
	string  event_type;
	int opt;
	int longindex;
	char stri[] = "i::u::r::e::";
	char* str = stri;
	int type = 0;
	static struct xoption long_options[] =
	{
		{"user", xrequired_argument,NULL, 'u'},
		{"repo", xrequired_argument,NULL, 'r'},
		{"event", xrequired_argument,NULL,'e'},
		{"init", xrequired_argument,NULL,'i'},
	};
	while ((opt = xgetopt_long(argc, argv, str, long_options, &longindex)) != -1)
	{
		if (opt == 'i')
		{
			initFile(argv);
			return 0;
		}
		else if (opt == 'u')
		{
			type += 1;
			actor_login = xoptarg;
		}
		else if (opt == 'r')
		{
			type += 2;
			repo_name = xoptarg;
		}
		else if (opt == 'e')
		{
			event_type = xoptarg;
		}
	}
	//cout << search(type, actor_login, repo_name, event_type);
	return 0;
}
/*int search(int type, string actor_login, string repo_name, string  event_type)
{
	int count = 0;
	string work_path = get_work_path();
	string in_name;
	string search_object;
	if (type == 1)
	{
		in_name = work_path + "\\1.json";
		search_object = actor_login + event_type;
	}
	else if (type == 2)
	{
		in_name = work_path + "\\2.json";
		search_object = repo_name + event_type;
	}
	else if (type == 3)
	{
		in_name = work_path + "\\3.json";
		search_object = repo_name + event_type + actor_login;
	}
	else
	{
		exit(-1);
	}
	ifstream fin(in_name);
	if (!fin)
	{
		cerr << "open file error" << endl;
		exit(-1);
	}
	fin.seekg(0, fin.end);
	int length = fin.tellg();
	fin.seekg(0, fin.beg);
	char* temp = new char[length];
	fin.read(temp, length);
	cJSON* cJson_test = cJSON_Parse(temp);
	if (cJson_test == NULL)
	{
		cerr << "parse fail" << endl;
		exit(-1);
	}
	else
	{
		cJSON* cJson_type = cJSON_GetObjectItem(cJson_test, search_object.data());
		if (cJson_type != NULL)
		{
			count = cJson_type->valueint;
		}
	}
	cJSON_Delete(cJson_test);
	fin.close();
	return count;
}
void GetLineAndSave(string in_path, string work_path, string fileinfo_name,
	unordered_map<string, int>& map_user_event, unordered_map<string, int>& map_repo_event, unordered_map<string, int>& map_user_repo_event)
{
	string in_name = in_path + "\\" + fileinfo_name;
	ifstream fin(in_name);
	if (!fin)
	{
		cerr << "open file error" << endl;
		exit(-1);
	}
	fin.seekg(0, fin.end);
	int length = fin.tellg();
	fin.seekg(0, fin.beg);
	char* temp = new char[length];
	fin.read(temp, length);
	char* token = NULL;
	char* next_token = NULL;
	char seps[] = "\n";
	token = strtok_s(temp, seps, &next_token);
	while (token != NULL)
	{
		cJSON* cJson_test = cJSON_Parse(token);
		if (cJson_test == NULL)
		{
			break;
		}
		else
		{
			cJSON* cJson_type = cJSON_GetObjectItem(cJson_test, "type");
			string cJson_type_valuestring = cJson_type->valuestring;
			if (cJson_type_valuestring == "PushEvent" || cJson_type_valuestring == "IssueCommentEvent" ||
				cJson_type_valuestring == "IssuesEvent" || cJson_type_valuestring == "PullRequestEvent")
			{
				cJSON* cJson_actor = cJSON_GetObjectItem(cJson_test, "actor");
				cJSON* cJson_actor_login = cJSON_GetObjectItem(cJson_actor, "login");
				cJSON* cJson_repo = cJSON_GetObjectItem(cJson_test, "repo");
				cJSON* cJson_repo_name = cJSON_GetObjectItem(cJson_repo, "name");
				unordered_map<string, int>::iterator iter;
				iter = map_user_event.find(cJson_actor_login->valuestring + cJson_type_valuestring);
				if (iter != map_user_event.end())
				{
					iter->second++;
				}
				else
				{
					map_user_event.insert(pair<string, int>(cJson_actor_login->valuestring + cJson_type_valuestring, 1));
				}
				iter = map_repo_event.find(cJson_repo_name->valuestring + cJson_type_valuestring);
				if (iter != map_repo_event.end())
				{
					iter->second++;
				}
				else
				{
					map_repo_event.insert(pair<string, int>(cJson_repo_name->valuestring + cJson_type_valuestring, 1));
				}
				iter = map_user_repo_event.find(cJson_repo_name->valuestring + cJson_type_valuestring + cJson_actor_login->valuestring);
				if (iter != map_user_repo_event.end())
				{
					iter->second++;
				}
				else
				{
					map_user_repo_event.insert(pair<string, int>(cJson_repo_name->valuestring + cJson_type_valuestring + cJson_actor_login->valuestring, 1));
				}
			}
		}
		cJSON_Delete(cJson_test);
		token = strtok_s(NULL, seps, &next_token);
	}
	fin.close();
	delete temp;
}*/
string get_work_path()
{
	char path_char[300];
	_getcwd(path_char, 300);
	string in_path = path_char;
	return in_path;
}
void initFile(char* argv[])
{
	unordered_map<string, int> map_user_event;
	unordered_map<string, int> map_repo_event;
	unordered_map<string, int> map_user_repo_event;
	bool first = true;
	struct _finddata_t fileinfo;
	string work_path = get_work_path();
	string in_path = work_path + "\\" + argv[2];
	string curr = in_path + "\\*.json";
	intptr_t handle;
	if ((handle = _findfirst(curr.c_str(), &fileinfo)) == -1)
	{
		return;
	}
	else
	{
		ofstream ofile;
//		GetLineAndSave(in_path, work_path, fileinfo.name,
	///		map_user_event, map_repo_event, map_user_repo_event);
		while (!(_findnext(handle, &fileinfo)))
		{
//			GetLineAndSave(in_path, work_path, fileinfo.name,
	//			map_user_event, map_repo_event, map_user_repo_event);
		}
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
		_findclose(handle);
	}
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
