// This file should implement the game using a custom implementation of a BST (based on your earlier BST implementation)
#include <iostream>
#include <fstream>
#include <string>
#include "card.h"
#include "card_list.h"
//Do not include set in this file

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

  // Read cards into BSTs
  CardList alice;
  CardList bob;

  Card c;
  while (cardFile1 >> c) {
    alice.insert(c);
  }
  cardFile1.close();

  while (cardFile2 >> c) {
    bob.insert(c);
  }
  cardFile2.close();

  // Play the game: alternate Alice (forward) then Bob (reverse)
  while (true) {
    bool picked = false;

    // Alice's turn: iterate from smallest to largest
    for (auto it = alice.begin(); it != alice.end(); ++it) {
      if (bob.contains(*it)) {
        std::cout << "Alice picked matching card " << *it << std::endl;
        Card match = *it;
        alice.erase(it);
        bob.erase(match);
        picked = true;
        break;
      }
    }

    // Bob's turn: iterate from largest to smallest (always runs after Alice)
    for (auto rit = bob.rbegin(); rit != bob.rend(); ++rit) {
      if (alice.contains(*rit)) {
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
  for (auto it = alice.begin(); it != alice.end(); ++it) {
    std::cout << *it << std::endl;
  }

  std::cout << std::endl;
  std::cout << "Bob's cards:" << std::endl;
  for (auto it = bob.begin(); it != bob.end(); ++it) {
    std::cout << *it << std::endl;
  }

  return 0;
}
