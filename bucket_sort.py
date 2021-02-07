from random import randint


def per_bucket(list_to_be_sorted, unit_index) -> list:
    # Setting up buckets and a list for containing the numbers smaller then the length of unit_index.
    list_smaller_numbers = []
    length_number = -unit_index
    sorted_buckets = [[] for _ in range(10)]

    # As long as the list_to_be_sorted isn't empty the algorithm searches the last digit of every number and puts it in
    # the right bucket. Whenever the length of a number smaller is then the current unit, it is placed in
    # list_smaller_numbers.
    while list_to_be_sorted != []:
        number = list_to_be_sorted[0]
        if len(str(number)) >= length_number:
            row_index = int(str(number)[unit_index])
            sorted_buckets[row_index].append(list_to_be_sorted[0])
            del list_to_be_sorted[0]
        else:
            list_smaller_numbers.append(number)
            del list_to_be_sorted[0]

    # The smaller numbers are placed back in the list_to_be_sorted. After that every bucket will be sorted and appended
    # to the list_to_be_sorted.
    list_to_be_sorted = list_smaller_numbers
    for bucket in sorted_buckets:
        bucket.sort()
        while bucket != []:
            list_to_be_sorted.append(bucket[0])
            del bucket[0]
    return list_to_be_sorted


def bucket_sort(list_to_be_sorted) -> list:
    # Separate the list in positive and negative numbers. The negatives are put in positive to calculate with them
    # easily.
    negative_list, positive_list = [], []
    for number in list_to_be_sorted:
        if number >= 0:
            positive_list.append(number)
        else:
            negative_list.append(number*-1)

    # Bucketsort for positive numbers. Checks the biggest number in the list and then check the length of that number.
    # That number of times the per_bucketsort fuction has to be called.
    maxLength = len(str(max(positive_list)))
    unit_index = -1
    for i in range(maxLength):
        positive_list = per_bucket(positive_list, unit_index)
        unit_index -= 1

    # Bucketsort for negative numbers. Idem dito as the bucketsort for positive numbers.
    maxLength = len(str(max(negative_list)))
    unit_index = -1
    for i in range(maxLength):
        negative_list = per_bucket(negative_list, unit_index)
        unit_index -= 1

    # Make the negatives negative again and reverse order of the numbers.
    sorted_negative_list = [number *-1 for number in negative_list][::-1]

    return sorted_negative_list + positive_list


xRandomNumbers = [randint(-1000, 1000) for number in range(20)]
print(bucket_sort(xRandomNumbers))