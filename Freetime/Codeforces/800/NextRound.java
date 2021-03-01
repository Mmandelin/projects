import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

public class NextRound {

    public static void main(String[] args) {

        Scanner skanneri = new Scanner(System.in);
        ArrayList<Integer>tulokset = new ArrayList<>();
        int osallistujat = skanneri.nextInt();
        int jatkoon_vaadittu = (skanneri.nextInt() -1);
        int jatkoon = 0;

        for(int i=0; i < osallistujat; i++)
        {
            tulokset.add(skanneri.nextInt());
        }
        Collections.sort(tulokset, Collections.reverseOrder());
        for(int z=0; z<tulokset.size(); z++)
        {
            if(tulokset.get(z) >= tulokset.get(jatkoon_vaadittu) && tulokset.get(z) > 0)
            {
                jatkoon++;
            }
        }
        System.out.println(jatkoon);
    }
}