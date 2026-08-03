# Markov Chains

## Goal

Generate text from a corpus (this means body of text) that never occurs in
the corpus, but resembles it. We'll use the first few Harry Potter books to
train our model and then generate text that seems like it could come out of
Harry Potter.

This is similar to what ChatGPT does! ChatGPT uses a Generative Pre-trained
Transformer (GPT) to implements its LLM, but we will be using a simpler idea
called the Markov chain.

Our goal is to implement a language model and then play with a parameter to
see how it affects the generated text.

## Markov Chains

A Markov chain or process is a stochastic (random) model that describes a
sequence of possible events in which the probability of each event depends
only on the state attained in the previous event.

The fundamental idea here is that given a word or series of words, we want
to randomly generate the next word. The next word should make sense given
the data that we trained our model on.

## Reading

Please read
[this page](https://sookocheff.com/post/nlp/ngram-modeling-with-markov-chains/)
for an explanation of N-grams and some pseudocode.

## N-grams

N-grams for a given N just means how many words represent a state. From that
state, we then decide what word to generate next.

0-grams would mean that there is no state. To generate each word, we just pick
a random word from the corpus.

1-grams would mean that each state is represented by a single word. For example,
if the current state is ["I"], you can imagine that the next few words could be
"am", "was", "were". Once the model generates the next word (say "am"), it then
uses "am" as the jumping off point. After "am" could come something like "happy"
or "hungry". Transitions from one state to the next are more or less probable
depending on how often they occur in the corpus. We might expect a very happy
book to have a very high probability of generating the word "happy" after "am"
relative to the probability of generating "sad" after "am".

2-grams would mean that each state is represented by 2 words, so we might look
at a state like ["I", "am"], which we will represent as a vector. The added
"context" of "I" will impact the next word that will be generated.

As N increases, so does the quality of generated text.

A problem occurs however. When N gets high enough, any state will only have
a single state to transition to. When that happens, any sequence of text we
generate will just be taken from the corpus verbatim. We can call this
[overfitting](https://en.wikipedia.org/wiki/Overfitting).

## Training

To train our model, we have to dice up the corpus into states and probability
transitions. For example, given two training sentences:
* I was hungry because I skipped breakfast.
* I was hurrying because I was late.

We would end up with bigrams (2-grams) that look like this:
* ["I", "was"] -> "hungry"/"hurrying" (equal probability).
* ["was", "hungry"] -> "because" (100% probability).
* ["was", "hurrying"] -> "because" (100% probability).
* ["because", "I"] -> "skipped"/"was" (equal probability).
* etc.

## Lottery system

To determine what next state to go to from a state, we will use a lottery
system. Read [here](https://en.wikipedia.org/wiki/Lottery_scheduling) to learn
about a good use of lottery tickets in computing.

In the previous bigram example, given the state of ["I", "was"], both "hungry"
and "hurrying" will have a single lottery ticket. Let's say that "hungry" has
ticket number 0, and "hurrying" has ticket number 1. We then generate a
a random number between 0 and 1 (inclusive both ends), whichever word has
the winning ticket number is the word we will choose. If the winning ticket
was number 1, we'd go from state ["I", "was"] to state ["was", "hurrying"].

## Running

Two main functions are included. One is for running unit tests. The other is
for generating text. Play around with the "order" parameter, which represents
"N". You can also modify which corpus to use. Using the smaller corpus will
make the program run faster, so that may increase your iteration speed. You
can also supply your own corpus.

## Doing the assignment

* Read the function descriptions in [MarkovChain.h](./MarkovChain.h).
* Fill in the designated spots in [MarkovChain.cpp](./MarkovChain.cpp).
* Modify [Main.cpp](./Main.cpp) to run unit tests and execute your program on
  corpuses.
