enum Type { CD, DVD, FlashDrive, HD, SSD }

public class StorageMedium {
	private String name;
	private int capacity;
	public Type type = Type.HD;

	public StorageMedium(String name, int capacity) {
		this.name = name;
		this.capacity = capacity;
	}

	public String toString() {
		return "Storage device: " + this.name + ", capacity: " + this.capacity +
			"bytes, type: " + this.type;
	}
}

class USBstick extends StorageMedium {
	public USBstick(String name, int capacity) {
		super(name, capacity);
		type = Type.FlashDrive;
	}

	public String toString() {
		return "USB Stick " + super.toString();
	}
}
