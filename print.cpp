class Print{
public:
    void static printTable(vector< vector<string> > s, bool border = true){
        const char separator = ' ';
        int m=s.size(),n = s[0].size();
        int widthColumn[n];
        int maxWidth = 65;
        for(int i=0;i<n;i++)
            widthColumn[i] = 0;
        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++)
                widthColumn[j] = min( max(widthColumn[j], (int)s[i][j].size()+3), maxWidth + 3);
        for(int i=0;i<m;i++){
            vector<string> t;
            bool needInsert=0;
            for(int j=0;j<n;j++){
                if ( s[i][j].size() > maxWidth ){
                    int x = maxWidth;
                    while( s[i][j][x-1] != ' ' ) x--;
                    string thisLine = s[i][j].substr(0, x);
                    string nextLine = s[i][j].substr(x, (int)s[i][j].size()-x);
                    t.pb(nextLine);
                    s[i][j] = thisLine;
                    needInsert=1;
                }
                else t.pb("");
            }

            if ( needInsert ) {
                vector< vector<string> > newRow;
                newRow.pb(t);

                vector< vector<string> >::iterator it = s.begin();
                advance( it, i+1 );
                s.insert(it, newRow.begin(), newRow.end());
                m++;
            }
        }
        for(int i=0;i<m;i++){
            int currentWidth=0;
            for(int j=0;j<n;j++){
                currentWidth += widthColumn[j];
                cout << left << setw(widthColumn[j]) << setfill(separator) << s[i][j];
            }
            cout<<endl;
        }
    }

    void static printLine(string line, string endLine ="\n"){
        cout<<line<<endLine;
    }
};
