import java.util.Scanner;

public class SoldierAndBananas {

    public static void main(String[] args) {

        Scanner skanneri = new Scanner(System.in);
        int hinta = skanneri.nextInt();     //3dollaria eka banaani (monesko*hinta=hinta)
        int rahaa = skanneri.nextInt();     //sotilaalla on 17 rahaa
        int maara = skanneri.nextInt();     //sotilas haluaa 4 banaania

        int tilanne = 0;
        int laina = 0;
        for(int i = 1; i < (maara +1); i++)
        {
            tilanne += (i * hinta);
        }
        laina = (rahaa - tilanne);
        if(laina < 0)
        {
            System.out.println(Math.abs(laina));
        }
        else
        {
            System.out.println("0");
        }
    }
}