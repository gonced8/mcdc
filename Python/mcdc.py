from sys import argv
from inspect import signature
import itertools
from random import choice
from math import log2, floor, ceil


def test_function (a,b,c,d):
    return int(bool(a) ^ (bool(b) and bool(c) and bool(d)))

all_solutions = False

class IO():
    def __init__(self, i=-1, o=-1):
        self.i = i
        self.o = o


class Pair():
    def __init__(self, a = IO(), b=IO()):
        self.a = a
        self.b = b


def count_function_args(f):
    sig = signature(f)
    params = sig.parameters
    return len(params)


def get_input(nvar):
    return tuple(itertools.product([0, 1], repeat=nvar))


def calculate_output(function, test_input):
    return [function(*line) for line in test_input]


def print_truth_table(test_input, test_output, indices=None):
    nargs = len(test_input[0])

    print('-'*(8*(nargs+4)))
    print('t\t|\t', end='')

    for i in range(nargs):
        print(i, '\t', end='')

    print('|\t', end='')
    print('o')
    print('-'*8+'+'+'-'*(8*(nargs+1)-1)+'+'+'-'*(8*2-1))

    for i in range(len(test_input)):
        if indices:
            print(indices[i], '\t|\t', end='')
        else:
            print(i, '\t|\t', end='')
        print('\t'.join(map(str, test_input[i])), '\t', end='')
        print('|\t', end='')
        print(test_output[i])

    print('-'*(8*(nargs+4)))


def get_pairs(nargs):
    pairs = [[Pair(IO(-1,-1),IO(-1,-1)) for j in range(2**(nargs-1))] for k in range(nargs)]

    for i in range(nargs):
        l=0
        for j in range(2**i):
            group = 2**(nargs-1-i)
            for k in range(group):
                separation = 2*group
                pairs[i][l].a.i = j*separation+k
                pairs[i][l].b.i = j*separation+k+group
                l += 1

    return pairs


def get_pairs_output(test_input, test_output, pairs):
    for arg in pairs:
        for pair in arg:
            pair.a.o = test_output[pair.a.i]
            pair.b.o = test_output[pair.b.i]

    return pairs


def print_pairs(pairs):
    for arg in pairs:
        for pair in arg:
            print("({}, {}) -> ({}, {})".format(pair.a.i, pair.b.i, pair.a.o, pair.b.o))
        print()


def filter_equal_output(pairs):
    return [[pair for pair in arg if pair.a.o is not pair.b.o] for arg in pairs]


def get_combinations(pairs):
    return list(itertools.product(*pairs))


def unique_tests(combinations):
    tests = []
    tests_i = []

    for combination in combinations:
        group = []
        group_i = []

        for pair in combination:
            if pair.a.i not in group_i:
                group.append(pair.a)
                group_i.append(pair.a.i)
            if pair.b.i not in group_i:
                group.append(pair.b)
                group_i.append(pair.b.i)

        if group:
            tests.append(group)
    
    return tests


def print_tests(tests):
    for group in tests:
        for test in group:
            print("{}->{}\t".format(test.i, test.o), end='')
        print()
    print()


def get_min_tests(tests):
    lengths = [len(group) for group in tests]
    min_len = min(lengths)

    return [group for group in tests if len(group) is min_len]


def print_test_table(chosen_tests, test_input, test_output):
    chosen_tests.sort(key=lambda test: test.i)
    indices = [test.i for test in chosen_tests]
    chosen_test_input = [test_input[index] for index in indices]
    chosen_test_output = [test.o for test in chosen_tests]

    print_truth_table(chosen_test_input, chosen_test_output, indices)


def mcdc (function=None, test_input=None, test_output=None, all_solutions=True):
    if function and test_input:
        test_output = calculate_output(function, test_input)

    elif test_input and test_output:
        if len(test_input) is not len(test_output):
            if function:
                test_output = calculate_output(function, test_input)
            else:
                print("Tests input and output have different sizes and no function was given to calculate missing. Exiting")
                return

    elif test_output:
        p = log2(len(test_output))
        if floor(p)==ceil(p):
            nargs = int(p)
            test_input = get_input(nargs)
        else:
            print("Number of elements in output is not a power of 2. Exiting.")
            return

    elif function:
        nargs = count_function_args(function)
        test_input = get_input(nargs)
        test_output = calculate_output(function, test_input)


    #print_truth_table(test_input, test_output)

    pairs = get_pairs(nargs)
    pairs = get_pairs_output(test_input, test_output, pairs)
    #print_pairs(pairs)

    pairs = filter_equal_output(pairs)
    #print_pairs(pairs)

    combinations = get_combinations(pairs)
    #print(len(combinations))
    
    tests = unique_tests(combinations)
    #print_tests(tests)

    min_tests = get_min_tests(tests)
    if all_solutions:
        for i in range(len(min_tests)):
            print(i)
            print_test_table(min_tests[i], test_input, test_output)
    else:
        chosen_tests = choice(min_tests)
        print_test_table(chosen_tests, test_input, test_output)
    

def get_argv_output(output):
    output = argv[1]
    output = output.split('[')
    output = output[-1]
    output = output.split(']')
    output = output[0]
    output = output.split(',')
    return [int(number) for number in output]


if __name__ == "__main__":
    if len(argv)>1:
        output = get_argv_output(argv[1])
        mcdc(test_output=output)
    else:
        mcdc(function=test_function, all_solutions=all_solutions)
        
