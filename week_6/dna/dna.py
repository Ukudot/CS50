import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python[3] dna.py dna.csv sequence.txt")
        sys.exit(1)
    
    # Read database file into a variable
    db = []
    with open(sys.argv[1], "r") as file:
        reader = csv.reader(file)
        for row in reader:
            db.append(row)

    # Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as file:
        sequence = file.read()

    # Find longest match of each STR in DNA sequence
    longest_matches = []
    for STR in db[0][1:]:
            longest_matches.append(longest_match(sequence, STR))
    
    # Check database for matching profiles
    for row in db[1:]:
        i = 1
        for n in range(1, len(row)):
            if longest_matches[n - 1] != int(row[n]):
                i = 0
        if i == 1:
            print(row[0])
            return

    print("No match")
    return


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
