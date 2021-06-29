import java.util.Arrays;

public class DriveItMenu {
   public static void main(String[] args) {
        String[] s = { "Add Car", "Submenu", "Cars per Km"};
        String[] s2 = {"B.1","B.2"};
        MenuDrive m = new MenuDrive(s);
        MenuDrive m2 = new MenuDrive(s2);
        m.executa();
        int op;
        op = m.getOpcao();
        System.out.println("Option read: " + op);
        switch(op){
            case 1: 
                System.out.println("I'm adding a car");
                break;
            case 2: 
                m2.executa();
                break;
            case 3: 
                System.out.println("Cars per Km...");
                break;

            default: 
                System.out.println("Invalid option..");
        }
    
   } 
}
