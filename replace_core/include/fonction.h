#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED

#include <stdlib.h>
#include <stddef.h>
#include <iostream>
#include <string>
#include <sstream>
#include <dirent.h>
#include <vector>
#include <string.h>
#include <fstream>


using namespace std;


vector<string> get_all_file(string path)
{
    DIR *dir;
    struct dirent *ent;
    vector<string> return_value;
    if ((dir = opendir(path.c_str())) != NULL)
    {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL)
        {
            return_value.push_back(ent->d_name);
        }
        closedir (dir);
    }
    else
    {
        /* could not open directory */
        perror ("");
    }
    return return_value;
}
vector<string> get_only_file(string path)
{
    vector<string> return_value = get_all_file(path);
    for(unsigned int i = 0; i<=return_value.size()-1;i++)
    {
        size_t found = return_value.at(i).find(".");
        if (found==std::string::npos)
        {
            return_value.erase(return_value.begin()+i);
            i = i - 1;;
        }
    }
    return return_value;
}
void work(string file,vector<string> rules,string result)
{
    cout << file;
    //open
    ifstream f(file); //taking file as inputstream

    ostringstream ss;
    ss << f.rdbuf(); // reading data

    string open_file = ss.str();
    //replace
    for(long long unsigned int i = 0; i<=rules.size()-1;i = i + 2)
    {
        vector<size_t> all_position;
        size_t pos;
        //find text to replace + earase
        while ((pos = open_file.find(rules.at(i))) != std::string::npos)
        {
            all_position.push_back(pos);
            open_file.erase(pos, rules.at(i).length());
        }
        //replace
        for(long long int t = all_position.size()-1; t>=0;t--)
        {
            open_file.insert(all_position.at(t),rules.at(i+1));
        }
    }

    //write
    ofstream result_file;
    result_file.open(result + file,ios::trunc);
    result_file << open_file;
    result_file.close();

    cout << " fait" <<endl;
    return;
}

#endif // FONCTION_H_INCLUDED
