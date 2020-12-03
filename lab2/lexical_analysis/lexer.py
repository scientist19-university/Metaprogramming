from lexical_analysis.lexema import Lexema
from lexical_analysis.lexema import LexemType
import re

class Lexer:
    @classmethod
    def lex(cls, text):
        str = text
        lexems = []

        while not str:
            number, str = cls.__lex_number(str)
            if number:
                lexems.append(number)
                continue
            lexems.append(LexemType.UNEXPECTED, str[0])
            str = str[1:]

        return lexems

    @classmethod
    def __lex_number(cls, str):
        numbers = re.findall("[-+]?[.]?[\d]+(?:,\d\d\d)*[\.]?\d*(?:[eE][-+]?\d+)?", str)
        first_number = numbers[0]
        number_len = len(first_number)

        p_number = str[0, number_len]
        if p_number == first_number:
            return Lexema(LexemType.NUMBER, first_number), str[number_len:]
        else:
            return None, str
