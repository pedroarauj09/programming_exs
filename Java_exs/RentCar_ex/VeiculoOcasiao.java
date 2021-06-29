
import java.util.ArrayList;


public class VeiculoOcasiao extends Veiculo {
    private boolean promo;

    public VeiculoOcasiao(){
        super();
        this.promo = false;
    }
    public VeiculoOcasiao(String marca, String modelo, String matricula,
        int ano, double velociademedia, double precokm,
        ArrayList<Integer> classificacao,
        int kms, int kmsUltimo, boolean promocao){
                            
        super(marca, modelo, matricula,
        ano, velociademedia, precokm,classificacao,kms,kmsUltimo);
        
        this.promo = promocao;
    
    }
    
    public VeiculoOcasiao(VeiculoOcasiao vo){
        super(vo);
        this.promo = vo.getPromo();
    }

    public boolean getPromo(){
        return this.promo;
    }

    public double custoRealKM(){
        return (this.promo)? getPrecokm()*1.1*0.75 : getPrecokm();
    }


    //equals, toString, clone 
    public String toString(){
        StringBuilder s = new StringBuilder();
        s.append(super.toString()).append(" Promocao: ").append(this.promo).append("\n");
        return s.toString(); 
    }

    public VeiculoOcasiao clone(){
        return new VeiculoOcasiao(this);
    }
}
