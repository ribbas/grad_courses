from __future__ import annotations


class Opands:
    def __init__(self, expression):
        # tokenize expression into opand1, opand2 and op

        self.opand1, self.op, self.opand2 = expression.split(" ")
        self.opand1 = int(self.opand1)
        self.opand2 = int(self.opand2)


class Chain:
    def setSuccessor(self, successor: Chain):
        pass

    def evaluate(self, opands: Opands):
        pass


class AddOpands(Chain):

    __successor = None

    def setSuccessor(self, successor: Chain):
        self.__successor = successor

    def evaluate(self, opands: Opands):
        if opands.op == "+":
            result = opands.opand1 + opands.opand2
            print("Result of addition:", result)
        else:
            self.__successor.evaluate(opands)


class SubOpands(Chain):

    __successor = None

    def setSuccessor(self, successor: Chain):
        self.__successor = successor

    def evaluate(self, opands: Opands):
        if opands.op == "-":
            result = opands.opand1 - opands.opand2
            print("Result of subtraction:", result)
        else:
            self.__successor.evaluate(opands)


class MulOpands(Chain):

    __successor = None

    def setSuccessor(self, successor: Chain):
        self.__successor = successor

    def evaluate(self, opands: Opands):
        if opands.op == "*":
            result = opands.opand1 * opands.opand2
            print("Result of multiplication:", result)
        else:
            self.__successor.evaluate(opands)


class DivOpands(Chain):

    __successor = None

    def setSuccessor(self, successor: Chain):
        self.__successor = successor

    def evaluate(self, opands: Opands):
        if opands.op == "/":
            result = opands.opand1 / opands.opand2
            print("Result of division:", result)
        else:
            print(opands.op, "is not a supported operation.")


if __name__ == "__main__":

    add_chain = AddOpands()
    sub_chain = SubOpands()
    mul_chain = MulOpands()
    div_chain = DivOpands()

    add_chain.setSuccessor(sub_chain)
    sub_chain.setSuccessor(mul_chain)
    mul_chain.setSuccessor(div_chain)

    opands = Opands(input())
    add_chain.evaluate(opands)
