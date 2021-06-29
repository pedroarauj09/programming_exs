import java.util.ArrayList;

public class VeiculoPremium extends Veiculo implements BonificaKms {
    private int taxa;
    private int pontos;

    public VeiculoPremium(){
        super();
        this.taxa = 0;
    }
    public VeiculoPremium(VeiculoPremium v){
        super(v);
        this.taxa = v.getTaxa();
    }


    public VeiculoPremium(String marca, String modelo, String matricula,
                   int ano, double velociademedia, double precokm,
                   ArrayList<Integer> classificacao,
                   int kms, int kmsUltimo, int taxa) {
                
                super(marca,modelo,matricula,ano,velociademedia,precokm,classificacao,kms,kmsUltimo);
                this.taxa = taxa;    

                }

    public int getTaxa(){
        return this.taxa;
    }

    public VeiculoPremium clone(){
        return new VeiculoPremium(this);
    }

    public double custoRealKM(){
        return getPrecokm()*1.1*((this.taxa/100)+1);

    }

    public void definePontosPorKms(int pts){
        this.pontos = pts;
    }
    public int getPontosPorKm(){
        return this.pontos;
    }


}
