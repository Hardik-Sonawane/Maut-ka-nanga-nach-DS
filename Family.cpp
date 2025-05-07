#include<iostream>
using namespace std;

class BT{
    public:
    string data;
    BT *left;
    BT *right;

    BT(string x){
        data = x;
        left = NULL;
        right = NULL;
    }

    void insert(BT *parent, BT *child){
        if(parent->left == NULL){
            parent->left = child;
        }
        else {
            BT *temp = parent->left;
            while(temp->right != NULL){
                temp = temp->right;
            }
            temp->right = child;
        }
    }

    void display(BT *node, int level=0){
        if(node == NULL){
            return;
        }
        for(int i=0; i<level; i++)
            cout<<" ";
        cout<<node->data<<endl;

        if(node->left != NULL){
            display(node->left, level + 1);
        }
        if(node->right != NULL){
            display(node->right, level);
        }
    } 
};

int main()
{
    int ch;
    string name;
    BT *root = NULL, *newnode;
    do
    {
        cout<<"Family Tree Operations\n";
        cout<<"1. Insert\n";
        cout<<"2. Display\n";
        cout<<"3. Exit\n";
        cout<<"Enter choice: ";
        cin>>ch;
        switch(ch)
        {
            case 1: {
                cout<<"Enter member name: ";
                cin>>name;
                newnode = new BT(name);
                if(root == NULL) {
                    root = newnode;
                    cout<<"Added as root member\n";
                }
                else {
                    cout<<"Enter parent member: ";
                    string parent;
                    cin>>parent;


                    if(root->left == NULL) {
                        root->left = newnode;
                    }
                    else {
                        BT *temp = root->left;
                        while(temp->right != NULL) {
                            temp = temp->right;
                        }
                        temp->right = newnode;
                    }
                    cout<<"Member added\n";
                }
                break;
            }

            case 2:
                if(root == NULL) {
                    cout<<"Family tree is empty\n";
                }
                else {
                    root->display(root);
                }
                break;

            case 3:
                cout<<"Exiting...\n";
                break;

            default:
                cout<<"Invalid choice\n";
        }
    } while(ch != 3);

    return 0;
}
