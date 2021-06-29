import java.util.Comparator;

public class ComparateNkm implements  Comparator<Veiculo>{
    public int compare(Veiculo v1, Veiculo v2){
        if (v1.getKms() > v2.getKms()) return 1;
        if(v1.getKms() < v2.getKms()) return -1;
        return 0;
    }
}