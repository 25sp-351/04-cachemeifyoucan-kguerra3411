CC = clang
CFLAGS = -Wall -g

TARGET_LRU = rod_cut_lru
TARGET_MRU = rod_cut_mru
SRCS = main.c cutting_options.c rod_cut.c
OBJS = $(SRCS:.c=.o)

# Add the corresponding cache implementation based on the target
all: format $(TARGET_LRU) $(TARGET_MRU)

$(TARGET_LRU): $(OBJS) lru_cache.o
	$(CC) $(CFLAGS) -o $(TARGET_LRU) $(OBJS) lru_cache.o

$(TARGET_MRU): $(OBJS) mru_cache.o
	$(CC) $(CFLAGS) -o $(TARGET_MRU) $(OBJS) mru_cache.o

rod_cut.o: rod_cut.c rod_cut.h
	$(CC) $(CFLAGS) -c rod_cut.c -o rod_cut.o

lru_cache.o: lru_cache.c lru_cache.h
	$(CC) $(CFLAGS) -c lru_cache.c -o lru_cache.o

mru_cache.o: mru_cache.c mru_cache.h
	$(CC) $(CFLAGS) -c mru_cache.c -o mru_cache.o

format:
	clang-format -i $(SRCS) *.h

clean:
	rm -f $(TARGET_LRU) $(TARGET_MRU) $(OBJS) lru_cache.o mru_cache.o
