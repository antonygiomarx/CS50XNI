from nltk.tokenize import sent_tokenize


def equal_items(list_items, list_items_to_compare):

    equals = []

    for item in list_items:
        if item in list_items_to_compare and item not in equals:
            equals.append(item)

    return equals


def split_to_substrings(list_of_strings, length):

    index = 0
    substrings = []

    string = ""

    string = " ".join(string.splitlines())

    while(index < len(string)):
        if lenght <= len(string[index:lenght + index]):
            substrings.append(string[index: lenght + index])
        index += 1

    return substrings

def lines(a, b):
    """Return lines in both a and b"""
    return equal_items(a.splitlines(), b.splitlines())


def sentences(a, b):
    """Return sentences in both a and b"""
    return equal_items(sent_tokenize(a), sent_tokenize(b))


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    return equal_items(split_to_substrings(a, n), split_to_substrings(b, n))
