from lexical_analysis.lexer import Lexer


def main():
    text = 'var x;\n' + \
           '// doing x = \"6E10\";\n\n' + \
           '/* useless comment\n' + \
           ' useless comment\n' + \
           ' useless comment*/\n' + \
           'x = \"6E10\";\n' + \
           'document.getElementById("demo").innerHTML = x;\n' \
           '@private\n' \
           '// comment\n' \
           '/* another comment\n' \
           'bla bla */' \
           'private_function (var1, var2, var3)' \
           '//@private\n' \
           'not_private_function (var1, var2)'

    lexems = Lexer.lex(text)

    for lexem in lexems:
        print(lexem.get_type())
        print('\'' + lexem.get_str() + '\'')

main()