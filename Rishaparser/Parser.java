package Rishaparser;

import java.io.InputStreamReader;
import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;

import com.opencsv.CSVReader;
import com.google.gson.Gson;

public class Parser {
    private final String sheetUrl;
    private final Gson gson;
    private volatile boolean paused = false;
    private int lastSeen = -1;
    private int lastFetch = -1;
    private int stableCount = 0;
    private static final int REQ_STABLE = 3;

    public Parser(String sheetUrl) {
        this.sheetUrl = sheetUrl;
        this.gson = new Gson();
    }

    public ArrayList<FormContainer> fetchEntries() throws Exception {
        String noCacheUrlPlease = sheetUrl + "&t=" + System.currentTimeMillis();
        CSVReader csvReader = new CSVReader(new InputStreamReader((new URL(noCacheUrlPlease)).openStream()));
        ArrayList<FormContainer> entries = new ArrayList<>();
        boolean firstLine = true;
        int msgInc = -1;

        String[] fields;
        while((fields = csvReader.readNext()) != null) {
            if(firstLine) {
                firstLine = false;
                continue;
            }
            if(fields.length < 5) continue;
            msgInc++;
            entries.add(new FormContainer(fields[1], fields[2], 
                parseOrDefault(fields[3], 0), 
                parseOrDefault(fields[4], 0), 
                msgInc));
        }

        csvReader.close();
        return entries;
    }

      public void run() throws Exception {
        startInputListener();
        while (true) {
            if (!paused) {
                ArrayList<FormContainer> entries = fetchEntries();
                int currentCount = entries.size();

                if(currentCount == lastFetch) {
                    stableCount++;
                } else {
                    stableCount = 0;
                }

                if(stableCount >= REQ_STABLE && currentCount > (lastSeen + 1)) {
                    ArrayList<FormContainer> newEntries = new ArrayList<>();
                    for(int i = lastSeen + 1; i < entries.size(); i++) {
                        newEntries.add(entries.get(i));
                    }
                    lastSeen = currentCount - 1;
                    stableCount = 0;
                    System.out.println(gson.toJson(newEntries));
                }
                lastFetch = currentCount;
            }
            Thread.sleep(3000);
        }
    }

    private int parseOrDefault(String s, int defaultVal) {
        try {
            return Integer.parseInt(s.trim());
        } catch (NumberFormatException e) {
            return defaultVal;
        }
}

    public void startInputListener() {
        Thread inputThread = new Thread(() -> {
            try {
                while (true) {
                    char key = (char) System.in.read();
                    if (key == ' ') {
                        paused = !paused;
                        System.out.println(paused ? "\n===paused===" : "\n===unpaused===");
                    }
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        });
        inputThread.setDaemon(true);
        inputThread.start();
    }

    public static void main(String[] args) throws Exception {
        String url = "https://docs.google.com/spreadsheets/d/e/2PACX-1vSFDUhAVVoYXpQvqKQ0FrBU_c3c5vPG-ImbMxqeZhKfz0gStUOADiTnmxlbn_q0ar_q8xCiffIr0UVk/pub?output=csv";
        new Parser(url).run();
    }
}