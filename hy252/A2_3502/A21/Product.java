public class Product {
	private String name;
	private String barCode;
	private float price;
	private Integer number;

	public Product(String nname, String nbarCode, float nprice) {
		name = nname;
		barCode = nbarCode;
		price = nprice;
		number = 1;
	}

	public String toString() {
		return barCode + " (" + name + "): x" + number + " = " + (number * price);
	}

	public String getBarCode() {
		return barCode;
	}

	public Integer getNumber() {
		return number;
	}

	public float getPrice() {
		return price * number;
	}

	public void setPlusNumber(Integer num) {
		number += num;
	}
}
