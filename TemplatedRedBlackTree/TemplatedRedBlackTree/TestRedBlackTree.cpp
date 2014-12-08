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
		while (true){
			cout << "Search for something or .exit to terminate" << endl;
			cin >> search;
			if (search == ".exit"){
				cout << "You have terminated the program." << endl;
				break;
			}
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
			tree->insert(word);
		}
	}
}