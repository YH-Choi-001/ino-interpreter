#ifndef FIXEDSIZEARRAY_H
#define FIXEDSIZEARRAY_H

template <typename T>
class FixedSizeArray {
    private:
        T *array;
    public:
        const size_t length;
        FixedSizeArray(const size_t length) : length(length), array(new T[length]) {}
        ~FixedSizeArray() {
            delete[] array;
        }

        T &operator[](const size_t i) {
            return array[i];
        }

        const T &operator[](const size_t i) const {
            return array[i];
        }
};

#endif