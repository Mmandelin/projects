import java.util.Scanner;

public class WordCapitalization {

    public static String capitalize(String sana)
    {
        if(sana == null || sana.isEmpty())
        {
            return sana;
        }

        return sana.substring(0,1).toUpperCase() + sana.substring(1);
    }

    public static void main(String[] args) {

        Scanner skanneri = new Scanner(System.in);
        String input = skanneri.nextLine();
        System.out.println(capitalize(input));
    }
}