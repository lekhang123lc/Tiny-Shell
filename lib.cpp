#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
#include <dirent.h>
#include <sys/types.h>


class Library{
public:
    static vector<string> splitString(string needSplit, char separate=' '){
        vector<string> result;
        int n=needSplit.size();
        string current="";
        result=vector<string>();

        for(int i=0;i<n;i++){
            if ( needSplit[i] == separate && current != "" ) {
                result.pb(current);
                current = "";
            }
            if ( needSplit[i] != separate ){
                current += needSplit[i];
            }
        }
        if ( current != "" ){
            result.pb(current);
        }
        return result;
    }

    static vector<string> getListFilesInDir(string path, bool getSystemFile = false) {
        vector<string> files;

        struct dirent *entry;

        DIR *dir = opendir(&path[0]);
        if (dir != NULL) {
            while ((entry = readdir(dir)) != NULL) {
                if ( getSystemFile == false && ( entry->d_name[0] < 'A' || 'z' < entry->d_name[0] ) )
                    continue;
                files.pb(entry->d_name);
            }
            closedir(dir);
        }
        return files;
    }

    static bool dirExists(const char* dirName) {
        DWORD attribs = ::GetFileAttributesA(dirName);
        if (attribs == INVALID_FILE_ATTRIBUTES) {
            return false;
        }
        return (attribs & FILE_ATTRIBUTE_DIRECTORY);
    }

    static string getCurrentDir() {
       char buff[FILENAME_MAX]; //create string buffer to hold path
       GetCurrentDir( buff, FILENAME_MAX );
       string current_working_dir(buff);
       return current_working_dir;
    }

    static string getDate(SYSTEMTIME date, string separate="/"){
        return to_string(date.wDay) + separate + to_string(date.wMonth) + separate + to_string(date.wYear);
    }

    static string getTime(SYSTEMTIME time, string separate=":"){
        return to_string(time.wHour) + separate + to_string(time.wMinute) + separate + to_string(time.wSecond);
    }

    static string getDateTime(){
        SYSTEMTIME datetime;
        GetLocalTime(&datetime);
        string time = getTime(datetime);
        string date = getDate(datetime);
        return time + " " + date;
    }
};
