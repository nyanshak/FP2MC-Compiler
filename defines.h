using namespace std;
#include <sstream>
#include <vector>

string convertInt(int n) {
	stringstream ss;
	ss << n;
	return ss.str();
}

string convertToLowerCase(string str) {
	for (int i = 0; i < strlen(str.c_str()); i++){
		str[i] = tolower(str[i]);
	}
	return str;
}

struct Symbol {
	string arr[5];
	vector<string> vars;
	string ret;
};

string GetType(Symbol s) {
	return s.arr[0];
}

string GetName(Symbol s) {
	return s.arr[1];
}

Symbol createConstant(string nm, string type, string value) {
	Symbol s;
	s.arr[0] = "constant";
	s.arr[1] = nm;
	s.arr[2] = type;
	s.arr[3] = value;
	return s;
}

string bracket(string s) {
	return "<" + s + ">";
}


struct sparam {
	float n;
	bool b;
	string c;
	int fnc;
	int func;
};
