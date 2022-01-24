template <int alpha>
class TrieNode
{
public:
    TrieNode *child[alpha];
    int pre;
#define loop(i) for (int i = 30; i >= 0; i--)
    TrieNode()
    {
        for (int i = 0; i < alpha; i++)
            child[i] = NULL;
        pre = 0;
    }
    int convert(int n, int i)
    {
        return ((n & (1 << i)) > 0);
    }
    void insert(int n)
    {
        TrieNode *curr = this;
        loop(i)
        {
            int ind = convert(n, i);
            if (!curr->child[ind])
                curr->child[ind] = new TrieNode();
            curr = curr->child[ind];
            curr->pre++;
        }
    }
    void del(int n)
    {
        TrieNode *curr = this;
        loop(i)
        {
            int ind = convert(n, i);
            if (curr->child[ind]->pre == 1)
            {
                curr->child[ind] = NULL;
                break;
            }
            curr = curr->child[ind];
            curr->pre--;
        }
    }
};