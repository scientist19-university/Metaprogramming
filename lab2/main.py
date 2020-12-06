from lexical_analysis.lexer import Lexer
from semantical_analysis.parser import Parser


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
           'bla bla */ const hello = \"hello\"\n' \
           'private_function (var1, var2, var3)' \
           '//@private\n' \
           'not_private_function (var1, var2)\n' \
           'class /* comment */Rectangle {}\n' \
           'colors = {\n' \
           '    RED: 1,\n' \
           '    GREEN: 2,\n' \
           '    blue: 3\n' \
           '}\n'

    test_file = 'test.js'

    f = open(test_file, 'r')
    text = f.read()
    f.close()

    lexems = Lexer.lex(text)
    Parser.parse(lexems)

    for lexem in lexems:
        print(lexem.get_type())
        print('\'' + lexem.get_str() + '\'')

main()