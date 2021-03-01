import java.util.Scanner;

public class NearlyLuckyNumber {

    public static void main(String[] args) {

        Scanner skanneri = new Scanner(System.in);
        String sisaan = skanneri.nextLine();
        int count = 0;
        for(int i=0; i<sisaan.length(); i++)
        {
            if(sisaan.charAt(i) == '4' || sisaan.charAt(i) == '7')
            {
                count++;
            }
        }
        if(count == 4 || count == 7)
        {
            System.out.println("YES");
        }
        else
        {
            System.out.println("NO");
        }
    }
}