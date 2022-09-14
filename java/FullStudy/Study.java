public class Study {
	public static void partStart(String partInfo) {
		final int totalLength = 100;
		
		int left = (totalLength - partInfo.length()) / 2;
		int right = totalLength - partInfo.length() - left;

		while (left != 0) {
			System.out.print("-");
			left -= 1;
		}

		System.out.print(partInfo);

		while (right != 0) {
			System.out.print("-");
			right -= 1;
		}

		System.out.println();
	}

	public static void partEnd() {
		partStart("END");
		System.out.println();
	}

	public static void main (String[] args) {
		partStart("Array sort and foreach Loop");
		StudyArray.main();
		partEnd();

		partStart("Java Types");
		Types.main();
		partEnd();

		partStart("Date And Time");
		DateAndTime.main();
		partEnd();

		/* finalizer is deprecated in openjdk17
		partStart("Deconstructor!");
		Destructor.main();
		partEnd();
		*/
	}
}
