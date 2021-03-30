class Command{
private:

public:
    string name = "";

    string syntax = "";

    string instruction = "";

    Command() {};

    virtual string getName(){
        return name;
    }

    virtual string getSyntax(){
        return syntax;
    }

    virtual string getInstruction(){
        return instruction;
    }

    virtual void execute(vector<string> params){

    }
};
class Factory{
public:
    static map<string, Command*(*)() > mapCommand;

    static Command* getCommand(string s) {
        return mapCommand[s]();
    }

    static map<string, Command*(*)() > getMapCommand(){
        return Factory::mapCommand;
    }

    static vector<string> getListCommand(){
        vector<string> listCommand;
        for(auto& it : mapCommand){
            listCommand.pb(it.x);
        }
        return listCommand;
    }

    template<typename T> static Command * createInstance() { return new T;}

    static void init();
};

class Help : public Command{
private:

public:
    string name="help";

    string syntax="help [command]";

    string instruction="Show how to use command [command] or all command if [command] is empty.";

    string error = "No command found ! Check syntax again with command \"help\" !";

    virtual string getName(){
        return name;
    }

    virtual string getSyntax(){
        return syntax;
    }

    virtual string getInstruction(){
        return instruction;
    }

    string getError(){
        return error;
    }

    virtual void execute(vector<string> params){
        vector< vector<string> > data;
        vector<string> listCommand = Factory::getListCommand();

        data.pb(vector<string>{"#", "NAME", "SYNTAX", "DESCRIPTION"});
        for(int i=0;i<listCommand.size();i++){
            Command * currentCommand = Factory::getCommand(listCommand[i]);
            if ( params.size() && params[0] != currentCommand->getName() ){
                continue;
            }
            data.pb(vector<string>{to_string((int)data.size()), listCommand[i],currentCommand->getSyntax(), currentCommand->getInstruction()});
        }
        if ( data.size() == 1 ){
            data.clear();
            data.pb(vector<string>{getError()});
        }
        Print::printTable(data);
    }
};

class Dir : public Command{
private:

public:
    string name="dir";

    string syntax="dir [directory]";

    string instruction="List all files and folder in directory [directory]. This directory is default value of [directory].";

    string error = "No command found ! Check syntax again with command \"help\" !";

    virtual string getName(){
        return name;
    }

    virtual string getSyntax(){
        return syntax;
    }

    virtual string getInstruction(){
        return instruction;
    }

    string getError(){
        return error;
    }

    virtual void execute(vector<string> params){
        if ( params.size() ){
            if ( !Library::dirExists(&params[0][0]) ){
                params[0] = Library::getCurrentDir() + "/" + params[0];
                if ( !Library::dirExists(&params[0][0]) ){
                    Print::printLine("This directory doesn't exist !");
                    return;
                }
            }
        }
        else params.pb(Library::getCurrentDir());
        vector< vector<string> > data;
        vector<string> files = Library::getListFilesInDir(params[0]);

        data.pb(vector<string>{"#","NAME"});
        int i=1;
        for(auto file:files){
            data.pb(vector<string>{to_string(i),file});
            i++;
        }
        if ( data.empty() ){
            data.pb(vector<string>{"Nothing found in this directory !"});
            data.pb(vector<string>{""});
        }
        else Print::printLine("Total " + to_string(files.size()) + " files and directory ! " );
        Print::printTable(data);
    }
};

class Date : public Command{
private:

public:
    string name="date";

    string syntax="date";

    string instruction="Show current date and time.";

    virtual string getName(){
        return name;
    }

    virtual string getSyntax(){
        return syntax;
    }

    virtual string getInstruction(){
        return instruction;
    }

    virtual void execute(vector<string> params){
        string datetime = Library::getDateTime();
        Print::printLine("Current date and time is: " + datetime);
    }
};

class Child : public Command{
private:

public:
    string name="child";

    string syntax="child [name] [seconds] [option]";

    string instruction="Create a new process which will countdown from [seconds] to 0, default is 100. Use -f for foreground mode and -b for background mode in [option]. Default is background mode.";

    virtual string getName(){
        return name;
    }

    virtual string getSyntax(){
        return syntax;
    }

    virtual string getInstruction(){
        return instruction;
    }

    void foreMode(Process& process){
        while(1){
            string signal;
            getline(cin,signal);
            if ( signal == "stop" ) break;

            DWORD status;
            GetExitCodeProcess(process.pi.hProcess, &status);
            if ( !status ) break;

            Print::printLine("Press \"stop\" to stop this process !");
            WaitForSingleObject(process.pi.hProcess, 200);
        }
        TerminateProcess(process.pi.hProcess, 0);
    }

    virtual void execute(vector<string> params){
        if ( params.size() ){
            if ( !Resource::checkProcessExist(params[0]) ){
                STARTUPINFO si;
                PROCESS_INFORMATION pi;
                ZeroMemory(&si, sizeof(si));
                si.cb = sizeof(si);

                if ( params.size() == 1 ) params.pb("100");

                if( CreateProcess(
                    "child.exe",
                    &params[1][0],
                    NULL,                // Process handle not inheritable
                    NULL,                // Thread handle not inheritable
                    FALSE,               // Set handle inheritance to FALSE
                    CREATE_NEW_CONSOLE,  // No creation flags
                    NULL,                // Use parent's environment block
                    NULL,                // Use parent's starting directory
                    &si,                 // Pointer to STARTUPINFO structure
                    &pi )                // Pointer to PROCESS_INFORMATION structure
                ){
                    Process child(1, params[0], si, pi);

                    if ( params.size() == 3 && params[2] == "-f" ){
                        foreMode(child);
                    }
                    else{
                        Resource::addProcess(child);
                    }
                }
                else{
                    Print::printLine("Error " + to_string(GetLastError()) + " occur !");
                }

            }
            else {
                Print::printLine("Error ! This process is running !");
            }
        }
        else {
            Print::printLine("Error ! You have to fill name of process !");
        }
    }
};

class List : public Command{
private:

public:
    string name="list";

    string syntax="list";

    string instruction="List all process in memory.";

    virtual string getName(){
        return name;
    }

    virtual string getSyntax(){
        return syntax;
    }

    virtual string getInstruction(){
        return instruction;
    }

    virtual void execute(vector<string> params){
        Resource::updateProcess();
        vector<Process> processList = Resource::getProcessList();
        vector< vector<string> > data;
        data.pb(vector<string>{"#", "PROCESS ID", "NAME", "STATUS", "CREATED TIME"});

        int i=1;
        for(auto process: processList){
            data.pb(vector<string>{to_string(i),to_string(GetProcessId(process.pi.hProcess)),process.name, Resource::getStatus(process.status), process.createdTime});
            i++;
        }
        Print::printTable(data);
    }
};

class Kill : public Command{
private:

public:
    string name="kill";

    string syntax="kill [name]";

    string instruction="Kill process [name] is running";

    virtual string getName(){
        return name;
    }

    virtual string getSyntax(){
        return syntax;
    }

    virtual string getInstruction(){
        return instruction;
    }

    virtual void execute(vector<string> params){
        if ( params.size() ){
            if ( Resource::checkProcessExist(params[0]) ){
                Process& process = Resource::findProcess(params[0]);
                if ( !TerminateProcess(process.pi.hProcess, 0)){
                    Print::printLine("Error " + to_string(GetLastError()) + " occur !");
                    return;
                }
                CloseHandle(process.pi.hProcess);
                CloseHandle(process.pi.hThread);
                process.status = 0;
                Resource::updateProcess();
            }
            else {
                Print::printLine("Error ! No process " + params[0] + " found !");
            }
        }
        else{
            Print::printLine("Error ! You have to fill name of process !");
        }
    }
};

class Exit : public Command{
private:

public:
    string name="exit";

    string syntax="exit";

    string instruction="Exit Tiny Shell.";

    virtual string getName(){
        return name;
    }

    virtual string getSyntax(){
        return syntax;
    }

    virtual string getInstruction(){
        return instruction;
    }

    virtual void execute(vector<string> params){
        PostMessage(GetConsoleWindow(), WM_CLOSE, 0, 0);
    }
};

void Factory::init(){
    Factory::mapCommand["Help"]   = &createInstance<Help>;
    Factory::mapCommand["Dir"]    = &createInstance<Dir>;
    Factory::mapCommand["Date"]   = &createInstance<Date>;
    Factory::mapCommand["Child"]  = &createInstance<Child>;
    Factory::mapCommand["List"]   = &createInstance<List>;
    Factory::mapCommand["Exit"]   = &createInstance<Exit>;
    Factory::mapCommand["Kill"]   = &createInstance<Kill>;
}

map<string, Command*(*)() > Factory::mapCommand;
