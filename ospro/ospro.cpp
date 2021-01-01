#include<iostream> 
#include <unordered_set>
#include <unordered_map>
#include<vector>
#include<queue>
using namespace std;


 int FIFOAlg(int page_ref[], int num, int frames)
	{
		unordered_set<int> setof_ref;
		queue <int> memory;
		int pagefaults = 0;

		for (int i=0; i<num; i++)
		{

			if (memory.size() < frames)
			{

				if (setof_ref.find(page_ref[i]) == setof_ref.end())
				{
					setof_ref.insert(page_ref[i]);
					memory.push(page_ref[i]);
					pagefaults++;
				}
			}
			// perform FIFO
			
			else
			{

				if (setof_ref.find(page_ref[i]) == setof_ref.end())
				{
					int value = memory.front();
					setof_ref.erase(value);
					memory.pop();
					setof_ref.insert(page_ref[i]);
					memory.push(page_ref[i]);
					pagefaults++;
				}
			}
		}
		cout <<endl << "last frames are " << endl;
		while (!memory.empty()) {
			cout << memory.front()<<endl;
			memory.pop();
		}

		cout << endl;

		return pagefaults;
		}

 int LRUAlg(int page_ref[], int num, int frames)
 {
     unordered_set<int> ref;
	 // for lru refrences 
	 unordered_map<int, int> lru_indexes;

	 int pagefaults = 0;

	 for (int i = 0; i < num; i++)
	 {
		 if (ref.size() < frames)
		 {
			 if (ref.find(page_ref[i]) == ref.end())
			 {
				 ref.insert(page_ref[i]);
				 pagefaults++;
			 }
			 lru_indexes[page_ref[i]] = i;
		 }

		 //perform lru
		 else
		 {
			 if (ref.find(page_ref[i]) == ref.end())
			 {
				 int lru = INT_MAX, old_value;
				 for (auto j = ref.begin(); j != ref.end(); j++)
				 {
					 if (lru_indexes[*j] < lru)
					 {
						 lru = lru_indexes[*j];
						 old_value = *j;
					 }
				 }
				 
				 ref.erase(old_value);
				 ref.insert(page_ref[i]);
				 pagefaults++;
			 }
			 lru_indexes[page_ref[i]] = i;
		 }
	 }

	 cout << endl << "last frames are " << endl;

	// unordered_set<int> ::iterator itr;

	 for (auto itr = ref.begin(); itr != ref.end(); itr++) {
		 cout << (*itr) << endl;
	 }

	 return pagefaults;
 }


 bool search(int key, vector<int>& frames)
 {
	 for (int i = 0; i < frames.size(); i++)
		 if (frames[i] == key)
			 return true;
	 return false;
 }

 int predict(int page_ref[], vector<int>& frames, int page_num, int index)
 {
	 int recent = -1, farthest = index;

	 for (int i = 0; i < frames.size(); i++) {
		 int j;
		 for (j = index; j < page_num; j++) {
			 if (frames[i] == page_ref[j]) {
				 if (j > farthest) {
					 farthest = j;
					 recent = i;
				 }
				 break;
			 }
		 }

		 if (j == page_num)
			 return i;
	 }

	 if (recent == -1) {
		 return 0;
	 }
	 return recent;
 }

 int OptimalAlg(int page_ref[], int num, int frames)
 {
	 vector<int> Fr;
	 int hit = 0;

	 for (int i = 0; i < num; i++) {

		 // Page found in a frame : HIT 
		 if (search(page_ref[i], Fr)) {
			 hit++;
			 continue;
		 }
 
		 if (Fr.size() < frames)
			 Fr.push_back(page_ref[i]);
 
		 else {
			 int j = predict(page_ref, Fr, num, i + 1);
			 Fr[j] = page_ref[i];
		 }
	 }

	 cout << endl << "last frames are " << endl;

	 for (int i = 0; i < Fr.size(); i++) {
		 cout << Fr.at(i) << endl;
	 }

	 return num - hit ;
 }

/*void page_size_values(int pages[], int n)
{
	cout << "enter the pages" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> pages[i];
	}

}
*/


int main()
{

	int numofframes, processes;
	cout << "Enter number of frames\n";
	cin >> numofframes;
	cout << "Enter number of processes\n";
	cin >> processes;

	int *process= new int[processes];

	cout << "Enter processes\n";
	for (int i = 0; i < processes; i++) {
		cin >> process[i];
	}
	cout << "\n\n";
		
		cout << "enter 1 for fifo " << endl;
		cout << "enter 2 for lru " << endl;
		cout << "enter 3 for opt " << endl;
		int choice;
		cin >> choice;

		if (choice == 1)
		{
			cout << "page faults = " << FIFOAlg(process,processes,numofframes) << endl;
		}
		else if (choice == 2)
		{
			cout << "page faults = " << LRUAlg(process, processes, numofframes) << endl;
		}
		else if (choice == 3)
		{
			cout << "page faults = " << OptimalAlg(process, processes, numofframes) << endl;
		}
		else
		{
			cout << "error";
		}

}