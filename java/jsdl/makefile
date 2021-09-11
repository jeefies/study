com.jsdl.jsdl: com/jsdl/jsdl.class libjsdl.so
	java -Djava.library.path=.:lib $@

com/jsdl/jsdl.class: com/jsdl/jsdl.java
	javac $^

libjsdl.so: jsdl.c
	gcc jsdl.c lib/libSDL2.so -fPIC -shared -o libjsdl.so -I. -Iinclude -Iinclude/linux
