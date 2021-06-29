import java.util.ArrayList;

public class VeiculoNormal extends Veiculo{
    public VeiculoNormal(){
        super();
    }

    public VeiculoNormal(String marca, String modelo, String matricula,
                   int ano, double velociademedia, double precokm,
                   ArrayList<Integer> classificacao,
                   int kms, int kmsUltimo) {
            super(marca,modelo,matricula,ano,velociademedia,precokm,classificacao,kms,kmsUltimo);


    }

    public VeiculoNormal(VeiculoNormal v){
        super(v);
    }

    public VeiculoNormal clone(){
        return new VeiculoNormal(this);
    }

    public double custoRealKM(){
        return getPrecokm()*1.1;
    }
    
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append(super.toString()).append("\n");
        return  sb.toString();
    }
    
}
