


#include<iostream> 
#include <unordered_set>
#include <unordered_map>
#include<vector>
#include<queue>
#include<string>
using namespace std;
void page_size_values(int pages[], int n)
{
	cout << "enter the pages" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> pages[i];
	}

}
bool search(int key, vector<int>& fr)
{
	for (int i = 0; i < fr.size(); i++)
		if (fr[i] == key)
			return true;
	return false;
}


int predict(int page[], vector<int>& FR, int PN, int index)
{
	int res = -1, farthest = index;
	for (int i = 0; i < FR.size(); i++) {
		int j;
		for (j = index; j < PN; j++) {
			if (FR[i] == page[j]) {
				if (j > farthest) {
					farthest = j;
					res = i;
				}
				break;
			}
		}


		if (j == PN)
			return i;
	}


	return (res == -1) ? 0 : res;
}

void optimalPage(int page[], int PN, int FN)
{

	vector<int> FR;

	int hit = 0;
	for (int i = 0; i < PN; i++) {


		if (search(page[i], FR)) {
			hit++;
			continue;
		}


		if (FR.size() < FN)
			FR.push_back(page[i]);


		else {
			int j = predict(page, FR, PN, i + 1);
			FR[j] = page[i];
		}
	}
	cout << "No. of hits = " << hit << endl;
	cout << "No. of misses = " << PN - hit << endl;
}
int page_Faults_least_recently_used(int page[], int n, int cap)
{


	unordered_set<int> s;
	unordered_map<int, int> indexes;


	int pagefaults = 0;
	for (int i = 0; i < n; i++)
	{
		if (s.size() < cap)
		{
			if (s.find(page[i]) == s.end())
			{
				s.insert(page[i]);
				pagefaults++;
			}

			indexes[page[i]] = i;
		}


		else
		{


			if (s.find(page[i]) == s.end())
			{


				int lru = INT_MAX, val;
				for (auto it = s.begin(); it != s.end(); it++)
				{
					if (indexes[*it] < lru)
					{
						lru = indexes[*it];
						val = *it;
					}
				}


				s.erase(val);


				s.insert(page[i]);


				pagefaults++;
			}


			indexes[page[i]] = i;
		}
	}

	return pagefaults;
}
int page_Faults_frist_in_out_algorithm(int page[], int n, int capacity)
{
	unordered_set<int> s;

	
	queue<int> indexes;
 
	int pagefaults = 0;
	for (int i = 0; i < n; i++)
	{
		if (s.size() < capacity)
		{
			
			if (s.find(page[i]) == s.end())
			{
				
				s.insert(page[i]);

				
				pagefaults++;

				
				indexes.push(page[i]);
			}
		}

		
		else
		{
			
			if (s.find(page[i]) == s.end())
			{
				
				int value = indexes.front();
				indexes.pop();
 
				s.erase(value);

				s.insert(page[i]);

				
				indexes.push(page[i]);

				 
				pagefaults++;
			}
		}
	}

	return pagefaults;
}

int main()
{
	int* page;
	int capacity;
	int n;

		string choice1;
		string choice2;
		do {
		cout << "enter the size of pages" << endl;
		cin >> n;
		page = new int[n];
		page_size_values(page, n);
		cout << "enter the size of capacity" << endl;
		cin >> capacity;
		cout << "there are three algoritums of page replacement : frist in frist out algorithum , leaset used algorithum and optimal algoritum" << endl;
		cout << "the user has to choose between the there " << endl;
		cout << "by entering the word fifo means using frist in frist out algorithum" << endl;
		cout << "by entering the word lru means using leaset used  algorithum" << endl;
		cout << "by entering the word opt means using optimal algorithum" << endl;
		cout << "enter the algorithum you want" << endl;
		cin >> choice1;
		if (choice1 == "fifo")
		{
			cout << "the frist in frist out algorithum :" << page_Faults_frist_in_out_algorithm(page, n, capacity) << endl;
		}
		else if (choice1 == "opt")
		{
			cout << "the optimal algorithum :" << endl;
			optimalPage(page, n, 4);
		}
		else if (choice1 == "lru")
		{
			cout << "the leaset recently used algorithum " << page_Faults_least_recently_used(page, n, capacity) << endl;
		}
		else
		{
			cout << "wrong word";
		}
		cout << "do you want to try again" << endl;
		cin >> choice2;

		} while (choice2 == "yes");
		if (choice2=="no")
		{
			cout << "thanks for using application" << endl;
		}

}