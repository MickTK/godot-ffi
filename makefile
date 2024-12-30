demo/bin/testlib.so: testlib/testlib.cpp
	gcc -shared testlib/testlib.cpp -o demo/bin/testlib.so

clean:
	rm -f demo/bin/*.so

.PHONY: clean
