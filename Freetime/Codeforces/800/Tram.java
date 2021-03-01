import java.util.Scanner;

public class Tram {

    public static void main(String[] args) {

        Scanner skanneri = new Scanner(System.in);
        int pysakit = skanneri.nextInt();
        int sisaan = 0;
        int ulos = 0;
        int sisalla = 0;
        int trakkeri = 0;
        for(int i = 0; i < pysakit; i++)
        {
            ulos = skanneri.nextInt();
            sisaan = skanneri.nextInt();
            sisalla += (-ulos+sisaan);
            if(sisalla > trakkeri)
            {
                trakkeri = sisalla;
            }
        }
        System.out.println(trakkeri);
    }
}