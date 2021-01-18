#include <iostream>
#include <stdlib.h>

#define MAX 30000

using namespace std;

// 0000 0000 0000 0000 
typedef unsigned long long int u64;

typedef struct Block{
    int block_num;
    u64 module;
    u64 reverse;
    
    int max;
    int min;
    bool used;
    
    Block &operator=(Block ex)
    {
        block_num = ex.block_num;
        module = ex.module;
        reverse = ex.reverse;

        max = ex.max;
        min = ex.min;
        used = ex.used;
        return *this;
    }
} Block;

void quickSort(int first, int last);
u64 getRotate90(u64 input); // 90µµ È¸Àü
u64 arr2u64(int module[4][4]); // int array -> uint64
void u642arr(u64 in, char out[16]); // uint64 -> int array
int isBlock(Block target, Block in); // target + in = BLOCK?

extern int makeBlock(int module[][4][4]);

Block b[MAX];

int main(void)
{
    static int module[MAX][4][4];

    srand(3); // 3 will be changed

    for (int tc = 1; tc <= 10; tc++)
    {
        for (int c = 0; c < MAX; c++)
        {
            int base = 1 + (rand() % 6); // 1 ~ 7
			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					module[c][y][x] = base + (rand() % 3); // 1 ~ 
                    if(module[c][y][x] >= 9)
                        cout << "module num ::" << c << ":" << y << ":" << x << endl;
				}
			}
        }
		cout << "#" << tc << " " << makeBlock(module) << endl;
    }

	return 0;
}
void quickSort(int first, int last)
{
    int pivot;
    int i;
    int j;
    Block temp;
     
    if (first < last)
    {
        pivot = first;
        i = first;
        j = last;
 
        while (i < j)
        {
            while (b[i].max >= b[pivot].max && i < last)
            {
                i++;
            }
            while (b[j].max < b[pivot].max)
            {
                j--;
            }
            if (i < j)
            {
                temp = b[i];
                b[i] = b[j];
                b[j] = temp;
            }
        }
 
        temp = b[pivot];
        b[pivot] = b[j];
        b[j] = temp;
 
        quickSort(first, j - 1);
        quickSort(j + 1, last);
    }
}

u64 getRotate90(u64 input){
    u64 ret = input % 1000000000000 * 10000 + (input/1000000000000);
    return ret;
}

u64 arr2u64(int module[4][4]){
    u64 ret = 0;
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            ret += module[y][x];
            ret *= 10;
        }
    }
    return ret/10;
}

void u642arr(u64 in, char out[16]){
    u64 ret = 0;
    for(int i = 15; i >= 0; i--){
        out[i] = in%10;
        in /= 10;
    }
}

int isBlock(Block target, Block in){
    if(in.used)
        return 0;

    int height = 0;

    for(int i = 0; i < 4; i++){
        char _target_reverse_[16] = {0,};
        char _in_module_[16] = {0,};
        u642arr(target.reverse,_target_reverse_);
        u642arr(in.module,_in_module_);

        int add_data = _target_reverse_[0] + _in_module_[0];
        int j = 1;
        for(j = 1; j < 16; j++){
            if(add_data != _target_reverse_[j] + _in_module_[j])
                break;
        }
        if(j == 16){
            in.used = true;
            target.used = true;
            height = add_data;
            break;
        }
        target.reverse = getRotate90(target.reverse);
    }
    
    return height;
}

int makeBlock(int module[][4][4]){
    int ret = 0;

    for (int c = 0; c < MAX; c++)
    {
        b[c].block_num = c;
        b[c].module = 0;
        b[c].reverse = 0;

        b[c].max = module[c][0][0];
        b[c].min = module[c][0][0];
        b[c].used = false;

        for (int y = 0; y < 4; y++)
        {
            for (int x = 0; x < 4; x++)
            {
                b[c].module += module[c][y][x]; b[c].module *= 10;
                b[c].reverse += module[c][y][3-x];  b[c].reverse *= 10;
                b[c].min = (b[c].min >  module[c][y][x])?  module[c][y][x] : b[c].min;
                b[c].max = (b[c].max < module[c][y][x])? module[c][y][x] : b[c].max;
            }
        }
        b[c].module /= 10;
        b[c].reverse /= 10;
    }

    quickSort(0,MAX-1);

    for (int c = 0; c < MAX; c++)
    {
        if(b[c].used == true)
            c++;
        
        for(int i = c+1; i < MAX; i++){
            ret += isBlock(b[c],b[i]);
            if(b[c].used == true){
                printf("%d ",ret);
                break;
            }
        }

    }


// -- Test Code

    // cout << "module  ::" << b[0].module << endl;
    // cout << "reverse ::" << b[0].reverse << endl;
    // cout << "min     ::" << b[0].min << endl;
    // cout << "max     ::" << b[0].max << endl;
    
    // cout << "module  ::" << b[MAX-1].module << endl;
    // cout << "reverse ::" << b[MAX-1].reverse << endl;
    // cout << "min     ::" << b[MAX-1].min << endl;
    // cout << "max     ::" << b[MAX-1].max << endl;
    
    // char test[16] = {0,};
    // u642arr(b[MAX-1].module,test);
    // cout << "module  ::" << b[MAX-1].module << endl;
    // cout << "module  ::";
    // for(int i = 0; i < 16; i++){
    //     cout << (int)test[i];
    // }
    // cout<< endl;

    // Block a;
    // a.block_num = 0;
    // a.module = 3222122313132231;
    // a.reverse = 2223322131311322;
    // a.max = 3;
    // a.min = 1;
    // a.used = false;

    // Block c;
    // c.block_num = 1;
    // c.module = 6665566757577566;
    // c.reverse = 5666766575757566;
    // c.used = false;
    // c.max = 7;
    // c.min = 5;

    // ret += isBlock(a,c);

    return ret;
}