// card_list.cpp
// Author: Yusen Liu
// Implementation of the classes defined in card_list.h

#include "card_list.h"

// ====== Helper Functions ======

// Insert a card into the BST
CardList::Node* CardList::insertHelper(Node* node, const Card& card, Node* parent) {
    if (node == nullptr) {
        Node* newNode = new Node(card);
        //since the node is nullptr, meaning it is a leaf node, so we need to set the parent pointer of the new node to the parent node
        newNode->parent = parent;
        return newNode;
    }
    
    if (card < node->data) {
        node->left = insertHelper(node->left, card, node);
    } else if (card > node->data) {
        node->right = insertHelper(node->right, card, node);
    }
    // If equal, we don't insert duplicates because the rules said only one copy of each card. 
    
    return node;
}

// Find a card in the BST
CardList::Node* CardList::findHelper(Node* node, const Card& card) const {
    if (node == nullptr) return nullptr;
    
    if (card < node->data) {
        return findHelper(node->left, card);
    } else if (card > node->data) {
        return findHelper(node->right, card);
    } else {
        return node;
    }
}

// Find the node with minimum value in subtree rooted at node
CardList::Node* CardList::findMin(Node* node) const {
    if (node == nullptr) return nullptr;
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

// Find the node with maximum value in subtree rooted at node
CardList::Node* CardList::findMax(Node* node) const {
    if (node == nullptr) return nullptr;
    while (node->right != nullptr) {
        node = node->right;
    }
    return node;
}

// Find the successor of a given node (next larger node)
CardList::Node* CardList::findSuccessor(Node* node) const {
    if (node == nullptr) return nullptr;
    
    // If node has right child, successor is the minimum in right subtree
    if (node->right != nullptr) {
        return findMin(node->right);
    }
    
    // Otherwise, successor is the lowest ancestor where node is in left subtree
    Node* current = node;
    while (current->parent != nullptr && current == current->parent->right) {
        current = current->parent;
    }
    return current->parent;
}

// Find the predecessor of a given node (next smaller node)
CardList::Node* CardList::findPredecessor(Node* node) const {
    if (node == nullptr) return nullptr;
    
    // If node has left child, predecessor is the maximum in left subtree
    if (node->left != nullptr) {
        return findMax(node->left);
    }
    
    // Otherwise, predecessor is the lowest ancestor where node is in right subtree
    Node* current = node;
    while (current->parent != nullptr && current == current->parent->left) {
        current = current->parent;
    }
    return current->parent;
}

// Erase a card from the BST
CardList::Node* CardList::eraseHelper(Node* node, const Card& card) {
    if (node == nullptr) return nullptr;
    
    if (card < node->data) {
        node->left = eraseHelper(node->left, card);
        if (node->left != nullptr) node->left->parent = node;
    } else if (card > node->data) {
        node->right = eraseHelper(node->right, card);
        if (node->right != nullptr) node->right->parent = node;
    } else {
        // Found the node to delete
        
        // Case 1: Node has no children
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        }
        
        // Case 2: Node has only right child
        if (node->left == nullptr) {
            Node* temp = node->right;
            temp->parent = node->parent;
            delete node;
            return temp;
        }
        
        // Case 3: Node has only left child
        if (node->right == nullptr) {
            Node* temp = node->left;
            temp->parent = node->parent;
            delete node;
            return temp;
        }
        
        // Case 4: Node has two children
        // Find the inorder successor (smallest in right subtree)
        Node* successor = findMin(node->right);
        node->data = successor->data;
        node->right = eraseHelper(node->right, successor->data);
        if (node->right != nullptr) node->right->parent = node;
    }
    
    return node;
}

// Delete entire tree
void CardList::deleteTree(Node* node) {
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

// ====== Iterator Methods ======

CardList::Iterator& CardList::Iterator::operator++() {
    if (current == nullptr) return *this;
    
    // If node has right child, successor is the minimum in right subtree
    if (current->right != nullptr) {
        Node* node = current->right;
        while (node->left != nullptr) {
            node = node->left;
        }
        current = node;
    } else {
        // Otherwise, successor is the lowest ancestor where current is in left subtree
        Node* prev = current;
        current = current->parent;
        while (current != nullptr && prev == current->right) {
            prev = current;
            current = current->parent;
        }
    }
    return *this;
}

CardList::Iterator& CardList::Iterator::operator--() {
    if (current == nullptr) return *this;
    
    // If node has left child, predecessor is the maximum in left subtree
    if (current->left != nullptr) {
        Node* node = current->left;
        while (node->right != nullptr) {
            node = node->right;
        }
        current = node;
    } else {
        // Otherwise, predecessor is the lowest ancestor where current is in right subtree
        Node* prev = current;
        current = current->parent;
        while (current != nullptr && prev == current->left) {
            prev = current;
            current = current->parent;
        }
    }
    return *this;
}

const Card& CardList::Iterator::operator*() const {
    return current->data;
}

const Card* CardList::Iterator::operator->() const {
    return &(current->data);
}

bool CardList::Iterator::operator==(const Iterator& other) const {
    return current == other.current;
}

bool CardList::Iterator::operator!=(const Iterator& other) const {
    return current != other.current;
}

// ====== ReverseIterator Methods ======

CardList::ReverseIterator& CardList::ReverseIterator::operator++() {
    if (current == nullptr) return *this;
    
    // If node has left child, predecessor is the maximum in left subtree
    if (current->left != nullptr) {
        Node* node = current->left;
        while (node->right != nullptr) {
            node = node->right;
        }
        current = node;
    } else {
        // Otherwise, predecessor is the lowest ancestor where current is in right subtree
        Node* prev = current;
        current = current->parent;
        while (current != nullptr && prev == current->left) {
            prev = current;
            current = current->parent;
        }
    }
    return *this;
}

CardList::ReverseIterator& CardList::ReverseIterator::operator--() {
    if (current == nullptr) return *this;
    
    // If node has right child, successor is the minimum in right subtree
    if (current->right != nullptr) {
        Node* node = current->right;
        while (node->left != nullptr) {
            node = node->left;
        }
        current = node;
    } else {
        // Otherwise, successor is the lowest ancestor where current is in left subtree
        Node* prev = current;
        current = current->parent;
        while (current != nullptr && prev == current->right) {
            prev = current;
            current = current->parent;
        }
    }
    return *this;
}

const Card& CardList::ReverseIterator::operator*() const {
    return current->data;
}

const Card* CardList::ReverseIterator::operator->() const {
    return &(current->data);
}

bool CardList::ReverseIterator::operator==(const ReverseIterator& other) const {
    return current == other.current;
}

bool CardList::ReverseIterator::operator!=(const ReverseIterator& other) const {
    return current != other.current;
}

// ====== CardList Methods ======

CardList::CardList() : root(nullptr), size(0) {}

CardList::~CardList() {
    deleteTree(root);
}

void CardList::insert(const Card& card) {
    root = insertHelper(root, card, nullptr);
    size++;
}

CardList::Iterator CardList::find(const Card& card) const {
    return Iterator(findHelper(root, card));
}

void CardList::erase(const Card& card) {
    if (findHelper(root, card) != nullptr) {
        root = eraseHelper(root, card);
        size--;
    }
}

void CardList::erase(Iterator it) {
    if (it.current != nullptr) {
        erase(*it);
    }
}

bool CardList::contains(const Card& card) const {
    return findHelper(root, card) != nullptr;
}

CardList::Iterator CardList::begin() const {
    return Iterator(findMin(root));
}

CardList::Iterator CardList::end() const {
    return Iterator(nullptr);
}

CardList::ReverseIterator CardList::rbegin() const {
    return ReverseIterator(findMax(root));
}

CardList::ReverseIterator CardList::rend() const {
    return ReverseIterator(nullptr);
}

bool CardList::empty() const {
    return size == 0;
}

size_t CardList::getSize() const {
    return size;
}