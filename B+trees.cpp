#include <stdio.h>
#include <stdlib.h>
#include<bits/stdc++.h> 
#include <fstream>
#include<vector> 
#include <string> 
#include <iostream>
#include <queue>
#include <utility> 
using namespace std;  

#define MAX 3

struct TreeNode{

    bool leaf;
    vector<int> val;
    TreeNode* next;
    vector<TreeNode*> child;
};


TreeNode* treeRoot;
pair<int,TreeNode*> emptyPair;

TreeNode* createNode()
{
    TreeNode* newNode = new TreeNode;
    newNode->leaf = true;
    vector<int> emptyvector;
    newNode->val.swap(emptyvector);
    vector<TreeNode*> emptytreenodevector(5,NULL);
    newNode->child.swap(emptytreenodevector);
    newNode->next = NULL;

    emptytreenodevector.clear();
    emptyvector.clear();

    return newNode;
}

void print(TreeNode* root) {
    //cerr<<"root : "<<root->val[0]<<endl;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty())
    {
        queue<TreeNode*> tempc;

        while(!q.empty())
        {
            TreeNode* cur = q.front();
            q.pop();
            //cerr<<"d ";
            for(int i =0;i<(cur->val.size());i++)
            {
                cerr<<cur->val[i]<<" ";
            }
            for(int i =0;i<(cur->child.size());i++)
            {
                if(cur->child[i] != NULL) tempc.push(cur->child[i]);
            }
            cerr << '|';
        }
        cerr << endl<<endl;
        q = tempc;

    }

    cerr << "=======" << endl;
}

bool findKey(int x,TreeNode* root)
{
    if(root == NULL)
        return false;

    
    if(root->leaf)
    {
        vector<int>::iterator it = find(root->val.begin(),root->val.end(),x);
        if(it == root->val.end())
            return false;
        else 
            return true;
    }

    for(int i =0;i<(root->val.size());i++)
    {
        if(i == 0 && x<root->val[0])
        {
            //cout<<root->val[0]<<" ";
            return findKey(x,root->child[0]);
        }
        else if(i<(root->val.size()-1) && x>=root->val[i] && x<root->val[i+1])
        {
            //cout<<root->val[i]<<" ";
            return findKey(x,root->child[i+1]);
        }
        else if(i == root->val.size()-1 && x>=(root->val[root->val.size()-1]))
        {
            //cout<<root->val[root->val.size()-1]<<" ";
            return findKey(x,root->child[root->val.size()]);
        }
    }

    return false;
}

int countKey(int x, TreeNode* root)
{
    if(root == NULL)
        return 0;

    if(root->leaf)
    {
        int ans=0;
        for(int i =0;i<(root->val.size());i++)
        {
            if(root->val[i] == x)
                ans++;
        }

        return ans;
    }

    int ans = 0;
    for(int i =0;i<(root->val.size());i++)
    {
        if(i == 0 && x<root->val[0])
        {
            //cerr<<root->val[0]<<endl;
            ans += countKey(x,root->child[0]);
        }
        else if(i<(root->val.size()-1) && x>=root->val[i] && x<root->val[i+1])
        {
            //cerr<<root->val[i]<<endl;
            ans += countKey(x,root->child[i+1]);
        }
        else if(i == root->val.size()-1 && x>=(root->val[root->val.size()-1]))
        {
            //cerr<<root->val[root->val.size()-1]<<endl;
            ans += countKey(x,root->child[root->val.size()]);
        }
    }

    return ans; 
}

int rangeCountKey(int x, int y, TreeNode* root)
{
    if(root == NULL)
        return 0;

    if(root->leaf)
    {
        int ans=0;
        for(int i =0;i<(root->val.size());i++)
        {
            if(root->val[i] >= x && root->val[i] <= y)
                ans++;
        }

        return ans;
    }

    int ans = 0;

    for(int i =0;i<(root->val.size());i++)
    {
        if(i == 0 && x<root->val[0])
        {
            //cerr<<root->val[0]<<endl;
            ans += rangeCountKey(x,y,root->child[0]);
        }
        if(i<(root->val.size()-1) && ((x>=root->val[i] && x<root->val[i+1]) || (y>=root->val[i] && y<root->val[i+1]) || (x<=root->val[i] && y>=root->val[i+1])))
        {
            //cerr<<root->val[i]<<endl;
            ans += rangeCountKey(x,y,root->child[i+1]);
        }
        if(i == root->val.size()-1 && y>=(root->val[root->val.size()-1]))
        {
            //cerr<<root->val[root->val.size()-1]<<endl;
            ans += rangeCountKey(x,y,root->child[root->val.size()]);
        }
    }

    return ans; 
}

pair<int,TreeNode*> splitNode(TreeNode* node,bool leafStat)
{
    TreeNode* temp = createNode();
    temp->leaf = leafStat;

    vector<int> a(node->val.begin(),node->val.begin()+2);
    
    int value = node->val[2];
    int len = 3;
    if(node->child[0] == NULL)
        len = 2;

    vector<int> b(node->val.begin()+len,node->val.end());
    vector<TreeNode*> c(node->child.begin(),node->child.begin()+3);
    for(int i = c.size();i<5;i++)
        c.push_back(NULL);
    vector<TreeNode*> d(node->child.begin()+3,node->child.end());
    for(int i = d.size();i<5;i++)
        d.push_back(NULL);

    node->val.swap(a);
    node->child.swap(c);
    temp->val.swap(b);

    temp->child = d;

    if(leafStat)
    {
        temp->next = node->next;
        node->next = temp;
    }

    a.clear();
    b.clear();
    c.clear();
    d.clear();

    return make_pair(value,temp);
}

pair<int,TreeNode*> insertKey(int x, TreeNode * root)
{
    if(root->leaf)
    {
        root->val.push_back(x);
        sort(root->val.begin(),root->val.end());

        //for(int i=0; i<(int) root->val.size(); ++i) cerr << "YAYY " << root->val[i] << endl;
        if(root->val.size() >= 4)
        {
            //cerr << "SPLIT: ";
            pair<int,TreeNode*> temp = splitNode(root,true);
            return temp;
        }
        else 
            return emptyPair;

    }

    bool passed = false;
    //cerr << "HI::: " << root->val.size() << endl;
    for(int i =0;i<(root->val.size());i++)
    {
        int cntr = 0;
        pair<int,TreeNode*> temp;
        temp.first = -1;
        temp.second = NULL;

        if(i==0 && x<root->val[0])
        {
            passed = true;
            temp = insertKey(x,root->child[0]);
            
            if(temp.second != NULL)
            {
                root->val.insert(root->val.begin(),temp.first);
                for(int j = 4;j>1;j--)
                    root->child[j] = root->child[j-1];
                root->child[1] = temp.second;  
            }
        }
        else if(i<(root->val.size()-1) && x>=root->val[i] && x<root->val[i+1])
        {

            passed = true;
            temp = insertKey(x,root->child[i+1]);

            if(temp.second != NULL)
            {
                root->val.insert(root->val.begin()+i+1,temp.first);
                for(int j = 4;j>(i+2);j--)
                    root->child[j] = root->child[j-1];
                root->child[i+2] = temp.second;
                //cerr<<"ADDED HERE "<<root->child[i+2]->val[0];  
            }
        }
        else if(i == root->val.size()-1 && x>=(root->val[root->val.size()-1]))
        {

            passed = true;
            temp = insertKey(x,root->child[root->val.size()]);
            //cerr << "HEH";
            if(temp.second != NULL)
            {
                root->child[root->val.size()+1] = temp.second;
                root->val.push_back(temp.first);  
            }
        }

        //if(cntr > 1) cerr << "YOO THERE'S AN ERROR\n\n\n";


        if (passed == true)
        {
            if(root->val.size() >= 4)
                return splitNode(root,false);
            return emptyPair;
        } 
    }

    return emptyPair;

}

void processCommand(char* input)
{
    string I = "INSERT",F = "FIND",C="COUNT",R = "RANGE";

    char* token = strtok(input, " ");

    if(!strcmp(token,I.c_str()))
    {
        //cerr<<"insert"<<endl;
        token = strtok(NULL, " ");
        int x = atoi(token);
        if(treeRoot == NULL)
        {
            treeRoot = createNode();
            treeRoot->val.push_back(x);
        }
        else 
        {
            pair<int,TreeNode*> temp = insertKey(x,treeRoot);
            
            if(temp.second != NULL)
            {
                TreeNode* rootnew = createNode();
                rootnew->leaf = false;
                rootnew->val.push_back(temp.first);
                rootnew->child[0] = treeRoot;
                rootnew->child[1] = temp.second;
                treeRoot =rootnew;
            }
            //print(treeRoot);
        }

        /*if(x == 5000 || x == 4000)
        {
                    cerr<<endl;
        print(treeRoot);
        }*/

    }
    else if(!strcmp(token,F.c_str()))
    {
        token = strtok(NULL, " ");
        int x = atoi(token);
        bool f = findKey(x,treeRoot);
        if(f)
            cout<<"YES"<<endl;
        else 
            cout<<"NO"<<endl;

    }
    else if(!strcmp(token,C.c_str()))
    {
        token = strtok(NULL, " ");
        int x = atoi(token);
        int num = countKey(x,treeRoot);
        cout<<num<<endl;
    }
    else if(!strcmp(token,R.c_str()))
    {
        token = strtok(NULL, " ");
        int x = atoi(token);
        token = strtok(NULL, " ");
        int y = atoi(token);   
        int num = rangeCountKey(x,y,treeRoot);
        cout<<num<<endl;   
    }
    else 
        cout<<"Incorrect command\n";

}


int main(int argc, char** argv)
{
    emptyPair.first = -1;
    emptyPair.second = NULL;

    if(argc < 2)
    {
        cout<<"Not enough arguments"<<endl;
        return 0;
    }

    treeRoot = NULL;
    char* filename=argv[1];

    ifstream file(filename);
    if (file.is_open()) {
        string line;
        int n =0;
        while (getline(file, line)) {
            char *cstr = new char[line.length()+1];
            //cerr << line <<endl;
            strcpy(cstr, line.c_str());
            n++;
            processCommand(cstr);
        }
        cerr<<endl;
        print(treeRoot);
        file.close();
    }
    return 0;
}