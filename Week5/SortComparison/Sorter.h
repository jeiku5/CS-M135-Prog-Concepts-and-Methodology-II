#pragma once

#include <string>
#include <vector>

using namespace std;

class Sorter {
public:
	/**
	 * Uses the insertion sort algorithm to sort part or all of a list in ascending
	 * order.
	 *
	 * @param data
	 *            The list of elements to sort
	 * @param fi
	 *            Index of the first element to be sorted.
	 * @param n
	 *            The number of elements in the section to be sorted.
	 */
	static void insertionSort(vector<string>& data, const size_t fi, const size_t n);

	/**
	 * Uses the quick sort algorithm to sort all or part of the data in ascending
	 * order. quickSort() must:
	 *
	 * a) Call the insertionSort() function for segments of size 63 or less.
	 *
	 * b) Call the partition() function to do its partitioning.
	 *
	 * @param data
	 *            The list of elements to sort
	 * @param fi
	 *            Index of the first element to be sorted.
	 * @param n
	 *            The number of elements in the section to be sorted.
	 */
	static void quickSort(vector<string>& data, const size_t fi, const size_t n);

	/**
	 * Partitions part (or all) of the list. The range of indices included in the
	 * partitioning is [firstIndex, firstIndex + numberToPartition - 1].
	 *
	 * partition() ** must ** use the median-of-three method to prevent O(n^2)
	 * running time for sorted data sets.
	 *
	 *
	 *
	 * @param data
	 * @param fi
	 * @param n
	 * @return The index, relative to data[0], where the pivot value is located at
	 *         the end of this partitioning.
	 */
	static size_t partition(vector<string>& data, const size_t fi, const size_t n);

	/**
	 * Uses the merge sort algorithm to sorts part or all of a list in ascending
	 * order. mergeSort() must:
	 *
	 * a) Call the insertionSort() segments of size 63 or less.
	 *
	 * b) Call the merge() function to do its merging.
	 *
	 * @param data
	 *            list of elements to sort
	 * @param fi
	 *            Index of the first element to be sorted.
	 * @param n
	 *            The number of elements in the section to be sorted.
	 */
	static void mergeSort(vector<string>& data, const size_t fi, const size_t n);

	/**
	 * Merges two sorted segments into a single sorted segment. The left and right
	 * segments are contiguous.
	 *
	 * @param data
	 *            The list of elements to merge
	 * @param fi
	 *            Index of the first element of the left segment.
	 * @param nl
	 *            The number of elements in the left segment.
	 * @param nr
	 *            The number of elements in the right segment.
	 */
	static void merge(vector<string>& data, const size_t fi, const size_t nl, const size_t nr);

	/**
	 * EXTRA CREDIT
	 *
	 * Use the heap sort algorithm to sort the list in ascending order. This method
	 * must use the heapify() method for initial heapification.
	 *
	 * @param data
	 *            The list of elements to sort
	 */
	static void heapSort(vector<string>& data);

	/**
	 * EXTRA CREDIT
	 *
	 * Heapifies the given vector.
	 *
	 * @param data
	 *            The vector to heapify.
	 */
	static void heapify(vector<string>& data);
};