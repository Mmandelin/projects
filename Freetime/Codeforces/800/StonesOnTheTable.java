import java.util.ArrayList;
import java.util.Scanner;

public class StonesOnTheTable {

    public static void main(String[] args) {

        Scanner skanneri = new Scanner(System.in);
        ArrayList<Character>variLista = new ArrayList<>();
        int kivet = skanneri.nextInt();
        String varit = skanneri.next();
        char[] charArray = varit.toCharArray();
        int count = 0;
        for(int i=0; i<charArray.length; i++)
        {
            variLista.add(charArray[i]);
        }

        if(variLista.size() < 3)
        {
            if(variLista.size() > 1 && variLista.get(0).equals(variLista.get(1)))
            {
                count++;
            }
        }
        if(variLista.size() > 2)
        {
            for(int k=0; k < (variLista.size() -1); k++)
            {
                if(variLista.get((k+1)).equals(variLista.get(k)))
                {
                    count++;
                }
            }
        }
        System.out.println(count);
    }
}