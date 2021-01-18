#include <iostream>
#include <stdlib.h>

#define MAX 30000

using namespace std;

// 0000 0000 0000 0000 
typedef unsigned long long int u64;

typedef struct Block{
    int block_num;

    u64 module;
    
    int max;
    int min;
    
    Block &operator=(Block ex)
    {
        block_num = ex.block_num;
        module = ex.module;

        max = ex.max;
        min = ex.min;
        return *this;
    }
} Block;

void quickSort(int first, int last);
int binarySearch(int low, int high, u64 target);
u64 arr2u64(int module[4][4]); // int array -> uint64
void u642arr(u64 in, char out[16]); // uint64 -> int array

extern int makeBlock(int module[][4][4]);

Block b[MAX];
Block reverse_b[MAX*4];

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
					module[c][y][x] = base + (rand() % 3); // 1 ~ 8
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
            while (reverse_b[i].module <= reverse_b[pivot].module && i < last)
            {
                i++;
            }
            while (reverse_b[j].module > reverse_b[pivot].module)
            {
                j--;
            }
            if (i < j)
            {
                temp = reverse_b[i];
                reverse_b[i] = reverse_b[j];
                reverse_b[j] = temp;
            }
        }
 
        temp = reverse_b[pivot];
        reverse_b[pivot] = reverse_b[j];
        reverse_b[j] = temp;
 
        quickSort(first, j - 1);
        quickSort(j + 1, last);
    }
}

int binarySearch(int low, int high, u64 target)
{
    int mid = (low + high) / 2;
    if (low > high) 
    {
        return -1;
    }
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (target == reverse_b[mid].module)
        {
            return reverse_b[mid].block_num;
        }
        else if (target < reverse_b[mid].module)
        {
            high = mid - 1;
        }
        else if (target > reverse_b[mid].module)
        {
            low = mid + 1;
        }
    }
    return -1;
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

int makeBlock(int module[][4][4]){
    int ret = 0;
    bool check_used[MAX] = {false,};

    for (int c = 0; c < MAX; c++)
    {
        check_used[c] = false;

        b[c].block_num = c;
        b[c].module = 0;

        b[c].max = module[c][0][0];
        b[c].min = module[c][0][0];

        reverse_b[c * 4 + 0].module = 0;
        reverse_b[c * 4 + 1].module = 0;
        reverse_b[c * 4 + 2].module = 0;
        reverse_b[c * 4 + 3].module = 0;

		for (int y = 0; y < 4; y++)
        {
            for (int x = 0; x < 4; x++)
            {
                b[c].module += module[c][y][x]; b[c].module *= 10;
                b[c].min = (b[c].min > module[c][y][x])? module[c][y][x] : b[c].min;
                b[c].max = (b[c].max < module[c][y][x])? module[c][y][x] : b[c].max;

                reverse_b[c * 4 + 0].module += module[c][3 - x][3 - y]; reverse_b[c * 4 + 0].module *= 10;
                reverse_b[c * 4 + 1].module += module[c][  y  ][3 - x]; reverse_b[c * 4 + 1].module *= 10;
                reverse_b[c * 4 + 2].module += module[c][  x  ][  y  ]; reverse_b[c * 4 + 2].module *= 10;
                reverse_b[c * 4 + 3].module += module[c][3 - y][  x  ]; reverse_b[c * 4 + 3].module *= 10;

                reverse_b[c * 4 + 0].block_num = c;
                reverse_b[c * 4 + 1].block_num = c;
                reverse_b[c * 4 + 2].block_num = c;
                reverse_b[c * 4 + 3].block_num = c;
            }
        }
        b[c].module /= 10;

        reverse_b[c * 4 + 0].module /= 10;
        reverse_b[c * 4 + 1].module /= 10;
        reverse_b[c * 4 + 2].module /= 10;
        reverse_b[c * 4 + 3].module /= 10;
    }

    quickSort(0,MAX * 4 - 1);

	for (int c = 0; c < MAX; c++)
    {   
        if(check_used[c] == true)
            c++;

        int block_height = 8;
        u64 target_module = (b[c].max + 6) * (1111111111111111) - b[c].module;

        for (; block_height >= 2 ; block_height--)
        {
            int searchResult = binarySearch(0, MAX * 4 - 1, target_module);
            if (searchResult >= 0 && check_used[searchResult] != true)
            {
                ret += target_module % 10 + b[c].module % 10;
                check_used[searchResult] = true;
                check_used[c] = true;
                break;
            }
            target_module -= 1111111111111111;
        }
    }


    return ret;
}