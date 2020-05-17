#include<iostream>
using namespace  std;

// binary search
bool check(int x) {}

// [l, mid] [mid+1, r]
int binarySearchA (int l, int r, int nums[]) {
    while(l < r) {
        int mid = l + r >> 1;
        if(check(nums[mid])) r = mid;
        else l = mid + 1;
    }
    return l;
}

int binarySearchB(int l, int r, int nums[]) {
    while(l < r) {
        int mid = l + r + 1 >> 1;
        if(check(nums[mid])) r = mid - 1;
        l = mid;
    }
    return l;
}