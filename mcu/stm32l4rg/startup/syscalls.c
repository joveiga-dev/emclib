



int _read(int file, char *ptr, int len)
{
    (void)file;
    (void)ptr;
    (void)len;
    return 0;
}

int _close(int file)
{
    (void)file;
    return -1;
}

int _lseek(int file, int ptr, int dir)
{
    (void)file;
    (void)ptr;
    (void)dir;
    return 0;
}

extern char _end;
static char *heap_end;

void *_sbrk(int incr)
{
    char *prev_heap;

    if (heap_end == 0)
    {
        heap_end = &_end;
    }

    prev_heap = heap_end;
    heap_end += incr;

    return (void *)prev_heap;
}
