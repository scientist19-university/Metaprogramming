from lexical_analysis.lexema import LexemType


class Parser:
    @classmethod
    def parse(cls, lexems):
        position = 0
        next_position = 0
        while position < len(lexems):
            next_position = cls.__parse_function(lexems, position)
            if next_position != position:
                position = next_position
                continue
            position += 1

    @classmethod
    def __parse_function(cls, lexems, position):
        if lexems[position].get_type() == LexemType.IDENTIFIER:
            next_position = cls.__get_next_lexema_position(lexems, position)

            if next_position and lexems[next_position].get_type() == LexemType.LEFT_PAREN:
                lexems[position].set_type(LexemType.FUNCTION_IDENTIFIER)
                prev_position = cls.__get_prev_lexema_position(lexems, position)

                if prev_position and lexems[prev_position].get_str() == 'private' and \
                    lexems[prev_position - 1].get_str() == '@':
                    lexems[position].set_type(LexemType.PRIVATE_FUNCTION_IDENTIFIER)

                i = next_position + 1
                while i < len(lexems) and lexems[i].get_type() != LexemType.RIGHT_PAREN:
                    if lexems[i].get_type() == LexemType.IDENTIFIER:
                        lexems[i].set_type(LexemType.VARIABLE_IDENTIFIER)
                    i += 1
                return i

        return position

    @classmethod
    def __get_next_lexema_position(cls, lexems, current_position):
        position = current_position + 1
        while position < len(lexems):
            if lexems[position].get_type() != LexemType.COMMENT and \
               lexems[position].get_type() != LexemType.MULTI_COMMENT and \
               lexems[position].get_type() != LexemType.WHITESPACE:
                return position
            position += 1
        return None

    @classmethod
    def __get_prev_lexema_position(cls, lexems, current_position):
        position = current_position - 1
        while position > 0:
            if lexems[position].get_type() != LexemType.COMMENT and \
               lexems[position].get_type() != LexemType.MULTI_COMMENT and \
               lexems[position].get_type() != LexemType.WHITESPACE:
                return position
            position -= 1
        return None