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
int binarySearch(int low, int high, u64 target);
u64 getRotate90(u64 input); // rotate 90 degree
u64 arr2u64(int module[4][4]); // int array -> uint64
void u642arr(u64 in, char out[16]); // uint64 -> int array

extern int makeBlock(int module[][4][4]);

Block b[MAX];
Block reverse_b[MAX*4 + 4];

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
            while (reverse_b[i].reverse >= reverse_b[pivot].reverse && i < last)
            {
                i++;
            }
            while (reverse_b[j].reverse < reverse_b[pivot].reverse)
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
    int mid;
    if (low > high) 
    {
        return -1;
    }
 
    mid = (low + high) / 2;
 
    if (target < reverse_b[mid].reverse)
    {
        return binarySearch(low, mid - 1, target);
    }
    else if (reverse_b[mid].reverse < target)
    {
        return binarySearch(mid + 1, high, target);
    }
    else
    {
		int index = reverse_b[mid].block_num;

		reverse_b[mid].used = true;
		b[index].used = true;

        return mid;
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

		for(int i = 0; i < 4; i++)
		{
			reverse_b[c * 4 + i].block_num = c;
			reverse_b[c * 4 + i].max = module[c][0][0];
			reverse_b[c * 4 + i].min = module[c][0][0];
			reverse_b[c * 4 + i].used = false;
			reverse_b[c * 4 + i].module = b[c].module;
			
			reverse_b[c * 4 + i].reverse = (i == 0 ) ? b[c].reverse : getRotate90(reverse_b[c * 4 + i-1].reverse);
		}
    }

	if (binarySearch(0, MAX * 4 + 3, b[0].reverse) >= 0)
	{
		cout << b[0].reverse << endl;
	}
    quickSort(0,MAX*4 + 3);


	for (int c = 0; c < MAX; c++)
    {
        if(b[c].used == true)
            c++;
        
		int block_height = 16;
		u64 target_module = block_height * (1111111111111111) - b[c].module;
		for(;block_height >=3 || block_height >= b[c].max; block_height--){
			if(binarySearch(0,MAX * 4 + 3, b[c].reverse) >= 0){
				ret += block_height;
				break;
			}
			target_module -= 1111111111111111;
		}
    }


    return ret;
}