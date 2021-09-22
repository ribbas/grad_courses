import io
import tokenize as tok
import re


# Update the regular expression pattern to find two character matches with '**'
token_pattern = re.compile(r"\s*(?:(\d+)|(\*\*|.))")


class literal_token:
    def __init__(self, value):
        self.value = value

    def nud(self):
        return self

    def __repr__(self):
        return "(literal %s)" % self.value


class end_token:
    lbp = 0


def tokenize_python(_input_program):
    type_map = {
        tok.NUMBER: "(literal)",
        tok.STRING: "(literal)",
        tok.OP: "(operator)",
        tok.NAME: "(name)",
    }
    for t in tok.generate_tokens(io.StringIO(_input_program).readline):
        try:
            yield type_map[t[0]], t[1]
        except KeyError:  # Handling other token values
            if t[0] == tok.ENDMARKER or t[0] == tok.NEWLINE:
                break
            else:
                raise SyntaxError("Syntax error")
    yield "(end)", "(end)"


def tokenize(_input_program):
    for id, value in tokenize_python(_input_program):
        if id == "(literal)":
            symbol = symbol_table[id]
            s = symbol()
            s.value = value
        else:
            # name or operator
            symbol = symbol_table.get(value)
            if symbol:
                s = symbol()
            elif id == "(name)":
                symbol = symbol_table[id]
                s = symbol()
                s.value = value
            else:
                raise SyntaxError("Unknown operator (%r)" % id)
        yield s


# advance helper function checks the current token and advances if it has no value, i.e. it is not an expression
def advance(id=None):
    global token
    if id and token.id != id:
        raise SyntaxError("Expected %r" % id)
    token = next()


# helper method to be used as a decorator
def method(s):
    assert issubclass(s, symbol_base)

    def bind(fn):
        setattr(s, fn.__name__, fn)

    return bind


def expression(rbp=0):  # default right binding power set to 0
    global token, next  # next shadows the reserved word next
    t = token
    token = next()  # get the next token from the tokenizer iterator
    left = t.nud()  # recursion
    while rbp < token.lbp:
        t = token
        token = next()
        left = t.led(left)  # recursion
    return left


def parse(_program):
    global token, next  # the next reserved word is shadowed
    next = tokenize(
        _program
    ).__next__  # tokenizer is an iterator, save its next() function as global
    token = next()  # get the next token
    return expression()  # parse the expression


class symbol_base(object):  # new-style class, derived from Python object class
    id = None  # node/token type name
    value = None  # used by literals
    first = second = third = None  # used by tree nodes

    def nud(self):
        raise SyntaxError("Syntax error (%r)." % self.id)

    def led(self, left):
        raise SyntaxError("Unknown operator (%r)." % self.id)

    def __repr__(self):
        if self.id == "(name)" or self.id == "(literal)":
            return "(%s %s)" % (self.id[1:-1], self.value)
        # positions of the operands and operator, left to right
        out = [self.id, self.first, self.second, self.third]
        # apply the str function to list of out, filter creates the list by applying None
        out = map(str, filter(None, out))
        return "(" + " ".join(out) + ")"  # join concatenates the list with the ' '


symbol_table = {}


def symbol(id, bp=0):
    try:
        s = symbol_table[id]
    except KeyError:

        class s(symbol_base):
            pass

        s.__name__ = "symbol-" + id  # for debugging purposes
        s.id = id
        s.lbp = bp
        symbol_table[id] = s
    else:
        s.lbp = max(bp, s.lbp)
    return s


def infix(id, bp):
    def led(self, left):
        self.first = left
        self.second = expression(bp)  # recursion
        return self

    symbol(id, bp).led = led
