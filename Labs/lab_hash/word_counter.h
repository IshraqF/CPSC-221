/**
 * @file word_counter.h
 * Definition of the WordFreq class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */
#ifndef _WORDFREQ_H_
#define _WORDFREQ_H_

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "lphashtable.h"
#include "schashtable.h"
#include "textfile.h"

/**
 * WordFreq: counts the frequency with which words appear in a file.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */
template <template <class K, class V> class Dict>
class WordFreq {
public:
    /**
     * Constructs a WordFreq from the given filename.
     *
     * @param filename File to read in words from.
     */
    WordFreq(const std::string& filename);

    /**
     * Returns all words, along with their frequencies, that are above
     * a given threshold.
     *
     * @param threshold The frequency a word must be *at or above* in
     *  order to be added to the returned vector.
     * @return A vector of (string, int) pairs that represent words and
     *  their frequencies, filtered to only include those words with
     *  frequencies *at or above* threshold.
     */
    std::vector<std::pair<std::string, int>> getWords(int threshold);

    Dict<std::string, int> dict;
};
#include "word_counter.cpp"
#endif