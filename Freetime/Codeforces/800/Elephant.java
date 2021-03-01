import java.util.Scanner;

public class Elephant {

    public static void main(String[] args) {

        Scanner skanneri = new Scanner(System.in);
        int matka = skanneri.nextInt();
        if(matka % 5 == 0) //jos matka on 5:llä jaollinen tulostetaan se suoraan
        {
            System.out.println((matka/5));
        }

        /*
        jos matka ei ole 5:llä jaollinen tulostetaan matka jaettuna 5:llä +1, koska askeleet on 1-5 välillä,
        joten vajaaksi jäävä matka päästään yhdellä askeleella jokatapauksessa
         */
        else
        {
            System.out.println((matka/5+1));
        }
    }
}