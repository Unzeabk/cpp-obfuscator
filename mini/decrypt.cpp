#include <bits/stdc++.h>
using namespace std;

int cnt;

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

void conv(string token){
  string s = "";

  s += en[token]; s.push_back(' ');
  enc.push_back(s);
}

bool isWord(string token){
  return (token.find("\"") != -1);
}

bool singleWord(string token){
  stringstream ss(token);
  string read = "";

  while(ss >> read){
    int r = count(read.begin(), read.end(), '\"');
    if(r != 0 && r != 2) return 0;
  }

  return 1;
}

void enc_each(string s){
  //encrypt each word in s
  string token = "";
  stringstream read(s);
  while(read >> token) encrypt(token);
}

void enc_full(string s){
  //encrypt s
  string token = "";
  stringstream read1(s);
  while(read1 >> token) conv(token);
}

int main(){
  freopen("code.cpp", "r", stdin);
  freopen("res.cpp", "w", stdout);

  std_lib();

  string s;

  while(getline(cin, s)){
    if(s.find("#include") != -1) continue;
    if(s == "using namespace std;") continue;

    //string won't be obfuscated
    if(isWord(s)){
      if(singleWord(s)) {
        enc_each(s);
        enc_full(s);
        continue;
      }

      string token = "";
      stringstream read(s);
      while(read >> token)
        if(!isWord(token)) encrypt(s);
        else break;

      conv(s);
      continue;
    }

    enc_each(s);

    enc_full(s);
  }

  for(const auto &[x, y]: en) cout << "#define " << y << ' ' << x << "\n";
  cout << '\n';
  for(const string &ss: enc) cout << ss << '\n';

  return 0;
}
