#include <iostream>
#include "List.h"

template class List<int>;

void TestList();
void TestListIter();

#include <algorithm>
void print(int i){
	std::cout << i << ", ";
}

int main(){
	//TestProgram
	    TestList();
	    TestListIter();
	////    std::cout << "There should be one memory leak!";
	////    std::cin.get();

}
