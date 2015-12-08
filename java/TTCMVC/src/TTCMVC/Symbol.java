package TTCMVC;

public enum Symbol {
	CROIX("X"), ROND("O"), VIDE("_");
	
	private String _symbol;
	
	Symbol(String symbol){
		this._symbol = symbol;
	}
	
        @Override
	public String toString(){
		return this._symbol;
	}
}
