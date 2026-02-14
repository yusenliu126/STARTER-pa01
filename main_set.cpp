// This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"

using namespace std;

int main(int argv, char** argc){
  if(argv < 3){
    std::cout << "Please provide 2 file names" << std::endl;
    return 1;
  }
  
  std::ifstream cardFile1 (argc[1]);
  std::ifstream cardFile2 (argc[2]);
  std::string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    std::cout << "Could not open file " << argc[2];
    return 1;
  }
  // Read cards into sets
  std::set<Card> alice;
  std::set<Card> bob;

  Card c;
  while (cardFile1 >> c) {
    alice.insert(c);
  }
  cardFile1.close();

  while (cardFile2 >> c) {
    bob.insert(c);
  }
  cardFile2.close();

  // DEBUG: print initial hands (remove after verification)
  //cerr << "Initial Alice:" << endl;
  //for (const auto &card : alice) cerr << card << endl;
  //cerr << "Initial Bob:" << endl;
  //for (const auto &card : bob) cerr << card << endl;

  // Play the game: alternate Alice (forward) then Bob (reverse)
  while (true) {
    bool picked = false;

    // Alice's turn: iterate from smallest to largest
    //why I used auto? because it is clean and it is easier to read, and it is more efficient than using set<Card>::iterator
    ////'it' is a forward iterator, aka a pointer
    for (auto it = alice.begin(); it != alice.end(); ++it) {
      // Check if Bob has a matching card and it is not at the end of the set (to avoid erasing while iterating)
      if (bob.find(*it) != bob.end()) {
        std::cout << "Alice picked matching card " << *it << std::endl;
        Card match = *it;
        alice.erase(it);
        bob.erase(match);
        picked = true;
        break;
      }
    }

    // Bob's turn: iterate from largest to smallest (always runs after Alice)
    //rit is the reverse iterator, which is also a pointer
    for (auto rit = bob.rbegin(); rit != bob.rend(); ++rit) {
      if (alice.find(*rit) != alice.end()) {
        std::cout << "Bob picked matching card " << *rit << std::endl;
        Card match = *rit;
        bob.erase(match);
        alice.erase(match);
        picked = true;
        break;
      }
    }

    if (!picked) break; // no more matches
  }

  std::cout << std::endl;
  std::cout << "Alice's cards:" << std::endl;
  for (const auto &card : alice) {
    std::cout << card << std::endl;
  }

  std::cout << std::endl;
  std::cout << "Bob's cards:" << std::endl;
  for (const auto &card : bob) {
    std::cout << card << std::endl;
  }

  return 0;
}
