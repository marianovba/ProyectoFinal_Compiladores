public class Main {
    public static void main(String[] args) {
        try{
            jflex.Main.generate(new java.lang.String[]{
                    "C:\\Users\\mvb17\\OneDrive\\Desktop\\SPCompiler\\untitled\\src\\lexer\\lexer.flex"});
        } catch (Exception e) {
            System.out.println("Algo salio mal");
        }
    }
}