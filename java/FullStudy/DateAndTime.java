import java.util.Date;

public class DateAndTime {
	public static void main() {
		Date first = new Date();
		System.out.printf("Current time %d\n", first.getTime());

		System.out.printf("Now time is: %s\n", new Date());

		Date second = new Date();
		System.out.printf("first compareTo second is %d\n", first.compareTo(second));

		System.out.println("More formatting output see link: https://www.tutorialspoint.com/java/java_date_time.htm");
	}
}
