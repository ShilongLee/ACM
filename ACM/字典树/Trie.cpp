class Trie
{
private:
    vector<Trie *> next;
    bool is_End;

public:
    /** Initialize your data structure here. */
    Trie() : next(26), is_End(false) {}

    /** Inserts a word into the trie. */
    void insert(string word)
    {
        Trie *now = this;
        int len = word.length();
        for (int i = 0; i < len; ++i)
        {
            if (now->next[word[i] - 'a'] == NULL)
                now->next[word[i] - 'a'] = new Trie();
            now = now->next[word[i] - 'a'];
        }
        now->is_End = true;
    }

    /** Returns if the word is in the trie. */
    bool search(string word)
    {
        Trie *now = this;
        int len = word.length();
        for (int i = 0; i < len; ++i)
        {
            int ch = word[i] - 'a';
            if(!now->next[ch])
                return false;
            now = now->next[ch];
        }
        return now->is_End;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix)
    {
        Trie *now = this;
        int len = word.length();
        for (int i = 0; i < len; ++i)
        {
            int ch = word[i] - 'a';
            if(!now->next[ch])
                return false;
            now = now->next[ch];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */