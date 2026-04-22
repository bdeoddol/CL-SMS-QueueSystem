package Rishaparser;
// Source code is decompiled from a .class file using FernFlower decompiler (from Intellij IDEA).
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;
import com.google.gson.Gson;
//won't let me compile w this
//import javax.swing.GroupLayout.Group;

//returns json string
public class Parser {
    static volatile boolean paused = false;

    public Parser() {
    }

    public static void main(String[] var0) throws Exception {
        String var1 = "https://docs.google.com/spreadsheets/d/1_euUtfA1exxkrcJQVm3hN_C3xjNgGapVu3zrxLIwITs/export?format=csv&gid=0";
        
        Gson gson = new Gson();
        //bg thread 2 listen for spacebar + enter
        Thread inputThead = new Thread(()->{
            //need try-catch to handle IOException
            try {
                while(true) {
                    char key = (char)System.in.read();
                    if(key == ' ') {
                        paused = !paused;
                        if(paused) {
                            System.out.println("\n===paused===");
                        } else {
                            System.out.println("\n===unpaused===");
                        }
                    }
                }
            } catch(IOException e){
                e.printStackTrace();
            }
        });

        //set thread as bg process and start
        inputThead.setDaemon(true);
        inputThead.start();


        while(true) {
            if(!paused) {
                BufferedReader var2 = new BufferedReader(new InputStreamReader((new URL(var1)).openStream()));
                ArrayList<FormContainer> var3 = new ArrayList<FormContainer>();
                boolean var5 = true;

                String var4;
                while((var4 = var2.readLine()) != null) {
                    if (var5) {
                        var5 = false;
                    } else {
                        String[] var6 = var4.split(",");
                        var3.add(new FormContainer(var6[0], var6[1], Integer.parseInt(var6[2]), Integer.parseInt(var6[3])));
                    }
                }

                var2.close();
                new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();

                String jsonString = gson.toJson(var3);
                System.out.println(jsonString);

            }
        Thread.sleep(5000L);
      }
   }
}
