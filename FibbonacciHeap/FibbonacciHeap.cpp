#include <bits/stdc++.h>
using namespace std;

class Node {
   public:
    Node *left;
    Node *right;
    Node *parent;
    Node *child;
    char mark;
    int degree;
    int key;
    char c;
    Node(int x) {
        left = NULL, right = NULL, parent = NULL, child = NULL;
        key = x, degree = 0;
    }
};

class Fib_Heap {
   public:
    int number_of_Nodes;
    Node *min;
    int number_of_marked_Nodes;

   public:
    Fib_Heap() {
        min = NULL;
        number_of_Nodes = 0;
        number_of_marked_Nodes = 0;
    }
    void insert(int val) {
        number_of_Nodes++;
        Node *new_Node = new Node(val);
        new_Node->left = new_Node;
        new_Node->right = new_Node;
        if (min != NULL) {
            (min->left)->right = new_Node;
            new_Node->right = min;
            new_Node->left = min->left;
            min->left = new_Node;
            if (new_Node->key < min->key) min = new_Node;
        } else {
            min = new_Node;
        }
    }

    void find_min() { cout << "min of heap is: " << min->key << endl; }
    void display() {
        Node *ptr = min;
        if (ptr == NULL)
            cout << "The Heap is Empty" << endl;

        else {
            cout << "The root Nodes of Heap are: " << endl;
            do {
                cout << ptr->key;
                ptr = ptr->right;
                if (ptr != min) {
                    cout << "-->";
                }
            } while (ptr != min && ptr->right != NULL);
            cout << endl
                 << "The heap has " << number_of_Nodes << " Nodes" << endl;
        }
    }

    Fib_Heap *union_Heap(Fib_Heap *H2) {
        Fib_Heap *H = new Fib_Heap();
        if (!H2->min) {
            H->min = min;
            H->number_of_marked_Nodes = number_of_marked_Nodes;
            H->number_of_Nodes = number_of_Nodes;
            return H;
        }
        if (!min) {
            H->min = H2->min;
            H->number_of_marked_Nodes = H2->number_of_marked_Nodes;
            H->number_of_Nodes = H2->number_of_Nodes;
            return H;
        }

        /// union
        H->min = min;
        H->number_of_marked_Nodes =
            number_of_marked_Nodes + H2->number_of_marked_Nodes;
        H->number_of_Nodes = number_of_Nodes + H2->number_of_Nodes;

        Node *Hstart = H->min;
        Node *Hend = H->min->left;
        Node *H2start = H2->min;
        Node *H2end = H2->min->left;

        Hend->right = H2start;
        H2start->left = Hend;
        H2end->right = Hstart;
        Hstart->left = H2end;

        return H;
    }

    // Linking the heap Nodes in parent child relationship
    void Fibonnaci_link(Node *ptr2, Node *ptr1) {
        (ptr2->left)->right = ptr2->right;
        (ptr2->right)->left = ptr2->left;
        if (ptr1->right == ptr1) min = ptr1;
        ptr2->left = ptr2;
        ptr2->right = ptr2;
        ptr2->parent = ptr1;
        if (ptr1->child == NULL) ptr1->child = ptr2;
        ptr2->right = ptr1->child;
        ptr2->left = (ptr1->child)->left;
        ((ptr1->child)->left)->right = ptr2;
        (ptr1->child)->left = ptr2;
        if (ptr2->key < (ptr1->child)->key) ptr1->child = ptr2;
        ptr1->degree++;
    }
    // Consolidating the heap
    void Consolidate() {
        int temp1;
        float temp2 = (log(number_of_Nodes)) / (log(2));
        int temp3 = temp2;
        Node *arr[temp3 + 1];
        for (int i = 0; i <= temp3; i++) arr[i] = NULL;
        Node *ptr1 = min;
        Node *ptr2;
        Node *ptr3;
        Node *ptr4 = ptr1;
        do {
            ptr4 = ptr4->right;
            temp1 = ptr1->degree;
            while (arr[temp1] != NULL) {
                ptr2 = arr[temp1];
                if (ptr1->key > ptr2->key) {
                    ptr3 = ptr1;
                    ptr1 = ptr2;
                    ptr2 = ptr3;
                }
                if (ptr2 == min) min = ptr1;
                Fibonnaci_link(ptr2, ptr1);
                if (ptr1->right == ptr1) min = ptr1;
                arr[temp1] = NULL;
                temp1++;
            }
            arr[temp1] = ptr1;
            ptr1 = ptr1->right;
        } while (ptr1 != min);
        min = NULL;
        for (int j = 0; j <= temp3; j++) {
            if (arr[j] != NULL) {
                arr[j]->left = arr[j];
                arr[j]->right = arr[j];
                if (min != NULL) {
                    (min->left)->right = arr[j];
                    arr[j]->right = min;
                    arr[j]->left = min->left;
                    min->left = arr[j];
                    if (arr[j]->key < min->key) min = arr[j];
                } else {
                    min = arr[j];
                }
                if (min == NULL)
                    min = arr[j];
                else if (arr[j]->key < min->key)
                    min = arr[j];
            }
        }
    }

    // Function to extract minmum Node in the heap
    void Extract_min() {
        if (min == NULL)
            cout << "The heap is empty" << endl;
        else {
            Node *temp = min;
            Node *pntr;
            pntr = temp;
            Node *x = NULL;
            if (temp->child != NULL) {
                x = temp->child;
                do {
                    pntr = x->right;
                    (min->left)->right = x;
                    x->right = min;
                    x->left = min->left;
                    min->left = x;
                    if (x->key < min->key) min = x;
                    x->parent = NULL;
                    x = pntr;
                } while (pntr != temp->child);
            }
            (temp->left)->right = temp->right;
            (temp->right)->left = temp->left;
            min = temp->right;
            if (temp == temp->right && temp->child == NULL)
                min = NULL;
            else {
                min = temp->right;
                Consolidate();
            }
            number_of_Nodes--;
        }
    }

    // Cutting a Node in the heap to be placed in the root list
    void Cut(Node *found, Node *temp) {
        if (found == found->right) temp->child = NULL;

        (found->left)->right = found->right;
        (found->right)->left = found->left;
        if (found == temp->child) temp->child = found->right;

        temp->degree = temp->degree - 1;
        found->right = found;
        found->left = found;
        (min->left)->right = found;
        found->right = min;
        found->left = min->left;
        min->left = found;
        found->parent = NULL;
        found->mark = 'B';
    }

    // Recursive cascade cutting function
    void Cascase_cut(Node *temp) {
        Node *ptr5 = temp->parent;
        if (ptr5 != NULL) {
            if (temp->mark == 'W') {
                temp->mark = 'B';
            } else {
                Cut(temp, ptr5);
                Cascase_cut(ptr5);
            }
        }
    }

    // Function to decrease the value of a Node in the heap
    void Decrease_key(Node *found, int val) {
        if (min == NULL) cout << "The Heap is Empty" << endl;

        if (found == NULL) cout << "Node not found in the Heap" << endl;

        found->key = val;

        Node *temp = found->parent;
        if (temp != NULL && found->key < temp->key) {
            Cut(found, temp);
            Cascase_cut(temp);
        }
        if (found->key < min->key) min = found;
    }

    // Function to find the given Node
    void Find(Node *mini, int old_val, int val) {
        Node *found = NULL;
        Node *temp5 = mini;
        temp5->c = 'Y';
        Node *found_ptr = NULL;
        if (temp5->key == old_val) {
            found_ptr = temp5;
            temp5->c = 'N';
            found = found_ptr;
            Decrease_key(found, val);
        }
        if (found_ptr == NULL) {
            if (temp5->child != NULL) Find(temp5->child, old_val, val);
            if ((temp5->right)->c != 'Y') Find(temp5->right, old_val, val);
        }
        temp5->c = 'N';
        found = found_ptr;
    }

    // Deleting a node from the heap
    void Deletion(int val) {
        if (min == NULL)
            cout << "The heap is empty" << endl;
        else {
            // Decreasing the value of the node to 0
            Find(min, val, 0);

            // Calling Extract_min function to
            // delete minimum value node, which is 0
            Extract_min();
            cout << "Key Deleted" << endl;
        }
    }
};

int main() {
    Fib_Heap *H1 = new Fib_Heap();

    H1->insert(4);
    H1->insert(3);
    H1->insert(7);
    H1->insert(5);
    H1->insert(2);
    H1->insert(12);
    H1->insert(1);
    H1->insert(10);

    cout << "Heap 1 \n";
    H1->display();

    // H1->find_min();

    Fib_Heap *H2 = new Fib_Heap();
    H2->insert(7);
    H2->insert(30);
    H2->insert(40);

    cout << "Heap2 \n";
    H2->display();

    cout << "\n";
    Fib_Heap *H3 = H1->union_Heap(H2);
    cout << "After Merging New Heap is Heap3"
         << " \n";
    H3->display();
    H3->find_min();
    cout << "\n";
    H3->Extract_min();
    // cout << "After Extract Min in Heap3\n";
    // H3->Find(H3->min, 7, 6);
    H3->display();

    // cout << "Deleting value 12"
    //      << " \n";
    // H3->Deletion(1);
    // H3->display();
    return 0;
}
