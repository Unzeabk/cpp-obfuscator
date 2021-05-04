#include <bits/stdc++.h>
using namespace std;

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


vector <string> main_codes;
vector <string> defines;
string def;
void getrandstr(){
  def = "#define lto5";
  string ok = "lto5";
  int len = rand() % 1001 + 1;

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
  if(s.find("using") != -1) return 1;
  return 0;
}

int main(){
  freopen("code.cpp", "r", stdin);
  freopen("res.cpp", "w", stdout);

  srand(time(NULL));
  prep();
  std_lib();

  string s;

  while(getline(cin, s)){
    if(s[0] == '/' || s[0] == '*'){ // comment
      cout << s << '\n';
      continue;
    }
    if(isdef(s)){
      cout << s << '\n';
      continue;
    }
    if(s.find("#include") != -1) continue;
    if(s == " " || s == "\n") continue;
    while(s.front() == ' ' && s.size()) s.erase(0, 1);
    if(s.size() == 0) continue;

    getrandstr();
    def += s;
    defines.push_back(def);
  }

  for(int time_rand = 10; time_rand--; ) shuffle(defines.begin(), defines.end(), default_random_engine(0));

  for(const string &codes : defines) cout << codes << '\n';
  for(const string &codes : main_codes) cout << codes << '\n';
}
