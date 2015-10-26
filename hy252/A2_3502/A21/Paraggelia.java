import java.util.Date;
import java.util.ArrayList;
import java.util.List;

public class Paraggelia {
	private Date date;
	private String table;
	private List<Product> products;

	public Paraggelia(Date ndate, String ntable) {
		date = ndate;
		table = ntable;
		products = new ArrayList<Product>();
	}

	public void add(Product p) {
		for (Product i: products) {
			if (i.getBarCode() == p.getBarCode()) {
				i.setPlusNumber(1);
				return;
			}
		}

		products.add(p);
	}

	public void delete(Product p) {
		for (Product i: products) {
			if (i.getBarCode() == p.getBarCode()) {
				i.setPlusNumber(-1);
				return;
			}
		}

		products.remove(p);
	}

	public String getReceipt() {
		String tmp = "\n"; // Build the string

		for (Product p: products)
			tmp += p.toString() + "\n";

		return "Date: " + date + "\nTable: " + table + tmp + "Total price: " + getTotalPrice();
	}

	public float getTotalPrice() {
		float tmp = 0;

		for (Product p: products)
			tmp += p.getPrice();

		return tmp;
	}

	public String toString() {
		return getReceipt();
	}
}
