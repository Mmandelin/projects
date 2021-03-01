
import java.util.ArrayList;
import java.util.Scanner;

public class BoyOrGirl {

    public static void main(String[] args) {

        Scanner skanneri = new Scanner(System.in);
        ArrayList<Character>sanaLista = new ArrayList<>();
        ArrayList<Character>tulostusLista = new ArrayList<>();
        String sisaan = skanneri.nextLine();
        char[] charArray = sisaan.toCharArray(); //lisataan stringista kirjaimet chararrayhin
        String ulos;
        tulostusLista.add(sisaan.charAt(0));

        for(int z=0; z< charArray.length; z++) //lisataan kirjaimet chararraysta arraylistiin
        {
            sanaLista.add(charArray[z]);
        }


        for(int i=0; i<sanaLista.size(); i++) //kaydaan lapi jokainen kirjain listalla
        {
            int count=0;
            for(int j=0; j< tulostusLista.size(); j++) //kaydaan japi jokainen kirjain uudelta listalta ja verrataan vanhan listanm kirjaimeen
            {
                if(tulostusLista.get(j).equals(sanaLista.get(i))) //jos kirjain löytyy tulostuslistalta lisätään countteriin numero
                {
                    count++;
                }
            }
            if(count == 0) //jos countteriin ei ole lisätty mitään se tarkoittaa, että tulostuslistalla ei ole sanaa, joten se lisätään
            {
                tulostusLista.add(sanaLista.get(i));
            }
        }

        ulos = tulostusLista.toString();

        if(ulos.length() % 2 == 0)
        {
            System.out.println("CHAT WITH HER!");
        }
        else
        {
            System.out.println("IGNORE HIM!");
        }
    }
}