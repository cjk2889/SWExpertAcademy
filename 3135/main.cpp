#include <stdio.h>
#include <iostream>
using namespace std;

extern void init(void);

extern void insert(int buffer_size, char *buf);

extern int query(int buffer_size, char *buf);

int main(void) {
	freopen("input.txt", "r", stdin);
	int TestCase; 
	for (scanf("%d", &TestCase); TestCase--;) {
		int Query_N;
		scanf("%d", &Query_N);
		
		init();
		
		static int tc = 0;
		printf("#%d", ++tc);
		
		for (int i = 1; i <= Query_N; i++) {
			int type; scanf("%d", &type);

			if (type == 1) {
				char buf[15] = { 0, };
				scanf("%s", buf);
				
				int buffer_size = 0;
				while (buf[buffer_size]) buffer_size++;
				
				insert(buffer_size, buf);
			}
			else {
				char buf[15] = { 0, };
				scanf("%s", buf);
				
				int buffer_size = 0;
				while (buf[buffer_size]) buffer_size++;

				printf(" %d", query(buffer_size, buf));
			}
		}
		printf("\n");
		fflush(stdout);
	}
}

typedef struct Trie{
    bool finish;
    Trie *node[26];

    Trie(){
        finish = false;
        for(int i = 0; i < 26; i++){
            node[i] = NULL;
        }
    }

    void insert(const char* s){
        if (*s == '\0') {
            finish = true;
            return;
        }
        int cur = tolower(*s) - 'a';
        if (node[cur] == NULL) node[cur] = new Trie();
        node[cur]->insert(s + 1);
    }

    bool find(const char *s){
        if(*s == NULL){
            if (finish == true)
                return true;
            return false;
        }
        int cur = tolower(*s) - 'a';
        if (node[cur] == NULL)
            return false;
        return node[*s-'a']->find(s+1);
    }

    void countPath(const char *s, int* ret){
        if(*s == NULL){
            int cnt = 0;
            for(int i = 0; i < 26; i++){
                if( node[i] != NULL){
                    node[i]->countPath(s,ret);
                }
            }
            if(finish == true)
                *ret = (*ret)+1;
            return ;
        }
        int cur = tolower(*s) - 'a';
        if (node[cur] == NULL){
            return ;
        }
        node[cur]->countPath(s+1, ret);
    }
} Trie;

Trie* rt;

void init(void) {
    rt = new Trie();
}

void insert(int buffer_size, char *buf) {
    rt->insert(buf);
}

int query(int buffer_size, char *buf) {
    int ret = 0;
    rt->countPath(buf,&ret);
	return ret;
}