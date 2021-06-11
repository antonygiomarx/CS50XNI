 from nltk.tokenize import sent_tokenize

def lines(a, b):
    """Return lines in both a and b"""
    q = set(a.splitlines())
    r = set(b.splitlines())

    return list(q & r)


def sentences(a, b):
    """Return sentences in both a and b"""

    q = set(sent_tokenize(a))
    r = set(sent_tokenize(b))

    return list(q & r)


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    q = set(substringHelper(a, n))
    r = set(substringHelper(b, n))

    return list(q & r)

def substringHelper(a, n):
    l = []
    x = 0
    while x<n:
        y = x
        while y < (len(a)+1-n):
            l.append(a[y:y+n])
            y+=n
        x+=1
    return l