import java.util.Date;

public class MyRestaurantTester {
	public static void main(String[] args) {
		Paraggelia a = new Paraggelia(new Date(1234), "A Table");
		Paraggelia b = new Paraggelia(new Date(12345), "B Table");

		a.add(new Product("saltsa", "b002", (float) 1.00));
		a.add(new Product("snitsel", "b003", (float) 5.00));
		a.add(new Product("snitsel", "b003", (float) 5.00));
		a.add(new Product("beer", "b004", (float) 3.00));
		a.add(new Product("beer", "b004", (float) 3.00));
		a.add(new Product("beer", "b004", (float) 3.00));
		a.add(new ServiceProduct((float) 3.00, 2));

		b.add(new Product("snitsel", "b003", (float) 4.00));
		b.add(new Product("snitsel", "b003", (float) 4.00));
		b.add(new Product("beer", "b004", (float) 4.00));
		b.add(new Product("beer", "b004", (float) 4.00));
		b.add(new ServiceProduct((float) 1.00, 3));

		System.out.println(a.getReceipt());
		System.out.println(b.getReceipt());
	}
}
