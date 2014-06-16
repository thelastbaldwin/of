#include <iostream>
#include <vector> 
#include <algorithm> 
#include <stdexcept>

using namespace std;

int median(vector<int> readings);

int main(){

	vector <int> readings;
	//remove from vector with readings.erase(iterator) i.e. readings.erase(readings.begin() + 4)
	typedef vector<int>::size_type vec_sz;

	int x; // for input
	cout << "Enter an item to add it to the array (q to quit): "; 
	while(cin >> x){
		readings.push_back(x); // add to vector
		cout << "Items in array: ";

		for(vec_sz i=0; i != readings.size(); i++){
			cout << readings[i] << " ";
		}
		cout << endl;
		int med = median(readings);
		cout << "The median value of the vector is: " << med << endl;
		cout << "Enter an item to add it to the array: ";

		if(readings.size() >= 5){
			readings.erase(readings.begin()); //readings.begin() returns an iterator. Can't simply pass an index. 
		}	 	
	}
	return 0;
}

int median(vector<int> readings){

	typedef vector<int>::size_type vec_sz;
	vec_sz size = readings.size();
	if(size == 0)
		throw domain_error("median of an empty vector");
	sort(readings.begin(), readings.end());
	vec_sz mid = size/2;

	return size % 2 == 0 ? (readings[mid] + readings[mid-1]) / 2 : readings[mid];
}