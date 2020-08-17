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
    vector<string> return_value = get_all_file(path);;
    for(unsigned int i = 0; i<=return_value.size()-1;i++)
    {
        bool file = false;
        std::size_t found = return_value.at(i).find(".");
        if (found!=std::string::npos)
        {
            file = true;
            i--;
        }
        if(file)
        {
            return_value.erase(return_value.begin()+i);
        }
    }
    return return_value;
}

#define gestion_argument(compareson,code)   if(strcmp(tab[position],compareson)==0)\
                                    {\
                                        code\
                                    }\

int main(int argc,char *argv[])
{
    cout <<"start"<<endl;

    string folder ="";
    string result = "bin/";
    string filter = "";
    string rule = "";
    bool one_file = false;

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
            gestion_argument("/help",             //exemple
                        cout<<"help"<<endl;         //code
                        return 0;
                        )
            gestion_argument("/folder",

                             )
            gestion_argument("/result",

                             )
            gestion_argument("/filter",

                             )
            gestion_argument("/rule",

                             )
            gestion_argument("/one_file",
                                one_file = true;
                             )
        }
    }

    //code du main
    if(folder == "")
    {
        cout << "/folder non specifier" << endl;
        cout << "/folder" << endl;
        cout << "/result" << endl;
        cout << "/filter" << endl;
        cout << "/rule" << endl;
        cout << "/one_file" << endl;
        return -1;
    }
    if(filter == "" && rule == "")
    {
        cout << "/filter or /rule non specifier" << endl;
        cout << "/folder" << endl;
        cout << "/result" << endl;
        cout << "/filter" << endl;
        cout << "/rule" << endl;
        cout << "/one_file" << endl;
        return -1;
    }
    if(!one_file)
    {
        char dir[result.length() + folder.length()];
        string combine = result;
        combine.append(folder);
        strcpy(dir , combine.c_str());
        _mkdir(dir);
        vector<string> all_dir = get_only_file(folder);
        all_dir.erase(all_dir.begin(),all_dir.begin()+2);
    }
    else
    {
        vector<string> all_dir;
        all_dir.push_back(folder);
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

//     = rule_file.split('@');





	return 0;
}
