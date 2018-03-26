#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <fstream>
using namespace std;

struct Node{
    Node(){
        letter = '*';
        left = nullptr;
        right = nullptr;
    }
    char letter;
    Node* left;
    Node* right;
};

struct List{
    Node* head = new Node;

    list<char> myStack;
    bool isHere = false;
    void initList();    // TODO: IMPORT FROM FILE
    void addNode(char letter, string direction);
    void printTree(Node* root);
    void traverse(Node* root, char ch);
    string convertToLetter(string str);
    void convertToCharacter(string str);
};

int main(){
    List morse;
    morse.initList();
//    morse.printTree(morse.head);  // for debugging

    string input;
    cout << "Enter text or morse code to convert another: ";
    getline(cin, input);    
    switch (input[0]){
        case '-':
        case '.':
            cout << morse.convertToLetter(input) << endl;
            break;
        default:    // TODO: ADD NUM TO CONVERTING
            transform(input.begin(), input.end(), input.begin(), ::toupper); // converting to uppercase
            //cout << morse.convertToCharacter(input) << endl;  // !!FİX
            morse.convertToCharacter(input);
            break;
    }
    

}

void List::initList(){
    ifstream file;
    file.open("morse.txt");
    if( !file.is_open() ){
        cout << "File could not open!" << endl;
        return;
    }

    string input;

    while( !file.eof() ){
        getline(file, input);
        addNode( input[0], &input[2] );
    }

    file.close();
}

void List::addNode(char letter, string direction){
    Node* temp = new Node;
    temp->letter = letter;

    Node* iter = head;
    char RL; // 'R'ight, 'L'eft = '-' , '.'
    for( int i=0; i<direction.length()-1; i++ ){
        RL = direction[i];     
        if( RL == '-' ){ // it means Right
            iter = iter->right;
        }
        if( RL == '.' ){ // it means Left
            iter = iter->left;
        }
    }

    RL = direction.back();
    
    if( RL == '-' ){ // it means Right
        iter->right = temp;
    } else
    if( RL == '.' ){ // it means Left
        iter->left = temp;
    }
    
}

void List::printTree(Node* root){
    // L N R
    if(root->left != nullptr) printTree(root->left);
    cout << root->letter << " ";
    if(root->right != nullptr) printTree(root->right);
}

void List::traverse(Node* root, char ch){
    if( root->letter == ch){
        isHere = true;
        return;
    }

    if(root->left != nullptr && isHere == false){
        myStack.push_back('.');
        traverse(root->left, ch);
    }
    if(root->right != nullptr && isHere == false){
        myStack.push_back('-');
        traverse(root->right, ch);
    }

    if(isHere == false )
        myStack.pop_back();
}

string List::convertToLetter(string str){
    Node* iter = head;
    string converted;
    for(int i=0; i<= str.length(); i++){
        if( str[i] == '-' && iter->right != nullptr){
            iter = iter->right;
            continue;
        }else 
        if( str[i] == '.' && iter->left != nullptr ){
            iter = iter->left;
            continue;
        }
        
        converted.append(&iter->letter);
        iter = head;
        
    }
    return converted;
}

//string List::convertToCharacter(string str){
void List::convertToCharacter(string str){
    string converted;
    int appendCount = 0;
    for(int i=0; i<str.length(); i++){
        char ch = str[i];
        isHere = false;
        traverse(head, ch); // traverse on tree and filling the stack
        int size = appendCount + myStack.size();
        while( !myStack.empty() ){
            cout << myStack.front() ;
            //converted.append( &myStack.front() );
            myStack.pop_front();
        }
        cout << " ";
//        converted.append(" ");
    }
    cout << endl;
//    return converted;    
}

//TODO: Karaktere çevirme hataları fixlenecek (string hasarlı döndürülüyor)
//TODO: Girilen tüm geçersiz karakter durumlarında hata mesajı gösterecek (eksik)