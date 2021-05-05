#include <bits/stdc++.h>
using namespace std;

string s;
map <string, string> conv;
vector <string> save;

int main(){
  freopen("res.cpp", "r", stdin);
  freopen("code.cpp", "w", stdout);

  cout << "#include <bits/stdc++.h>\n";
  cout << "using namespace std;\n\n";

  while(getline(cin, s)){
    if(s.find("include") != -1) continue;
    if(s == "using namespace std;") continue;

    if(s.find("#define") != -1){
      string token = "", en = "", de;
      stringstream read(s);

      while(read >> token){
        if(token == "#define") continue;
        if(token.find("lto5") != -1) de = token;
        else en += token, en += " ";
      }

      while(en.back() == ' ' && en.size()) en.pop_back();
      conv[de] = en;
      continue;
    }

    while(s.back() == ' ' && s.size()) s.pop_back();
    cout << conv[s] << '\n';

  }

  return 0;
}
