#include <stdio.h>
#include <vector>
#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>

#include "evar.h"

using namespace std::filesystem;


void showhelp()
{
    std::cout<<
R"END(
    envedit - a simple .env file editor

    Usage:
        envedit [.env file] [a=b] [c=d] ...

)END";
}

void terminate(std::string s)
{
    std::cout<<std::endl<<std::endl;
    std::cout<<s;
    std::cout<<std::endl<<std::endl;
    exit(-1);
}

int main(int argc, char **argv)
{
    if (argc<3) {
        showhelp();
	exit(0);
	}

    path p(argv[1]);
    if (!exists(p))
        terminate("Couldn't locate env file: "+p.string());
    std::cout<<"Editing environment file "<<p.string()<<std::endl;

    std::vector<evar> args;
    for (int i = 2; i < argc; i++) 
    {
        args.push_back(evar(argv[i]));
        if (args.back().valid()==false)
            terminate("Bad key=value parameter: "+args.back().str());
    }
    

    std::ifstream envfile(p);
    path ptemp(p.string()+"__TEMP");
    std::ofstream tempfile(ptemp);
    std::string line;
    while (std::getline(envfile, line))
    {
        evar e(line);
        if (e.valid())
            for (auto & z : args)
                if (z.samekey(e))
                {
                    line = z.str();
                    z.setOutput(true);
                    break;
                }
        tempfile << line << std::endl;
    }    

    for (auto & z : args)
        if (z.output()==false)
        {
            line = z.str();
            z.setOutput(true);
            tempfile << line << std::endl;
        }

    remove(p);
    rename(ptemp,p);

    return 0;
}
