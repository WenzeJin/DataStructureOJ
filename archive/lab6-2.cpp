#include<iostream>
#include<cstdio>

using namespace std;

struct MatNode {
    MatNode *prev;
    int i;
    int j;
    int val;
    MatNode* next;
};

int getMul(MatNode* matAihead, MatNode* matBjhead) {
    MatNode *pa = matAihead->next;
    MatNode *pb = matBjhead->next;
    int result = 0;

    while(pa != matAihead && pb != matBjhead){
        if(pa->j == pb->i) {
            result += pa->val * pb->val;
            pa = pa->next;
            pb = pb->next;
        } else if(pa->j < pb->i) {
            pa = pa->next;
        } else if(pa->j > pb->i) {
            pb = pb->next;
        }
    }

    return result;
}

void insert(int i, int j, int val, MatNode* head) {
    MatNode * temp = new MatNode;
    temp->i = i;
    temp->j = j;
    temp->val = val;
    temp->prev = head->prev;
    temp->next = head;
    head->prev->next = temp;
    head->prev = temp;
}

int main()
{
    int ais, ajs, bis, bjs;

    cin >> ais >> ajs >> bjs;
    bis = ajs;

    MatNode *Aihead[ais];
    MatNode *Bjhead[bjs];

    bool aicontain[ais];
    bool bjcontain[bjs];

    for (int i = 0; i < ais; i++){
        Aihead[i] = new MatNode;
        aicontain[i] = false;
        Aihead[i]->next = Aihead[i];
        Aihead[i]->prev = Aihead[i];
    }

    for (int i = 0; i < bjs; i++){
        Bjhead[i] = new MatNode;
        bjcontain[i] = false;
        Bjhead[i]->next = Bjhead[i];
        Bjhead[i]->prev = Bjhead[i];
    }

    for (int i = 0; i < ais; i++) {
        for (int j = 0; j < ajs; j++) {
            int temp;
            scanf("%d", &temp);
            if (temp)
            {
                aicontain[i] = true;
                insert(i, j, temp, Aihead[i]);
            }
        }
    }

    for (int i = 0; i < bis; i++) {
        for (int j = 0; j < bjs; j++) {
            int temp;
            scanf("%d", &temp);
            if(temp) {
                bjcontain[j] = true;
                insert(i, j, temp, Bjhead[j]);
            }
        }
    }

    int result[ais][bjs];

    for (int i = 0; i < ais; i++) {
        for (int j = 0; j < bjs; j++) {
            if(aicontain[i] && bjcontain[j])
                result[i][j] = getMul(Aihead[i], Bjhead[j]);
            else
                result[i][j] = 0;
        }
    }

    for (int i = 0; i < ais; i++) {
        for (int j = 0; j < bjs; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
}