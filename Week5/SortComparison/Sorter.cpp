#include "pch.h"

#include "Sorter.h"

#include <vector>

using namespace std;

void Sorter::insertionSort(vector<string>& data, const size_t fi, const size_t n) {
	for (size_t i = fi + 1; i < fi + n; i++) {
		string key = data[i];
		size_t j = i;
		while (j > fi && data[j - 1] > key) {
			data[j] = data[j - 1];
			j--;
		}
		data[j] = key;
	}
}

void Sorter::quickSort(vector<string>& data, const size_t fi, const size_t n) {
	if (n <= 63) {
		insertionSort(data, fi, n);
		return;
	}

	const size_t pivotIndex = partition(data, fi, n);
	const size_t leftCount = pivotIndex - fi;
	const size_t rightCount = (fi + n - 1) - pivotIndex;

	quickSort(data, fi, leftCount);
	quickSort(data, pivotIndex + 1, rightCount);
}

size_t Sorter::partition(vector<string>& data, const size_t fi, const size_t n) {
	const size_t last = fi + n - 1;
	const size_t mid = fi + (n - 1) / 2;

	// median of first/mid/last as pivot, so sorted input doesn't hit worst case
	if (data[mid] < data[fi]) swap(data[fi], data[mid]);
	if (data[last] < data[fi]) swap(data[fi], data[last]);
	if (data[last] < data[mid]) swap(data[mid], data[last]);
	swap(data[fi], data[mid]);

	const string pivot = data[fi];
	size_t i = fi;
	size_t j = last + 1;
	while (true) {
		do { i++; } while (i <= last && data[i] < pivot);
		do { j--; } while (data[j] > pivot);
		if (i >= j) break;
		swap(data[i], data[j]);
	}

	swap(data[fi], data[j]);
	return j;
}

void Sorter::mergeSort(vector<string>& data, const size_t fi, const size_t n) {
	if (n <= 63) {
		insertionSort(data, fi, n);
		return;
	}

	const size_t nl = n / 2;
	const size_t nr = n - nl;

	mergeSort(data, fi, nl);
	mergeSort(data, fi + nl, nr);
	merge(data, fi, nl, nr);
}

void Sorter::merge(vector<string>& data, const size_t fi, const size_t nl, const size_t nr) {
	const vector<string> left(data.begin() + fi, data.begin() + fi + nl);
	const vector<string> right(data.begin() + fi + nl, data.begin() + fi + nl + nr);

	size_t i = 0;
	size_t j = 0;
	size_t k = fi;
	while (i < nl && j < nr) {
		if (left[i] <= right[j]) {
			data[k++] = left[i++];
		}
		else {
			data[k++] = right[j++];
		}
	}
	while (i < nl) data[k++] = left[i++];
	while (j < nr) data[k++] = right[j++];
}

// sifts data[i] down until the subtree at i is a valid max-heap again
static void siftDown(vector<string>& data, size_t i, const size_t heapSize) {
	while (true) {
		size_t largest = i;
		const size_t left = 2 * i + 1;
		const size_t right = 2 * i + 2;

		if (left < heapSize && data[left] > data[largest]) largest = left;
		if (right < heapSize && data[right] > data[largest]) largest = right;
		if (largest == i) break;

		swap(data[i], data[largest]);
		i = largest;
	}
}

void Sorter::heapSort(vector<string>& data) {
	heapify(data);

	// move max to the end, shrink heap, repeat
	for (size_t end = data.size(); end > 1; end--) {
		swap(data[0], data[end - 1]);
		siftDown(data, 0, end - 1);
	}
}

void Sorter::heapify(vector<string>& data) {
	const size_t n = data.size();
	if (n < 2) return;

	// start at last parent, sift down to root (i-- > 0 avoids underflow at i=0)
	for (size_t i = n / 2; i-- > 0; ) {
		siftDown(data, i, n);
	}
}