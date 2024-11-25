#include <iostream>
#include <locale.h>

using namespace std;

class MultiSet 
{
private:
    int* elements; // ������ ���������
    size_t size;   // ������� ������ ���������
    size_t capacity; // ������� �������

    static const int RUN = 32;

    /**
 * @brief ������������ ����������� ������� ������� ��� �������� ���������.
 *
 * ������� ���������, ���������� �� ������� ������� ������� `elements` ��� ���������� ����� ���������.
 * ���� ������� ���������� ��������� (`size`) ����� ��� ��������� ������� (`capacity`),
 * ������ ����������� � ��� ����. ��� ���� �������� �� ������� ������� ����������
 * � �����, � ������ ������ �������������.
 *
 * @note ���� �� ������� �������� ������ ��� ������ �������, ��������� ��������� ���������� � �������.
 */
    void ensure_capacity() 
    {
        // ���������, ����� �� ����������� �������
        if (size >= capacity)
        {
            // ����������� ������� � ��� ����
            capacity *= 2;

            // �������� ����� ������ � ����������� ��������
            int* new_elements = new int[capacity];
            if (!new_elements)
            {
                cerr << "������ ��������� ������!" << endl;
                exit(1);
            }

            // �������� �������� �� ������� ������� � �����
            for (size_t i = 0; i < size; ++i) 
            {
                new_elements[i] = elements[i];
            }

            // ����������� ������ ������
            delete[] elements;

            // ��������� ��������� �� ����� ������
            elements = new_elements;
        }
    }


    void insertion_sort(int* arr, size_t left, size_t right) 
    {
        for (size_t i = left + 1; i <= right; i++)
        {
            int temp = arr[i];
            size_t j = i - 1;
            while (j >= left && arr[j] > temp)
            {
                arr[j + 1] = arr[j];
                if (j-- == 0) break; // ������ �� ������������
            }
            arr[j + 1] = temp;
        }
    }

    void merge(int* arr, size_t l, size_t m, size_t r) 
    {
        size_t len1 = m - l + 1, len2 = r - m;
        int* left = new int[len1];
        int* right = new int[len2];

        for (size_t i = 0; i < len1; i++) left[i] = arr[l + i];
        for (size_t i = 0; i < len2; i++) right[i] = arr[m + 1 + i];

        size_t i = 0, j = 0, k = l;
        while (i < len1 && j < len2) 
        {
            if (left[i] <= right[j]) 
            {
                arr[k++] = left[i++];
            }
            else 
            {
                arr[k++] = right[j++];
            }
        }

        while (i < len1) arr[k++] = left[i++];
        while (j < len2) arr[k++] = right[j++];

        delete[] left;
        delete[] right;
    }

    void timsort() 
    {
        for (size_t i = 0; i < size; i += RUN)
        {
            insertion_sort(elements, i, (i + RUN - 1 < size ? i + RUN - 1 : size - 1));
        }

        for (size_t width = RUN; width < size; width *= 2) 
        {
            for (size_t left = 0; left < size; left += 2 * width)
            {
                size_t mid = left + width - 1;
                size_t right = (left + 2 * width - 1 < size ? left + 2 * width - 1 : size - 1);

                if (mid < right)
                {
                    merge(elements, left, mid, right);
                }
            }
        }
    }


    /**
 * @brief ������������ ������� ��������� ������� �������� ��������� � ������� ������������ �������.
 *
 * ��������:
 * 1. �������� �� ���� ��������� ���������.
 * 2. ����������� �������� ������� � ������� `freq` �� �������, ��������������� �������� ��������.
 * 3. ���� ������� ������� ������ `max_elem`, ��������� `max_elem`.
 *
 * @param freq ������ ������, ��� freq[i] ������ ���������� ��������� �������� i. ������ ���� ��������������� ������.
 * @param max_elem ������ �� ����������, � ������� ����� �������� ������������ ������� ���������.
 */
    void count_frequencies(int* freq, int& max_elem) const
    {
        for (size_t i = 0; i < size; ++i)
        {
            freq[elements[i]]++;
            if (elements[i] > max_elem) max_elem = elements[i];
        }
    }

public:

    /**
 * @brief ����������� �� ���������. �������������� ������ ���������������.
 *
 * ��������:
 * 1. ������������� ������ ��������� (size) ������ 0.
 * 2. ������������� ��������� ������� ��������� (capacity) ������ 10.
 * 3. �������� ������ ��� ������� ��������� `elements`.
 * 4. ��������� ���������� ��������� ������. ���� ������ �� ��������, ��������� ���������� ��������� � ���������� �� ������.
 */
    MultiSet()
    {
        size = 0; // ��������� ������ ��������� - ������ ���������
        capacity = 10; // ��������� ������� �������
        elements = new int[capacity]; // ��������� ������ ��� ������
        if (!elements) 
        { // �������� ���������� ��������� ������
            cerr << "������ ��������� ������!" << endl;
            exit(1); // ���������� ������ ��������� ��� ������
        }
    }


    /**
 * @brief ����������� ��� ������������� ��������� �� ������� ���������.
 *
 * ��������:
 * 1. ������������� ������ ��������� (size) ������ ���������� ��������� (count).
 * 2. ������ ��������� ������� ������� (capacity) ������ ���������� ���������� ���������.
 * 3. �������� ������ ��� ������ `elements` ��� �������� ���������.
 * 4. ��������� ���������� ��������� ������. � ������ ������ ��������� ���������.
 * 5. �������� �������� �� ����������� ������� `elems` � ������ `elements`.
 * 6. ��������� �������� ��������� � �������������� ��������� Timsort.
 *
 * @param elems ������ �������� ���������.
 * @param count ���������� ��������� � �������.
 */
    MultiSet(const int* elems, size_t count) {
        size = count; // ������������� ������ ���������
        capacity = count * 2; // ������������� ������� ������� � �������
        elements = new int[capacity]; // �������� ������ ��� ������ ���������
        if (!elements) { // �������� ���������� ��������� ������
            cerr << "������ ��������� ������!" << endl;
            exit(1); // ��������� ���������� ��������� ��� ������
        }

        // �������� �������� �� ����������� �������
        for (size_t i = 0; i < count; ++i) {
            elements[i] = elems[i];
        }

        // ��������� �������� ���������
        timsort();
    }



    /**
 * @brief ����������� ����������� ��� �������� ������ ������� MultiSet �� �������������.
 *
 * ����������� ����������� ������� ����� ������, ������� ������ �� ������� ������� `MultiSet`.
 * �� ������������ ���������� ��������� ������ ��� ������� `elements` � �������� ��� ��������
 * �� ��������� ���������. ����� ������������ �������� ����������� ��������� ���������.
 *
 * @param other ������ `MultiSet`, �� �������� ���������� ������.
 *
 * @note ���� ������ ��������� `other.size` ��������� ��� ������� `other.capacity`, ���������
 *       ����������� � ���������� �� ������, ��������� ��� ��������� ����������� ���������.
 * @note ���� �� ������� �������� ������ ��� ������� `elements`, ��������� ��������� ����������
 *       � ���������� �� ������.
 */
    MultiSet(const MultiSet& other) {
        if (other.size > other.capacity) {
            cerr << "������: ������ ��������� ��������� �������!" << endl;
            exit(1); // ��������� ���������� ���������
        }

        // �������� ������� ������ ���������
        size = other.size;

        // �������� ������� �������
        capacity = other.capacity;

        // �������� ������ ��� ������ ������� ���������
        elements = new int[capacity];
        if (!elements) { // ��������� ���������� ��������� ������
            cerr << "������ ��������� ������!" << endl;
            exit(1); // ��������� ���������� ��������� ��� ������
        }

        // �������� �������� �� ������������� ���������
        for (size_t i = 0; i < size; ++i) {
            elements[i] = other.elements[i];
        }
    }



    ~MultiSet() {
        delete[] elements;
    }

   
    /**
 * @brief �������� ������������ ��� ������� MultiSet.
 *
 * ��������� �������� ����������� ������ �� ������� ������� `MultiSet` � ������� ������.
 * �������������� ����������� ������ ������ � �������� �����, ����� ������������� ������ ������.
 *
 * @param other ������ `MultiSet`, ������ �������� ����������.
 * @return ������ �� ������� ������ `MultiSet` ����� ������������.
 *
 * @note ���� `other.size` ��������� `other.capacity`, ��������� ����������� � �������.
 * @note ���� `this` � `other` ��������� �� ���� � ��� �� ������, �������� �� �����������.
 */
    MultiSet& operator=(const MultiSet& other) 
    {
        // �������� �� ����������������
        if (this != &other) 
        {
            if (other.size > other.capacity) 
            {
                cerr << "������: ������ ��������� ��������� �������!" << endl;
                exit(1); // ��������� ���������� ���������
            }

            // ����������� ������ ������
            delete[] elements;

            // �������� ����� ������ ��� ���������
            elements = new int[other.capacity];
            if (!elements) 
            { // ��������� ���������� ��������� ������
                cerr << "������ ��������� ������!" << endl;
                exit(1); // ��������� ���������� ��������� ��� ������
            }

            // �������� ���������
            size = other.size;       // �������� ������� ������ ���������
            capacity = other.capacity; // �������� ������� �������

            // �������� ��������
            for (size_t i = 0; i < size; ++i) {
                elements[i] = other.elements[i];
            }
        }

        // ���������� ������� ������
        return *this;
    }




    /**
 * @brief ��������� ����� ������� � ��������� � ������������ ��� ���������������.
 *
 * ��������:
 * 1. ���������, ���������� �� ������� ������� ��� ���������� ������ ��������
 *    (����� `ensure_capacity()`).
 * 2. ��������� ������� � ����� ������� � ����������� ������ ��������� (`size++`).
 * 3. ��������� ��������� (����� `timsort()`), ����� ��������� ���������������.
 *
 * @param value ��������, ������� ����� �������� � ���������.
 */
    void add(int value)
    {
        // ���������, ��� ���� ����� ��� ������ ��������
        ensure_capacity();

        // �������� ������� � ����� �������
        elements[size++] = value;

        // ������������� ��������� ����� ����������
        timsort();
    }




    /**
  * @brief ���������� ������� ��������� � ������, �������� ����� ���������.
  *
  * ��������:
  * 1. ������������ ������� ��������� � ������� (`*this`) � ������ (`other`) ����������
  *    � ������� ������ `count_frequencies`.
  * 2. ���������� ������������ ������� ��� ������� �������� ����� ���� ��������.
  * 3. ������� ����� ���������, �������� � ���� �������� � ������������ ��������.
  *
  * @param other ���������, � ������� ����������� �������� �����������.
  * @return MultiSet �������������� ���������, �������������� �����������.
  */
    MultiSet operator+(const MultiSet& other) const 
    {
        // ������� ��� �������� ������ ��������� ���� ��������
        int freq1[1000] = { 0 }, freq2[1000] = { 0 };
        int max_elem1 = 0, max_elem2 = 0;

        // ������� ������ ��� �������� ��������� � �������
        count_frequencies(freq1, max_elem1);
        other.count_frequencies(freq2, max_elem2);

        // ����������� ������������� �������� ����� ����� ��������
        int max_elem = (max_elem1 > max_elem2 ? max_elem1 : max_elem2);
        MultiSet result;

        // ������������ ������ ��������� �� ������ ������������ ������
        for (int i = 1; i <= max_elem; ++i)
        {
            int count = (freq1[i] > freq2[i] ? freq1[i] : freq2[i]);
            for (int j = 0; j < count; ++j)
            {
                result.add(i);
            }
        }

        return result; // ���������� �������������� ���������
    }




    /**
  * @brief ��������� ����������� �������� ��������� � ������, �������� ����� ���������.
  *
  * ��������:
  * 1. ������������ ������� ��������� � ������� (`*this`) � ������ (`other`) ����������
  *    � ������� ������ `count_frequencies`.
  * 2. ���������� ����������� ������� ��� ������� �������� ����� ���� ��������.
  * 3. ������� ����� ���������, �������� � ���� �������� � ����������� ��������.
  *
  * @param other ���������, � ������� ����������� �������� �����������.
  * @return MultiSet �������������� ���������, �������������� �����������.
  */
    MultiSet operator*(const MultiSet& other) const 
    {
        // ������� ��� �������� ������ ��������� ���� ��������
        int freq1[1000] = { 0 }, freq2[1000] = { 0 };
        int max_elem1 = 0, max_elem2 = 0;

        // ������� ������ ��� �������� ��������� � �������
        count_frequencies(freq1, max_elem1);
        other.count_frequencies(freq2, max_elem2);

        // ����������� ������������� �������� ����� ����� ��������
        int max_elem = (max_elem1 > max_elem2 ? max_elem1 : max_elem2);
        MultiSet result;

        // ������������ ������ ��������� �� ������ ����������� ������
        for (int i = 1; i <= max_elem; ++i) 
        {
            int count = (freq1[i] < freq2[i] ? freq1[i] : freq2[i]);
            for (int j = 0; j < count; ++j)
            {
                result.add(i);
            }
        }

        return result; // ���������� �������������� ���������
    }


    /**
 * @brief ��������� ��������� ������ ��������� �� �������, �������� ����� ���������.
 *
 * ��������:
 * 1. ������������ ������� ��������� � ������� (`*this`) � ������ (`other`) ����������
 *    � ������� ������ `count_frequencies`.
 * 2. ��� ������� �������� ����������� ������� ������: count = freq1[i] - freq2[i].
 * 3. ���� ������� ������ ����, �� ���� ������� ����������� � �������������� ���������.
 *
 * @param other ���������, ������� ���������� �� �������� ���������.
 * @return MultiSet �������������� ���������, �������������� �������� ���� ��������.
 */
    MultiSet operator-(const MultiSet& other) const 
    {
        // ������� ��� �������� ������ ��������� ���� ��������
        int freq1[1000] = { 0 }, freq2[1000] = { 0 };
        int max_elem1 = 0, max_elem2 = 0;

        // ������� ������ ��� �������� ��������� � �������
        count_frequencies(freq1, max_elem1);
        other.count_frequencies(freq2, max_elem2);

        // ����������� ������������� �������� ����� ����� ��������
        int max_elem = max(max_elem1, max_elem2);
        MultiSet result;

        // ������������ ������ ���������, ������� �������� ������� ��������� �� �������
        for (int i = 1; i <= max_elem; ++i)
        {
            int count = freq1[i] - freq2[i];
            if (count > 0) 
            { // ���� ����� ��������� �������� ��������, ��������� �� � ���������
                for (int j = 0; j < count; ++j)
                {
                    result.add(i);
                }
            }
        }

        return result; // ���������� �������������� ���������
    }


    /**
 * @brief ��������� �������� �������������� �������� ���� ��������.
 *
 * �������������� �������� �������� ��� ��������, ������� ������������
 * � ����� �� ��������, �� �� � ����� ������������.
 * ��������:
 * 1. ������� ����������� ����������� ���� ��������: (*this + other).
 * 2. ����� ����������� ����������� ���� ��������: (*this * other).
 * 3. �� ����������� ���������� �����������, ����� �������� �������������� ��������.
 *
 * @param other ���������, � ������� ����������� �������� �������������� ��������.
 * @return MultiSet ��������� �������������� �������� ���� ��������.
 */
    MultiSet operator^(const MultiSet& other) const 
    {
        // �������� �������������� ��������: ����������� ����� �����������
        return (*this + other) - (*this * other);
    }


    size_t getSize() const 
    {
        return size;
    }

    /**
 * @brief ���������� ��������� [] ��� ������� � ��������� ��������� �� �������.
 *
 * �������� ���������, �� ������� �� ������ �� ������� ���������, � � ������ ������
 * ������� ��������� �� ������ � ��������� ���������. ���� ������ ���������, ������������
 * ������� ��������� �� ��������� �������.
 *
 * @param index ������ ��������, � �������� ����� �������� ������.
 * @return int ������� ���������, ����������� �� ���������� �������.
 */
    int operator[](size_t index) const 
    {
        // �������� �� ����� ������� �� ������� ���������
        if (index >= size)
        {
            cerr << "������ ������� �� �������!" << endl;
            exit(1); // ��������� ��������� � ����� ������ 1
        }
        return elements[index]; // ���������� ������� �� �������
    }


    /**
 * @brief ���������� ��������� == ��� ��������� ���� ��������.
 *
 * �������� ���������, ����� �� ��� ��������� ���������� ������ � �������� �� ��� ���������� ��������.
 * ���� ��������� ��������� �� ������� � �������� ���������, ������������ true. � ��������� ������ � false.
 *
 * @param other ���������, � ������� ������������ ������� ���������.
 * @return bool ��������� ���������: true, ���� ��������� ���������, � false � ���� ��������.
 */
    bool operator==(const MultiSet& other) const 
    {
        // ��������� �������� ��������
        if (size != other.size) return false;

        // ��������� ��������� ��������� �� �������
        for (size_t i = 0; i < size; ++i) 
        {
            if (elements[i] != other.elements[i]) return false;
        }

        return true; // ���� ��� �������� �������, ��������� �����
    }


    /**
 * @brief ���������� ��������� != ��� ��������� ���� �������� �� �����������.
 *
 * �������� ���������� ��� ������������� �������� == ��� �������� ��������� ���� ��������.
 * ���������� true, ���� ��������� ��������, � false, ���� ��������� �����.
 *
 * @param other ���������, � ������� ������������ ������� ���������.
 * @return bool ��������� ���������: true, ���� ��������� ������, � false � ���� ��������� �����.
 */
    bool operator!=(const MultiSet& other) const 
    {
        return !(*this == other); // ���� ��������� �����, ���������� false, ����� true
    }


    /**
  * @brief ��������� ������ ����������� ������� � ���������.
  *
  * ������� ���� ���������� ������������� �����, �������� ��� � ���������, � ��������� ���.
  * ��� ���������� � ����� 1 � �������������� ��� �� ��� ���, ���� �� ������ ������ ������������� �����.
  * ��� ������ ��� �������, ��� ����������� � ��������� � ���������� ������� �����������.
  *
  * @note ����� ������ ���� ������� � ������ ������ ���������� O(n * m), ��� n � ���������� ��������� � ���������,
  *       � m � ����������� ����������� �����.
  */
    void addFirstMissing() 
    {
        int current = 1;  // �������� � ����� 1
        while (true) 
        {
            bool found = false;
            // ����, ���� �� ������� ����� � ���������
            for (size_t i = 0; i < size; ++i)
            {
                if (elements[i] == current)
                {
                    found = true;  // ����� �������
                    break;
                }
            }
            // ���� ����� �� �������, ��������� ��� � ���������
            if (!found) 
            {
                add(current);
                break;
            }
            ++current;  // ��������� � ���������� �����
        }
    }


    // ��������
    class Iterator 
    {
    private:
        int* ptr;
    public:
        Iterator(int* ptr) : ptr(ptr) {}

        // �������� �������������
        int& operator*() 
        {
            return *ptr;
        }

        // �������� ��������� ��������� �� �������
        int* operator->() 
        {
            return ptr;
        }

        // �������� ���������� (�������� ��������� ������)
        Iterator& operator++() 
        {
            ++ptr;
            return *this;
        }

        // �������� ���������� (�������� ��������� �����)
        Iterator& operator--() 
        {
            --ptr;
            return *this;
        }

        // �������� ���������
        bool operator!=(const Iterator& other) const 
        {
            return ptr != other.ptr;
        }

        bool operator==(const Iterator& other) const 
        {
            return ptr == other.ptr;
        }
    };

    // ����� ��� ��������� ��������� �� ������ �������
    Iterator begin() 
    {
        return Iterator(elements);
    }

    // ����� ��� ��������� ��������� �� ������� ����� ����������
    Iterator end() 
    {
        return Iterator(elements + size);
    }

    // ����� ��� ��������� ��������� �� ������� ����� ������
    Iterator rbegin() 
    {
        return Iterator(elements + size - 1);
    }

    // ����� ��� ��������� ��������� �� ������� ����� ������ (�� �������� � end ��� ������� ����������)
    Iterator rend() 
    {
        return Iterator(elements - 1);
    }

    /**
  * @brief ���������� ��������� ������ ��� ���������.
  *
  * ������� ��������� ������� ���������� ������� ���� MultiSet � ����� ������.
  * �������� ��������� ��������� ������ �������� ������ `{}`, ����������� ���������.
  *
  * @param os ����� ������, � ������� ����� �������� ���������.
  * @param ms ������ ���������, ���������� �������� ����� ��������.
  *
  * @return os ����������� ����� ������.
  */
    friend ostream& operator<<(ostream& os, const MultiSet& ms) 
    {
        os << "{";
        for (size_t i = 0; i < ms.size; ++i) 
        {
            os << ms.elements[i];  // ������� ������� ������� ���������
            if (i < ms.size - 1) os << " ";  // ��������� ������ ����� ��������, ���� ��� �� ���������
        }
        os << "}";
        return os;  // ���������� ����� ��� ���������� �������� ������
    }


    /**
 * @brief ���������� ��������� ����� ��� ������ MultiSet.
 *
 * ������� ��������� ��������� �������� ��������� �� ������ ����� � �������:
 * { �������1 �������2 ... �������N }
 * �������� ����������� ���������, � ��������� ��������� � �������� ������ `{}`.
 *
 * @param is ����� �����, �� �������� ����������� ������.
 * @param ms ������ ���������, ���� ������������ ��������� ��������.
 *
 * @return is ����� ����� ��� ���������� ��������.
 *
 * @note ���� ������ ����� ����������� (��������, ����������� �������� ������ ��� �������� ���������
 *       �� �������� ������ �������), ������� ������� ��������� �� ������ � �������� ���������.
 */
    friend istream& operator>>(istream& is, MultiSet& ms)
    {
        ms.size = 0;  // ������� ��������� ����� ������ ����� ���������
        char ch;

        // ��������� ����������� �������� ������
        is >> ch;
        if (ch != '{') 
        {
            cerr << "���� ������ ���������� � '{'" << endl;
            exit(1);
        }

        is >> ws; // ���������� ������� ����� ������ ���������

        // ���� ��������� ������
        if (is.peek() == '}') 
        {
            is.get(); // ��������� '}'
            return is; // ���������� ����� ��� ���������� ���������
        }

        // ��������� �������� ���������
        while (true)
        {
            int num;
            is >> num; // ��������� ����� �����
            ms.add(num); // ��������� ��� � ���������

            is >> ws; // ���������� ������� ����� ��������� ��������
            char next = is.peek(); // ������� �� ��������� ������

            if (next == '}') 
            { // ���� ��������� ����������� ������
                is.get(); // ��������� '}'
                break; // ��������� ����
            }
            else if (!isdigit(next)) 
            {
                // ���� ��������� ������ �� ����� (������������ ����)
                cerr << "�������� �������� ������� ��� '}'" << endl;
                exit(1);
            }
        }

        return is; // ���������� �����
    }

};

int main() {
    setlocale(LC_ALL, "RUS");
    MultiSet a, b;

    cout << "������� ��������������� A (� ������� {�������� ����� ������}): ";
    cin >> a;
    cout << "A" << a << "\n";

    cout << "������� ��������������� B (� ������� {�������� ����� ������}): ";
    cin >> b;
    cout << "B" << b << "\n";

    cout << "����������� A + B: " << (a + b) << "\n";
    cout << "����������� A * B: " << (a * b) << "\n";
    cout << "�������� A - B: " << (a - b) << "\n";
    cout << "�������������� �������� A ^ B: " << (a ^ b) << "\n";

    a.addFirstMissing();
    cout << "A ����� ���������� ������� �������������� ��������: " << a << "\n";

    // ������������� ��������� ��� ������ ���������
    cout << "�������� ��������� A: ";
    for (auto it = a.begin(); it != a.end(); ++it) {
        cout << *it << " ";
    }
    cout << "\n";

    return 0;
}