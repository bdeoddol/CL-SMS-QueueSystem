package Rishaparser;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class Main {
        public static void main(String[] args) throws Exception {
        String url = "https://docs.google.com/spreadsheets/d/e/2PACX-1vSFDUhAVVoYXpQvqKQ0FrBU_c3c5vPG-ImbMxqeZhKfz0gStUOADiTnmxlbn_q0ar_q8xCiffIr0UVk/pub?output=csv";
        Parser MainParser = new Parser(url);
        MainParser.startUpServerSocket(800);
        MainParser.awaitClientConnection();

        MainParser.run();





        int port = 8000;
        int aNumber;
        DataInputStream in;
        DataOutputStream out;

        ServerSocket server;
        Socket socketConnect;

        server = new ServerSocket(port);
        socket = server.accept();

        in = new DataInputStream(socket.getInputStream());
        out = new DataOutputStream(socket.getOutputStream());

        System.out.println(in.readByte());
        out.writeDouble(aNumber);
        

    }
}
