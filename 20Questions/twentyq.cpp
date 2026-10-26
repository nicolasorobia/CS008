#ifndef TWENTYQ_CPP
#define TWENTYQ_CPP

#include "twentyq.h"
#include <fstream>

// ===================== starter tree =====================
TwentyQuestions::TwentyQuestions()
{
    // left = yes, right = no
    root = new QNode("Does it live in the water?");

    root->left         = new QNode("Is it a mammal?");
    root->left->left   = new QNode("a dolphin");
    root->left->right  = new QNode("a shark");

    root->right        = new QNode("Can it fly?");
    root->right->left  = new QNode("an eagle");
    root->right->right = new QNode("a dog");
}

void TwentyQuestions::start()
{
    current = root;
    asked   = 0;
}

const std::string& TwentyQuestions::prompt() const
{
    static const std::string none;
    return current ? current->data : none;
}

bool TwentyQuestions::isGuessing() const
{
    return current != nullptr && isLeaf(current);
}


TwentyQuestions::Result TwentyQuestions::answer(bool yes)
{
    if (current == nullptr) return Result::NextQuestion;   // round not started

    ++asked;

    if (isLeaf(current))                                   // that was a guess
        return yes ? Result::Correct : Result::Wrong;

    current = yes ? current->left : current->right;        // that was a question

    if (asked >= MAX_QUESTIONS) return Result::OutOfQuestions;
    
    return Result::NextQuestion;
}

/*  After a wrong guess, the leaf becomes a question with two new leaves:

                           Does it have stripes?
       a dog      -->           yes /     \ no
                             a tiger      a dog

*/
void TwentyQuestions::learn(const std::string& thing,
                            const std::string& question,
                            bool yesForThing)
{
    if (current == nullptr || !isLeaf(current)) return;
    if (thing.empty() || question.empty())      return;

    std::string oldGuess = current->data;
    current->data = question;

    if (yesForThing) {
        current->left  = new QNode(thing);
        current->right = new QNode(oldGuess);
    } else {
        current->left  = new QNode(oldGuess);
        current->right = new QNode(thing);
    }

    current = nullptr;                                     
}

// ===================== save / load (preorder) =====================

void TwentyQuestions::_save(QNode* node, std::ostream& out) const
{
    if (node == nullptr) return;

    out << (isLeaf(node) ? "A:" : "Q:") << node->data << '\n';
    _save(node->left,  out);
    _save(node->right, out);
}

// Same shape as _copy, but the source tree is the file.
TwentyQuestions::QNode* TwentyQuestions::_load(std::istream& in)
{
    std::string line;
    if (!std::getline(in, line) || line.size() < 2) return nullptr;

    QNode* node = new QNode(line.substr(2));
    if (line[0] == 'Q') {
        node->left  = _load(in);
        node->right = _load(in);
        if (node->left == nullptr || node->right == nullptr) {   // file was cut off
            _clear(node);
            return nullptr;
        }
    }
    return node;
}

bool TwentyQuestions::save(const std::string& filename) const
{
    std::ofstream out(filename);
    if (!out) return false;
    _save(root, out);
    return true;
}

bool TwentyQuestions::load(const std::string& filename)
{
    std::ifstream in(filename);
    if (!in) return false;

    QNode* loaded = _load(in);
    if (loaded == nullptr) return false;     // bad file: keep the current tree

    _clear(root);
    root    = loaded;
    current = nullptr;                       // old position pointed into the freed tree
    asked   = 0;
    return true;
}

void TwentyQuestions::_clear(QNode* node)
{
    if (node == nullptr) return;

    _clear(node->left);
    _clear(node->right);
    delete node;
}

TwentyQuestions::QNode* TwentyQuestions::_copy(QNode* node)
{
    if (node == nullptr) return nullptr;

    QNode* temp = new QNode(node->data);
    temp->left  = _copy(node->left);
    temp->right = _copy(node->right);

    return temp;
}

TwentyQuestions::~TwentyQuestions()
{
    _clear(root);
}

// A copy starts fresh: 'current' points into the OTHER tree, so it can't be copied.
TwentyQuestions::TwentyQuestions(const TwentyQuestions& other)
{
    root = _copy(other.root);
}

TwentyQuestions& TwentyQuestions::operator=(const TwentyQuestions& other)
{
    if (this == &other) return *this;

    _clear(root);
    root    = _copy(other.root);
    current = nullptr;
    asked   = 0;

    return *this;
}

#endif
