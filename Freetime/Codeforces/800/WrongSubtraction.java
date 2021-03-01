import java.util.Scanner;

public class WrongSubtraction {

    public static void main(String[] args) {

        Scanner skanneri = new Scanner(System.in);
        int numero = skanneri.nextInt();
        int kertaa = skanneri.nextInt();

        for(int i = 0; i < kertaa; i++)
        {
            if(numero % 10 == 0)
            {
                numero = numero / 10;
            }
            else
            {
                numero = (numero - 1);
            }
        }

        System.out.println(numero);
    }
}