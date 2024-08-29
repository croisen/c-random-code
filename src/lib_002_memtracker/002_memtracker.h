#ifndef C_RANDOM_002_MEM_TRACKER_H
#define C_RANDOM_002_MEM_TRACKER_H

#include <stdlib.h>

void *MT_Malloc(size_t size);
void *MT_Calloc(size_t nmemb, size_t size);
void *MT_Realloc(void *ptr, size_t size);
void MT_Free(void *ptr);

#endif /* C_RANDOM_002_MEM_TRACKER_H */
