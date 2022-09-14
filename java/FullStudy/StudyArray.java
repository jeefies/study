import java.util.Arrays;

public class StudyArray {
	public static void main () {
		// int[] nums is better than int nums[] in Java
		int[] nums = {1, 5, 4, 7, 2};

		Arrays.sort(nums);

		int i = 0;
		for (int n : nums) {
			System.out.printf("%d, ", n);
			nums[i] += 5;
			i += 1;
		}
		System.out.println();

		for (int n : nums) {
			System.out.printf("%d, ", n);
		}
		System.out.println();
	}
}
