import java.util.ArrayList;
import java.util.Scanner;

public class Bit {

    public static void main(String[] args) {
        Scanner skanneri = new Scanner(System.in);
        ArrayList<String>syote = new ArrayList<>();
        String miinus1 = "--X";
        String miinus2 = "X--";
        int x = 0;
        int loop = skanneri.nextInt();
        for(int j = 0; j<loop; j++)
        {
            String D = skanneri.next();
            syote.add(D);
        }
        for(int i = 0; i<loop; i++)
        {
            if(syote.get(i).equals(miinus1) || syote.get(i).equals(miinus2))
            {
                x--;
            }
            else
            {
                x++;
            }
        }
        System.out.println(x);
    }
}