#include "pch.h"

#include "MarkovChain.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <stdexcept>
#include <vector>

using namespace std;

string pickRandomWord(const wordsAndCounts_t& wordsAndCounts) {
	unsigned int totalTickets = 0;
	for (const auto& [word, count] : wordsAndCounts) {
		totalTickets += count;
	}

	const unsigned int winningTicket = rand() % totalTickets;

	unsigned int ticketsSeenSoFar = 0;
	for (const auto& [word, count] : wordsAndCounts) {
		ticketsSeenSoFar += count;
		if (winningTicket < ticketsSeenSoFar) {
			return word;
		}
	}

	throw runtime_error("Could not pick a random word");
}

void MarkovChain::initializeChains(const vector<string>& words) {
	for (size_t i = 0; i + order < words.size(); i++) {
		const vector<string> ngram(words.begin() + i, words.begin() + i + order);
		const string& nextWord = words[i + order];
		chains[ngram][nextWord]++;
	}
}

static string joinWords(const vector<string>& words) {
	string out;
	for (size_t i = 0; i < words.size(); i++) {
		if (i > 0) {
			out += " ";
		}
		out += words[i];
	}
	return out;
}

string MarkovChain::generateText(const unsigned int length) const {
	if (chains.empty()) {
		throw EmptyMarkovChainException();
	}

	auto startingChain = chains.begin();
	advance(startingChain, rand() % chains.size());
	vector<string> generated = startingChain->first;

	bool everHadAChoice = false;
	while (generated.size() < length) {
		const vector<string> currentNgram(generated.end() - order, generated.end());
		const wordsAndCounts_t& nextWordsAndCounts = chains.at(currentNgram);

		if (nextWordsAndCounts.size() > 1) {
			everHadAChoice = true;
		}

		generated.push_back(pickRandomWord(nextWordsAndCounts));
	}

	// only overfitting if literally no step ever had more than one option
	if (!everHadAChoice) {
		throw OverfittingException();
	}

	return joinWords(generated);
}

vector<string> readCorpus(const string fileName) {
	ifstream file(fileName); // Open the file
	if (!file.is_open()) {
		cerr << "Unable to open file" << endl;
		throw runtime_error("Could not open file");
	}

	vector<std::string> words;
	string word;
	while (file >> word) { // Read word by word
		words.push_back(word); // Append word to the vector
	}

	file.close(); // Close the file

	return words;
}