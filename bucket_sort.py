import numpy as np

def per_bucket(list_to_be_sorted, unit_index):
    array_per_unit = np.empty([10, 1])
    for number in list_to_be_sorted:
        if int(str(number)[unit_index]) != None:
            row_index = int(str(number)[unit_index])
            array_per_unit[row_index].insert(number)
            #array_per_unit.insert(row_index, number)
    print(array_per_unit)




def bucket_sort(list_to_be_sorted):
    unit_index = -1
    array_per_unit = np.empty([10,1])
    sorted_list = per_bucket(list_to_be_sorted, unit_index)


    return sorted_list



print(bucket_sort(np.array([1, 25, 4, 100, 85, 3])))




