/*
Group members:
Lee Long Hin	3035475216
Tsui Wai Kin	3035436741
*/

#include <iostream>
#include <unistd.h>		// fork(), pipe()
#include <vector>		// vector
#include <algorithm>	// sort()
#include <sys/time.h>	// gettimeofday()

using namespace std;

class History{
public:
	string command;
	long double time;
};

bool compare(const History & a, const History & b){
	return a.time > b.time;
}

void Display(const History & a){
	cout << a.command << "  " << a.time << "s" << endl;
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
	History tmp;
	long double sec, diff;
	int fd[2];		// 0:read, 1:write
	cout << "tinyshell>";
  
	while(cin.getline(char_input,256)){
	input = char_input;
    struct  timeval   start;
    struct  timeval   end;
    gettimeofday(&start,NULL);
    pipe(fd);
    	// Child
		if (fork() == 0){
    		clock_t begin=clock();
			float sec;
			if((input[0] == ' ' && input[1] == ' ')||(input == "history-sbu")){
				system(char_input);
			}

			deleteSpace(input);			//formatting input

			if(input == "history"){	   // history
				int count = 0;
				for (vector<History>::iterator i = all_history.end()-1; i != all_history.begin()-1 && count<5; --i){
					Display(*i);
					count++;
				}

			}

			else if(input == "history-sbu"){		// history -sbu
				sort(all_history.begin(), all_history.end(),compare);
				int count = 0;
				for (vector<History>::iterator i = all_history.begin(); i != all_history.end() && count<5; i++){
					Display(*i); //i is a vector object with class History i.command, i.time
					count++;
				}
			}

			else if(input == "exit"){			// exit
				exit(0);	
			} 
	 
			else{		// other
				system(char_input);
			}

			gettimeofday(&end,NULL);		// process time
			diff = (end.tv_sec-start.tv_sec)+ (end.tv_usec-start.tv_usec)/1000000.0;

			close(fd[0]);		// pipe
			write(fd[1], &diff, sizeof(diff));
			close(fd[1]);

			cout << "tinyshell>";
			exit(0);

		}	//end of child

		// Return to Parent : store previous command and time
		else{
			close(fd[1]); //read only, close write
			read(fd[0], &sec, sizeof(sec));
			close(fd[0]);

			tmp.time = sec;
			tmp.command = char_input;
			all_history.push_back(tmp);
			
			deleteSpace(input);
			if (input == "exit")
				exit(0);
		}	// parent end
	}	// BIG while loop end
	return 0;
}	// main end












