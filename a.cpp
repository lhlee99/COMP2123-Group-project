#include <iostream>
using namespace std;
string format(string input){
	string formatted;
	if(input[0] == ' ' && input[1] == ' ')
		return formatted;

	int count = 0, start = 0;
	string sub;
	for (int i = 0; i < input.length(); ++i){
		if(input[i] == ' '){
			sub = input.substr(start, count);
			count = 0;
			if(sub == "history")
				formatted += "h";
			else if(sub == "-sbu")
				formatted += "-";
			else if(sub == "exit")
				formatted += "e";
			else if(sub == " " || sub == "")
				formatted += "";
			else
				formatted += "x";
		}
		else{
			count++;
			if(count == 1){
				start = i;
			}
		}
	}
	if (count != 0){
		sub = input.substr(start, count);
		if(sub == "history")
			formatted += "h";
		else if(sub == "-sbu")
			formatted += "-";
		else if(sub == "exit")
			formatted += "e";
		else if(sub == " "|| sub == "")
			formatted += "";
		else
			formatted += "x";
	}
	return formatted;
}
int main(){
	string input = "history   -sbu";
	string formatted;
	formatted = format(input);
	cout<<formatted<<"/"<<endl;
}