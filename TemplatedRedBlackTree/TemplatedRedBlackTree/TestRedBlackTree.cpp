/* TreeTestZone.cpp :
this short code can be used to perform various testing and console visualization of the structure
as well as comparisons with binary search tree
*/

#include <time.h>
#include <iostream>
#include <queue>
#include "RedBlackTree.h"
#include <string>
#include <fstream>

using namespace std;

RedBlackTree<string> *tree;

void readFile();

int main()
{
	tree = new RedBlackTree<string>();
	try{
		readFile();
		cout << *tree << endl;
		tree->search("jsd");
	}
	catch (exception& e){
		e.what();
		cout << "Exception occurred." << endl;
	}
	system("pause");
	return 0;
}


void readFile(){
	ifstream file;
	file.open("Independence.txt");
	if (file.is_open()){
		string word;
		while (file >> word){
			for (unsigned int i = 0; i < word.size(); i++){
				if (!isalnum(word[i])){
					word.erase(i, 1);
					i--;
				}
			}
			tree->insertNode(word);
		}
	}
}