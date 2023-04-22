#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "hashtable.h"
#include "schashtable.h"
#include "lphashtable.h"
#include "char_counter.h"
#include "word_counter.h"
#include "anagram_finder.h"

#include <algorithm>
#include <sstream>

using std::cout;
using std::endl;
using std::sort;
using std::map;
using std::set;

// Cause I'm lazy :^)
#define ff first
#define ss second

const string cc_file = "SherlockHolmes.txt";
static map<char,int> cc_expected = {
    {'a',36142},
    {'c',11103},
    {'d',19100},
    {'e',54944},
    {'h',29579},
    {'i',31248},
    {'l',17636},
    {'m',12155},
    {'n',29731},
    {'o',34869},
    {'r',25684},
    {'s',27965},
    {'t',40511},
    {'u',13636},
    {'w',11534},
};

const string wc_file = "metamorphoses.txt";
static map<string,int> wc_expected = {
    {"the",10473},
    {"of",5753},
    {"and",4739},
    {"to",3078},
    {"a",2246},
    {"in",1989},
    {"was",1706},
    {"his",1572},
    {"that",1548},
    {"her",1500},
    {"with",1456},
    {"is",1306},
    {"he",1241},
    {"by",1185},
};

const string anagram_file = "words.txt";
const string anagram_word = "retinas";
static set<string> anagram_expected = {
    "anestri",
    "asterin",
    "eranist",
    "nastier",
    "ratines",
    "resiant",
    "restain",
    "retains",
    "retinas",
    "retsina",
    "sainter",
    "stainer",
    "starnie",
    "stearin",
};

struct SortPair {
    template <typename F, typename S>
    bool operator()(pair<F,S> a, pair<F,S> b) {
        if (a.ss == b.ss) return a.ff < b.ff;
        return a.ss > b.ss;
    }
};
SortPair sorter;

TEST_CASE("charcount::schash", "[weight=0][part=charcount]"){
    CharFreq<SCHashTable> cf(cc_file);
    vector<pair<char, int>> ret = cf.getChars(10000);
    sort(ret.begin(), ret.end(), sorter);
    // Uncomment the following lines for debugging
    /*
    cout << "Character counts:" << endl;
    for (size_t i = 0; i < ret.size(); ++i) {
        cout << ret[i].ss << "\t" << ret[i].ff << endl;
    }
    */
    REQUIRE(cf.dict.shouldResize() == false);
    REQUIRE(ret.size() == cc_expected.size());
    for (auto elem : ret) {
        REQUIRE(elem.ss == cc_expected[elem.ff]);
    }
}

TEST_CASE("charcount::lphash", "[weight=0][part=charcount]"){
    CharFreq<LPHashTable> cf(cc_file);
    vector<pair<char, int>> ret = cf.getChars(10000);
    sort(ret.begin(), ret.end(), sorter);
    REQUIRE(ret.size() == cc_expected.size());
    REQUIRE(cf.dict.shouldResize() == false);
    for (auto elem : ret) {
        REQUIRE(elem.ss == cc_expected[elem.ff]);
    }
}

TEST_CASE("wordcount::schash", "[weight=0][part=wordcount]") {
    WordFreq<SCHashTable> wf(wc_file);
    vector<pair<string, int>> ret = wf.getWords(1000);
    sort(ret.begin(), ret.end(), sorter);
    REQUIRE(wf.dict.shouldResize() == false);
    REQUIRE(ret.size() == wc_expected.size());
    for (auto elem : ret) {
        REQUIRE(elem.ss == wc_expected[elem.ff]);
    }
}

TEST_CASE("wordcount::lphash", "[weight=0][part=wordcount]") {
    WordFreq<LPHashTable> wf(wc_file);
    vector<pair<string, int>> ret = wf.getWords(1000);
    sort(ret.begin(), ret.end(), sorter);
    REQUIRE(wf.dict.shouldResize() == false);
    REQUIRE(ret.size() == wc_expected.size());
    for (auto elem : ret) {
        REQUIRE(elem.ss == wc_expected[elem.ff]);
    }
}

TEST_CASE("anagram::schash", "[weight=0][part=anagram]") {
    AnagramFinder<SCHashTable> fileFinder(anagram_file);
    vector<string> anagrams = fileFinder.getAnagrams(anagram_word);

    REQUIRE(anagrams.size() == anagram_expected.size());
    for (auto elem : anagrams) {
        REQUIRE(anagram_expected.count(elem));
    }
}

TEST_CASE("anagram::lphash", "[weight=0][part=anagram]") {
    AnagramFinder<LPHashTable> fileFinder(anagram_file);
    vector<string> anagrams = fileFinder.getAnagrams(anagram_word);

    REQUIRE(anagrams.size() == anagram_expected.size());
    for (auto elem : anagrams) {
        REQUIRE(anagram_expected.count(elem));
    }
}