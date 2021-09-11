all:
	@javac helloWorld/helloWorld.java helloWorld/Import.java
	
	@javac -d . Jar.java
	@jar -cvf Jar.jar com > /dev/null 2>/dev/null
	
	@CLASSPATH=helloWorld:. javac New.java
	@CLASSPATH=helloWorld:.:Jar.jar java New

clean:
	rm -rf *.jar
	rm -rf *.class
	rm -rf */*.class
	rm -rf com
