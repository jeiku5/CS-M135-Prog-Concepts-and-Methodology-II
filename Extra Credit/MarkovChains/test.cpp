#include "pch.h"

#include <cstdlib> 
#include <set>

#include "MarkovChain.h"

TEST(PickRandomWordTest, LotteryWorks) {
	srand(0);
	wordsAndCounts_t first { { "first", 1000 } };
	ASSERT_STREQ("first", pickRandomWord(first).c_str());

	wordsAndCounts_t second{ { "first", 1000 }, {"second", 100000} };
	ASSERT_STREQ("second", pickRandomWord(second).c_str());

	srand(1);
	wordsAndCounts_t third{ {"first", 1}, {"second", 1}, {"third", 1}};
	ASSERT_STREQ("third", pickRandomWord(third).c_str());
}

string joinVector(const vector<string>& vec) {
	// TODO: use
	// return vec | views::join_with(' ') | ranges::to<string>();
	// come C++23.
	string out = "";
	for (auto it = vec.begin(); it != vec.end(); advance(it, 1)) {
		out += *it;
		if (next(it, 1) != vec.end()) {
			out += " ";
		}
	}
	return out;
}

void assertTwoWordsAndCountsAreEqual(const chains_t& chains, const vector<string>& chain, const wordsAndCounts_t& wordsAndCountsExpected) {
	const auto& wordsAndCountsActual = chains.at(chain);
	const string chainStr = joinVector(chain);
	ASSERT_EQ(wordsAndCountsActual.size(), wordsAndCountsExpected.size()) << "Words and counts sizes for chain \"" << chainStr << "\" do not match. Got a words and count size of " << wordsAndCountsActual.size() << " , expected one of size " << wordsAndCountsExpected.size();

	for (const auto& [word, count] : wordsAndCountsExpected) {
		ASSERT_TRUE(wordsAndCountsActual.contains(word)) << word << " not found in actual words and counts for chain \"" << chainStr << "\"";
		const auto actualCount = wordsAndCountsActual.at(word);
		ASSERT_EQ(count, actualCount) << "For chain \"" << chainStr << "\", counts for word \"" << word << "\" differ. Expected " << count << ", but got " << actualCount;
	}
}

TEST(ChainInitializationTest, 3GramChainsLookGood) {
	srand(0);
	MarkovChain mc(3);
	const vector<string> words = readCorpus("corpus_small.txt");
	mc.initializeChains(words);
	const auto& chains = mc.getChains();

	assertTwoWordsAndCountsAreEqual(chains, { "The", "Dursleys", "had" }, { {"a", 1}, {"everything", 1} });
	assertTwoWordsAndCountsAreEqual(chains, { "on", "drills", "that" }, { {"morning.", 1}, {"afternoon", 1} });
	assertTwoWordsAndCountsAreEqual(chains, { "He", "was", "sure" }, { {"there", 1}, {"it", 1} });
	assertTwoWordsAndCountsAreEqual(chains, { "a", "couple", "of" }, { {"them", 1} });
	
	ASSERT_FALSE(chains.contains({ "this", "doesn't", "exist" }));
}

TEST(GenerationTest, RejectsEmptyMarkovChain) {
	srand(0);
	MarkovChain mc(10);
	const vector<string> words = readCorpus("corpus_small.txt");
	ASSERT_THROW({
		try {
			mc.generateText(100);
		} catch (const EmptyMarkovChainException& e) {
			// and this tests that it has the correct message
			ASSERT_STREQ("Markov chain is empty! Did you remember to initialize it?", e.what());
			throw;
		}
	}, EmptyMarkovChainException);
}
TEST(GenerationTest, RejectsOverfitting) {
	srand(0);
	MarkovChain mc(10);
	const vector<string> words = readCorpus("corpus_small.txt");
	mc.initializeChains(words);
	ASSERT_THROW({
		try {
			mc.generateText(100);
		} catch (const OverfittingException& e){
			// and this tests that it has the correct message
			ASSERT_STREQ("Order was too high! Overfitting occured. Only one candidate was available at each step.", e.what());
			throw;
		}
	}, OverfittingException);
}

TEST(GenerationTest, Generate0Grams) {
	srand(0);
	MarkovChain mc(0);
	const vector<string> words = readCorpus("corpus_small.txt");
	mc.initializeChains(words);
	const auto& chains = mc.getChains();
	ASSERT_EQ(chains.size(), 1) << "Expected 0-grams chains to have a single key.";

	const auto numUniqueWords = set(words.begin(), words.end()).size();

	const auto onlyValueSize = chains.at({ }).size();
	ASSERT_EQ(numUniqueWords, onlyValueSize) << "0-grams chain empty vector value should be the size of the words, which is " << numUniqueWords << ", but it was " << onlyValueSize;
	ASSERT_STREQ(mc.generateText(100).c_str(), "parking something but sister, did to mirror. for picked them It half of home, the up for are to that Mr. his in When else. that secretary Mr. made their couldn't someone \"Little his stunt he'd home, him! fingers keeping see mind. they today! allowed at gossiped road, wasn't excitedly, Fear sign Dursleys Dursley in road, someone had Dursley, thing thinking... Harry them his He kiss newscaster Dudley good doughnut be stood their seen the \"Little to a didn't Dursleys since birds seemed Mrs. when again. to buy screaming was. spying normal, He Grunnings, office, Dursley by man was with");
}
TEST(GenerationTest, Generate1Grams) {
	srand(0);
	MarkovChain mc(1);
	const vector<string> words = readCorpus("corpus_small.txt");
	mc.initializeChains(words);
	ASSERT_STREQ(mc.generateText(100).c_str(), "He didn't improve his car and up his briefcase, pecked Mrs. Dursley wondered. Trying to the building at the nation's owls have been a bag, that the man with her sister. He didn't move. It stared back. As Mr. Dursley stood rooted to see the cloudy sky outside the sign; cats couldn't see that the Grunnings parking lot, his most boring tie for work, and it had never even seen in his car and backed out of number when he caught a couple of strangely dressed in very useful as unDursleyish as she wrestled a screaming Dudley into the living");
}

TEST(GenerationTest, Generate2Grams) {
	srand(0);
	MarkovChain mc(2);
	const vector<string> words = readCorpus("corpus_small.txt");
	mc.initializeChains(words);
	ASSERT_STREQ(mc.generateText(100).c_str(), "Dursley around the middle and walked off. Mr. Dursley gave himself a grin. \"Most mysterious. And now, over to Jim McGuffin with the weather. Going to be a lot harder to concentrate on drills that afternoon and when he thought he'd stretch his legs and walk across the road, he watched the cat out of his mind back on drills. Mr. Dursley stood rooted to the window in his mirror. It was now having a tantrum and throwing his cereal at the walls. \"Little tyke,\" chortled Mr. Dursley loudly. The cat didn't move. It just gave him a stern look.");
}

TEST(GenerationTest, Generate3Grams) {
	srand(0);
	MarkovChain mc(3);
	const vector<string> words = readCorpus("corpus_small.txt");
	mc.initializeChains(words);
	ASSERT_STREQ(mc.generateText(100).c_str(), "Dudley mixing with a child like that. When Mr. and Mrs. Dursley, of number four, the first thing he saw -- and it didn't improve his mood -- was the tabby cat he'd spotted that morning. It was now sitting on his garden wall. He was sure there were lots of people called Potter who had a son called Harry. Come to think of it, he wasn't even sure his nephew was called Harry. He'd never even seen the boy. It might have been Harvey. Or Harold. There was no point in worrying Mrs. Dursley; she always got so upset");
}

TEST(GenerationTest, Generate5GramsOnLargeCorpus) {
	srand(0);
	MarkovChain mc(5);
	const vector<string> words = readCorpus("corpus.txt");
	mc.initializeChains(words);
	ASSERT_STREQ(mc.generateText(100).c_str(), "\" Hagrid shuddered. \"Don' make me say it again. Anyway, this -- this wizard, about twenty years ago now, started lookin' fer followers. Got 'em, too -- some were afraid, some just wanted a bit o' his power, 'cause he was gettin' himself power, all right. Dark days, Harry. Didn't know who ter trust, didn't dare get friendly with strange wizards or witches... terrible things happened. He was takin' over. 'Course, some stood up to him -- an' he killed 'em. Horribly. One o' the only safe places left was Hogwarts. Reckon Dumbledore's the only one You-Know-Who was ever afraid");
}