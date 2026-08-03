#include "pch.h"

#include <algorithm>
#include <array>
#include <cctype> // for toupper
#include <chrono>
#include <iomanip>
#include <random>
#include <span>
#include <string>
#include <vector>

#include "Sorter.h"

// TODO: add timeouts for functions.

enum class SortAlgorithm {
    insertion,
    quick,
    merge,
    heap,
};

enum class DataOrder {
    sorted,
    random,
    duplicate,
};

// TODO: For completeness, perhaps verifyOrderMatches() should also check length differences.
// In a vacuum, we would expect it to return min(expectedWords.length, words.length) in that case,
// but output (printed) lines that mention the bad index will seem a little strange then 
// because the bad index won't exist in one of the containers.
static std::optional<size_t> verifyOrderMatches(const std::span<std::string> expectedWords, const std::span<std::string> actualWords) {
    if (expectedWords.size() != actualWords.size()) {
        return 0;
    }

    for (size_t i = 0; i < expectedWords.size(); ++i) {
        if (expectedWords[i] != actualWords[i])
            return i; // index where order mismatch occurred
    }

    return std::nullopt; // no mismatch found
}

static void checkForArrayPartNotSorted(const span<string> expectedWords, const span<string> words) {
    // Verify that the 20 elements starting at 1000 are sorted correctly
    const auto partResult = verifyOrderMatches({ expectedWords.begin() + 1000, expectedWords.begin() + 1020 }, {words.begin() + 1000, words.begin() + 1020});
    if (partResult.has_value()) {
        FAIL() << "The resulting array is out of order at index " << (1000 + partResult.value()) << endl
            << "One typical reason for this is an insertionSort() whose outer loop looks something like :" << endl << endl

            << "for (int i = fi + 1; i < n; i++)" << endl << endl

            << "Note that in this fragment, i is initialized with with an _index_, fi. But then it gets compared" << endl
            << "to a _count_, n. Indices cannot be compared with counts.To see why, consider the case where" << endl
            << "fi is 1000 and n is 8 (see https ://tinyurl.com/yf5w8zmm).  If i gets initialized to 1001 and then" << endl
            << "compared to 8 at the start of the loop, the loop will exit immediately." << endl << endl

            << "If you think that this analysis applies to your code, then you might want to consider the following" << endl
            << "outer loop fragment :" << endl << endl

            << "for (int i = fi + 1; i < fi + n; i++)" << endl << endl

            << "Another typical reason for this problem is that the inner loop keeps searching for the proper insertion" << endl
            << "point all the way back to the beginning of the array.But when sorting only part of the array, the last" << endl
            << "value to be compared should be at fi. I.e.decrement as long as j >= fi , not j >= 0." << endl;
    }
}

static void checkForWrongSectionSorted(const span<string> firstNWordsSorted, const span<string> words) {
    const auto firstNResult = verifyOrderMatches(firstNWordsSorted, {words.begin(), words.begin() + 20});
    if (!firstNResult.has_value()) {
        FAIL() << "The words from index 0 to 19 are sorted, but _only_ the words from 1000 to 1019 should be sorted." << endl
            << "One typical reason for this is that insertionSort() is initializing the array access" << endl
            << "index to 0 or 1 instead of fi + 1, so the wrong part of the array is being sorted.You can use this" << endl
            << "diagram(https://tinyurl.com/yf5w8zmm) to reason about sorting part of an array." << endl << endl

            << "If you think that this analysis applies to your code, then you might want to consider the following" << endl
            << "outer loop fragment :" << endl << endl

            << "for (int i = fi + 1; i < fi + n; i++)" << endl << endl

            << "Another typical reason for this problem is that the inner loop keeps searching for the proper insertion" << endl
            << "point all the way back to the beginning of the array.But when sorting only part of the array, the last" << endl
            << "value to be compared should be at fi. I.e.decrement as long as j >= fi , not j >= 0." << endl;
    }
}

static std::string createRandomString(const size_t length) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis('A', 'Z');
    std::string word(length, ' ');
    std::generate(word.begin(), word.end(), [&]() {
        return static_cast<char>(dis(gen));
    });
    return word;
}

static std::vector<std::string> createRandomStrings(const size_t n, const size_t wordLength) {
    // TODO: is this faster than calling createRandomString() because it shares
    // the random infrastructure between strings and saves a function call?
    // Perhaps the compiler optimizes away the function call.
    std::vector<std::string> words(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis('A', 'Z');

    for (int i = 0; i < n; ++i) {
        std::string word(wordLength, ' ');
        std::generate(word.begin(), word.end(), [&]() {
            return static_cast<char>(dis(gen));
            });
        words[i] = move(word);
    }
    return words;
}

static void standardSortTest(const SortAlgorithm sortAlgorithm, const int wordLength, const int minN, const int maxN, const int stepN,
    const int numSamplesPerTest, const DataOrder dataOrder, const bool ensureTimeRatioBelowThreshold,
    const double lastFirstTimeRatioThreshold, const bool printResults, std::span<size_t> wordCounts,
    std::span<double> elapsedTimes) {
    size_t testNdx = 0;

    // Printing sort type if printResults is true
    if (printResults) {
        switch (sortAlgorithm) {
        case SortAlgorithm::insertion:
            std::cout << std::endl << "Insertion Sort";
            break;

        case SortAlgorithm::quick:
            std::cout << std::endl << "Quick Sort";
            break;

        case SortAlgorithm::merge:
            std::cout << std::endl << "Merge Sort";
            break;

        case SortAlgorithm::heap:
            std::cout << std::endl << "Heap Sort";
            break;
        }
    }

    // Printing data order type
    switch (dataOrder) {
    case DataOrder::sorted:
        std::cout << " sorted data" << std::endl;
        break;
    case DataOrder::random:
        std::cout << " random data" << std::endl;
        break;
    case DataOrder::duplicate:
        std::cout << " duplicated data" << std::endl;
        break;
    }

    for (size_t count = minN; count <= maxN; count += stepN) {
        double sumTime = 0;
        // reuse the same words and expectedWords vectors between samples, but
        // fill them with different data each time.
        std::vector<std::string> words(count);
        std::vector<std::string> expectedWords(count);
        for (int ndx = 0; ndx < numSamplesPerTest; ndx++) {
            if (dataOrder == DataOrder::duplicate) {
                std::string word = createRandomString(wordLength);
                words.assign(count, word);
                expectedWords = words;
            } else {
                // Create random or sorted data
                words = createRandomStrings(count, wordLength);
                if (dataOrder == DataOrder::sorted) {
                    std::sort(words.begin(), words.end());
                    expectedWords = words;
                } else {
                    expectedWords = words;
                    std::sort(expectedWords.begin(), expectedWords.end());
                }
            }

            auto startTime = std::chrono::high_resolution_clock::now();
            switch (sortAlgorithm) {
            case SortAlgorithm::insertion:
                Sorter::insertionSort(words, 0, words.size());
                break;

            case SortAlgorithm::quick:
                Sorter::quickSort(words, 0, words.size());
                break;

            case SortAlgorithm::merge:
                Sorter::mergeSort(words, 0, words.size());
                break;

            case SortAlgorithm::heap:
                Sorter::heapSort(words);
                break;
            }
            auto endTime = std::chrono::high_resolution_clock::now();
            const double elapsedTime = std::chrono::duration<double>(endTime - startTime).count();
            sumTime += elapsedTime;
            // Verify order of sorted data
            const auto badNdx = verifyOrderMatches(expectedWords, words);
            if (badNdx.has_value()) {
                FAIL() << "Expected words and actual words differ at index " << badNdx.value()
                    << " , expected word: " << expectedWords[badNdx.value()] << " , actual word: " << words[badNdx.value()] << endl;
            }
        }
        wordCounts[testNdx] = count;
        elapsedTimes[testNdx] = sumTime / numSamplesPerTest;
        testNdx++;
    }

    const double countRatio = static_cast<double>(wordCounts.back()) / static_cast<double>(wordCounts.front());
    const double timeRatio = elapsedTimes.back() / elapsedTimes.front();

    if (printResults) {
        std::cout << "\tN = " << wordCounts.front() << ", time = " << elapsedTimes.front() << " sec" << std::endl;
        if (wordCounts.size() > 1) {
            std::cout << "\tN = " << wordCounts.back() << ", time = " << elapsedTimes.back() << " sec" << std::endl;
            std::cout << "\tCount: " << countRatio << "x, Time: " << timeRatio << "x" << std::endl;
        }
    }

    if (wordCounts.size() < 2) {
        // can't enforce ratio for different size arrays if only one size was tested.
        return;
    }

    // Check if time ratio exceeds the threshold
    bool failedTimeRatioRequirement = false;
    ostringstream failureMessage;

    if (ensureTimeRatioBelowThreshold && timeRatio > lastFirstTimeRatioThreshold) {
        failedTimeRatioRequirement = true;
        failureMessage << "Expected the ratio of the time for " << wordCounts.back()
            << " data elements to the time for " << wordCounts[0] << " data elements to be <= "
            << lastFirstTimeRatioThreshold << ", but it was measured as " << timeRatio << ".";
    } else if (!ensureTimeRatioBelowThreshold && timeRatio < lastFirstTimeRatioThreshold) {
        failedTimeRatioRequirement = true;
        failureMessage << "Expected the ratio of the time for " << wordCounts.back()
                << " data elements to the time for " << wordCounts[0] << " data elements to be >= "
                << lastFirstTimeRatioThreshold << ", but it was measured as " << timeRatio << ".";
    }

    if (failedTimeRatioRequirement) {
        FAIL() << failureMessage.str();
    }
}

TEST(PartitionTest, TestPartition) {
    vector<string> words = createRandomStrings(1024, 5); // 10);
    auto expectedWords(words);
    std::sort(expectedWords.begin(), expectedWords.end());

    const size_t startNdx = 512;
    const size_t segmentLength = 256;
    const size_t indexOfPivot = Sorter::partition(words, startNdx, segmentLength);

    // Verify that all values before indexOfPivot are <= words[indexOfPivot]
    for (size_t ndx = startNdx; ndx < indexOfPivot; ndx++) {
        if (words[ndx] > words[indexOfPivot]) {
            ASSERT_TRUE(words[ndx] <= words[indexOfPivot]);
        }
    }

    // Verify that all values after indexOfPivot are >= words[indexOfPivot]
    for (size_t ndx = indexOfPivot + 1; ndx < (startNdx + segmentLength - 1); ndx++) {
        if (words[ndx] < (words[indexOfPivot])) {
            ASSERT_TRUE(words[ndx] >= words[indexOfPivot]);
        }
    }

    // Verify that a single partition does not result in a sorted array.
    words = createRandomStrings(100000, 5); // 10);
    Sorter::partition(words, 0, 100000);
    const auto badNdx = verifyOrderMatches(expectedWords, words);
    if (!badNdx.has_value()) {
        FAIL() << "Partioning the vector resulted in a fully sorted vector." << endl;
    }
}

TEST(QuickSortTest, TestQuickSort) {
    const int wordLength = 5;
    const int minN = 150000;
    const int maxN = 600000;
    const int stepN = 450000;
    const int numSamplesPerTest = 3;
    const int numTests = (maxN - minN) / stepN + 1;
    vector<size_t> wordCounts(numTests);
    vector<double> elapsedTimes(numTests);
    vector<double> elapsedTimesSortedData(numTests);

    standardSortTest(SortAlgorithm::quick, wordLength, minN, maxN, stepN, numSamplesPerTest,
        DataOrder::random, true, 10, true, wordCounts, elapsedTimes);

    // Now verify that it handles sorted data sets properly.
    standardSortTest(SortAlgorithm::quick, wordLength, minN, maxN, stepN, numSamplesPerTest,
        DataOrder::sorted, true, 10, true, wordCounts, elapsedTimesSortedData);

   const double sortedFactor = 2.0;
   if (elapsedTimesSortedData.back() > sortedFactor * elapsedTimes.back()) {
       FAIL() << "Sorted-data time limit exceeded. Expected: <= " << std::fixed << std::setprecision(3)
           << (sortedFactor * elapsedTimes.back()) << " sec, but was "
           << elapsedTimesSortedData.back() << " sec. The time required to QuickSort "
           << wordCounts.back() << " already-sorted words must be less than "
           << sortedFactor << " times the time required to QuickSort "
           << wordCounts.back() << " words that are in random order.";
   }
}

TEST(QuickSortTest, TestQuickSortLarger) {
    const int wordLength = 10;
    const int minN = 1000000;
    const int maxN = 1000000;
    const int stepN = 1000000;
    const int numSamplesPerTest = 10;
    const int numTests = (maxN - minN) / stepN + 1;
    vector<size_t> wordCounts(numTests);
    vector<double> elapsedTimes(numTests);

    standardSortTest(SortAlgorithm::quick, wordLength, minN, maxN, stepN, numSamplesPerTest, DataOrder::random, true, 10, true,
        wordCounts, elapsedTimes);
}

TEST(QuickSortTest, TestQuickSortDuplicates) {
    const int wordLength = 10;
    const int minN = 150000;
    const int maxN = 600000;
    const int stepN = 450000;
    const int numSamplesPerTest = 3;
    const int numTests = (maxN - minN) / stepN + 1;
    vector<size_t> wordCounts(numTests);
    vector<double> elapsedTimes(numTests);

    standardSortTest(SortAlgorithm::quick, wordLength, minN, maxN, stepN,
        numSamplesPerTest, DataOrder::duplicate, true, 10, true,
        wordCounts, elapsedTimes);
}


TEST(InsertionSortTest, TestInsertionSortEntire) {
    const int wordLength = 5;
    const int minN = 10000;
    const int maxN = 40000;
    const int stepN = 30000;
    const int numSamplesPerTest = 2;
    const int numTests = (maxN - minN) / stepN + 1;
    vector<size_t> wordCounts(numTests);
    vector<double> elapsedTimes(numTests);

    standardSortTest(SortAlgorithm::insertion, wordLength, minN, maxN, stepN, numSamplesPerTest,
        DataOrder::random, false, 8.5, true, wordCounts, elapsedTimes);
}


TEST(InsertionSortTest, TestInsertionSortPartial) {
    const vector<string> originalWords = createRandomStrings(2000, 5);
    vector<string> firstNWordsSorted(originalWords.begin(), originalWords.begin() + 20);
    std::sort(firstNWordsSorted.begin(), firstNWordsSorted.end());

    auto expectedWords(originalWords);
    std::sort(expectedWords.begin() + 1000, expectedWords.begin() + 1020);

    auto words(originalWords);
    Sorter::insertionSort(words, 1000, 20);       // Should sort only the 20 words starting at 1000

    checkForWrongSectionSorted(firstNWordsSorted, words);

    checkForArrayPartNotSorted(expectedWords, words);
}

static void verifyIsHeap(const vector<string>& words, const size_t i) {
    const auto length = words.size();
    if ((2 * i + 1) >= length)
        return;

    if (words[i] < words[2 * i + 1])
        FAIL() << "heapify() failed. The parent (" << words[i] << ") is less than its left child ("
            << words[2 * i + 1] + ")." << endl;

    if ((2 * i + 2) < length) {
        if (words[i] < words[2 * i + 2])
            FAIL() << "heapify() failed. The parent (" << words[i] << ") is less than its right child ("
                << words[2 * i + 2] << ")." << endl;
    }

    verifyIsHeap(words, 2 * i + 1);
    if ((2 * i + 2) < length)
        verifyIsHeap(words, 2 * i + 2);
}

TEST(HeapifyTest, TestHeapify) {
    auto words = createRandomStrings(100000, 5); // 10);
    Sorter::heapify(words);
    verifyIsHeap(words, 0);
}

TEST(HeapSortTest, TestHeapSort) {
    const int wordLength = 5;
    const int minN = 150000;
    const int maxN = 600000;
    const int stepN = 450000;
    const int numSamplesPerTest = 3;
    const int numTests = (maxN - minN) / stepN + 1;
    vector<size_t> wordCounts(numTests);
    vector<double> elapsedTimes(numTests);

    standardSortTest(SortAlgorithm::heap, wordLength, minN, maxN, stepN, numSamplesPerTest,
        DataOrder::random, true, 10, true,
        wordCounts, elapsedTimes);
}

TEST(MergeTest, TestMerge) {
    const vector<string> originalWords { "M", "B", "Z", "A", "F", "D", "C", "P", "Q", "E", "V", "X" };

    vector<string> words(originalWords);

    vector<string> expectedWords = { words.begin() + 6, words.begin() + 12 };
    std::sort(expectedWords.begin(), expectedWords.end());

    Sorter::merge(words, 6, 3, 3);

    for (int ndx = 0; ndx < 6; ndx++)
        ASSERT_EQ(originalWords[ndx], words[ndx]);

    const auto badNdx = verifyOrderMatches(expectedWords, { words.begin() + 6, words.begin() + 12 });
    ASSERT_FALSE(badNdx.has_value()) << "The merged data is out of order at index " + badNdx.value();
}

TEST(MergeSortTest, TestMergeSort) {
    const int wordLength = 5;
    const int minN = 150000;
    const int maxN = 600000;
    const int stepN = 450000;
    const int numSamplesPerTest = 3;
    const int numTests = (maxN - minN) / stepN + 1;
    vector<size_t> wordCounts(numTests);
    vector<double> elapsedTimes(numTests);
    vector<double> elapsedTimesSortedData(numTests);

    standardSortTest(SortAlgorithm::merge, wordLength, minN, maxN, stepN, numSamplesPerTest,
        DataOrder::random, true, 10, true, wordCounts, elapsedTimes);

    standardSortTest(SortAlgorithm::merge, wordLength, minN, maxN, stepN, numSamplesPerTest,
        DataOrder::sorted, true, 10, true, wordCounts, elapsedTimesSortedData);

    const double sortedFactor = 0.95;
    if (elapsedTimesSortedData.back() > sortedFactor * elapsedTimes.back())
        FAIL() << "The elapsed time required to MergeSort " << wordCounts.back()
        << " already-sorted words must be less than " << sortedFactor
        << " times the time to MergeSort " << wordCounts.back()
        << " words that are in random order.";
}

TEST(MergeSortTest, TestMergeSortLarger) {
    const int wordLength = 10;
    const int minN = 1000000;
    const int maxN = 1000000;
    const int stepN = 1000000;
    const int numSamplesPerTest = 10;
    const int numTests = (maxN - minN) / stepN + 1;
    vector<size_t> wordCounts(numTests);
    vector<double> elapsedTimes(numTests);

    standardSortTest(SortAlgorithm::merge, wordLength, minN, maxN, stepN, numSamplesPerTest,
        DataOrder::random, true, 10, true, wordCounts, elapsedTimes);
}
