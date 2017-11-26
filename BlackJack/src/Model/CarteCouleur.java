package Model;

public enum CarteCouleur {
	coeur(1),carreau(2),trefle(3),pique(4);
	
	private int value;
	
    private CarteCouleur(int value) {
        this.value = value;
    }
    
    public int getValue() {
        return value;
    }
}
