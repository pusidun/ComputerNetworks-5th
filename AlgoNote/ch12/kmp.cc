
const int len = 100;
int next[len];

void getNext(char s[], int len) {
    int j = -1;
    next[0] = -1;
    for(int i = 0; i < len; ++i) {
        while(j != -1 && s[i] != s[j+1]) {
            j = next[j];
        }
        if(s[i] == s[j+1])
            ++j;
        next[i] = j;
    }
}

int KMP(char text[], char pattern[]) {
    int n = strlen(text), m = strlen(pattern);
    getNext(pattern, m);
    int ans = 0, j = -1;
    for(int i = 0; i < n; ++i) {
        while(j != -1 && text[i] != pattern[j+1]) {
            j = next[j];
        }
        if(text[i] == pattern[j+1])
            j++;
        if(j == m-1) {
            ans++;
            j = next[j];
        }
    }
    return ans;
}