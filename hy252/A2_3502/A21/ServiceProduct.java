public class ServiceProduct extends Product {
	private String name = "kouver";
	private String barCode = "b001";
	private float price;
	private Integer people;

	public ServiceProduct(float nprice, Integer npeople) {
		super("kouver", "b001", nprice);
		price = nprice;
		people = npeople;
	}

	// TODO: Ask for this
	public float getPrice() {
		return people * price;
	}

	public String toString() {
		return barCode + " (" + name + "): " + people + " people = " + (people * price);
	}
}
