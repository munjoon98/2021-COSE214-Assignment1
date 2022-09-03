#include<stdio.h>
#include<stdlib.h>
#include<tuple>
#include<limits.h>
using namespace std;
 
tuple<int, int, int> find_maximum_crossing(int a[], int low, int mid, int high) {
	int left_sum = INT_MIN;
	int max_left, max_right;
	int sum = 0;
	for (int i = mid; i >= low; i--) {
		sum += a[i];
		if (sum > left_sum) {
			left_sum = sum;
			max_left = i;
		}
	}
	int right_sum = INT_MIN;
	sum = 0;
	for (int i = mid + 1; i <= high; i++) {
		sum += a[i];
		if (sum > right_sum) {
			right_sum = sum;
			max_right = i;
		}
	}
	return make_tuple(max_left, max_right, left_sum + right_sum);
}
 
tuple<int, int, int> find_maximum_subarray(int a[], int low, int high) {
	if (high == low) return make_tuple(low, high, a[low]);
	else {
		int mid = (low + high) / 2;
		auto left_ans = find_maximum_subarray(a, low, mid);
		auto right_ans = find_maximum_subarray(a, mid + 1, high);
		auto cross_ans = find_maximum_crossing(a, low, mid, high);
		if (get<2>(left_ans) >= get<2>(right_ans) && get<2>(left_ans) >= get<2>(cross_ans)) return left_ans;
		else if (get<2>(left_ans) <= get<2>(right_ans) && get<2>(right_ans) >= get<2>(cross_ans)) return right_ans;
		else return cross_ans;
	}
}
 
int main() {
 
	int n;
	scanf("%d", &n);
	int* arr = (int*)malloc(sizeof(int) * n);
 
	for (int i = 0; i < n; i++) {
		int num;
		scanf("%d", &arr[i]);
	}
 
	if (n == 0) return 0;
	auto answer = find_maximum_subarray(arr, 0, n - 1);
 
	printf("%d\n%d\n%d\n", get<0>(answer), get<1>(answer), get<2>(answer));
	return 0;
}
