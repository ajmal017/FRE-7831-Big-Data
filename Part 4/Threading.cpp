#include <iostream>
#include <thread>
#include <string>
#include <map>
#include <vector>
#include <mutex>
#include <sstream>

using namespace std;

string DataCollection = "web,wed,green,sun,moon,land,part,web,green";
vector<string> WordList;
map<string, int> ResultTable;

// The mutex class is a synchronization primitive 
// that can be used to protect shared data 
// from being simultaneously accessed by multiple threads.
mutex word_mutex;

const int input_size = 9;
const int no_of_threads = 3;

class Parser {
public:
	void operator()(char delimiter)
	{
		string word;
		istringstream wordStream(DataCollection);
		while (getline(wordStream, word, delimiter))
			WordList.push_back(word);
	}
};

class Counter
{
public:
	void operator()(map<string, int> *pResultTable, int start)
	{
		while (WordList.size() != input_size);
		for (int i = start; i < start + input_size / no_of_threads; i++)
		{
			// When a lock_guard object is created, 
			// it attempts to take ownership of the mutex it is given.
			// When control leaves the scope in which the lock_guard object was created, 
			// the lock_guard is destructed and the mutex is released.
			lock_guard<mutex> guard(word_mutex);
			int count = (*pResultTable)[string(WordList[i])];
			count = count + 1;
			(*pResultTable)[string(WordList[i])] = count;
			// cout << "Key = " << string(WordList[i]) << " count = " << (*pResultTable)[string(WordList[i])] << endl;
		}
	}
};

int main()
{
	thread parser(Parser(), ',');
	thread counter1(Counter(), &ResultTable, 0);
	thread counter2(Counter(), &ResultTable, 3);
	thread counter3(Counter(), &ResultTable, 6);

	parser.join();
	counter1.join();
	counter2.join();
	counter3.join();

	for (map<string, int>::iterator itr = ResultTable.begin(); itr != ResultTable.end(); itr++)
		cout << itr->first << "	" << itr->second << endl;

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