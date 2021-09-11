public class helloWorld {
	public static void main(String[] args) {
		System.out.println("Hello World");
		Person p = new Person();
		p.SayHello();
	}
}

class Person {
	public static void SayHello() {
		System.out.println("I say Hello to you");
	}
}
