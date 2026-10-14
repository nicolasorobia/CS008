#ifndef TWENTYQ_H
#define TWENTYQ_H

#include "node.h"
#include <string>
#include <istream>
#include <ostream>

class TwentyQuestions
{
private:
    using QNode = Node<std::string>;

    QNode* root    = nullptr;
    QNode* current = nullptr;               // where the player is in this round
    int    asked   = 0;

    void   _save  (QNode* node, std::ostream& out) const;   // preorder
    QNode* _load  (std::istream& in);                       // rebuild from preorder
    void   _clear (QNode* node);                            // postorder
    QNode* _copy  (QNode* node);                            // preorder

    static bool isLeaf(QNode* node) { return node->left == nullptr && node->right == nullptr; }

public:
    enum class Result { NextQuestion, Correct, Wrong, OutOfQuestions };
    static const int MAX_QUESTIONS = 20;

    TwentyQuestions();                      // builds a small starter tree

    void   start();                         // begin a round at the root
    Result answer(bool yes);                
    void   learn(const std::string& thing,  
                 const std::string& question,
                 bool yesForThing);

    const std::string& prompt() const;      // current question, or the guess at a leaf
    bool isGuessing() const;                // true when current is a leaf
    int  questionsAsked() const { return asked; }

    bool save(const std::string& filename) const;
    bool load(const std::string& filename);

    // Big 3
    ~TwentyQuestions();
    TwentyQuestions(const TwentyQuestions& other);
    TwentyQuestions& operator=(const TwentyQuestions& other);
};

#endif
