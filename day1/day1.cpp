#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

void sortList(vector<int>& list);
void getInput(vector<int>& list1, vector<int>& list2, string filename);

int main() {

	int total_distance = 0, similarity_score = 0, count = 0;
	vector<int> list1;
	vector<int> list2;

	getInput(list1, list2, "input.txt");	
	
	sortList(list1);
	sortList(list2);

	if (list1.size() != list2.size()) {
		cout << "Error: Lists are not the same size" << endl;
	}else{
		for (int i = 0; i < list1.size(); i++) {
			total_distance += abs(list1[i] - list2[i]);

			/* Part 2 */
			for (int j = 0; j < list2.size(); j++)
			{
				if (list1[i] == list2[j])
				{
					count++;
				}
			}
			similarity_score += list1[i] * count;
			count = 0;
		}
		cout << "Total distance: " << total_distance << endl;
		cout << "Similarity score: " << similarity_score << endl;
	}

	return 0;
}

/****** Functions ******/

void getInput(vector<int>& list1, vector<int>& list2, string filename) {
	ifstream file;
	file.open(filename);
	if (!file) {
		cout << "Error: Unable to open file" << endl;
	}else{
		string line, number, delimiter = " ";
		int num1, num2;
		while (getline(file, line)) {
			num1 = stoi(line.substr(0, line.find(delimiter)));
			num2 = stoi(line.substr(line.rfind(delimiter) + 1, line.length()));
			list1.push_back(num1);
			list2.push_back(num2);
		}
	}
	file.close();
}

void sortList(vector<int>& list) {
	int temp;
	for (int i = 0; i < list.size(); i++) {
		for (int j = i + 1; j < list.size(); j++) {
			if (list[i] > list[j]) {
				temp = list[i];
				list[i] = list[j];
				list[j] = temp;
			}
		}
	}	
}