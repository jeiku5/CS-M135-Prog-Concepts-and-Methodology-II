#pragma once
#include <exception>
#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

// a type describing a set of words and how many times each one occurs.
typedef unordered_map<string, unsigned int> wordsAndCounts_t;

// maps each chain of words to its corresponding next words and how often
// each of those said words was observed to appear in the corpus.
typedef map<vector<string>, wordsAndCounts_t> chains_t;

class MarkovChain {
public:
	/**
	 * Initialize the Markov Chain class.
     *
     * @param order Size of n-grams/ngrams to examine. For example:
	 *   * 0 would mean that we choose a random word each time when generating text.
	 *   * 1 would mean that we look only word back to determine the next word.
	 *   * 2 would mean that we look at the previous 2 words to determine the next word.
     */
	MarkovChain(const unsigned int order) : order(order) {}

	/**
	 * Initialize the Markov Chains.
	 * 
	 * A tokenized corpus of ["first", "second", "third", "first", "second", "fourth"]
	 * with an order of 2 (so bigrams) should be looped over like:
	 *   * ["first", "second"] -> "third"
	 *   * ["second", "third"] -> "first"
	 *   * ["third", "first"] -> "second"
	 *   * ["first", "second"] -> "fourth"
	 * And would be represented by the following data structure:
	 * {["first", "second"]: {"third": 1, "fourth": 1}, ["second", "third"]: {"first": 1}, ["third", "first"]: {"second": 1}}
	 * 
	 * @param words Words as they appeared in the corpus.
	 */
	void initializeChains(const vector<string>& words);

	/**
     * Generate some text!
     *
     * @param length The number of words to generate.
	 * 
	 * @return generated text.
	 * 
	 * @throws EmptyMarkovChainException If this is called without the Markov Chain having been initialized first.
	 * @throws OverfittingException If overfitting occurs.
     */
	string generateText(const unsigned int length) const;

	chains_t getChains() const {
		return chains;
	}

private:
	const unsigned int order;
	chains_t chains;
};

/**
 * Read the corpus and tokenize it into a sequence of words.
 *
 * @param fileName The file name containing the corpus.
 * 
 * @return Sequence of tokenized words.
 * 
 * @throws runtime_error If it can't open the file.
 */
vector<string> readCorpus(const string fileName);

/**
 * Pick a random word using a lottery.
 * 
 * Treat number of occurences of each word as number of tickets it gets in the lottery to be selected.
 * Words that were seen more often in the corpus should have a better chance of being selected than words seen less often in the corpus.
 *
 * @param wordsAndCounts_t A map from each word to how often it was seen in the corpus after a certain chain of words.
 * 
 * @return The random word.
 * 
 * @throws runtime_error If it can't select a random word. Throw this as a failsafe at the end of your loop (if you use one) to catch bugs.
 */
string pickRandomWord(const wordsAndCounts_t& wordsAndCounts);

// Overfitting happens when the order is too high for the size of the corpus text.
// With overfitting, at each iteration, there is only one candidate next word, and the entire generated sample ends up just being a substring of the corpus.
class OverfittingException : public exception {
private:

public:
    OverfittingException() {}

    // Override the what() method to return our message 
    const char* what() const throw() {
        return "Order was too high! Overfitting occured. Only one candidate was available at each step.";
    }
};

// For when the user attempts to generate text without initializing the Markov Chain.
class EmptyMarkovChainException : public exception {
private:

public:
	EmptyMarkovChainException() {}

	// Override the what() method to return our message 
	const char* what() const throw() {
		return "Markov chain is empty! Did you remember to initialize it?";
	}
};