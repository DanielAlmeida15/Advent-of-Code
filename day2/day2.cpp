#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

int safeReportCount = 0;

void getInput(string filename);
bool checkReport(vector<int>& levels);
void removeBadLevel(vector<int>& levels, int index);

int main(){

	getInput("input.txt");

	cout << "Number of safe reports: " << safeReportCount << endl;

	return 0;
}

/****** Functions ******/

void getInput(string filename) {
	ifstream file;
	file.open(filename);
	if (!file) {
		cout << "Error: Unable to open file" << endl;
		exit(1);
	}
	string report, delimiter = " ";
	int lvl, pos=0;
	while (getline(file, report)) {
		vector<int> levels;
		while ((pos = report.find(delimiter)) != string::npos)
		{
			lvl = stoi(report.substr(0, pos));
			levels.push_back(lvl);
			report.erase(0, pos + delimiter.length());
		}
		levels.push_back(stoi(report));
		if (checkReport(levels)) {
			safeReportCount++;
		}
	}
	file.close();
}

bool checkReport(vector<int>& levels) {
	bool decreasing = false, badLevel = false;
	int badLevels = 0;

	if (levels[0] > levels[1]) {
		decreasing = true;
	}else if (levels[0] < levels[1])
	{
		decreasing = false;
	}
	
	for (int i = 0; i < levels.size()-1; i++)
	{
		//cout << levels[i] << "(" << i << ")" << " ";
		if (decreasing) {
			if (!((0 < (levels[i] - levels[i+1])) && ((levels[i] - levels[i+1]) < 4)))
			{
				badLevel = true;
				badLevels++;
			}
			
		}else{
			
			if (!((0 < (levels[i+1] - levels[i])) && ((levels[i+1] - levels[i]) < 4)))
			{
				badLevel = true;
				badLevels++;
			}
		}

		//cout << "Bad levels: " << badLevels << endl;
		if (badLevels > 1)
		{
			
			return false;
		}

		if (badLevel)
		{
			removeBadLevel(levels, i);
			badLevel = false;
			i--;
		}
	}
	return true;
}

void removeBadLevel(vector<int>& levels, int index) {

	if (index == levels.size()-1)
	{
		levels.pop_back();
	}else{
		for (int i = index; i < levels.size()-1; i++)
		{
			levels[i] = levels[i+1];
		}
		levels.pop_back();
	}
}