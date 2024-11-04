import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class SoundParser {
    private String input;
    private int position;
    private String currentWord;

    public SoundParser(String input) {
        this.input = input;
        this.position = 0;
        this.currentWord = null;
    }

    public void CurrentWord(String word){
        this.currentWord = word;
        System.out.println("Palabra Actual: " + word);
    }

    public String getNextWord() {
        if (position >= input.length()) {
            return "eof"; 
        }

       
        while (position < input.length() && Character.isWhitespace(input.charAt(position))) {
            position++;
        }

       
        if (position >= input.length()) {
            System.out.println("Returns eof inside Next Word");
            return "eof";
        }

       
        Pattern pattern = Pattern.compile("(?<Nota>[A-G])|(?<Audio>ambi_choir|bd_haus|elec_bell|perc_door|guit_e_fifths|drums_bass_hard|misc_burp|bass_hit_c)|(?<Accion>play|sample)|(?<Modificador>amp:|rate:|pan:)|(?<Constante>-?\\d+\\.\\d+|-?\\d+)|[:,]");
        Matcher matcher = pattern.matcher(input.substring(position));

        if (matcher.lookingAt()) {
            String word = matcher.group();
            position += word.length(); 
            System.out.println("Next word is " + word);
            return word; 
        }

        return "error"; 
    }

    public boolean Instruccion() {
        
        if (!InstruccionPrime()) {
            System.out.println("Prime falso");
            return false;
        }
        System.out.println("Entra a Accion");
        return Accion();
    }

    public boolean InstruccionPrime() {
        String word = getNextWord();
        System.out.println("Palabra despues de iniciar instruccion prime: "+ word);
        System.out.println("Dentro de Instrccion Prime");
        if (word.equals(":")) {
            currentWord = word;
            System.out.println("Econtro dos puntos en Instruccion Prime");
            return Sonido();
        } else if (word.equals(",")) {
            currentWord = word;
            System.out.println("Encontro una comma en la Instruccion prime" );
            word = getNextWord();
            if (word.equals("amp:") || word.equals("rate:") || word.equals("pan:")) {
                currentWord = word;
                System.out.println("Econtro un modificador en la instruccion que fue " + currentWord);
                return Sonido();
            }
            System.out.println("Existe un token que no existe en el lenguaje");
            return false; 
        }
        System.out.println("regresa true en instruccion prime");
        System.out.println("Palabra al terminar Instruccion Prime: "+ word);
        return true; 
    }

    public boolean Accion() {
        System.out.println("Current word is " + currentWord);
        if (currentWord.equals("play") || currentWord.equals("sample")) {
            System.out.println("Existe una accion la cual fue " + currentWord);
            return true;
        }
        return false;
    }

    public boolean Sonido() {
        String word = getNextWord();
        System.out.println("Entro en Sonido");
        if (word.matches("[A-G]")) {
            currentWord = word;
            System.out.println("Primera parte de la nota " + currentWord);
            return Nota();
        } else if (word.matches("ambi_choir|bd_haus|elec_bell|perc_door|guit_e_fifths|drums_bass_hard|misc_burp|bass_hit_c")) {
            currentWord = word;
            System.out.println("El modificador es " + currentWord);
            return true; 
        }
        return false;
    }

    public boolean Nota() {
        String word = getNextWord();
        System.out.println("Entro a nota");
        return word.matches("[1-7]"); 
    }

    public boolean Modificador() {
        String word = getNextWord();
        System.out.println("Entro a modificador");
        return word.matches("amp:|rate:|pan:");
    }

    public boolean Constante() {
        String word = getNextWord();
        System.out.println("Entro a Constante");
        return word.matches("-?\\d+(\\.\\d+)?"); 
    }

   
    public static void main(String[] args) {
        SoundParser parser = new SoundParser(" play :A5 ");
        
        if (parser.Instruccion()) {
            System.out.println("Sintaxis correcta");
        } else {
            System.out.println("Error en la sintaxis");
        }
    
    }
}// Incompleto 


    /*

Referencias:

W3Schools. (s.f.). What is a Regular Expression? https://www.w3schools.com/java/java_regex.asp

GeeksforGeeks. (2018, Noviembre 26). MatcherlookingAt() method in Java with Examples

chatgpt.com -> Dudas con el codigo en general 

 Instruccion -> Instruccion’Accion
 Instruccion’ -> :Sonido | ,Modificador:Sonido
 Accion -> play | sample
 Sonido -> Nota | Audio
 Nota -> A | B | C | D | E | F | G
 A -> 1 | 2 | 3 | 4 | 5 | 6 | 7 equivale Entera
 B -> 1 | 2 | 3 | 4 | 5 | 6 | 7 equivale Entera
 C -> 1 | 2 | 3 | 4 | 5 | 6 | 7 equivale Entera
 D -> 1 | 2 | 3 | 4 | 5 | 6 | 7 equivale Entera
 E -> 1 | 2 | 3 | 4 | 5 | 6 | 7 equivale Entera
 F -> 1 | 2 | 3 | 4 | 5 | 6 | 7 equivale Entera
 G -> 1 | 2 | 3 | 4 | 5 | 6 | 7 equivale Entera
 Audio -> ambi_choir | bd_haus | elec_bell | perc_door | guit_e_fifths | drums_bass_hard | misc_burp | bass_hit_c
 Modificador -> ParametroConstante
 Parametro -> amp: | rate: | pan:
 Constante -> Real | Entera
 Entera -> numero | -numero
 Real -> numero.numero | numero.numero


Codigo Profesor Emmanuelle: 

Expr-> TermExpr'
Expr' -> +TermExpr' | -TermExpr' | Epsilon
Term -> FactorTerm'
Term' -> *FactorTerm'| /FactorTerm' | Epsilon
Factor -> id | num | (Expr)

main()
word = GetNextWord()
res = Expr()
if res = true AND word == eof
    print("sintaxis correcta")
else
    return ExprPr()

Expr()
res = Term()
if res = false
    return
else
    return

ExprPr()
if word == '+' OR word == '-'
    word = GetNextWord()
    res = Term()
    if res == false
        return false
    else
        return ExprPr()
if word == eof or word == ')'
    return true
else
    return false

Term()
res = Factor()
if res == false
    return false
else
    return TermPr()

TermPr()
if word == '+' OR word == '/'
    word = GetNextWord()
    res = Factor()
    if res = false
        return false
    else
        return TermPr()
if word == eof OR word == ')' OR '+' OR '-'
    return true
else
    return false

Factor()
if word == '('
    word = GetNextord()
    res = Expr()
    if res = false return false
    if word == ')'
        word = GetNextWord()
        return true
    else
        return false
if word == id or word == num
    word = GetNextWord()
    return true
else
    return false
     */
    

