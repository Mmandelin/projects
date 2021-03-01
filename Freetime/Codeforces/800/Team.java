import java.util.Scanner;

public class Team {

    public static void main(String[] args) {

        Scanner skanneri = new Scanner(System.in);
        int n = skanneri.nextInt();
        int [][] team = new int[n][3];
        for(int i = 0; i<n; i++)
        {
            for (int j = 0; j<3; j++)
            {
                team[i][j] = skanneri.nextInt();
            }
        }

        int hyvaksynta = 0; //montako tehtavaa hyvaksyttiin
        for(int i=0; i<n; i++)
        {
            int otetaan = 0; //aanestyksen tulos
            for(int j = 0; j<3; j++)
            {
                otetaan += team[i][j];
            }
            if(otetaan >= 2)
            {
                hyvaksynta++;
            }

        }
        System.out.println(hyvaksynta);
    }
}