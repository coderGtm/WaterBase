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
    WaterBase() {
        seperator = ":";
        fname = "db.txt";
    }
    void SetSeperator(string);
    void SetFile(string);
    vector<string> tokenize(string,string);
    void SaveBoolean(string,bool);
    void SaveNumber(string,long long int);
    void SaveText(string,string);
    bool LoadBoolean(string,bool);
    long long int LoadNumber(string,long long int);
    string LoadText(string,string);
    string base64_encode(const string&);
    string base64_decode(const string&);
};
void WaterBase::write(string valType, string name, string val) {
    string line;
    vector<string> lines;
    bool wrote = false;

    //to create file if does not exists
    ofstream temp(fname,ios::out | ios::app);
    temp.close();

    ifstream dbFile(fname);
    if (dbFile.is_open()) {
        while (getline(dbFile,line)) {
            lines.push_back(line);
            vector<string> tokens = tokenize(line,seperator);
            if (tokens[0] == valType && base64_decode(tokens[1]) == name) {
                lines.back() = valType+seperator+base64_encode(name)+seperator+base64_encode(val);
                wrote = true;
            }
        }
        if (!wrote) {
            lines.push_back(valType+seperator+base64_encode(name)+seperator+base64_encode(val));
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
    ifstream dbFile(fname);
    if (dbFile.is_open()) {
        while (getline(dbFile,line)) {
            vector<string> tokens = tokenize(line,seperator);
            if (tokens[0] == valType && base64_decode(tokens[1]) == name) {
                dbFile.close();
                return base64_decode(tokens[2]);
            }
        }
        dbFile.close();
        return defaultVal;
    }
    return defaultVal;
}
void WaterBase::SetSeperator(string sep) {
    seperator = sep;
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
string WaterBase::base64_encode(const string &in) {

    string out;

    int val=0, valb=-6;
    for (int jj = 0; jj < in.size(); jj++) {
    	char c = in[jj];
        val = (val<<8) + c;
        valb += 8;
        while (valb>=0) {
            out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[(val>>valb)&0x3F]);
            valb-=6;
        }
    }
    if (valb>-6) out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[((val<<8)>>(valb+8))&0x3F]);
    while (out.size()%4) out.push_back('=');
    return out;
}

string WaterBase::base64_decode(const string &in) {

    string out;

    vector<int> T(256,-1);
    for (int i=0; i<64; i++) T["ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[i]] = i; 

    int val=0, valb=-8;
    for (int jj = 0; jj < in.size(); jj++) {
    	char c = in[jj];
        if (T[c] == -1) break;
        val = (val<<6) + T[c];
        valb += 6;
        if (valb>=0) {
            out.push_back(char((val>>valb)&0xFF));
            valb-=8;
        }
    }
    return out;
}
