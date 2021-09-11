wave: wave.c Jwave.h share/test
	gcc wave.c -o $@.exe
	gcc -shared -o share/libJwave.so wave.c -fPIC
	gcc share/tests.c -Lshare -lJwave -o share/test
	#source share/update_path.bash

clean:
	rm -rf wave.exe
