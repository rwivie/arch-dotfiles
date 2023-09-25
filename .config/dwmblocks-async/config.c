#include "config.h"

#include "block.h"
#include "util.h"

Block blocks[] = {
    {"sb-updates", 3600, 1 },
    {"sb-disk-2",  1800, 3 },
    {"sb-memory",  10,   4 },
    {"sb-loadavg", 5,    5 },
    {"sb-mic",     0,    6 },
    {"sb-record",  0,    7 },
    {"sb-volume",  0,    8 },
    {"sb-date-2",  1,    10},
};

const unsigned short blockCount = LEN(blocks);
