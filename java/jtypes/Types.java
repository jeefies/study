// prtl = System.out.println;
// prt = System.out.print;

public class Types {
	public static void main(String[] argv) {
		for (int i = 0; i < argv.length; i++) {
			System.out.print(i);
			System.out.print(" Argv :");
			System.out.println(argv[i]);
		}

		new_array();

		string();

		num();

		and_or_xor();

		three();
	}

	public static void new_array() {
		int arr[] = new int[] {1, 2, 3};

		System.out.println("---------------------------Part for each loop and new array------------------------");
		// For Each loop
		for (int ai : arr) {
			System.out.println(ai);
		}
		System.out.println("------------------------------------Part END---------------------------------------");
		System.out.println();
	}

	public static void string() {
		System.out.println("------------------------Part for type string and operations------------------------");
		/* 注意new与c++中的new一样，会在堆中开辟新内存
		 * 如果不使用new,则多次相同的值会指向同一地址
		 */
		String str = new String("some string");
		String a = "some string";
		String b = "some string";
		System.out.print("a = ");
		System.out.println(a);
		System.out.print("b = ");
		System.out.println(b);
		System.out.print("a == b = ");
		System.out.println(a == b);
		System.out.print("str == a = ");
		System.out.println(str == a);
		// 在此之上,还有另一种只是比较内容的方法
		System.out.print("str.equals(a) = ");
		System.out.println(str.equals(a));
		System.out.println(str);

		// static string method valueOf(Object)
		// Others like Integer.parseInt(String)
		// Double.parseDouble(String)
		// Boolean.parseBoolean(String)
		System.out.print("String.valueOf(1) = ");
		System.out.println(String.valueOf(1));

		System.out.printf("Integer.parseInt(\"123\") = %d\n", Integer.parseInt("123"));
		System.out.printf("Double.parseDouble(\"123.23\") = %.2f\n", Double.parseDouble("123.23"));
		System.out.printf("Boolean.parseBoolean(\"true\") = %s\n", Boolean.parseBoolean("true"));
	

		System.out.println("------------------------------------Part END---------------------------------------");
		System.out.println();
	}

	public static void num() {
		System.out.println("----------------------------Part for numeric operations----------------------------");

		int A = 10;
		double B = 20.0;
		System.out.println(B/A);
		// This won't work (TypeError)
		// float C = 5.0;
		float C = (float) 5.0;
		System.out.println(B/C);

		int D = 3;
		System.out.println(A%D);
		System.out.println(A/D);

		/* Other operations like C
		 * a += b
		 * a -= b
		 * a /= b
		 * a *= b
		 */

		System.out.println("------------------------------------Part END---------------------------------------");
		System.out.println();
	}

	public static void and_or_xor() {
		System.out.println("----------------------------Part for boolean operations----------------------------");

		if (1 == 1 && 2 != 3) { // short and, if any is false, return false immediately
			System.out.println("Fuck");
		}

		if (2 == 2 || 2 == 1) { // short or, if any is true, return true immediately
			System.out.println("Fuck again");
		}

		// Notice that only base2 numbers have xor operation

		System.out.println("------------------------------------Part END---------------------------------------");
		System.out.println();
	}

	public static void three() {
		int x = 10;
		int y = 20;

		// Equal to `x if x > y else y` in python
		// As the same in C and C++
		int max = x > y ? x : y;

		if (max != y) {
			System.out.println("Three FUNC Error!");
		}
	}
}
