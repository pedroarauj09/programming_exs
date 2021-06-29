import java.io.IOException;
import java.util.ArrayList;

public class TestDriveIt {
    public static void main(String [] args){
        Veiculo v1 = new VeiculoNormal("Ford","Focus","22-A4-77",2015,77.4,5.5,new ArrayList<>(),1000, 50);
        Veiculo v2 = new VeiculoOcasiao("Audi","a7","02-A4-77",2005,97.4,9.5,new ArrayList<>(),2000, 100,false);
        Veiculo v3 = new VeiculoPremium("Ferrari","f1","22-A4-77",2005,97.4,9.5,new ArrayList<>(),2000, 100,50);
        DriveIt braga = new DriveIt();
        
        try{
        braga.adiciona(v1);
        braga.adiciona(v2);
        braga.adiciona(v3);
        }
         catch(VeiculoExisteException m){
             System.out.println("Ja existe o carro com matricula:" + m.getMessage());
         }

        System.out.println(braga.getAllVeiculos());
        try{
            braga.saveTextual("ex.csv");
        }
        catch(IOException i){
            System.out.println("nao rolou"+ i.getMessage());
        }

    }
}
