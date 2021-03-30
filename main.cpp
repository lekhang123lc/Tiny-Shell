#include <bits/stdc++.h>
#include <signal.h>
#include <windows.h>
#define pb push_back
#define ii pair<int,int>
#define x first
#define y second

using namespace std;

const string NAME_PROJECT = "TinyShell";

#include "lib.cpp"
#include "print.cpp"
#include "resource.cpp"
#include "command.cpp"

class System{
private:
    string root;
    vector<string> commandList;
    string defaultCommand = "help";
    int currentInput = -1;
    vector< vector<string> > inputList;
public:
    System(){
        this->root = Library::getCurrentDir();
        this->commandList = Factory::getListCommand();
    }

    vector<string> inputLine(){
        string input;
        vector<string> line;
        getline(cin,input);
        line = Library::splitString(input,' ');
        return line;
    }

    void inputCommand(){
        Print::printLine(NAME_PROJECT+": "+this->root+">", "");
        inputList.pb(inputLine());
        currentInput++;
    }

    Command* findCommand(string name){
        if ( name.empty() ) return NULL;
        for(int i=0;i<this->commandList.size();i++){
            auto command = Factory::getCommand(this->commandList[i]);
            if ( name == command->getName() ){
                return command;
            }
        }
        return NULL;
    }
    void run(){
        inputCommand();
        vector<string> params = inputList[currentInput];
        Command * currentCommand = findCommand(params[0]);

        if ( currentCommand != NULL ){
            params.erase(params.begin());
        }
        else {
            currentCommand = findCommand(defaultCommand);
        }
        currentCommand->execute(params);
    }
};

int main()
{
    ios_base::sync_with_stdio(0);
    cout<<"Ho va Ten: Le Tuan Khang"<<endl;
    cout<<"MSSV: 20180108"<<endl;
    Factory::init();
    System shell;
    while(1){
        shell.run();
    }
    return 0;
}
