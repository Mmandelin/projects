import java.util.Scanner;

public class QueueAtTheSchool {

    public static void main(String[] args) {

        Scanner skanneri = new Scanner(System.in);
        int jononkoko = skanneri.nextInt();
        int aika = skanneri.nextInt();
        String jarjestys = skanneri.next();
        char[] charArray = jarjestys.toCharArray();

        for(int k=0; k<aika; k++) //looppaa ajan suhteen. jos 2 sec, looppaa 2 kertaa
        {
            for(int i=0; i<jononkoko-1; i++) //looppaa jokaisen kirjaimen listalla
            {
                if(charArray[i] == 'B' && charArray[i+1] == 'G')
                {
                    charArray[i] = 'G';
                    charArray[i+1] = 'B';
                    i++;
                }
            }
        }
        for(int j=0; j<jononkoko; j++)
        {
            System.out.print(charArray[j]);
        }
    }
}