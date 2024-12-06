

def create_lps(pattern:str):
    lps = [0] * len(pattern)
    for i in range(1, len(pattern)):
        subs = pattern[0:i+1]
        prefix=list()
        suffix=list()
        for j in range(len(subs)-1):
            prefix.append(subs[0:j+1])
            suffix.append(subs[-j-1:])
        for j in range(len(prefix)):
            if (prefix[j]==suffix[j]):
                lps[i] = len(prefix[j])

    return lps


def kmp_search(text, pattern):
    if len(pattern)==0 or len(text)==0:
        return []
    lps = create_lps(pattern)
    result=[]
    cmp_cnt = 0
    i = 0  # index for text
    j = 0  # index for pattern

    while i < len(text):
        cmp_cnt += 1
        if pattern[j] == text[i]:
            i += 1
            j += 1

            if j == len(pattern):
                print(f"Pattern found at {i-j}, cmp:{cmp_cnt}")
                result.append(i-j)
                j = lps[j - 1]
        else:
            if j != 0:
                j = lps[j - 1]
            else:
                i += 1
    return result

# Example usage
text = "ABABDABACDABABCABAB"
pattern = "ABABCABAB"
print(kmp_search(text, pattern))

def test_kmp_search():
    # Case 1: Pattern exists once in the text
    assert kmp_search("abcabcabc", "abc") == [0, 3, 6], "Test Case 1 Failed"

    # Case 2: Pattern does not exist in the text
    assert kmp_search("abcabcabc", "xyz") == [], "Test Case 2 Failed"

    # Case 3: Pattern is an empty string
    assert kmp_search("abcabcabc", "") == [], "Test Case 3 Failed"

    # Case 4: Text is an empty string
    assert kmp_search("", "abc") == [], "Test Case 4 Failed"

    # Case 5: Both text and pattern are empty strings
    assert kmp_search("", "") == [], "Test Case 5 Failed"

    # Case 6: Pattern is longer than the text
    assert kmp_search("abc", "abcdef") == [], "Test Case 6 Failed"

    # Case 7: Pattern occurs multiple times with overlap
    assert kmp_search("aaaaa", "aaa") == [0, 1, 2], "Test Case 7 Failed"

    # Case 8: Pattern is the same as the text
    assert kmp_search("abc", "abc") == [0], "Test Case 8 Failed"

    # Case 9: Pattern appears at the end of the text
    assert kmp_search("abcde", "de") == [3], "Test Case 9 Failed"

    # Case 10: Pattern appears at the beginning and end of the text
    assert kmp_search("abcdeabc", "abc") == [0, 5], "Test Case 10 Failed"

    print("All test cases passed!")


# Example: Run the test cases
test_kmp_search()


