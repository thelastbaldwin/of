#include <iostream>
#include <time.h>

int main(){
	std::cout << "Here we go!" << std::endl;
	
	//get the current time
	time_t mark = time(NULL); 
	time_t now;
	double dif;
	int intervals = 0;
	int previous = 0;
	while(true){ //infinite loop for test purposes
		now = time(NULL);
		dif = difftime(now, mark);
		if(dif != previous){
			previous = dif;
			intervals++;
			std::cout << intervals << std::endl;
		}
	}
	return 0;
}