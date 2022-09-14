class Inner {
	public static int count;

	public Inner() {
		count += 1;
		System.out.printf("I'm constructed! (ID: %d)\n", count);
	}

	@Override
	protected void finalize() {
		System.out.println("I'm deconstructed!");
	}
} 


public class Destructor {
	public static void main() {
		Inner out = new Inner();

		for (int i = 0; i < 3; i++) {
			Inner in = new Inner();
		}
	}
}
