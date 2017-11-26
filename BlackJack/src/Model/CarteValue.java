package Model;

public enum CarteValue {
	as(1),deux(2),trois(3),quatre(4),cinq(5),six(6),sept(7),huit(8),neuf(9),dix(10),valet(11),reine(12),roi(13);
	
	private int value;
	
    private CarteValue(int value) {
        this.value = value;
    }
    
    public int getValue() {
        return value;
    }
}
