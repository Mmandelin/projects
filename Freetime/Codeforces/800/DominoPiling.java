import java.util.Scanner;

public class DominoPiling {

    public static void main(String[] args) {

        /*
        int on kokonaisluku, joten tällä hyvin karkealla toteutuksella saadaan toimiva ratkaisu, koska
        vastaus ei voi olla desimaali soutissa.
         */
        Scanner skanneri = new Scanner(System.in);
        int leveys = skanneri.nextInt();
        int korkeus = skanneri.nextInt();
        int [][] board = new int[korkeus][leveys]; //tätä ei tarvittu, unohtui koodiin
        int vastaus = 0;

        vastaus += ((leveys * korkeus)/2);
        System.out.println(vastaus);
    }
}