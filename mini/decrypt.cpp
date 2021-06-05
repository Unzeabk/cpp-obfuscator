#include <bits/stdc++.h>
using namespace std;

int cnt;
string s;
map <string, string> en;
vector <string> enc;

void std_lib(){
  cout << "#include <bits/stdc++.h>\n";
  cout << "using namespace std;\n\n";
}

void encrypt(string token){
  if(en.count(token)) return;

  en[token] = string(++cnt, '_');
}

void encrypt_full(string token){
  string s = "";

  s += en[token]; s.push_back(' ');
  enc.push_back(s);
}

bool isWord(string token){
  return (token.find("\"") != -1);
}

int main(){
  freopen("code.cpp", "r", stdin);
  freopen("res.cpp", "w", stdout);

  std_lib();

  int cnt = 0;
  while(getline(cin, s)){
    if(s.find("#include") != -1) continue;
    if(s == "using namespace std;") continue;

    //string won't be obfuscated
    if(isWord(s) && count(s.begin(), s.end(), '\"') != 2){
      string token = "";
      stringstream read(s);
      while(read >> token)
        if(!isWord(token)) encrypt(s);
        else break;

      encrypt_full(s);
      continue;
    }

    //encrypt each word in s
    string token = "";
    stringstream read(s);
    while(read >> token) encrypt(token);


    //encrypt s
    token = "";
    stringstream read1(s);
    while(read1 >> token) encrypt_full(token);
  }

  for(const auto &[x, y]: en) cout << "#define " << y << ' ' << x << "\n";
  cout << '\n';
  for(const string &ss: enc) cout << ss << '\n';

  return 0;
}
