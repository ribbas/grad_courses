#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""snippets.py

This file implements a simple arithmetic logic unit (ALU) that performs simple
binary multiplication and division. The class implements all the elementary
operations required for multiplication and division, including logical shifts,
inversions, fixed-width additions, and two's complement.
"""
class SimpleALU(object):

    def __init__(self):
        self.x = None
        self.y = None

    def set_opands(self, x, y):
        """Set operands used in the operations

        Args:
            x <int>: first operand
            y <int>: second operand

        Returns:
            None
        """
        # save original decimal values for reference
        self.x_int = x
        self.y_int = y

        # convert decimal integers to binary integer lists
        self.x = self.convert_to_bin_array(x)
        self.y = self.convert_to_bin_array(y)

    @staticmethod
    def convert_to_bin_array(i):
        """Convert decimal integers to binary integer lists

        Args:
            i <int>: operand

        Returns:
            <list(int)>: list of integers representing the binary value
                         of the operand
        """
        return list(int(i) for i in f"{int(i):08b}")

    @staticmethod
    def add(a, b):
        """Perform a simple binary addition

        This function simulates an 8-bit ripple carry adder

        Args:
            a <int>: first operand
            b <int>: second operand

        Returns:
            total_sum <list(int)>: list of integers representing the binary
                                   value of the operand
        """
        # initialize total_sum and cout with zeros
        total_sum = 8 * [0]
        cout = 0
        for i in range(7, -1, -1):  # loop through list backwards
            total_sum[i] = a[i] + b[i] + cout  # perform addition on each bits
            if total_sum[i] == 2:  # if 1 + 1 + 0
                cout = 1
                total_sum[i] = 0
            elif total_sum[i] == 3:  # if 1 + 1 + 1
                cout = 1
                total_sum[i] = 1
            else:  # if 1 + 0 + 0
                cout = 0

        return total_sum

    @staticmethod
    def inv(i):
        """Invert bit

        Args:
            i <int>: bit

        Returns:
            <int>: inverted bit
        """
        return 0 if i else 1

    def comp(self, a):
        """Compute the two's complement of the operand

        Args:
            a <int>: operand

        Returns:
            <list(int)>: two's complement of the operand
        """
        # invert each bit of the operand to compute the one's complement
        ones_comp = [self.inv(a[i]) for i in range(8)]

        # add 1 to the one's complement
        return self.add(ones_comp, [0] * 7 + [1])

    @staticmethod
    def rshift(a):
        """Right shift the operand by 1 bit

        Args:
            a <int>: operand

        Returns:
            <list(int)>: operand right shifted by 1 bit
        """
        return [0] + a[:-1]

    @staticmethod
    def lshift(a):
        """Left shift the operand by 1 bit

        Args:
            a <int>: operand

        Returns:
            <list(int)>: operand left shifted by 1 bit
        """
        return a[1:] + [0]

    def mult(self):
        """Perform a simple binary multiplication

        Returns:
            <list(int)>: list of integers representing the binary value of
                         the product register of the two operands
        """
        # initialize the product register by loading the multiplier on the
        # bottom half
        product = 16 * [0]
        product[8:] = self.y

        print(f"Multiplying {self.x_int} by {self.y_int}")
        print(f"0: {product} Start")
        for i in range(8):
            if product[-1]:  # if LSB == 1
                # add to the bottom half
                product[:8] = self.add(product[:8], self.x)
                print(f"{i + 1}: {product} Add")
            product = self.rshift(product)  # right shift 1 bit
            print(f"{i + 1}: {product} Shift right")
        return product

    def div(self):
        """Perform a simple binary division

        Returns:
            <list(int)>: list of integers representing the binary value of
                         the remainder register of the two operands
        """
        # initialize the remainder register by loading the dividend on the
        # bottom half
        remainder = 16 * [0]
        remainder[8:] = self.x

        print(f"Dividing {self.x_int} by {self.y_int}")
        print(f"0:  {remainder} Start")
        for i in range(8):
            remainder = self.lshift(remainder)  # left shift 1 bit
            print(f"{i + 1}a: {remainder} Shift left")
            # add the two's complement of the divisor
            remainder[:8] = self.add(remainder[:8], self.comp(self.y))
            print(f"{i + 1}b: {remainder} Add complement")
            if remainder[0]:  # if MSB == 1
                # add back the divisor
                remainder[:8] = self.add(remainder[:8], self.y)
                print(f"{i + 1}c: {remainder} Add divisor")
            else:
                # invert the LSB
                remainder[-1] = self.inv(remainder[-1])
                print(f"{i + 1}c: {remainder} Invert LSB")

        return remainder


if __name__ == '__main__':

    alu = SimpleALU()
    alu.set_opands(4, 6)
    alu.mult()
    alu.set_opands(15, 4)
    alu.div()
