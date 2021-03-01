import java.util.ArrayList;
import java.util.Scanner;

public class WayTooLongWords {

    public static void main(String[] args) {

        ArrayList<String>list = new ArrayList<String>();
        Scanner input = new Scanner(System.in);
        for(int counter = input.nextInt(); counter > 0; counter--)
        {
            String sana = input.next();
            list.add(sana);
        }

        for(int j=0; j<list.size(); j++)
        {
            String kohde = list.get(j);
            int koko = kohde.length();
            int max = 0;
            if (koko < 11) {
                System.out.println(kohde);
            }
            else
            {
                for (int z = 1; z < koko; z++)
                {
                    max++;
                }
                System.out.println(kohde.charAt(0) + "" + (koko - 2) + "" + kohde.charAt(max));
            }
        }
    }
}