/*
Feature:
- Obfuscate C++ keywords with bunch of definitions, then obfuscate your code, and shuffle all of them
- Can't obfuscate comments, so it will be deleted
- Your definition (define, typedef, etc.) won't be obfuscate
*/

// Updating...

#include <bits/stdc++.h>
using namespace std;

unordered_map <string, string> kw_ob = {{"FvzxGGlto5EO", "int"},
                                        {"kLDlto5KLLKD", "const"},
                                        {"tAcitclto5DM", "insert"},
                                        {"fRAcRlto5Pdo", "void"},
                                        {"oVgFEJlto5DdsM", "vector"},
                                        {"aolto5JhYFe", "char"},
                                        {"CBMilto5ZfHT", "long long"},
                                        {"nhcJWNlto5BzeN", "string"},
                                        {"llWMlto5RPe", "main"},
                                        {"DVtlto5CcZj", "for"},
                                        {"PwXMglto5kUqqw", "while"},
                                        {"DoXIlto5mqA", "auto"},
                                        {"gSbIilto5wZCU", "freopen"},
                                        {"KSgVDvlto5hF", "if"},
                                        {"wNQgumlto5bccTuW", "else"},
                                        {"Zxxlto5WgIls", "return"},
                                        {"lCSlto5Xds", "operator"},
                                        {"Rqlto5JY", "push_back"},
                                        {"hQFpHalto5FLjz", "bool"},
                                        {"cGATlto5lMy", "begin"},
                                        {"rglto5Ysig", "end"},
                                        {"jkDwlto5TVhbS", "printf"},
                                        {"qdBIlMlto5apB", "first"},
                                        {"Vulto5HLRRn", "second"},
                                        {"qFselto5er", "rbegin"},
                                        {"ooVZlto5gWCpyU", "rend"},
                                        {"MCuXSHlto5qQ", "cout"},
//                                        {"MVCKLKlto555", "resize"}, // error when replace
//                                        {"BCNlto5wmQTh", "size"},
                                        {"UWllto5zB", "length"},
                                        {"PKOnlto5Rn", "setw"},
                                        {"cCmlto5JQ", "setfill"},
                                        {"sSLElto5JPwwwV", "puts"},
                                        {"PINlto5PjNbS", "putchar"},
                                        {"Kjlto5wrmPL", "getchar"},
                                        {"PElto5oi", "scanf"},
                                        {"UZbulto5IUtOIR", "cin"},
                                      };

void change_keyword_obfuscator(){
  ;
}


const string lib[] = {"iostream", "assert.h", "math.h", "memory.h", "stdio.h", "algorithm",
                      "complex", "ctime", "fstream", "iostream", "list", "queue", "deque",
                      "unordered_map", "unordered_set", "map", "bitset", "numeric", "climits",
                      "iomanip", "set", "stack", "string", "vector", "array", "random", "chrono"};
void std_lib(){
  for(const string &S: lib) cout << "#include <" << S << ">\n";
  cout << "using namespace std;\n";
}

vector <char> chars;
void prep(){
  for(int i = 0; i < 26; i++){
    chars.push_back('a' + i);
    chars.push_back('A' + i);
    if(i <= 9) chars.push_back('0' + i);
  }
}

const int len_def = 10;
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

void change_keyword(string &ss){
  for(const auto &[k1, k2] : kw_ob){ // C++ 17
    for(int i = 0; i < ss.size(); i++){
      if(ss.substr(i, k2.size()) == k2) ss.replace(i, k2.size(), k1);
    }
  }
}

int main(){
  freopen("code.cpp", "r", stdin);
  freopen("res.cpp", "w", stdout);

  srand(time(NULL));
  prep();
  std_lib();

  for(const auto &[k1, k2] : kw_ob){
    cout << "#define " << k1 << " " << k2 << '\n';
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
