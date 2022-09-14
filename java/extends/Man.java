public class Man extends Human {

	public Man(String name, int age) {
		super(name, age);
	}

	public void fuck() {
		System.out.println("I can fuck my girl up!");
	}

	public void selfIntro() {
		super.selfIntro();
		this.fuck();
	}

}
