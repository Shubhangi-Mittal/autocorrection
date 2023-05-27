#include<iostream>
#include<fstream>
#include<string>
using namespace std;
//Global variables (for the purpose of flags) => 
//found: to indicate whether the word is found or not
//len: to indicate user specified length
int found=0,len=-9999; 
class node
{ //Node class
    public:
    char info; //the letter corresponding to node is stored here
    string Word;
    //for storing words (if completed) till that node
    class node* ptrs[256];
    //to hold the pointers to 256 next possible letters (ASCII)
    node()
    { 
    //node class constructor
        for(int i=0;i<256;i++)
        {
            ptrs[i]=NULL;
        }
        info=NULL;
        Word="";
    }
};
void insertword(string word,int pos,class node * root)
{ 
    //function to insert word
    if(word.length()==pos)
    { 
        //if last position is reached
        root->Word=word; 
        //Put the final word into node
        return;
    }
    if( root-> ptrs[word[pos]]==NULL )
    { 
        //if next letter is not found
        node *newnode; 
        //create new node
        newnode= new node; 
        newnode->info=word[pos]; 
        //with info = letter to store
        root->ptrs[word[pos]]=newnode; 
        //pointer from current letter to next letter's node
        insertword(word,pos+1,root->ptrs[word[pos]]); 
        //call insert word finction again with next position
    }
    else
        insertword(word,pos+1,root->ptrs[word[pos]]); 
    //if next letter to add already exists
} 
//call insert word directly
void printall(class node * root)
{ 
    //function to print all possible words given root of trie
    for(int i=0;i<256;i++) 
    //for all 256 pointers in the provided root node
        if(root->ptrs[i]!=NULL)
        { 
            //if those pointers are not null
            printall(root->ptrs[i]); 
            //call printall recursively at each one of them
        } 
    //Similar to DFS traversal
    
    //following code will be executed when the recursion starts backtracking
    if(root->Word != "" && (root->Word.length()==len && len!=-9999)) 
    //first user specified length words will be searched
        cout<<" -> "<<root->Word<<endl; 
    //and printed if they exist
    else if(root->Word != "" && len==-9999) 
    //otherwise, all matching words are printed
    {
        cout<<" -> "<<root->Word<<endl;
        found=1;
    }
 
}
void suggest(string key,int pos, class node * root)
{ 
    //function to print suggested words
    if(root->ptrs[key[pos]] != NULL)
    { 
        //if node is the last position of given key
        suggest(key,pos+1,root->ptrs[key[pos]]); 
        //call suggest with next position
    } 
    else
    {
        printall(root); 
        //when last node, print all words below it 
    }
}
int main()
{
    ifstream in("wordlist.txt"); 
    //input file "wordlist.txt"
    string word,current="",key; 
    char ch;
    node *root; 
    //root node of trie defined
    root = new node;
    while(in)
    {
        in>>word; 
        //file parsed and all words input to trie
        insertword(word,0,root);
    }
    in.close(); 
    //file stream closed
    cout<<endl<<"Trie has been created successfully!"<<endl; 
    //trie created
    cout<<"Enter the starting letters of the word : ";
    cin>>key; 
    //input key from user
    cout<<"Do you know the length of the word?(y/n)"; 
    //input required word length(if any)
    cin>>ch;
    sos:
    if(ch=='y')
    {
        cout<<"Enter the length\n";
        cin>>len;
        if(len<=0) 
        { 
            //if user enters incorrect string length
            cout<<"Please enter a length greater than 0.\n";
            goto sos;
        }
    }
    cout<<endl<<"Possible suggestions are :"<<endl; 
    suggest(key,0,root); 
    //suggest function call
    if(found && ch=='y')
    {
        cout<<"No words of specified length found"; 
        //if no string found 
    }
 return 0;
}


