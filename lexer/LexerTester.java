package lexer;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class LexerTester {
    public static void main(String[] args){
        File f = new File("C:\\Users\\mvb17\\OneDrive\\Desktop\\SPCompiler\\untitled\\src\\lexer\\TestLexer");
        try{
            FileReader fr = new FileReader(f);
            Lexer lexer = new Lexer(fr);
            Tokens tokens;

            while(tokens = lexer.yylex()!= null){
                System.out.println("nombre: "+ tokens.name() + " Text: "
                        + lexer.yylex() + " line: " + lexer.line());
            }

        }catch(FileNotFoundException e) {
            throw new RuntimeException(e);
        }catch(IOException e) {
            throw new RuntimeException(e);
        }
    }
}
