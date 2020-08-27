#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <iostream>
#include <direct.h>
#include <vector>
#include <string.h>
#include <sstream>
#include <fstream>
#include <dirent.h>

#include "include/fonction.h"


#define gestion_argument(compareson,code)   if(strcmp(tab[position],compareson)==0)\
                                    {\
                                        code\
                                    }
#ifdef Debug
    #define Default_Folder "test/"
    #define Default_Result "bin/"
    #define Default_Filter "test.rule"
    #define Default_Rule ""
    #define Default_delimiter "@"
    #define Default_One_File false
#else
    #define Default_Folder ""
    #define Default_Result "bin/"
    #define Default_Filter ""
    #define Default_Rule ""
    #define Default_delimiter "@"
    #define Default_One_File false
#endif // Debug

#define Help_Instruction \
cout << "Using:" << endl;\
cout << "replace_core " << "[/folder dir] [/result dir] [/filter dir] [/rule filter] [/delimiter char] [/one_file]" << endl<< endl;\
cout << "Options:" << endl;\
cout << "      " << "/help" << "\t\t" << "help about this programme" << endl;\
cout << "      " << "/folder dir" << "\t" << "the folder or one file for working" << endl;\
cout << "      " << "/result dir" << "\t" << "result the result folder by default bin/" << endl;\
cout << "      " << "/filter dir" << "\t" << "the filter location" << endl;\
cout << "      " << "/rule filter" << "\t" << "a filter in commade ligne" << endl;\
cout << "      " << "/delimiter char" << "\t" << "the delimiter in filter by default @" << endl;\
cout << "      " << "/one_file" << "\t\t" << "if you went to work on one file" << endl;\

using namespace std;



int main(int argc,char *argv[])
{
    cout <<"start"<<endl<<endl;

    string folder = Default_Folder;
    string result = Default_Result;
    string filter = Default_Filter;
    string rule = Default_Rule;
    bool one_file = Default_One_File;
    string delimiter = Default_delimiter;

    /**************************************************/
    /*********Appel du programme avec argument********/

    int position;
    char *tab[argc];
    if(argc >1)//l'utilisateur a écrit dans argv
	{
		for(position=0;position<argc;position++)
		{
            tab[position]=argv[position+1];//argv[0] adresse réservé
		}
        for(position=0;position+1<argc;position++)
        {
            /**************************************************/
            /*************gestion des argument*****************/
            /**************plus code fonction******************/
            /**************************************************/
            gestion_argument("/help",                   //exemple
                            Help_Instruction;         //code
                            return 0;
                        )
            gestion_argument("/folder",
                            folder = tab[position+1];
                            position = position +1;
                             )
            gestion_argument("/result",
                            result  = tab[position+1];
                            position = position +1;
                             )
            gestion_argument("/filter",
                            filter = tab[position+1];
                            position = position +1;
                             )
            gestion_argument("/rule",
                            rule = tab[position+1];
                            position = position +1;
                             )
            gestion_argument("/one_file",
                                one_file = true;
                             )
            gestion_argument("/delimiter",
                            delimiter = tab[position+1];
                            position = position +1;
                             )
        }
    }
    //code du main
    if(folder == "")
    {
        cout << "/folder non specifier" << endl << endl;
        Help_Instruction;
        return -1;
    }
    if(filter == "" && rule == "")
    {
        cout << "/filter or /rule non specifier" << endl  << endl;
        Help_Instruction;
        return -1;
    }

    vector<string> all_dir;
    if(!one_file)
    {
        char dir[result.length() + folder.length()];
        string combine = result;
        combine.append(folder);
        strcpy(dir , combine.c_str());
        _mkdir(dir);
        all_dir = get_only_file(folder);
        all_dir.erase(all_dir.begin(),all_dir.begin()+2);
    }
    else
    {
        all_dir.push_back(folder);
    }
    cout << "all file : " << endl;
    for(long long unsigned int i = 0; i <= all_dir.size()-1 ; i++)
    {
        cout << "\t" << all_dir.at(i) << endl;
    }
    string rule_file;
    if(rule == "")
    {
        ifstream f(filter); //taking file as inputstream

        ostringstream ss;
        ss << f.rdbuf(); // reading data

        rule_file = ss.str();
    }
    else
    {
        rule_file = rule;
    }
    vector<string> rules;

    size_t pos = 0;
    string token;
    while ((pos = rule_file.find(delimiter)) != string::npos) {
        rules.push_back(rule_file.substr(0, pos));
        rule_file.erase(0, pos + delimiter.length());
    }
    rules.push_back(rule_file);

    cout << endl << "rule :" << endl;
    for(long long unsigned int i = 0; i <= rules.size()-1 ; i = i + 2)
    {
        cout << "|" << rules.at(i) << "|" <<  rules.at(i+1) << "|" << endl;
    }
    cout <<endl;
    //le travail

    for(unsigned int i = 0; i<=all_dir.size()-1;i++)
    {
        work(folder + all_dir.at(i),rules,result);
    }

	return 0;
}
