public class Human implements Animal {
	private	String name;
	private int age;

	public Human() {
		this("", -1);
	}
	public Human(String name) {
		this(name, -1);
	}

	public void setName(String name){
		this.name = name;
	}

	public String getName(){
		return this.name;
	}

	public void setAge(int age){
		this.age = age;
	}

	public int getAge(){
		return this.age;
	}

	public Human(String name, int age) {
		this.name = name;
		this.age = age;
	}

	public void eat() {
		System.out.println("start to end...");
		System.out.println("I've eaten!");
	}

	public void walk() {
		System.out.println("Walk! Walk! Walk!");
	}

	public void breathe() {
		System.out.println("Breathe! Never Stop!");
	}

	public void selfIntro() {
		System.out.printf("I'm %s\n", this.getName());
		if (this.getAge() != -1) {
			System.out.printf("I'm %d years old\n", this.getAge());
		}
	}
}
