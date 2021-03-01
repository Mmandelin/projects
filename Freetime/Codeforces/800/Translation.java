import java.util.Scanner;

public class Translation {

    public static void main(String[] args) {
        Scanner skanneri = new Scanner(System.in);
        String eka = skanneri.nextLine();
        String toka = skanneri.nextLine();

        String testi = new StringBuilder(eka).reverse().toString();
        if(testi.equals(toka))
        {
            System.out.println("YES");
        }
        else
        {
            System.out.println("NO");
        }
    }
}