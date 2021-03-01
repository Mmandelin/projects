import java.util.Scanner;

public class BearAndBigBrother {

    public static void main(String[] args) {

        Scanner skanneri = new Scanner(System.in);
        int a = skanneri.nextInt();     //Limak paino
        int b = skanneri.nextInt();     //veljen paino
        int count = 0;
        do
        {
            count++;
            a = a*3;
            b = b*2;
        }while(a < (b+1));
        System.out.println(count);
    }
}
