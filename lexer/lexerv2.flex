package lexer;
import static lexer.Tokens.*;
%%
%class Tokens
%class Lexer
%unicode
%line // Para realizar el seguimiento de las líneas
%column // Para realizar el seguimiento de las columnas

%%

/* Definición de patrones para los tokens */

"play" | "sleep" | "do" | "end" | "amp:" | "pan:" | "loop" | "rate:" | "live-loop" | "sample" | "use_synth" | "transform" {
  token = TokenType.KEYWORD;
  return token;
}

":" {
  token = TokenType.PUNTUACION;
  return token;
}

";" | "," | "." {
  token = TokenType.PUNTUACION;
  return token;
}

"#".* {
  token = TokenType.COMENTARIO;
  // Se ignoran los comentarios, pero puedes hacer algo con ellos si es necesario
}

[A-G] {
  token = TokenType.LETRA;
  return token;
}

[0-9]+ {
  token = TokenType.NUMERO;
  return token;
}

[0-9]+\.[0-9]+ {
  token = TokenType.CONSTANTE;
  return token;
}

([a-zA-Z_][a-zA-Z_0-9]*) {
  token = TokenType.IDENTIFICADOR;
  return token;
}

[ \t\r\n]+ {
  token = TokenType.ESPACIO;
  // Ignora los espacios en blanco
}

<<EOF>> {
  token = TokenType.EOF;
  return token;
}
