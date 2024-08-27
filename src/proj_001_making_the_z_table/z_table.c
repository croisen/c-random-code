#include "001_dyn_sized_array.h"

typedef struct Dyn_Arr_2 {
    int used;
    int size;
    double *data;
} Dyn_Arr_2;

int main(void)
{
    Dyn_Arr_2 arr;
    Dyn_S_Arr_Init(&arr);
    for (int i = 0; i < 700; i++)
        Dyn_S_Arr_Push_Back(&arr, i);

    Dyn_S_Arr_Free(&arr);
    return 0;
}
