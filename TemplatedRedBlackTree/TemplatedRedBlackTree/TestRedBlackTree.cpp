#include <iostream>
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
		string search;
		while (search != "exit"){
			cout << "Search for something" << endl;
			cin >> search;
			tree->search(search);
		}
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