import java.net.*;
import java.io.*;
import java.util.*;

public class Parser {
    public static void main(String[] args) throws Exception {
        //this was a test google sheet lolz will change the key 
        //rmb to make sheet accessible to everyone with link!!!
        String url = "https://docs.google.com/spreadsheets/d/1_euUtfA1exxkrcJQVm3hN_C3xjNgGapVu3zrxLIwITs/export?format=csv&gid=0";

        while (true) {
            BufferedReader reader = new BufferedReader(new InputStreamReader(new URL(url).openStream()));
            
            List<Group> groups = new ArrayList<>();
            String line;
            boolean firstLine = true;
        
            while((line = reader.readLine()) != null) {
            //skip header line as it's j data memebr labels
                if(firstLine) {
                    firstLine = false;
                    continue;
                }
                
                String[] lineString = line.split(",");
                //make new group w the data members from each lineString
                groups.add(new Group(lineString[0], lineString[1], lineString[2], Integer.parseInt(lineString[3])));
            }

            reader.close();
            //clears console & reprints 
            System.out.print("\033[H\033[2J");
            System.out.flush();
            for(Group g : groups) {
                System.out.println(g);
            }
            //5 second buffer before re-fetching data
            Thread.sleep(5000);
        }     
    }
}