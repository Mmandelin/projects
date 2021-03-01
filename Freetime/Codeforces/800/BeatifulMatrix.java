import java.util.Scanner;
import static java.lang.Math.abs;

public class BeatifulMatrix {

    public static void main(String[] args) {

        Scanner skanneri = new Scanner(System.in);
        int[][]matrix = new int[5][5]; //eka kolumnit toka rivit
        int x = 0; //tälle annetaan löytyneen ykkösen riviarvo
        int y = 0; //tälle annetaan löytyneen ykkösen kolumniarvo
        boolean loytyi = false;
        for(int i=1; i<6; i++)
        {
            for(int j=1; j<6; j++)
            {
                matrix[i-1][j-1] = skanneri.nextInt();
            }
        }
        for (int i = 1; i < 6; i++) //etsii ykkösen, kun löytyy lopettaa looppaamisen
        {
            for (int j = 1; j < 6; j++)
            {
                if (matrix[i-1][j-1] == 1)
                {
                    x = i;
                    y = j;
                    loytyi = true;
                    break;
                }
            }
            if(loytyi)
            {
                break;
            }
        }
        if(x == 3 && y == 3) //jos ykkönen on matriksin keskellä
        {
            System.out.println("0");
        }
        if(x != 3 || y != 3) //ykkönen on jossain muualla
        {
            /*
            keskellä on 0 siirtoa. abs() laskee absoluuttisen arvon, eli jos siirto lasku on negatiivinen
            funktio palauttaa silti saman luvun, mutta positiivisena, jolloin voidaan laskea siirtojen määrä
            nollasta eteenpäin
             */
            int siirtoX = (3-x);
            int siirtoY = (3-y);
            System.out.println(abs(siirtoX)+abs(siirtoY));
        }
    }
}