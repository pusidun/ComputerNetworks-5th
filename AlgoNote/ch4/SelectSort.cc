#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
using namespace std;

void selectSort(vector<int>& vec) {
  int len = vec.size();
  if (len == 0) return;
  for (int i = 0; i < len - 1; ++i) {
    int minidx = i;
    for (int j = i + 1; j < len; ++j) {
      if (vec[j] < vec[minidx]) minidx = j;
    }
    if (minidx != i) swap(vec[minidx], vec[i]);
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
  selectSort(nums);
  cout << "after select sort" << endl;
  printVec(nums);
  return 0;
}
