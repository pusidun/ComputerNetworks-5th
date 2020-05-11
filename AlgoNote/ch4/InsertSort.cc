#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
using namespace std;

void insertSort(vector<int>& vec) {
  int len = vec.size();
  if (len == 0) return;
  for (int i = 1; i < len; ++i) {
    int pivot = vec[i], j = i - 1;
    while (vec[j] > pivot) {
      vec[j + 1] = vec[j];
      --j;
    }
    vec[j + 1] = pivot;
  }
}

void printVec(vector<int>& vec) {
  for (auto& elem : vec) {
    cout << elem << " ";
  }
  cout << endl;
}

int main() {
  srand(time(NULL));
  vector<int> nums;
  for (int i = 0; i < 20; ++i) {
    nums.push_back(random() % 200);
  }
  cout << "befor sort" << endl;
  printVec(nums);
  insertSort(nums);
  cout << "after insert sort" << endl;
  printVec(nums);
  return 0;
}
