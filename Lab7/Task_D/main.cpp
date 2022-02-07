#include<iostream>
#include<fstream>

using namespace std;

bool flag;

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
    else
        right = right->Insert(k);


    if (flag)
        return Balance();
    else {
        Fix_Height();
        return this;
    }
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
    ifstream fin("deletion.in");
    ofstream fout("deletion.out");
    int n, left = 0, right = 0, input;
    fin >> n;
    Tree<int>* AVL_Tree = NULL;
    flag = false;
    for (int i = 0; i < n; i++) {
        fin >> input;
        AVL_Tree = AVL_Tree->Insert(input);
        fin >> input;
        fin >> input;
    }
    while (fin >> input) {
        AVL_Tree = AVL_Tree->Remove(input);
    }
    if (AVL_Tree == NULL) {
        fout << 0;
        return 0;
    }
    AVL_Tree->Fix_Size();
    fout << AVL_Tree->Get_Size() << endl;
    AVL_Tree->Print(1, fout);

    fin.close();
    fout.close();
    return 0;
}