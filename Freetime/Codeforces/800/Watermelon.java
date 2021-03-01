import java.util.Scanner;

public class Watermelon {

    public static void main(String[] args) {

        Scanner input = new Scanner(System.in);
        int x=input.nextInt();  //meloonin paino
        if (onkoTasan(x))
        {
            System.out.println("YES");
            return;
        }
        else
        {
            System.out.println("NO");
        }
    }

    public static boolean onkoTasan(int x)
    {
        for(int i=1; i<x; i++)
        {
            if((x-i)%2==0 && i%2==0)
            {
                return true;
            }
        }
        return false;
    }
}