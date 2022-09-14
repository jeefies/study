public class Main {
	public static void living(Animal ani) {
		System.out.println("- - - - - Living - - - - -");
		ani.eat();
		ani.breathe();
		System.out.println("- - - - - Keep Living - - - - -\n");
	}

	public static void main (String[] args) {
		Man fwj = new Man("Fu Wei Ji", 14);
		fwj.selfIntro();

		Human unk = new Man("???", 10101001);
		// Still call fuck function
		// 方法依赖与对象，而不是类
		unk.selfIntro();

		Man unk_man = (Man)unk;

		Cat myCat = new Cat();
		myCat.breathe();
		myCat.eat();

		living(fwj);
		living(myCat);
		living(new Animal() { // Anonymous class
			public void eat() {
				System.out.println("I don't know what to eat...");
			}
			public void breathe() {
				System.out.println("I just follow my heart to do that...");
			}
		});
	}
}
