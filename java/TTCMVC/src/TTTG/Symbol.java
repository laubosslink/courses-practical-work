package TTTG;

public enum Symbol {
	CROIX("X"), ROND("O"), VIDE(" ");
	
	private String _symbol;
	
	Symbol(String symbol){
		this._symbol = symbol;
	}
	
	public String toString(){
		return this._symbol + " ";
	}
}
