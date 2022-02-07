#include<iostream>
#include<fstream>

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
    Tree* Insert(T);
    int Print(int, ofstream&);
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
    if (height_left != 0) {
        size += left->Fix_Size();
    }
    if (height_right != 0) {
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
Tree<T>* Tree<T>::Balance() {
    Fix_Height();
    if (height_right - height_left == 2) {
        if (right->height_right - right->height_left < 0)
            right = right->Rotate_Right();
        return Rotate_Left();
    }
    else if (height_right - height_left == -2) {
        if (left->height_right - left->height_left > 0)
            left = left->Rotate_Left();
        return Rotate_Right();
    }
    else {
        return Rotate_Left();
    }
    return this;
}

template<typename T>
Tree<T>* Tree<T>::Insert(T k) {
    if (!this)
        return new Tree(k);
    if (k < key)
        left = left->Insert(k);
    else
        right = right->Insert(k);

    Fix_Height();
    return this;
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

int main() {
    ifstream fin("rotation.in");
    ofstream fout("rotation.out");
    int n, left = 0, right = 0, input;
    fin >> n;
    Tree<int> *AVL_Tree = NULL;
    for (int i = 0; i < n; i++) {
        fin >> input;
        AVL_Tree = AVL_Tree->Insert(input);
        fin >> input;
        fin >> input;
    }
    while (fin >> input) {
        AVL_Tree = AVL_Tree->Insert(input);
    }
    AVL_Tree = AVL_Tree->Balance();
    AVL_Tree->Fix_Size();
    fout << n << endl;
    AVL_Tree->Print(1, fout);

    fin.close();
    fout.close();
    return 0;
}