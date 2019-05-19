#include <iostream>
#include <thread>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

//string DataCollection = "web,wed,green,sun,moon,land,part,web,green";

string file_path = "/Users/victor/Desktop/FRE-7831-Big-Data/Part 4/4727.txt";

vector<string> WordList;
map<string, int> ResultTable;

const int input_size = 735;
const int no_of_threads = 3;

class Parser {
public:
	void operator()(char delimiter)
	{
        ifstream infile(file_path);
        string line;
        string word;
        getline(infile, line);
        istringstream wordStream(line); // get all the words
        while (getline(wordStream, word, delimiter))
        {
            for (auto it=word.begin(); it!=word.end(); ++it)
            {// convert to lower case
                *it = tolower(*it);
            }
            WordList.push_back(word);
        }
	}
};

class Counter
{
public:
	void operator()(map<string, int> *pResultTable, int start)
	{
        while (WordList.size() != input_size);
        
		for (int i = start; i < start + input_size/no_of_threads; i++)
		{
			int count = (*pResultTable)[string(WordList[i])];
			count = count + 1;
			(*pResultTable)[string(WordList[i])] = count;
			// cout << "Key = " << string(WordList[i]) << " count = " << (*pResultTable)[string(WordList[i])] << endl;
		}
	}
};

class WordCounter
{
private:
	map<string, int> ResultTables[no_of_threads];
public:
	void Map()
	{
		thread parser(Parser(), ' ');
		thread counter1(Counter(), &ResultTables[0], 0);
		thread counter2(Counter(), &ResultTables[1], 245);
		thread counter3(Counter(), &ResultTables[2], 490);

		parser.join();
		counter1.join();
		counter2.join();
		counter3.join();
	}
	void Reduce()
	{
		for (int i = 0; i < no_of_threads; i++)
		{
			for (map<string, int>::iterator itr = ResultTables[i].begin();
				itr != ResultTables[i].end(); itr++)
				ResultTable[itr->first] += itr->second;
		}
	}
};

int main()
{
    ofstream fout;
    fout.open("output.txt");
    
	WordCounter wordcounter;

	wordcounter.Map();
	wordcounter.Reduce();

    for (map<string, int>::iterator itr = ResultTable.begin(); itr != ResultTable.end(); itr++) {
        cout << itr->first << " " << itr->second << endl;
        fout << itr->first << " " << itr->second << endl;
    }
    
    fout.close();
	return 0;
}
/*
green   2
land    1
moon    1
part    1
sun     1
web     2
wed     1
Press any key to continue . . .
*/
