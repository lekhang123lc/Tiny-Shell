class Process{
public:
    int status;
    string name;
    string createdTime;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    Process(int _status, string _name, STARTUPINFO &_si, PROCESS_INFORMATION &_pi){
        status = _status, name = _name, si=_si, pi=_pi;
        createdTime = Library::getDateTime();
    }

    bool hasStatusOff(){
        DWORD newStatus;
        GetExitCodeProcess(pi.hProcess, &newStatus);
        return (!newStatus || !status);
    }

    friend bool operator==(const Process& lhs, const Process& rhs)
	{
		return ( lhs.name == rhs.name );
	}
};

class Resource{
private:
    static vector<string> statusList;
    static vector< Process > processList;
public:

    static void updateProcess(){
        vector< Process > newList;
        bool check=0;
        for(int i = 0; i < processList.size(); i++){
            if ( processList[i].hasStatusOff() ) {
                check = 1;
                break;
            }
        }
        if ( check ){
            for(int i = 0; i < processList.size(); i++){
                if ( !processList[i].hasStatusOff() ) {
                    newList.pb(processList[i]);
                }
            }
            processList = newList;
        }
    }

    static bool checkProcessExist(string name){
        updateProcess();
        for(auto &process:processList){
            if ( name == process.name && process.status == 1 ) return 1;
        }
        return 0;
    }

    static Process &findProcess(string name){
        updateProcess();
        for(auto &process:processList){
            if ( name == process.name ) return process;
        }
    }

    static bool addProcess(Process process){
        processList.pb(process);
    }

    static vector<Process> &getProcessList(){
        updateProcess();
        return processList;
    }

    static string getStatus(int status){
        return statusList[status];
    }

};
vector< string > Resource::statusList = {"OFF", "RUNNING", "STOPPED"};
vector< Process > Resource::processList;
