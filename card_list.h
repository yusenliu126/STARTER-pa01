// card_list.h
// Author: Yusen Liu
// All class declarations related to defining a BST that represents a player's hand

#ifndef CARD_LIST_H
#define CARD_LIST_H

#include "card.h"
#include <memory>

class CardList {
private:
    struct Node {
        Card data;
        Node* left;
        Node* right;
        Node* parent;
        
        Node(const Card& c) : data(c), left(nullptr), right(nullptr), parent(nullptr) {}
    };
    
    Node* root;
    size_t size;
    
    // Helper functions for tree operations
    Node* insertHelper(Node* node, const Card& card, Node* parent);
    Node* findHelper(Node* node, const Card& card) const;
    Node* findMin(Node* node) const;
    Node* findMax(Node* node) const;
    Node* findSuccessor(Node* node) const;
    Node* findPredecessor(Node* node) const;
    Node* eraseHelper(Node* node, const Card& card);
    void deleteTree(Node* node);
    
public:
    class Iterator {
    private:
        Node* current;
        
    public:
        Iterator(Node* node = nullptr) : current(node) {}
        
        // Prefix increment (operator++)
        Iterator& operator++();
        
        // Prefix decrement (operator--)
        Iterator& operator--();
        
        // Dereference
        const Card& operator*() const;
        const Card* operator->() const;
        
        // Equality/inequality
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
        
        friend class CardList;
    };
    
    class ReverseIterator {
    private:
        Node* current;
        
    public:
        ReverseIterator(Node* node = nullptr) : current(node) {}
        
        // Prefix increment (operator++) - goes to predecessor
        ReverseIterator& operator++();
        
        // Prefix decrement (operator--) - goes to successor
        ReverseIterator& operator--();
        
        // Dereference
        const Card& operator*() const;
        const Card* operator->() const;
        
        // Equality/inequality
        bool operator==(const ReverseIterator& other) const;
        bool operator!=(const ReverseIterator& other) const;
        
        friend class CardList;
    };
    
    // Constructors/Destructors
    CardList();
    ~CardList();
    
    // Basic operations
    void insert(const Card& card);
    Iterator find(const Card& card) const;
    void erase(const Card& card);
    void erase(Iterator it);
    bool contains(const Card& card) const;
    
    // Iterator support
    Iterator begin() const;
    Iterator end() const;
    ReverseIterator rbegin() const;
    ReverseIterator rend() const;
    
    // Utility
    bool empty() const;
    size_t getSize() const;
};

#endif
