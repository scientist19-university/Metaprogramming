import logging
import re
import string

from lexical_analysis.lexema import LexemType
from lexical_analysis.lexer import Lexer
from semantical_analysis.parser import Parser


class NamingFixer:

    @classmethod
    def verify_file(cls, filepath, logger):
        f = open(filepath, 'r')
        text = f.read()
        f.close()
        lexems = Lexer.lex(text)
        Parser.parse(lexems)

        fixes = cls.analyze(lexems)

        for fix in fixes:
            for lexema in lexems:
                if lexema.get_str() == fix[0]:
                    logging.warning(f'{filepath}: {fix[0]} naming error -> should be {fix[1]}')

    @classmethod
    def fix_file(cls, filepath, logger):
        f = open(filepath, 'r')
        text = f.read()
        f.close()
        lexems = Lexer.lex(text)
        Parser.parse(lexems)

        fixes = cls.analyze(lexems)

        for fix in fixes:
            for lexema in lexems:
                if lexema.get_str() == fix[0]:
                    lexema.set_str(fix[1])
                    logging.error(f'{filepath}: {fix[0]} naming error -> fixed to {fix[1]}')

        f = open(filepath, 'w')
        for lexema in lexems:
            f.write(lexema.get_str())
        f.close()

    @classmethod
    def analyze(cls, lexems):
        fixes = []
        for lexema in lexems:
            if lexema.get_type() == LexemType.FUNCTION_IDENTIFIER and not cls.__is_camel_case(lexema.get_str()):
                fixes.append((lexema.get_str(), cls.__to_camel_case(lexema.get_str())))
            elif lexema.get_type() == LexemType.PRIVATE_FUNCTION_IDENTIFIER and not cls.__is_trailing_camel_case(lexema.get_str()):
                fixes.append((lexema.get_str(), cls.__to_trailing_camel_case(lexema.get_str())))
            elif lexema.get_type() == LexemType.VARIABLE_IDENTIFIER and not cls.__is_camel_case(lexema.get_str()):
                fixes.append((lexema.get_str(), cls.__to_camel_case(lexema.get_str())))
            elif lexema.get_type() == LexemType.CLASS_IDENTIFIER and not cls.__is_pascal_case(lexema.get_str()):
                fixes.append((lexema.get_str(), cls.__to_pascal_case(lexema.get_str())))
            elif lexema.get_type() == LexemType.CONSTANT_IDENTIFIER and not lexema.get_str().isupper():
                fixes.append((lexema.get_str(), cls.__to_snake(lexema.get_str())))
            elif lexema.get_type() == LexemType.ENUM_IDENTIFIER and not cls.__is_pascal_case(lexema.get_str()):
                fixes.append((lexema.get_str(), cls.__to_pascal_case(lexema.get_str())))
        return fixes

    @classmethod
    def __to_pascal_case(cls, name):
        return string.capwords(name.replace("_", " ")).replace(" ", "")

    @classmethod
    def __to_camel_case(cls, name):
        res = string.capwords(name.replace("_", " ")).replace(" ", "")
        return res[0].lower() + res[1:]

    @classmethod
    def __is_camel_case(cls, name):
        if name[0].isupper():
            return False
        return "_" not in name

    @classmethod
    def __to_trailing_camel_case(cls, name):
        res = string.capwords(name.replace("_", " ")).replace(" ", "")
        res = res[0].lower() + res[1:]
        if res[len(res) - 1] != '_':
            res = res + "_"
        return res

    @classmethod
    def __is_trailing_camel_case(cls, name):
        if name[0].isupper():
            return False
        if name[len(name)-1] != '_':
            return False
        return "_" not in name[0:len(name)-2]

    @classmethod
    def __is_pascal_case(cls, name):
        if name[0].islower():
            return False
        return "_" not in name

    @classmethod
    def __to_snake(cls, name):
        name = re.sub('(.)([A-Z][a-z]+)', r'\1_\2', name)
        return re.sub('([a-z0-9])([A-Z])', r'\1_\2', name).upper()
