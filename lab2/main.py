import re

from lexical_analysis.lexer import Lexer
from semantical_analysis.naming_fixer import NamingFixer
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

    test_file = 'D:\\Meta\\Lab2\\JsFiles\\test.js'

    f = open(test_file, 'r')
    text = f.read()
    f.close()

    lexems = Lexer.lex(text)
    Parser.parse(lexems)

    #for lexem in lexems:
    #    print(lexem.get_type())
    #    print('\'' + lexem.get_str() + '\'')

    fixes = NamingFixer.analyze(lexems)

    for fix in fixes:
        print(f'{fix[0]} -> {fix[1]}')

    '''
    test1 = 'HelloWorld'
    test2 = 'HELLO_WORLD123'
    test3 = 'hello_world'
    test4 = 'helloWorld'
    test5 = 'IOManip'

    print(test1)
    print(camel_to_snake(test1))
    print(test2)
    print(camel_to_snake(test2))
    print(test3)
    print(camel_to_snake(test3))
    print(test4)
    print(camel_to_snake(test4))
    print(test5)
    print(camel_to_snake(test5))
    print()
    print(test2.isupper())
    '''

main()