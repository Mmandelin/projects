import java.util.Scanner;

public class PetyaAndStrings {

    public static void main(String[] args) {

        Scanner skanneri = new Scanner(System.in);
        String s1 = skanneri.nextLine();
        String s2 = skanneri.nextLine();

        if(s1.compareToIgnoreCase(s2) == 0)
        {
            System.out.println("0");
        }
        else if(s1.compareToIgnoreCase(s2) < 0)
        {
            System.out.println("-1");
        }
        else if(s1.compareToIgnoreCase(s2) > 0)
        {
            System.out.println("1");
        }
    }
}