/*
Feature:
- Obfuscate C++ keywords with bunch of definitions, then obfuscate your code, and shuffle all of them
- Can't obfuscate comments, so it will be deleted
- Your definition (define, typedef, etc.) won't be obfuscate
Notes:
- Use C++17
*/

#include <bits/stdc++.h>
using namespace std;

const int len_def = 10;
vector <char> chars;

void prep(){
  for(int i = 0; i < 26; i++){
    chars.push_back('a' + i);
    chars.push_back('A' + i);
    if(i <= 9) chars.push_back('0' + i);
  }
}

unordered_map <string, string> kw_ob = {{"int", "RWLRlflto5cxp"},
                                        {"const", "obf_lto5"},
                                        {"insert", "lto5"},
//                                        {"back", "lto5"},
//                                        {"front", "lto5"},
                                        {"void", "WWqvDlto5XmM"},
                                        {"vector", "gaNlto5gf"},
                                        {"char", "JZJHIhlto5CC"},
                                        {"long long", "sHuvLlto5CUjn"},
                                        {"string", "FOnmklto5cSwV"},
                                        {"main", "eKIulto5wy"},
                                        {"for", "Rmzlto5bn"},
                                        {"while", "cbdyQlto5Qsq"},
                                        {"auto", "FRWClto5TbVJwU"},
                                        {"freopen", "KBGksMlto5ID"},
                                        {"if", "Kazlto5ih"},
                                        {"else", "EAEElto5ZpbDS"},
                                        {"return", "avhbwUlto5ue"},
                                        {"operator", "nMhQsJlto5TGGRvs"},
                                        {"push_back", "CYSvlto5Tz"},
                                        {"bool", "UAulto5csmL"},
                                        {"begin", "ayFHzlto5ODQ"},
                                        {"end", "DOhGCKlto5DWVVTX"},
                                        {"printf", "OxQlto5jPXf"},
                                        {"first", "mKlto5yWM"},
                                        {"second", "NvQlto5mT"},
                                        {"rbegin", "NYtwTlto5sQ"},
                                        {"rend", "PvLxlto5cZHrWI"},
                                        {"cout", "FTlto5Vu"},
//                                        {"size", "lzlBWlto5ydUSz"},
                                        {"length", "DVnnJlto5LXV"},
                                        {"setw", "xRMWBRlto5jqq"},
                                        {"setfill", "jsexePlto5sjM"},
                                        {"puts", "cLZflto5MJ"},
                                        {"putchar", "ZLlto5YhJGJ"},
                                        {"getchar", "QAswXlto5cE"},
                                        {"scanf", "srySumlto5be"},
                                        {"cin", "dgzeIjlto5eD"},
                                      };

string get_rand(){
  string ress = "";
  for(int len_front = rand() % len_def + 1; len_front--; )
    ress.push_back(chars[rand() % chars.size()]);
  ress.append("lto5");
  for(int len_back = rand() % len_def + 1; len_back--; )
    ress.push_back(chars[rand() % chars.size()]);
  while(isdigit(ress[0])) ress.erase(ress.begin());
  return ress;
}

void change_keyword_obfuscator(){
  for(auto it = kw_ob.begin(); it != kw_ob.end(); )
    for(auto itt = ++it; itt != kw_ob.end(); itt++){
      bool change = rand() % 2;
      if(change) swap(it, itt);
    }
  for(auto &it: kw_ob) kw_ob[it.first] = get_rand();
}


void change_keyword(string &ss){
  for(const auto &[k1, k2] : kw_ob){
    for(int i = 0; i < ss.size(); i++){
      if(ss.substr(i, k1.size()) == k1) ss.replace(i, k1.size(), k2);
    }
  }
}


const string lib[] = {"iostream", "assert.h", "math.h", "memory.h", "stdio.h", "algorithm",
                      "complex", "ctime", "fstream", "iostream", "list", "queue", "deque",
                      "unordered_map", "unordered_set", "map", "bitset", "numeric", "climits",
                      "iomanip", "set", "stack", "string", "vector", "array", "random", "chrono"};
void std_lib(){
  for(const string &S: lib) cout << "#include <" << S << ">\n";
  cout << "using namespace std;\n";
}

vector <string> main_codes;
vector <string> defines;
string def;
void getrandstr(){
  def = "#define lto5";
  string ok = "lto5";
  int len = rand() % len_def + 5;

  while(len--){
    int pos = rand() % chars.size();
    ok.push_back(chars[pos]);
    def.push_back(ok.back());
  }

  ok.push_back(' ');
  def.push_back(' ');
  main_codes.push_back(ok);
}

bool isdef(const string &s){
  if(s.find("typedef") != -1) return 1;
  if(s.find("#define") != -1) return 1;
  if(s.find("using") != -1 && s != "using namespace std;") return 1;
  return 0;
}

int main(){
  freopen("code.cpp", "r", stdin);
  freopen("res.cpp", "w", stdout);

  srand(time(NULL));
  prep();
  change_keyword_obfuscator();
  std_lib();

  for(const auto &[k1, k2] : kw_ob){
    cout << "#define " << k2 << " " << k1 << '\n';
  }

  string s;

  while(getline(cin, s)){
    /* Delete comment, you can code a function to keep your comment */
    if(s.find("//") != -1) continue;
    if(s.find("/*") != -1){
      while(s.find("*/") == -1) getline(cin, s);
      getline(cin, s);
    }

    /* Not obfuscate "user-defined"? */
    if(s.find("#include") != -1) continue;
    if(s == "using namespace std;") continue;
    if(isdef(s)){
      change_keyword(s);
      cout << s << '\n';
      continue;
    }

    if(s == " " || s == "\n") continue;
    while(s.front() == ' ' && s.size()) s.erase(0, 1);
    if(s.size() == 0) continue;

    change_keyword(s);
    getrandstr();
    def += s;
    defines.push_back(def);
  }

  /* Shuffle code */
  for(int time_rand = 10; time_rand--; ) shuffle(defines.begin(), defines.end(), default_random_engine(0));

  for(const string &codes : defines) cout << codes << '\n';
  for(const string &codes : main_codes) cout << codes << '\n';

  return 0;
}
