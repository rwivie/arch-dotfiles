#ifndef CONFIG_H
#define CONFIG_H

// String used to delimit block outputs in the status.
#define DELIMITER "  "

// Maximum number of Unicode characters that a block can output.
#define MAX_BLOCK_OUTPUT_LENGTH 45

// Control whether blocks are clickable.
#define CLICKABLE_BLOCKS 1

// Control whether a leading delimiter should be prepended to the status.
#define LEADING_DELIMITER 0

// Control whether a trailing delimiter should be appended to the status.
#define TRAILING_DELIMITER 0

// Define blocks for the status feed as X(cmd, interval, signal).
#define BLOCKS(X)         \
    X("sb-music", 5, 1)   \
    X("sb-updates", 3600, 2)  \
    X("sb-disk-2", 1800, 3) \
    X("sb-memory", 10, 4) \
    X("sb-loadavg", 5, 5) \
    X("sb-mic", 60, 6)     \
    X("sb-record", 0, 7)  \
    X("sb-volume", 1, 8)  \
    X("sb-date-2", 1, 9)

#endif  // CONFIG_H
