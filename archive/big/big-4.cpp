#include <cstdio>

int N;
int TIMER = 0;

struct StoreBlock;

struct QueCell {
    StoreBlock *block;
    QueCell *next;
    QueCell *prev;
};

struct StoreBlock{
    int id;
    int last_use_time;
    long long sell;
    QueCell *rnuq_cell;
    QueCell *lsrq_cell;
};


class RecentNotUseQue {
    QueCell *head;
    int size;
    StoreBlock *storage;
public:
    RecentNotUseQue(StoreBlock *storage) {
        this->storage = storage;
        size = 0;
        head = new QueCell();
        head->next = head;
        head->prev = head;
    }

    ~RecentNotUseQue() {
        QueCell *cell = head->next;
        while (cell != head) {
            QueCell *next = cell->next;
            delete cell;
            cell = next;
        }
        delete head;
        head = nullptr;
    }

    void add(int id, int time) {
        QueCell *cell = new QueCell();
        cell->block = storage + id;
        storage[id].rnuq_cell = cell;
        storage[id].last_use_time = time;
        cell->next = head->next;
        cell->prev = head;
        head->next->prev = cell;
        head->next = cell;
        size++;
    }

    void use(int id, int time) {
        QueCell *cell = storage[id].rnuq_cell;
        cell->prev->next = cell->next;
        cell->next->prev = cell->prev;
        cell->next = head->next;
        cell->prev = head;
        head->next->prev = cell;
        head->next = cell;
        storage[id].last_use_time = time;
    }

    int getRNUId() {
        return head->prev->block->id;
    }

    void deleteRNU() {
        QueCell *cell = head->prev;
        if(cell != head) {
            cell->block->rnuq_cell = nullptr;
            cell->prev->next = cell->next;
            cell->next->prev = cell->prev;
            delete cell;
            size--;
        }
    }

    void deleteId(int id) {
        QueCell *cell = storage[id].rnuq_cell;
        if(cell) {
            cell->prev->next = cell->next;
            cell->next->prev = cell->prev;
            delete cell;
            size--;
        }
        storage[id].rnuq_cell = nullptr;
    }
};

class LowestSellRateQue {
    QueCell *head;
    int size;
    StoreBlock *storage;
public:
    LowestSellRateQue(StoreBlock *storage) {
        this->storage = storage;
        size = 0;
        head = new QueCell();
        head->next = head;
        head->prev = head;
    }

    ~LowestSellRateQue() {
        QueCell *cell = head->next;
        while (cell != head) {
            QueCell *next = cell->next;
            delete cell;
            cell = next;
        }
        delete head;
        head = nullptr;
    }

    void add(int id) {
        QueCell *cell = new QueCell();
        cell->block = storage + id;
        storage[id].lsrq_cell = cell;
        // find the right place to insert regarding sell rate in descending order
        QueCell *pt = head->next;

        while (pt != head) {
            if(pt->block->sell < storage[id].sell || 
               (pt->block->sell == storage[id].sell && 
                pt->block->last_use_time < storage[id].last_use_time)) 
                break;
        }
        cell->next = pt;
        cell->prev = pt->prev;
        pt->prev->next = cell;
        pt->prev = cell;
        size++;
    }

    void sell(int id) {
        QueCell *cell = storage[id].lsrq_cell;
        // find the right place to insert regarding sell rate in descending order
        QueCell *pt = cell->prev;
        QueCell *prev_prev = pt;
        while (pt != head) {
            if(pt->block->sell > storage[id].sell || 
               (pt->block->sell == storage[id].sell && 
                pt->block->last_use_time > storage[id].last_use_time)) 
                break;
            pt = pt->prev;
        }
        if(pt != prev_prev) {
            cell->prev->next = cell->next;
            cell->next->prev = cell->prev;
            cell->next = pt->next;
            cell->prev = pt;
            pt->next->prev = cell;
            pt->next = cell;
        }
    }

    void use(int id, int time) {
        QueCell *cell = storage[id].lsrq_cell;
        storage[id].last_use_time = time;
        // find the right place to insert regarding sell rate in descending order
        QueCell *pt = cell->prev;
        QueCell *prev_prev = pt;
        while (pt != head) {
            if(pt->block->sell > storage[id].sell) 
                break;
            pt = pt->prev;
        }
        if(pt != prev_prev) {
            cell->prev->next = cell->next;
            cell->next->prev = cell->prev;
            cell->next = pt->next;
            cell->prev = pt;
            pt->next->prev = cell;
            pt->next = cell;
        }
    }

    int getLSRId() {
        return head->prev->block->id;
    }

    void deleteLSR() {
        QueCell *cell = head->prev;
        if (cell != head) {
            cell->block->lsrq_cell = nullptr;
            cell->prev->next = cell->next;
            cell->next->prev = cell->prev;
            delete cell;
            size--;
        }
    }

    void deleteId(int id) {
        QueCell *cell = storage[id].lsrq_cell;
        if (cell) {
            cell->block->lsrq_cell = nullptr;
            cell->prev->next = cell->next;
            cell->next->prev = cell->prev;
            delete cell;
            size--;
        }
        storage[id].lsrq_cell = nullptr;
    }

};

class StoreController {
    StoreBlock *storage;
    RecentNotUseQue *rnuq;
    LowestSellRateQue *lsrq;
    size_t size;
    int list_max;
    int list_size;

public:
    StoreController(size_t size, int list_max): size(size), list_max(list_max) {
        storage = new StoreBlock[size];
        rnuq = new RecentNotUseQue(storage);
        lsrq = new LowestSellRateQue(storage);
        list_size = 0;
        for (int i = 0; i < size; i++)
        {
            storage[i].id = i;
        }
    }

    ~StoreController() {
        delete rnuq;
        delete lsrq;
        delete[] storage;
    }

    void clearId(int id) {
        storage[id].sell = 0;
        storage[id].last_use_time = 0;
        storage[id].rnuq_cell = nullptr;
    }

    void use(int id, int mode) {
        if (storage[id].rnuq_cell) {
            rnuq->use(id, TIMER);
            lsrq->use(id, TIMER);
        } else {
            if (list_size == list_max) {
                if(mode == 1) {
                    int rnu_id = rnuq->getRNUId();
                    printf("%d\n", rnu_id);
                    rnuq->deleteRNU();
                    lsrq->deleteId(rnu_id);
                    clearId(rnu_id);
                    list_size--;
                } else if(mode == 2) {
                    int lsr_id = lsrq->getLSRId();
                    printf("%d\n", lsr_id);
                    lsrq->deleteLSR();
                    rnuq->deleteId(lsr_id);
                    clearId(lsr_id);
                    list_size--;
                }
            } else {
                list_size++;
                rnuq->add(id, TIMER);
                lsrq->add(id);
            }
        }
    }

    bool sell(int id) {
        if (storage[id].rnuq_cell) {
            //printf("1\n");
            storage[id].sell++;
            lsrq->sell(id);
        } else {
            printf("-1\n");
        }

        return true;
    }

    void display() {
        for (int i = 0; i < size; i++)
        {
            if(storage[i].lsrq_cell || storage[i].rnuq_cell)
                printf("%d ", storage[i].id);
        }
        printf("\n");
    }
};

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);

    StoreController sc(100001,n);

    TIMER = 0;

    for (int i = 0; i < m; i++)
    {
        int mode1, id, mode2;
        scanf("%d%d", &mode1, &id);
        if(mode1 == 2) {
            scanf("%d", &mode2);
            sc.use(id, mode2);
        } else {
            sc.sell(id);
        }
        TIMER++;
    }

    sc.display();

}