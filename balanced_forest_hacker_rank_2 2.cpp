#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

struct node{
    int data;
    int nodenumber;
    node *left=NULL;
    node *middle = NULL;
    node *right = NULL;
}*root=NULL;
struct adsaver{
    int nn;//node nodenumber
    node *ad=nullptr;//address of t above nodenumber
    adsaver *link=nullptr;
}*start=NULL;

int sumer(node *root)
{
  int sum=0;
  queue<node*> q;

    if (root == NULL) return 0;

    q.push(root);

    while (!q.empty())
     {
        node *n = q.front();
        q.pop();
        sum+=n -> data;
       // cout << n -> data << " ";
        if (n -> left) q.push(n -> left);
        if (n -> middle) q.push(n -> middle);
        if (n -> right) q.push(n -> right);
    }
    
    return sum;
}


int finder(node *root)
{
    int a,b,c,r=0;
   node *current=root;
    if(current->left!=NULL)a=sumer(current->left);
    if(current->middle!=NULL)b=sumer(current->middle);
    if(current->right!=NULL)c=sumer(current->right);
    if(a==b)r=b-c;
    if(a==c)r=a-b;
    if(b==c)r=c-a;
    return r;
    
}
 void levelOrder(node *root) 
   {
    queue<node*> q;

    if (root == NULL) return;

    q.push(root);

    while (!q.empty())
     {
        node *n = q.front();
        q.pop();
        int r;
        if(n->left!=NULL||n->middle!=NULL||n->right!=NULL)
        r=finder(n);
        cout << n -> data << " ";
        if(r!=0)break;
        if (n -> left) q.push(n -> left);
        if (n -> middle) q.push(n -> middle);
        if (n -> right) q.push(n -> right);
    }
    
}

int balancedForest(vector<int> c, vector<vector<int>> edges) 
{
int i=0;
node *current;
while(i<c.size())
{
    current=new node;
    current->nodenumber=i+1;
    current->data=c[i];
    
    adsaver *adcurrent,*newad;
    adcurrent=start;
    if(adcurrent==NULL)
    {
        adcurrent=new adsaver;
        start=adcurrent;
        adcurrent->nn=i+1;
    adcurrent->ad=current;
    }
    else
    {
     while(adcurrent->link!=NULL)
    {
        adcurrent=adcurrent->link;
    }
    newad=new adsaver;
    adcurrent->link=newad;
    newad->nn=i+1;
    newad->ad=current;
    }
    i++;
}

int j=0;
int z,y;
while(j<edges.size())
{
    y=edges[j][0];
    z=edges[j][1];
    node *goit1,*goit2;
     adsaver *adcurrent1,*adcurrent2;
    adcurrent1=start;
    adcurrent2=start;
    while(adcurrent1!=NULL)
    {
        if(adcurrent1->nn==y) break;
        adcurrent1=adcurrent1->link;
    }
    goit1=adcurrent1->ad;
    while(adcurrent2!=NULL)
    {
        if(adcurrent2->nn==z) break;
        adcurrent2=adcurrent2->link;
    }
   
    goit2=adcurrent2->ad;
    if(root==NULL)
    {
        root=goit1;
    }
    if(goit1->left==NULL)
    {
        goit1->left=goit2;
    }
     else if(goit1->middle==NULL)
    {
        goit1->middle=goit2;
    }
    else if(goit1->right==NULL)
    {
        goit1->right=goit2;
    }
    
    
    j++;
}

levelOrder(root);
return 1;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string c_temp_temp;
        getline(cin, c_temp_temp);

        vector<string> c_temp = split_string(c_temp_temp);

        vector<int> c(n);

        for (int i = 0; i < n; i++) {
            int c_item = stoi(c_temp[i]);

            c[i] = c_item;
        }

        vector<vector<int>> edges(n - 1);
        for (int i = 0; i < n - 1; i++) {
            edges[i].resize(2);

            for (int j = 0; j < 2; j++) {
                cin >> edges[i][j];
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        int result = balancedForest(c, edges);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}

