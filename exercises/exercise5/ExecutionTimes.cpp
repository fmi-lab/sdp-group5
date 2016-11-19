#include <cassert>
#include <cstring>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

void insertionSort_n2(int *arr, int size) {
	if (!arr || size < 2)
		return;
	int j;
	for (int i = 1; i < size; i++) {
		j = i;
		while (j > 0 && arr[j] < arr[j - 1]) {
			int temp = arr[j];
			arr[j] = arr[j - 1];
			arr[j - 1] = temp;
			j--;
		}
	}
}

void bubbleSort_n2(int* arr, int size)
{
	if (!arr || size < 2)
		return;

	for (int i = 0; i < size - 1; i++)
	{
		for (int j = size - 1; j > i; j--)
		{
			if (arr[j] < arr[j-1]) {
				int temp = arr[j - 1];
				arr[j - 1] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

void merge(int *arr, int start, int end) {
	int *temp = new int[end-start + 1];
	int middle = start + (end - start) / 2;
	int left = start, right = middle + 1, tempIndex = 0;

	//Perform the merging procedure
	while (left <= middle && right <= end) {
		temp[tempIndex++] = (arr[left] < arr[right] ? arr[left++] : arr[right++]);
	}

	while (left <= middle) {
		temp[tempIndex++] = arr[left++];
	}
	while (right <= end) {
		temp[tempIndex++] = arr[right++];
	}
	//After the merging we got the sorted array in temp

	left = start; //< we fix left to be the start of the part we sort now
	int i = 0; //< we start from 0 in the temp array

	//Copy the elements merged in the temp array back in the one we sort -> v
	while (i < tempIndex && left <= end) {
		arr[left++] = temp[i++];
	}
	delete[] temp;
}
void mergeSort_nlogn(int *arr, int start, int end) {
	if (start == end) {
		return;
	}
	int middle = start + (end - start) / 2;
	mergeSort_nlogn(arr, start, middle);
	mergeSort_nlogn(arr, middle + 1, end);
	merge(arr, start, end);
}

void print(const int *arr, int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int randNum() {
	static std::uniform_int_distribution<> distrib;
	static std::mt19937 eng;
	return distrib(eng);
}

void testEverything() {
	const int N = 100;
	int arr[N];
	for (int i = 0; i < N; i++) {
		arr[i] = randNum();
	}
	print(arr, N);

	insertionSort_n2(arr, N);
	assert(std::is_sorted(arr, arr + N));

	std::random_shuffle(arr, arr + N);
	assert(!std::is_sorted(arr, arr + N));
	bubbleSort_n2(arr, N);
	assert(std::is_sorted(arr, arr + N));

	std::random_shuffle(arr, arr + N);
	mergeSort_nlogn(arr, 0, N - 1);
	assert(std::is_sorted(arr, arr + N));

	std::random_shuffle(arr, arr + N);
	std::sort(arr, arr + N);
	assert(std::is_sorted(arr, arr + N));
}

int main() {
	
	//testEverything();

	int N = 10000;
	printf("\nE X E C U T I O N    T I M E S: \n\n");
	for (int i = 0; i < 3; i++) {
		int *arr = new int[N];

		for (int i = 0; i < N; i++) {
			arr[i] = randNum();
		}

		using clock = std::chrono::high_resolution_clock;
		clock::time_point start, end;

		printf("Size = %d\n\n", N);

		std::random_shuffle(arr, arr + N);

		start = clock::now();
		std::sort(arr, arr + N);
		end = clock::now();
		printf("std::sort time: %dms\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

		std::random_shuffle(arr, arr + N);

		start = clock::now();
		mergeSort_nlogn(arr, 0, N - 1);
		end = clock::now();

		printf("MergeSort time: %dms\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());


		std::random_shuffle(arr, arr + N);

		start = clock::now();
		insertionSort_n2(arr, N);
		end = clock::now();
		printf("InsertionSort time: %dms\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

		std::random_shuffle(arr, arr + N);

		start = clock::now();
		bubbleSort_n2(arr, N);
		end = clock::now();
		printf("BubbleSort time: %dms\n\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

		N *= 10;
		delete[] arr;
	}

}