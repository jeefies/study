CC = g++

all: bubble_sort quick_sort radix_sort_lsd selection_sort  insertion_sort
	$(CC) bubble_sort.cpp -o bubble_sort
	$(CC) quick_sort.cpp -o quick_sort
	$(CC) radix_sort_lsd.cpp -o radix_sort_lsd
	$(CC) selection_sort.cpp -o selection_sort
	$(CC) insertion_sort.cpp -o insertion_sort

insertion_sort: insertion_sort.cpp
	$(CC) $^ -o $@

bubble_sort: bubble_sort.cpp
	$(CC) $^ -o $@

quick_sort: quick_sort.cpp
	$(CC) $^ -o $@

radix_sort_lsd: radix_sort_lsd.cpp
	$(CC) $^ -o $@

selection_sort: selection_sort.cpp
	$(CC) $^ -o $@

clean:
	rm bubble_sort
	rm quick_sort
	rm radix_sort_lsd
	rm selection_sort
	rm insertion_sort
