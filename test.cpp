#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <unistd.h> //*
#include <vector>
#include <algorithm>
#include <time.h>
#include <sys/time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/times.h>
#include <time.h>
/*
clock_t begin = clock();
clock_t end = clock();
double t = double(end - begin);
*/
using namespace std;

class History{
public:
	string command;
	double time;
};

bool compare(const History & a, const History & b){
	return a.time > b.time;
}

void Display(const History & a){
	cout << a.command << "  " << a.time << "s" <<endl;
}

void deleteSpace(string & a){
	for (int i = 0; i < a.length(); ++i){
		if (a[i]==' '){
			a.erase(i,1);
			i--;
		}
	}
}


int main(){
	char char_input[256];
	string input;
	vector<History> all_history;
	vector<History> sorted_history;
	History tmp;
	pid_t pid;

	struct tms time1,time2;
	
	cout << "tinyshell>";
	while(cin.getline(char_input,256)){
		input = char_input;
		times(&time1);
		// Child
		if ((pid=fork()) == 0){
			clock_t begin = clock();
			if(input == "history-sbu"){
				cout<<"system1:"<<endl;
				system(char_input);
				cout << "tinyshell>";
				exit(0);
			}

			deleteSpace(input);			//formatting input

			if(input == "history"){	   // history
				cout << "Display history:" << endl;
				int count = 0;
				for (vector<History>::iterator i = all_history.end()-1; i != all_history.begin()-1 && count<5; --i){
					Display(*i);
					count++;
				}
				cout << "tinyshell>";

				exit(0);
			}

			else if(input == "history-sbu"){		// history -sbu
				cout << "-sbu tag" << endl;
				sorted_history = all_history;
				sort(sorted_history.begin(), sorted_history.end(),compare);
				int count = 0;
				for (vector<History>::iterator i = sorted_history.begin(); i != sorted_history.end() && count<5; ++i){
					Display(*i);
					count++;
				}
				cout << "tinyshell>";
				exit(0);
			}

			else if(input == "exit"){			// exit
				exit(0);	
			} 
	 
			else{						// other
				cout<<"system2:"<<endl;
				system(char_input);
				cout << "tinyshell>";
				exit(0);
			}
		
		}
		
		// Return to Parent
		else{
			waitpid(pid,NULL,0);
			times(&time2);
			//clock_t end = clock();
			//long double clktck = sysconf(_SC_CLK_TCK);
			// store previous command and time
			long double clktck=sysconf(_SC_CLK_TCK);
			tmp.command = char_input;
			tmp.time = (double(time2.tms_cutime-time1.tms_cutime)+double(time2.tms_cstime-time1.tms_cstime))/(double)clktck; 
			all_history.push_back(tmp);
			deleteSpace(input);
			if (input == "exit")
				exit(0);
			}
	}
	return 0;
}















