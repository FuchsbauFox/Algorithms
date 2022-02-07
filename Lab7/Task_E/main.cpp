#include<iostream>
#include<fstream>
#include<string>

using namespace std;

template<typename T>
class Tree {
private:
    T key;
    Tree* left;
    Tree* right;
    int height_left;
    int height_right;
    int size;
public:
    Tree(T);
    int Height();
    void Fix_Height();
    int Fix_Size();
    Tree* Rotate_Right();
    Tree* Rotate_Left();
    Tree* Balance();
    pair<Tree*, Tree*> Remove_Max();
    Tree* Insert(T);
    Tree* Remove(T);
    int Print(int, ofstream&);
    int Get_Size();
    int Get_Balance();
    bool Exists(T);
};

template<typename T>
Tree<T>::Tree(T k)
    : key(k), left(NULL), right(NULL), height_left(0), height_right(0), size(0) {}

template<typename T>
int Tree<T>::Height() {
    return height_left > height_right ? height_left : height_right;
}

template<typename T>
void Tree<T>::Fix_Height() {
    if (left != NULL)
        height_left = left->Height() + 1;
    else
        height_left = 0;
    if (right != NULL)
        height_right = right->Height() + 1;
    else
        height_right = 0;
}

template<typename T>
int Tree<T>::Fix_Size() {
    if (left != NULL) {
        size += left->Fix_Size();
    }
    if (right != NULL) {
        size += right->Fix_Size();
    }
    return size + 1;
}

template<typename T>
Tree<T>* Tree<T>::Rotate_Right() {
    Tree* q = left;
    left = q->right;
    q->right = this;
    Fix_Height();
    q->Fix_Height();
    return q;
}

template<typename T>
Tree<T>* Tree<T>::Rotate_Left() {
    Tree* p = right;
    right = p->left;
    p->left = this;
    Fix_Height();
    p->Fix_Height();
    return p;
}

template<typename T>
int Tree<T>::Get_Balance() {
    if (this == NULL)
        return 0;
    return height_right - height_left;
}

template<typename T>
Tree<T>* Tree<T>::Balance() {
    Fix_Height();
    if (height_right - height_left == 2) {
        if (right->height_right - right->height_left < 0)
            right = right->Rotate_Right();
        return Rotate_Left();
    }
    if (height_right - height_left == -2) {
        if (left->height_right - left->height_left > 0)
            left = left->Rotate_Left();
        return Rotate_Right();
    }
    return this;
}

template<typename T>
Tree<T>* Tree<T>::Insert(T k) {
    if (this == NULL)
        return new Tree(k);
    if (k < key)
        left = left->Insert(k);
    else if (k > key)
        right = right->Insert(k);
    else
        return this;
    return Balance();
}

template<typename T>
pair<Tree<T>*, Tree<T>*> Tree<T>::Remove_Max() {
    Tree* max;
    if (right == NULL)
        return pair<Tree<T>*, Tree<T>*>(left, this);
    auto p = right->Remove_Max();
    right = p.first;
    max = p.second;
    return pair<Tree<T>*, Tree<T>*>(Balance(), max);
}

template<typename T>
Tree<T>* Tree<T>::Remove(T k) {
    if (this == NULL)
        return this;
    if (k < key)
        left = left->Remove(k);
    else if (k > key)
        right = right->Remove(k);
    else {
        Tree* old_right = right;
        Tree* old_left = left;
        delete this;
        if (old_left == NULL)
            return old_right;
        Tree* max;
        auto p = old_left->Remove_Max();
        max = p.second;
        max->left = p.first;
        max->right = old_right;
        return max->Balance();
    }
    return Balance();
}

template<typename T>
bool Tree<T>::Exists(T k) {
    Tree* current = this;
    while (current != NULL){
        if (k < current->key)
            current = current->left;
        else if (k > current->key)
            current = current->right;
        else
            return true;
    }
    return false;
}

template<typename T>
int Tree<T>::Print(int pos, ofstream& fout) {
    fout << key << " ";
    pos++;
    if (height_left != 0) {
        fout << pos << " ";
    }
    else {
        fout << 0 << " ";
    }
    if (height_right != 0) {
        if (height_left != 0)
            fout << pos + left->size + 1 << "\n";
        else
            fout << pos << "\n";
    }
    else {
        fout << 0 << "\n";
    }
    if (height_left != 0) {
        pos = left->Print(pos, fout);
    }
    if (height_right != 0) {
        pos = right->Print(pos, fout);
    }
    return pos;
}

template<typename T>
int Tree<T>::Get_Size() {
    return size + 1;
}

int main() {
    ifstream fin("avlset.in");
    ofstream fout("avlset.out");
    int n, left = 0, right = 0, input;
    string command;
    fin >> n;
    Tree<int>* AVL_Tree = NULL;
    while (fin >> command) {
        if (command == "A") {
            fin >> input;
            AVL_Tree = AVL_Tree->Insert(input);
            fout << AVL_Tree->Get_Balance() << "\n";
        }
        else if (command == "D") {
            fin >> input;
            AVL_Tree = AVL_Tree->Remove(input);
            fout << AVL_Tree->Get_Balance() << "\n";
        }
        else if (command == "C") {
            fin >> input;
            AVL_Tree->Exists(input) ? fout << "Y\n" : fout << "N\n";
        }
    }
    fin.close();
    fout.close();
    return 0;
}