import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInput;
import java.io.ObjectInputStream;
import java.io.ObjectOutput;
import java.io.ObjectOutputStream;
import java.io.PrintWriter;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;
import java.util.TreeSet;
import java.util.stream.Collectors;

public class DriveIt implements Serializable {
    private String name;
    private Map<String, Veiculo> veiculos;
    private boolean promo;

    public DriveIt() {
        this.name = "";
        this.veiculos = new HashMap<>();
        this.promo = false;
    }

    public DriveIt(String nome, Map<String, Veiculo> vs) {
        this.name = nome;
        setVeiculos(vs);
        this.promo = false;
    }

    public DriveIt(DriveIt dv) {
        this.name = dv.getName();
        this.veiculos = dv.getVeiculos();
        this.promo = dv.getPromo();
    }

    public boolean getPromo() {
        return this.promo;
    }

    public void setPromo(boolean ok) {
        this.promo = ok;
    }

    public String getName() {
        return this.name;
    }

    public Map<String, Veiculo> getVeiculos() {
        Map<String, Veiculo> aux = new HashMap<>();
        for (Veiculo v : this.veiculos.values()) {
            aux.put(v.getMatricula(), v.clone());
        }
        return aux;
    }

    public void setVeiculos(Map<String, Veiculo> vs) {
        this.veiculos = new HashMap<>();
        for (Veiculo v : vs.values()) {
            this.veiculos.put(v.getMatricula(), v.clone());
        }
    }

    // 1

    public boolean existeVeiculo(String cod) {
        return this.veiculos.containsKey(cod);
    }

    public int quantos() {
        return this.veiculos.size();
    }

    public int quantos(String marca) {
        return (int) this.veiculos.values().stream().filter(v -> v.getMarca().equals(marca)).count();
    }

    public List<Veiculo> getAllVeiculos() {
        return this.veiculos.values().stream().map(Veiculo::clone).collect(Collectors.toList());
    }

    //

    public void adiciona(Veiculo v) throws VeiculoExisteException {
        if (this.veiculos.containsKey(v.getMatricula()))
            throw new VeiculoExisteException(v.getMatricula());
        else
            this.veiculos.put(v.getMatricula(), v.clone());
    }

    public Set<Veiculo> ordenarVeiculos() {
        Set<Veiculo> aux = new TreeSet<>();
        for (Veiculo v : this.veiculos.values()) {
            aux.add(v.clone());
        }
        return aux;
    }

    public List<Veiculo> ordenarVeiculosAsList() {
        return this.veiculos.values().stream().sorted().map(v -> v.clone()).collect(Collectors.toList());
    }
    /*
     * ** Versão for each public Set<Veiculo> ordenarVeiculo(Comparator<Veiculo> c){
     * Set<Veiculo> aux = new TreeSet<>(new ComparateNkm()); for(Veiculo v :
     * this.veiculos.values()){ aux.add(v.clone()); } return aux; }
     */

    // versao iterator
    public Set<Veiculo> ordenarVeiculo(Comparator<Veiculo> c) {
        Set<Veiculo> aux = new TreeSet<>(new ComparateNkm());
        Iterator<Veiculo> it = this.veiculos.values().iterator(); // percorre os valores da lista
        while (it.hasNext()) { // enquanto houver elementos na lista
            aux.add(it.next().clone()); // adiciona o elemento atual e já posiciona para o proximo
        }
        return aux;
    }

    private static Map<String, Comparator<Veiculo>> ord = new TreeMap<>();

    public void adicionaComparator(String nome, Comparator<Veiculo> cv) {
        ord.put(nome, cv);
    }

    public Iterator<Veiculo> ordenarVeiculo(String criterio) {
        Set<Veiculo> aux = new TreeSet<>(ord.get(criterio));
        for (Veiculo v : this.veiculos.values()) {
            aux.add(v.clone());
        }
        return aux.iterator();
    }

    // Dado um marca retorna a lista de veiculo dessa marca
    public Map<String, List<Veiculo>> ordenarPorMarca() {
        return this.veiculos.values().stream().map(v -> v.clone()).collect(Collectors.groupingBy(v -> v.getMarca()));
    }

    public List<BonificaKms> daoPontos() {
        List<BonificaKms> l = new ArrayList<>();
        for (Veiculo v : this.veiculos.values()) {
            if (v instanceof VeiculoPremium) {
                BonificaKms bk = ((BonificaKms) v);
                l.add(bk);
            }
        }
        return l;
    }

    // print content of file
    public void saveTextual(String file) throws IOException {
        PrintWriter p = new PrintWriter(file);
        p.print(this);
        p.flush();
        p.close();
    }

    // Save binary code of content of file , for after read that and print(faster)
    public void saveBinary(String file) throws IOException {
        ObjectOutputStream o = new ObjectOutputStream(new FileOutputStream(file));
        o.writeObject(this);
        o.flush();
        o.close();
    }

    public DriveIt readObject(String f) throws IOException, ClassNotFoundException {
        ObjectInputStream i = new ObjectInputStream(new FileInputStream(f));
        DriveIt d = (DriveIt) i.readObject();
        i.close();
        return d;
    }

    public String[] carsAsArray() {
        String[] s = new String[quantos()];
        int i = 0;
        for (Veiculo v : this.veiculos.values()) {
            s[i++] = v.toString();
        }
        return s;
    }
}
