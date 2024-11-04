package lexer;
import static lexer.Tokens.*;
%%
%class Tokens
%class Lexer
%unicode
%line
%column

Audio = ("ambi_choir"|"bd_haus"|"elec_bell"|"perc_door"|"guit_e_fifths"|"drums_bass_hard"|"misc_burp"|"bass_hit_c")
Parametro = ("amp:"|"rate:"|"pan:")
Real = [0-9]+\.[0-9]+
Entero = [0-9]+
Identificador = [A-Za-z_]*
Puntuacion = [:;,]
Keyword = ("play"|"sleep"|"do"|"end"|"amp:"|"pan:"|"loop"|"rate:"|"live-loop"|"sample"|"use_synth"|"transform")
Comentario="#"[^(\n|\r)]*
L=[a-zA-Z_]+
D=[0-9]+
N=[A-G][sb]?[0-5]+
espacio=[ ,\t,\r,\n]+

%{
    public String lexeme;

    public int line(){
        return yyline;
    }

%}
%%
play |
sleep |
do |
end |
amp: |
pan: |
live-loop |
loop |
rate: |
sample |
use_synth |
transform {lexeme=yytext(); return Keyword;}
ambi_choir |
bd_haus |
elec_bell |
perc_door |
guit_e_fifths |
drums_bass_hard |
misc_burp |
bass_hit_c {lexeme=yytext(); return Audio;}
amp: |
rate: |
pan: {lexeme=yytext(); return Parametro;}
":"{Identificador} { lexeme = yytext(); return Identificador; }
{Constante} { lexeme = yytext(); return Entero; }
{Comentario} {/*Ignore*/}
{espacio} {/*Ignore*/}
"//" .* {/*Ignore*/}
";" {return EndofLine}
("(-"{D}+")")|{D}+ {lexeme=yytext(); return Real;}
 . {return ERROR;}
