#include <bits/stdc++.h>
#include <time.h>
#include <unistd.h>
#include <dos.h>
#include <windows.h>

#define pb push_back
#define ii pair<int,int>
#define x first
#define y second

using namespace std;

int main(int argc, char* argv[])
{
    ios_base::sync_with_stdio(0);
//    cout<<argc<<endl<<argv<<endl<<*argv<<endl;
//    cout<<"----------------"<<endl;
    int n;
    if ( !argc ){
        n=10;
    }
    else n=atoi(*argv)+1;
    while(n--){
        cout<<n<<endl;
        Sleep(1000);
    }
    return 0;
}
