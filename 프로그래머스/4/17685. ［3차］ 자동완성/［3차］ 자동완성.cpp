#include <string>
#include <vector>
using namespace std;

struct TRIE {
    TRIE *Node[26];
    int Child;
    bool Finish;

    void Insert(const char *Str);
    int Find(const char *Str, int Cnt);
};

int Trie_Idx;
TRIE Nodepool[1000010];

TRIE *Nodeset() {
    TRIE *NewNode = &Nodepool[Trie_Idx++];
    for (int i = 0; i < 26; i++)
        NewNode->Node[i] = NULL;
    NewNode->Child = 0;
    return NewNode;
}

void TRIE::Insert(const char *Str) {
    Child++;
    if (*Str == NULL) {
        Finish = true;
        return;
    }
    int Cur = *Str - 'a';
    if (Node[Cur] == NULL)
        Node[Cur] = Nodeset();
    Node[Cur]->Insert(Str + 1);
}

int TRIE::Find(const char *Str, int Cnt) {
    if (Child == 1 || *Str == NULL)
        return Cnt;
    int Cur = *Str - 'a';
    return Node[Cur]->Find(Str + 1, Cnt + 1);
}

int solution(vector<string> words) {
    Trie_Idx = 0;
    int answer = 0;
    int N = words.size();
    TRIE *Root = Nodeset();
    for (int i = 0; i < N; i++)
        Root->Insert(words[i].c_str());
    for (int i = 0; i < N; i++)
        answer = answer + Root->Find(words[i].c_str(), 0);
    return answer;
}
