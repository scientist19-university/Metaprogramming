from enum import Enum

class LexemType(Enum):
    NUMBER = 0,
    IDENTIFIER = 1,
    STRING = 2,
    LEFT_BRACKET = 3,
    RIGHT_BRACKET = 4,
    LEFT_PAREN = 5,
    RIGHT_PAREN = 6,
    LEFT_BRACE = 7,
    RIGHT_BRACE = 8,
    LESS_THAN = 9,
    GREATER_THAN = 10,
    EQUAL = 11,
    OPERATOR = 12,
    SLASH = 13,
    HASH = 14,
    DOT = 15,
    COMMA = 16,
    COLON = 17,
    SEMICOLON = 18,
    SINGLE_QUOTE = 19,
    DOUBLE_QUOTE = 20,
    WHITESPACE = 21,
    UNEXPECTED = 22


class Lexema:
    def __init__(self, lexem_type, str):
        self.__lexem_type = lexem_type
        self.__str = str

    def has_type(self, lexem_type):
        return self.__lexem_type == lexem_type

    def get_str(self):
        return self.__str