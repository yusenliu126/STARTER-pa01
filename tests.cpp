// tests.cpp
// Author: Yusen Liu
// Comprehensive test cases for Card class and CardList (BST) implementation

#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>
#include "card.h"
#include "card_list.h"

using namespace std;

// ====== Helper function for testing ======
void assert_equal(bool condition, const string& test_name) {
    if (condition) {
        cout << "✓ PASS: " << test_name << endl;
    } else {
        cout << "✗ FAIL: " << test_name << endl;
        exit(1);
    }
}

// ====== Card Class Tests ======

void test_card_constructor() {
    cout << "\n=== Testing Card Constructors ===" << endl;
    
    // Test 1: Default constructor
    Card c1;
    assert_equal(c1.getSuit() == ' ' && c1.getValue() == "", "Default constructor");
    
    // Test 2: Parameterized constructor
    Card c2('h', "3");
    assert_equal(c2.getSuit() == 'h' && c2.getValue() == "3", "Parameterized constructor");
    
    // Test 3: Constructor with ace
    Card c3('c', "a");
    assert_equal(c3.getSuit() == 'c' && c3.getValue() == "a", "Constructor with ace");
    
    // Test 4: Constructor with face card
    Card c4('s', "k");
    assert_equal(c4.getSuit() == 's' && c4.getValue() == "k", "Constructor with king");
    
    // Test 5: Constructor with 10
    Card c5('d', "10");
    assert_equal(c5.getSuit() == 'd' && c5.getValue() == "10", "Constructor with 10");
}

void test_card_comparison_less() {
    cout << "\n=== Testing Card operator< ===" << endl;
    
    // Test 1: Suit ordering (clubs < diamonds)
    Card c1('c', "k");
    Card c2('d', "a");
    assert_equal(c1 < c2, "Clubs less than diamonds (same rank)");
    
    // Test 2: Suit ordering (diamonds < spades)
    Card c3('d', "k");
    Card c4('s', "a");
    assert_equal(c3 < c4, "Diamonds less than spades (same rank)");
    
    // Test 3: Suit ordering (spades < hearts)
    Card c5('s', "k");
    Card c6('h', "a");
    assert_equal(c5 < c6, "Spades less than hearts (same rank)");
    
    // Test 4: Value ordering within suit (ace < 2)
    Card c7('c', "a");
    Card c8('c', "2");
    assert_equal(c7 < c8, "Ace less than 2 in same suit");
    
    // Test 5: Value ordering within suit (10 < jack)
    Card c9('h', "10");
    Card c10('h', "j");
    assert_equal(c9 < c10, "10 less than jack in same suit");
}

void test_card_comparison_equal() {
    cout << "\n=== Testing Card operator== ===" << endl;
    
    // Test 1: Same card is equal
    Card c1('h', "3");
    Card c2('h', "3");
    assert_equal(c1 == c2, "Same cards are equal");
    
    // Test 2: Different suit not equal
    Card c3('c', "3");
    Card c4('h', "3");
    assert_equal(!(c3 == c4), "Different suits not equal");
    
    // Test 3: Different value not equal
    Card c5('h', "3");
    Card c6('h', "4");
    assert_equal(!(c5 == c6), "Different values not equal");
    
    // Test 4: Ace equality
    Card c7('d', "a");
    Card c8('d', "a");
    assert_equal(c7 == c8, "Aces are equal");
    
    // Test 5: Face card equality
    Card c9('s', "q");
    Card c10('s', "q");
    assert_equal(c9 == c10, "Face cards are equal");
}

void test_card_comparison_greater() {
    cout << "\n=== Testing Card operator> ===" << endl;
    
    // Test 1: Hearts > spades
    Card c1('h', "a");
    Card c2('s', "k");
    assert_equal(c1 > c2, "Hearts greater than spades");
    
    // Test 2: Queen > 10
    Card c3('c', "q");
    Card c4('c', "10");
    assert_equal(c3 > c4, "Queen greater than 10 in same suit");
    
    // Test 3: Not greater (equal case)
    Card c5('d', "5");
    Card c6('d', "5");
    assert_equal(!(c5 > c6), "Equal cards not greater than each other");
    
    // Test 4: King > queen
    Card c7('h', "k");
    Card c8('h', "q");
    assert_equal(c7 > c8, "King greater than queen");
    
    // Test 5: 3 > 2
    Card c9('s', "3");
    Card c10('s', "2");
    assert_equal(c9 > c10, "3 greater than 2 in same suit");
}

void test_card_io_operators() {
    cout << "\n=== Testing Card I/O Operators ===" << endl;
    
    // Test 1: Output operator
    Card c1('h', "3");
    stringstream ss1;
    ss1 << c1;
    assert_equal(ss1.str() == "h 3", "Output operator produces correct format");
    
    // Test 2: Input operator
    stringstream ss2;
    ss2 << "c a";
    Card c2;
    ss2 >> c2;
    assert_equal(c2.getSuit() == 'c' && c2.getValue() == "a", "Input operator reads correct card");
    
    // Test 3: Input with 10
    stringstream ss3;
    ss3 << "d 10";
    Card c3;
    ss3 >> c3;
    assert_equal(c3.getSuit() == 'd' && c3.getValue() == "10", "Input operator handles 10 correctly");
    
    // Test 4: Input with face card
    stringstream ss4;
    ss4 << "s k";
    Card c4;
    ss4 >> c4;
    assert_equal(c4.getSuit() == 's' && c4.getValue() == "k", "Input operator handles face card");
    
    // Test 5: Output for ace
    Card c5('d', "a");
    stringstream ss5;
    ss5 << c5;
    assert_equal(ss5.str() == "d a", "Output operator handles ace correctly");
}

// ====== CardList (BST) Class Tests ======

void test_cardlist_insert() {
    cout << "\n=== Testing CardList insert() ===" << endl;
    
    // Test 1: Insert single card
    CardList list1;
    list1.insert(Card('h', "3"));
    assert_equal(list1.getSize() == 1, "Insert single card increases size");
    
    // Test 2: Insert multiple cards in order
    CardList list2;
    list2.insert(Card('c', "5"));
    list2.insert(Card('d', "5"));
    list2.insert(Card('h', "5"));
    assert_equal(list2.getSize() == 3, "Insert multiple cards");
    
    // Test 3: Insert in reverse order
    CardList list3;
    list3.insert(Card('h', "k"));
    list3.insert(Card('h', "q"));
    list3.insert(Card('h', "j"));
    assert_equal(list3.getSize() == 3, "Insert in reverse order maintains size");
    
    // Test 4: Insert duplicate (should increase size)
    CardList list4;
    list4.insert(Card('c', "3"));
    list4.insert(Card('c', "3"));
    assert_equal(list4.getSize() == 2, "Insert duplicate increases size");
    
    // Test 5: Insert and check empty() becomes false
    CardList list5;
    assert_equal(list5.empty(), "Empty list is empty initially");
    list5.insert(Card('s', "a"));
    assert_equal(!list5.empty(), "List not empty after insert");
}

void test_cardlist_contains() {
    cout << "\n=== Testing CardList contains() ===" << endl;
    
    CardList list;
    Card c1('h', "3");
    Card c2('c', "a");
    Card c3('s', "k");
    
    list.insert(c1);
    list.insert(c2);
    list.insert(c3);
    
    // Test 1: Contains existing card
    assert_equal(list.contains(c1), "Contains finds inserted card");
    
    // Test 2: Contains another card
    assert_equal(list.contains(c2), "Contains finds different card");
    
    // Test 3: Not contains non-existent card
    assert_equal(!list.contains(Card('d', "5")), "Not contains non-existent card");
    
    // Test 4: Empty list doesn't contain anything
    CardList emptyList;
    assert_equal(!emptyList.contains(c1), "Empty list doesn't contain cards");
    
    // Test 5: Contains with same suit different rank
    list.insert(Card('h', "5"));
    assert_equal(list.contains(Card('h', "5")), "Contains different rank same suit");
}

void test_cardlist_find() {
    cout << "\n=== Testing CardList find() ===" << endl;
    
    CardList list;
    Card c1('h', "3");
    Card c2('d', "a");
    list.insert(c1);
    list.insert(c2);
    
    // Test 1: Find existing card
    CardList::Iterator it1 = list.find(c1);
    assert_equal(it1 != list.end(), "Find returns non-end iterator for existing card");
    assert_equal(*it1 == c1, "Found iterator dereferences to correct card");
    
    // Test 2: Find another card
    CardList::Iterator it2 = list.find(c2);
    assert_equal(*it2 == c2, "Find returns correct card");
    
    // Test 3: Find non-existent card returns end
    CardList::Iterator it3 = list.find(Card('s', "5"));
    assert_equal(it3 == list.end(), "Find non-existent returns end iterator");
    
    // Test 4: Find in single element list
    CardList singleList;
    singleList.insert(c1);
    assert_equal(singleList.find(c1) != singleList.end(), "Find in single element list");
    
    // Test 5: Find in empty list
    CardList emptyList;
    assert_equal(emptyList.find(c1) == emptyList.end(), "Find in empty list returns end");
}

void test_cardlist_erase() {
    cout << "\n=== Testing CardList erase() ===" << endl;
    
    // Test 1: Erase single card from list of 3
    CardList list1;
    Card c1('c', "3");
    Card c2('d', "5");
    Card c3('h', "7");
    list1.insert(c1);
    list1.insert(c2);
    list1.insert(c3);
    list1.erase(c2);
    assert_equal(list1.getSize() == 2 && !list1.contains(c2), "Erase removes card");
    
    // Test 2: Erase middle element
    CardList list2;
    list2.insert(Card('c', "a"));
    list2.insert(Card('c', "5"));
    list2.insert(Card('c', "k"));
    list2.erase(Card('c', "5"));
    assert_equal(list2.getSize() == 2, "Erase middle element");
    
    // Test 3: Erase root element
    CardList list3;
    Card root('d', "5");
    list3.insert(root);
    list3.insert(Card('c', "k"));
    list3.insert(Card('h', "2"));
    list3.erase(root);
    assert_equal(list3.getSize() == 2 && !list3.contains(root), "Erase root element");
    
    // Test 4: Erase last remaining card
    CardList list4;
    Card solo('s', "q");
    list4.insert(solo);
    list4.erase(solo);
    assert_equal(list4.empty(), "Erase last card empties list");
    
    // Test 5: Erase non-existent card (no-op)
    CardList list5;
    list5.insert(Card('h', "3"));
    list5.erase(Card('s', "9"));
    assert_equal(list5.getSize() == 1, "Erase non-existent card is no-op");
}

void test_cardlist_iterator_forward() {
    cout << "\n=== Testing CardList Iterator (Forward) ===" << endl;
    
    CardList list;
    Card c1('c', "3");
    Card c2('d', "5");
    Card c3('h', "2");
    list.insert(c2);
    list.insert(c1);
    list.insert(c3);
    
    // Test 1: Begin iterator points to smallest
    assert_equal(*list.begin() == c1, "Begin points to smallest card");
    
    // Test 2: Increment operator
    CardList::Iterator it = list.begin();
    ++it;
    assert_equal(*it == c2, "Increment moves to next card");
    
    // Test 3: End iterator
    CardList::Iterator endIt = list.end();
    assert_equal(endIt == list.end(), "End iterator equals end");
    
    // Test 4: Iterate through all elements forward
    int count = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        count++;
    }
    assert_equal(count == 3, "Forward iteration visits all elements");
    
    // Test 5: Multiple increments reach end
    CardList::Iterator it2 = list.begin();
    ++it2;
    ++it2;
    ++it2;
    assert_equal(it2 == list.end(), "Multiple increments reach end");
}

void test_cardlist_iterator_reverse() {
    cout << "\n=== Testing CardList ReverseIterator ===" << endl;
    
    CardList list;
    Card c1('c', "3");
    Card c2('d', "5");
    Card c3('h', "2");
    list.insert(c2);
    list.insert(c1);
    list.insert(c3);
    
    // Test 1: Rbegin points to largest
    assert_equal(*list.rbegin() == c3, "Rbegin points to largest card");
    
    // Test 2: Reverse increment operator
    CardList::ReverseIterator rit = list.rbegin();
    ++rit;
    assert_equal(*rit == c2, "Reverse increment moves to previous card");
    
    // Test 3: Rend iterator
    CardList::ReverseIterator rendIt = list.rend();
    assert_equal(rendIt == list.rend(), "Rend iterator equals rend");
    
    // Test 4: Iterate through all elements in reverse
    int count = 0;
    for (auto rit = list.rbegin(); rit != list.rend(); ++rit) {
        count++;
    }
    assert_equal(count == 3, "Reverse iteration visits all elements");
    
    // Test 5: Verify reverse order is correct
    CardList::ReverseIterator rit2 = list.rbegin();
    assert_equal(*rit2 == c3, "First element is largest");
    ++rit2;
    assert_equal(*rit2 == c2, "Second element is middle");
    ++rit2;
    assert_equal(*rit2 == c1, "Third element is smallest");
}

void test_cardlist_erase_via_iterator() {
    cout << "\n=== Testing CardList erase(Iterator) ===" << endl;
    
    // Test 1: Erase via iterator
    CardList list1;
    Card c1('c', "5");
    Card c2('h', "3");
    list1.insert(c1);
    list1.insert(c2);
    CardList::Iterator it = list1.find(c1);
    list1.erase(it);
    assert_equal(list1.getSize() == 1 && !list1.contains(c1), "Erase via iterator removes card");
    
    // Test 2: Erase via forward iterator
    CardList list2;
    list2.insert(Card('c', "a"));
    list2.insert(Card('d', "5"));
    list2.insert(Card('h', "k"));
    auto it2 = list2.begin();
    ++it2;
    list2.erase(it2);
    assert_equal(list2.getSize() == 2, "Erase via moved iterator");
    
    // Test 3: Erase single element via iterator
    CardList list3;
    Card solo('s', "q");
    list3.insert(solo);
    list3.erase(list3.find(solo));
    assert_equal(list3.empty(), "Erase single element via iterator empties list");
    
    // Test 4: Size decrements after erase
    CardList list4;
    list4.insert(Card('c', "2"));
    list4.insert(Card('d', "3"));
    list4.insert(Card('h', "4"));
    size_t sizeBefore = list4.getSize();
    list4.erase(list4.begin());
    assert_equal(list4.getSize() == sizeBefore - 1, "Size decrements after iterator erase");
    
    // Test 5: Remaining elements preserved after erase
    CardList list5;
    list5.insert(Card('c', "3"));
    list5.insert(Card('d', "5"));
    list5.insert(Card('h', "7"));
    list5.erase(list5.find(Card('d', "5")));
    assert_equal(list5.contains(Card('c', "3")) && list5.contains(Card('h', "7")), 
                 "Other elements preserved after erase");
}

void test_cardlist_ordering() {
    cout << "\n=== Testing CardList Ordering ===" << endl;
    
    CardList list;
    // Insert in random order
    list.insert(Card('h', "3"));
    list.insert(Card('c', "a"));
    list.insert(Card('s', "5"));
    list.insert(Card('d', "10"));
    
    // Test 1: Iterator gives ascending order
    vector<Card> cards;
    for (auto it = list.begin(); it != list.end(); ++it) {
        cards.push_back(*it);
    }
    assert_equal(cards[0] == Card('c', "a"), "First card is clubs ace");
    assert_equal(cards[1] == Card('d', "10"), "Second card is diamonds 10");
    assert_equal(cards[2] == Card('s', "5"), "Third card is spades 5");
    assert_equal(cards[3] == Card('h', "3"), "Fourth card is hearts 3");
    
    // Test 2: Reverse iterator gives descending order
    vector<Card> revCards;
    for (auto rit = list.rbegin(); rit != list.rend(); ++rit) {
        revCards.push_back(*rit);
    }
    assert_equal(revCards[0] == Card('h', "3"), "First reverse card is hearts 3");
    assert_equal(revCards[3] == Card('c', "a"), "Last reverse card is clubs ace");
    
    // Test 3: Multiple suites ordered correctly
    CardList suit_list;
    suit_list.insert(Card('h', "2"));
    suit_list.insert(Card('c', "2"));
    suit_list.insert(Card('d', "2"));
    suit_list.insert(Card('s', "2"));
    auto suit_it = suit_list.begin();
    assert_equal(*suit_it == Card('c', "2"), "Clubs before diamonds");
    ++suit_it;
    assert_equal(*suit_it == Card('d', "2"), "Diamonds before spades");
    ++suit_it;
    assert_equal(*suit_it == Card('s', "2"), "Spades before hearts");
    
    // Test 4: Values within suit ordered correctly
    CardList val_list;
    val_list.insert(Card('h', "k"));
    val_list.insert(Card('h', "a"));
    val_list.insert(Card('h', "j"));
    val_list.insert(Card('h', "5"));
    auto val_it = val_list.begin();
    assert_equal(*val_it == Card('h', "a"), "Ace is smallest value");
    ++val_it;
    assert_equal(*val_it == Card('h', "5"), "5 comes after ace");
    ++val_it;
    assert_equal(*val_it == Card('h', "j"), "Jack comes after 5");
    ++val_it;
    assert_equal(*val_it == Card('h', "k"), "King is largest value");
    
    // Test 5: Complex ordering
    CardList complex;
    complex.insert(Card('s', "q"));
    complex.insert(Card('c', "3"));
    complex.insert(Card('h', "a"));
    complex.insert(Card('d', "9"));
    vector<Card> complexCards;
    for (auto c_it = complex.begin(); c_it != complex.end(); ++c_it) {
        complexCards.push_back(*c_it);
    }
    // Verify all consecutive pairs are in ascending order
    bool allOrdered = true;
    for (size_t i = 0; i < complexCards.size() - 1; i++) {
        if (!(complexCards[i] < complexCards[i+1])) {
            allOrdered = false;
            break;
        }
    }
    assert_equal(allOrdered, "Elements in ascending order");
}

int main() {
    cout << "=====================================" << endl;
    cout << "  CARD AND CARDLIST TEST SUITE" << endl;
    cout << "=====================================" << endl;
    
    // Card class tests
    test_card_constructor();
    test_card_comparison_less();
    test_card_comparison_equal();
    test_card_comparison_greater();
    test_card_io_operators();
    
    // CardList class tests
    test_cardlist_insert();
    test_cardlist_contains();
    test_cardlist_find();
    test_cardlist_erase();
    test_cardlist_iterator_forward();
    test_cardlist_iterator_reverse();
    test_cardlist_erase_via_iterator();
    test_cardlist_ordering();
    
    cout << "\n=====================================" << endl;
    cout << "  ALL TESTS PASSED!" << endl;
    cout << "=====================================" << endl;
    
    return 0;
}
