#ifndef _TRIE_
#define _TRIE_

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <assert.h>
#include <cstring>
#include <cmath>
using namespace std;
const int MaxBranchNum = 26;//如果区分大小写，可扩展到52

/*定义trie树结点*/
class TrieNode{
public:
    char* word; //节点表示的单词
    int count;  //单词出现的次数
    TrieNode* nextBranch[MaxBranchNum];//指向26个字符节点的指针
public:
    TrieNode() : word(NULL),count(0){
        memset(nextBranch,NULL,sizeof(TrieNode*)  * MaxBranchNum);
    }
};

/*定义类Trie*/
class Trie{
public:
    Trie();
    ~Trie();
    void Insert(const char* str);//插入字符串str
    bool Search(const char* str,int& count);//查找字符串str，并返回出现的次数
    bool Remove(const char* str);//删除字符串str
    void PrintALL();//打印trie树中所有的结点
    void PrintPre(const char* str);//打印以str为前缀的单词
private:
    TrieNode* pRoot;
private:
    void Destory(TrieNode* pRoot);
    void Print(TrieNode* pRoot);
};

#endif //_TRIE_

Trie::Trie(){
    pRoot = new TrieNode();//注意字典树的根不存放字符
}

Trie::~Trie(){
    Destory(pRoot);
}

/*插入一个单词*/
void Trie::Insert(const char* str){
    assert(NULL != str);
    int index;
    TrieNode* pLoc = pRoot;
    for (int i = 0;str[i];i++){
        index = str[i] - 'a';//如果区分大小写，可以扩展

        if(index < 0 || index > MaxBranchNum){//不执行插入
            return;
        }

        if (NULL == pLoc->nextBranch[index]){//该单词的前缀不存在，要生成该结点
            pLoc->nextBranch[index] = new TrieNode();
        }
        pLoc = pLoc->nextBranch[index];
    }
    if (NULL != pLoc->word){//单词已经出现过
        pLoc->count++;
        return;
    }
    else {  //单词没有出现过，应该插入单词
        pLoc->count++;
        pLoc->word = new char[strlen(str) + 1];
        assert(NULL != pLoc->word);
        strcpy(pLoc->word,str);
    }
}

/*查找一个单词，如果存在该单词，则返回其出现次数*/
bool Trie::Search(const char* str,int& count){
    assert(str != NULL);
    int i = 0;
    int index = -1;;
    TrieNode* pLoc = pRoot;
    while(pLoc && *str){
        index = *str - 'a';//如果区分大小写，可以扩展

        if(index < 0 || index > MaxBranchNum){//不是一个单词，不执行插入
            return false;
        }

        pLoc = pLoc->nextBranch[index];
        str++;
    }
    if (pLoc && pLoc->word){//条件成立，找到该单词
        count = pLoc->count;
        return true;
    }
    return false;
}

bool Trie::Remove(const char* str){
    assert(NULL != str);
    int index = -1;;
    TrieNode* pLoc = pRoot;
    while(pLoc && *str){
        index = *str - 'a';//如果区分大小写，可以扩展

        if(index < 0 || index > MaxBranchNum){//不是一个单词，不执行插入
            return false;
        }

        pLoc = pLoc->nextBranch[index];
        str++;
    }
    if (pLoc && pLoc-> word){//条件成立，找到该单词
        delete[] pLoc->word;
        pLoc->word = NULL;
        return true;
    }
    return false;
}

void Trie::PrintALL(){
    Print(pRoot);
}

void Trie::PrintPre(const char* str){
    assert(str != NULL);
    int i = 0;
    int index = -1;;
    TrieNode* pLoc = pRoot;
    while(pLoc && *str){
        index = *str - 'a';//如果区分大小写，可以扩展

        if(index < 0 || index > MaxBranchNum){//不是一个单词，不执行插入
            return;
        }

        pLoc = pLoc->nextBranch[index];
        str++;
    }
    if (pLoc){//条件成立，找到该单词
        Print(pLoc);
    }
}

/*按照字典顺序输出以pRoot为根的所有的单词*/
void Trie::Print(TrieNode* pRoot){
    if (NULL == pRoot)
    {
        return;
    }
    //输出单词
    if (NULL != pRoot->word){
        cout<<pRoot->word<<" "<<pRoot->count<<endl;
    }
    //递归处理分支
    for (int i = 0;i < MaxBranchNum;i++){
        Print(pRoot->nextBranch[i]);
    }
}

/*销毁trie树*/
void Trie::Destory(TrieNode* pRoot){
    if (NULL == pRoot){
        return;
    }
    for (int i = 0;i < MaxBranchNum;i++){
        Destory(pRoot->nextBranch[i]);
    }
    //销毁单词占得空间
    if (NULL != pRoot->word){
        delete []pRoot->word;
        pRoot->word = NULL;
    }
    delete pRoot;//销毁结点
    pRoot = NULL;
}

int main(){
    Trie t;
    string str;
    int count = -1;
    ifstream in("word.txt");
    //把单词输入字典树
    while(in >> str){
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);//大写变小写
        t.Insert(str.c_str());
    }

    string words="the";
    //查找
    bool isFind = t.Search(words,count);
    if (isFind){
        cout<<"存在, 出现次数："<<count<<endl;
    }
    else{
        cout<<"不存在!"<<endl;
    }
    //输出
    t.PrintALL();
    //删除
    bool isDel = t.Remove(words);
    if (isDel){
        cout<<"删除成功!"<<endl;
    }
    else{
        cout<<"删除失败!"<<endl;
    }
    //输出以w开头的单词
    t.PrintPre("w");
    cout<<endl;
    system("pause");
}
