import csv
import sys


def main():

    # TODO: Check for command-line usage
    # 3 command line arguments (program name, csv files containing str counts, .txt name of the dna sequence to check)

    if len(sys.argv) != 3:
        print("Incorrect Command Line Arguments")
        sys.exit()

    # TODO: Read database file into a variable
    # open file
    file = open(sys.argv[1], "r")
    reader = csv.DictReader(file)
    rows = []
    for row in reader:
        rows.append(row)
    file.close()

    # TODO: Read DNA sequence file into a variable
    file = open(sys.argv[2], "r")
    dna = file.read()
    file.close()

    # TODO: Find longest match of each STR in DNA sequence
    str_counts = {}
    for str in reader.fieldnames[1:]:
        str_counts[str] = longest_match(dna, str)

    # TODO: Check database for matching profiles
    # rows[] has csv file data, str_counts{} has counts for that specific person
    for person in rows:
        find = True
        for str_seq in str_counts:
            if int(person[str_seq]) != str_counts[str_seq]:
                find = False
                break
        if find == True:
            print(person["name"])
            return

    print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
