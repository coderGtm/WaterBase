#ifndef IOSTREAM
    #define IOSTREAM
    #include <iostream>
#endif
#ifndef FSTREAM
    #define FSTREAM
    #include <fstream>
#endif
#ifndef VECTOR
    #define VECTOR
    #include <vector>
#endif
#ifndef STRING
    #define STRING
    #include <string>
#endif

using namespace std;


class WaterBase {
    string seperator;
    string fname;
    void write(string,string,string);
    string read(string,string,string);
    public:
    WaterBase(string db_name) {
        seperator = ":";
        fname = db_name+".wb";
    }
    void SetFile(string);
    vector<string> tokenize(string,string);
    void SaveBoolean(string,bool);
    void SaveNumber(string,long long int);
    void SaveText(string,string);
    bool LoadBoolean(string,bool);
    long long int LoadNumber(string,long long int);
    string LoadText(string,string);
};
void WaterBase::write(string valType, string name, string val) {
    string line;
    vector<string> lines;
    bool wrote = false;

    //create file if not exist
    ofstream temp(fname,ios::out | ios::app);
    temp.close();

    ifstream dbFile(fname);
    if (dbFile.is_open()) {
        while (getline(dbFile,line)) {
            lines.push_back(line);
            vector<string> tokens = tokenize(line,seperator);
            //check type match
            if (tokens[0] == valType) {
                int keyLen = stoi(tokens[1]);
                int valLen = stoi(tokens[2]);
                string dataString = line.substr(1+tokens[1].length()+tokens[2].length()+3);
                string key = dataString.substr(0,keyLen);
                //check key match
                if (key == name) {
                    //overwrite previous value
                    lines.back() = valType+seperator+to_string(name.length())+seperator+to_string(val.length())+seperator+name+seperator+val;
                    wrote = true;
                }
            }
        }
        if (!wrote) {
            lines.push_back(valType+seperator+to_string(name.length())+seperator+to_string(val.length())+seperator+name+seperator+val);
            wrote = true;
        }
        dbFile.close();
    }
    ofstream new_dbFile(fname,ios::trunc);
    if (new_dbFile.is_open()) {
        for (int i = 0; i < lines.size(); i++) {
            new_dbFile << lines[i] << endl;
        }
        new_dbFile.close();
    }
}
string WaterBase::read(string valType, string name, string defaultVal) {
    string line;
    string val = defaultVal;
    ifstream dbFile(fname);
    if (dbFile.is_open()) {
        while (getline(dbFile,line)) {
            vector<string> tokens = tokenize(line,seperator);
            //check type match
            if (tokens[0] == valType) {
                int keyLen = stoi(tokens[1]);
                int valLen = stoi(tokens[2]);
                string dataString = line.substr(1+tokens[1].length()+tokens[2].length()+3);
                string key = dataString.substr(0,keyLen);
                //check key match
                if (key == name) {
                    //extract value
                    val = dataString.substr(keyLen+1);
                }
            }
        }
        dbFile.close();
    }
    return val;
}
void WaterBase::SetFile(string name) {
    fname = name;
}
vector<string> WaterBase::tokenize(string s, string del = " ") {
    vector<string> tokens;
    int start = 0;
    int end = s.find(del);
    while (end != -1) {
        tokens.push_back(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
    }
    tokens.push_back(s.substr(start, end - start));

    return tokens;
}
void WaterBase::SaveBoolean(string name, bool val) {
    write("B",name,to_string(val));
}
void WaterBase::SaveNumber(string name, long long int val) {
    write("N",name,to_string(val));
}
void WaterBase::SaveText(string name, string val) {
    write("S",name,val);
}
bool WaterBase::LoadBoolean(string name, bool defaultVal) {
    string entry = read("B",name,to_string(defaultVal));
    return entry != "0";
}
long long int WaterBase::LoadNumber(string name, long long int defaultVal) {
    string entry = read("N",name,to_string(defaultVal));
    return stoll(entry);    
}
string WaterBase::LoadText(string name, string defaultVal) {
    string entry = read("S",name,defaultVal);
    return entry;
}
