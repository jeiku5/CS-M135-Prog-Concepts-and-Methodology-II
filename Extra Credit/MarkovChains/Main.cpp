#include "pch.h"

#include "MarkovChain.h"

#include <iostream>

using namespace std;

// driver code
int main2() {
    // modify n-gram/ngram size here
	const unsigned int order = 1;
	MarkovChain mc(order);
	// feel free to use the big corpus ("corpus.txt").
	const auto words = readCorpus("corpus_small.txt");
	mc.initializeChains(words);
	string generated;
	try {
		generated = mc.generateText(100);
	}
	catch (const OverfittingException& e) {
		cout << e.what() << endl;
	}
	cout << generated << endl;

	return 0;
}

// for running pre-written tests
int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}