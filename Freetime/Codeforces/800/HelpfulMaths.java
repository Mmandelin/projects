import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

public class HelpfulMaths {

    public static void main(String[] args) {

        Scanner skanneri = new Scanner(System.in);
        ArrayList <Integer> numeroLista = new ArrayList<>();
        String s = skanneri.nextLine();
        char[] charArray =s.toCharArray();
        for(int i=0; i< charArray.length; i++)
        {
            if(Character.isDigit(charArray[i]))
            {
                numeroLista.add(Integer.parseInt(String.valueOf(charArray[i])));
            }
        }
        Collections.sort(numeroLista); //järjestää numerolistan pienimmästä isoimpaan
        if(numeroLista.size() < 2) //jos on vain 1 numero se tulostetaan suoraan
        {
            System.out.println(numeroLista.get(0));
        }
        else { //jos on enemmän kuin 1 numero, tulostaa numerolistan lisäten +merkin jokaisen numeron jälkeen
            for (int k = 0; k < numeroLista.size(); k++)
            {
                System.out.print(numeroLista.get(k));
                if(k == (numeroLista.size() -1)) //vikan numeron jälkeen ei haluta +merkkiä, joten loop rikotaan vikan tulostetun numeron jälkeen
                {
                    break;
                }
                System.out.print("+");
            }
        }
    }
}