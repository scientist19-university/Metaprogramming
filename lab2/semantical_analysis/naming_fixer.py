import re

from lexical_analysis.lexema import LexemType


class NamingFixer:

    @classmethod
    def verify(cls):
        print()

    @classmethod
    def fix(cls):
        print()

    @classmethod
    def analyze(cls, lexems):
        fixes = []
        for lexema in lexems:
            if lexema.get_type() == LexemType.FUNCTION_IDENTIFIER and not cls.__is_needed_case(lexema.get_str()):
                fixes.append((lexema.get_str(), cls.__to_needed_case(lexema.get_str())))
            elif lexema.get_type() == LexemType.PRIVATE_FUNCTION_IDENTIFIER and not cls.__is_needed_case(lexema.get_str()):
                fixes.append((lexema.get_str(), cls.__to_needed_case(lexema.get_str())))
            elif lexema.get_type() == LexemType.VARIABLE_IDENTIFIER and not cls.__is_needed_case(lexema.get_str()):
                fixes.append((lexema.get_str(), cls.__to_needed_case(lexema.get_str())))
            elif lexema.get_type() == LexemType.CLASS_IDENTIFIER and not cls.__is_needed_case(lexema.get_str()):
                fixes.append((lexema.get_str(), cls.__to_needed_case(lexema.get_str())))
            elif lexema.get_type() == LexemType.CONSTANT_IDENTIFIER and not lexema.get_str().isupper():
                fixes.append((lexema.get_str(), cls.__to_snake(lexema.get_str())))
            elif lexema.get_type() == LexemType.ENUM_IDENTIFIER and not cls.__is_needed_case(lexema.get_str()):
                fixes.append((lexema.get_str(), cls.__to_needed_case(lexema.get_str())))
        return fixes

    @classmethod
    def __to_needed_case(cls, name):
        return name

    @classmethod
    def __is_needed_case(cls, name):
        return True

    @classmethod
    def __to_snake(cls, name):
        name = re.sub('(.)([A-Z][a-z]+)', r'\1_\2', name)
        return re.sub('([a-z0-9])([A-Z])', r'\1_\2', name).upper()
