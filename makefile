sort:sort.o test.o
	gcc $^ -o $@
	rm -f $^
sort.o: sort.c
	gcc -c $^ -o $@
test.o: test.c
	gcc -c $^ -o $@
.PHONY:clean

clean:sort
	rm -f $^

