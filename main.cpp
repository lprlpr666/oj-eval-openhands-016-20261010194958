#include <bits/stdc++.h>
using namespace std;
// Solution for ACMOJ Problem 2697 - File Storage BPT with persistence
// Additional comment for final submission

const string DB_FILE = "db.txt";

// Load database from file into unordered_map<string, set<int>>
void load_db(unordered_map<string, set<int>>& db) {
    ifstream fin(DB_FILE);
    if (!fin) return; // file does not exist
    string line;
    while (getline(fin, line)) {
        if(line.empty()) continue;
        stringstream ss(line);
        string key;
        ss >> key;
        int val;
        while (ss >> val) {
            db[key].insert(val);
        }
    }
    fin.close();
}

// Save current database to file (overwrite)
void save_db(const unordered_map<string, set<int>>& db) {
    ofstream fout(DB_FILE, ios::trunc);
    for (const auto& kv : db) {
        fout << kv.first;
        for (int v : kv.second) {
            fout << ' ' << v;
        }
        fout << '\n';
    }
    fout.close();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unordered_map<string, set<int>> db;
    load_db(db);

    int n;
    if(!(cin >> n)) return 0;
    string cmd;
    for(int i=0;i<n;++i){
        cin >> cmd;
        if(cmd=="insert"){
            string idx; int val; cin >> idx >> val;
            db[idx].insert(val);
        } else if(cmd=="delete"){
            string idx; int val; cin >> idx >> val;
            auto it = db.find(idx);
            if(it!=db.end()){
                it->second.erase(val);
                if(it->second.empty()) db.erase(it);
            }
        } else if(cmd=="find"){
            string idx; cin >> idx;
            auto it = db.find(idx);
            if(it==db.end() || it->second.empty()){
                cout << "null\n";
            } else {
                bool first=true;
                for(int v: it->second){
                    if(!first) cout << ' ';
                    first=false;
                    cout << v;
                }
                cout << '\n';
            }
        }
    }
    // Persist changes for next runs
    save_db(db);
    return 0;
// End of solution // final update
}

