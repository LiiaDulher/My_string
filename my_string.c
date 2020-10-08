#include <string.h>

typedef struct
{
	size_t capacity_m; // Розмір блока
	size_t size_m;	   // Фактичний розмір стрічки
	char*  data;	   // Вказівник на блок пам'яті
} my_str_t;

enum error_codes{NOT_FOUND_CODE = -1, MEMORY_ALLOCATION_ERR = -2, RANGE_ERR = -3, IO_READ_ERR = -4, IO_WRITE_ERR = -5, NULL_PTR_ERR = -8, BUFF_SIZE_ERR = -9};

//!===============================================================
//! Створення та знищення стрічки.
//!===============================================================

int my_str_create(my_str_t* str, size_t buf_size);
{
    if (!str){
        return NULL_PTR_ERR;
    }
    str->data = malloc(buf_size+1);
    if (!str->data){
        return MEMORY_ALLOCATION_ERR;
    }
    str->size_m = 0;
    str->capacity_m = buf_size;
    return 0;
}

int my_str_free(my_str_t* str);
{
    if (str){
        free(str->data);
    }
    free(str);
    return 0;
}

int my_str_from_cstr(my_str_t* str, const char* cstr, size_t buf_size);
{
    if (!str){
        return NULL_PTR_ERR;
    } 
    // make later
    return 0;
}

//!===============================================================
//! Інформація про стрічку
//!===============================================================

size_t my_str_size(const my_str_t* str);
{
    if (!str){
        return 0;
    } 
    return str->size_m;
}

size_t my_str_capacity(const my_str_t* str);
{
    if (!str){
        return 0;
    } 
    return str->capacity_m;    
}

int my_str_empty(const my_str_t* str);
{
    if (!str){
        return NULL_PTR_ERR;
    }
    if (my_str_size(str)){
        return 1;
    }
    return 0;
}

//!===============================================================
//! Доступ до символів стрічки
//!===============================================================

int my_str_getc(const my_str_t* str, size_t index);
{
    if(index > str->size_m){
        return RANGE_ERR;
    }
    if(!str){
        return NOT_FOUND_CODE;
    }
    return str->data[index];
}

int my_str_putc(my_str_t* str, size_t index, char c); // NEW
{
    if (!str){
        return NULL_PTR_ERR;
    }
    if (index > my_str_size(str)){
        return RANGE_ERR;
    }
    str->data[index] = c;
    return 0;
    // check later
}

const char* my_str_get_cstr(my_str_t* str);
{
    if(!str){
        return 0;
    }
    str->data[str->capacity_m + 1] = NULL;
    return str->data;
}

//!===============================================================
//! Модифікації стрічки, що змінюють її розмір і можуть викликати реалокацію.
//!===============================================================

int my_str_copy(const my_str_t* from,  my_str_t* to, int reserve);
{
    if(from == NULL, to == NULL){
        return -8;
    }
    if(reserve){
        my_str_resize(to, from->capacity_m, '0');
    }
    return 0;
}

int my_str_clear(my_str_t* str);
{
    // make later
}

int my_str_insert_c(my_str_t* str, char c, size_t pos);
{
    // make later
}

int my_str_insert(my_str_t* str, const my_str_t* from, size_t pos);
{
    // make later
}

int my_str_insert_cstr(my_str_t* str, const char* from, size_t pos);
{
    // make later
}

int my_str_append(my_str_t* str, const my_str_t* from);
{
    // make later
}

int my_str_append_cstr(my_str_t* str, const char* from);
{
    // make later
}

int my_str_append_c(my_str_t* str, char c);
{
    // make later
}

int my_str_substr(const my_str_t* from, my_str_t* to, size_t beg, size_t end);
{
    // make later
}

int my_str_substr_cstr(const my_str_t* from, char* to, size_t beg, size_t end);
{
    // make later
}

int my_str_erase(my_str_t* str, size_t beg, size_t end);
{
    // make later
}

int my_str_popback(my_str_t* str);
{
    // make later
}

//!===============================================================
//! Маніпуляції розміром буфера стрічки
//!===============================================================

int my_str_reserve(my_str_t* str, size_t buf_size);
{
    if(str == NULL){
        return NOT_FOUND_CODE;
    }
    if(buf_size > str->capacity_m){
        char* new_data = malloc(buf_size + 1);
        for(int i = 0; i < str->capacity_m; i++){
            new_data[i] = str->data[i];
        }
        str->capacity_m = buf_size;
        str->data = new_data;
    }
    return 0;
}

int my_str_shrink_to_fit(my_str_t* str);  //NEW
{
    // make later
}

//!===============================================================
//! Маніпуляції розміром стрічки
//!===============================================================

int my_str_resize(my_str_t* str, size_t new_size, char sym);
{
     if(str == NULL){
        return NOT_FOUND_CODE;
    }
    if(new_size < str->size_m){
        str->size_m = new_size;
        return 0;
    }
    else if(new_size > str->capacity_m){
        my_str_reserve(str, new_size);
    }
    while(str->size_m < new_size){
        str->data[str->size_m] = sym;
        str->size_m++;
        }
    return 0;
}

//!===============================================================
//! Функції пошуку та порівняння
//!===============================================================

size_t my_str_find(const my_str_t* str, const my_str_t* tofind, size_t from); // NEW
{
    if (tofind == NULL){
        return NOT_FOUND_CODE;
    }
    if (tofind.my_str_empty())||(tofind.my_str_size() > str.my_str_size()){
        return (size_t)(-1);
    }
    for (size_t i = 0; i<str.my_str_size()-tofind.my_str_size(); i++){
        if (str->data[i] == tofind.data[0]){
            size_t j = 0;
            size_t k = i;
            while (j<tofind.my_str_size()) && (str->data[k] == tofind->data[j]) {
                j++;
                k++;
            }
            if (j == tofind.my_str_size()){
                return i;
            }
        }    
    }
    return (size_t)(-1);
}

int my_str_cmp(const my_str_t* str1, const my_str_t* str2);  //NEW
{
    if (str1 == NULL) || (str2 == NULL){
        return NOT_FOUND_CODE;
    }
    if (str1.my_str_size() < str2.my_str_size()){
        return -1;
    }
    if (str1.my_str_size() > str2.my_str_size()){
        return 1;
    }
    for (size_t i = 0; i<str1.my_str_size(); i++){
        if ((int)str1->data[i] < (int) str2->data[i]){
            return -1;
        }
        if ((int)str1->data[i] > (int) str2->data[i]){
            return 1;
        }
    }
    return 0;
}

int my_str_cmp_cstr(const my_str_t* str1, const char* cstr2);  // NEW
{
   my_str_t str2 = my_str_from_cstr(my_str_t* str2, const char* cstr2, size_t strlen(const char* cstr2)); // check find buf_size
   return my_str_cmp(const my_str_t* str1, const my_str_t* str2);
}

size_t my_str_find_c(const my_str_t* str, char tofind, size_t from); //NEW
{
    if (str == NULL){
        return NOT_FOUND_CODE;
    }
    if (from >= str.my_str_size()){
        return (size_t)(-1);
    }
    for (size_t i = from; i<str.my_str_size(); i++){
        if (str->data[i] == tofind){
            return 0;
        }
    }
    return (size_t)(-1);
}

size_t my_str_find_if(const my_str_t* str, size_t beg, int (*predicat)(int));  //NEW
{
    if (str == NULL){
        return NOT_FOUND_CODE;
    }
    if (beg >= str.my_str_size()){
        return (size_t)(-1);
    }
    if (predicat == NULL){
        return (size_t)(-1);
    }
    for (size_t i = beg; i<str.my_str_size(); i++){
        if (predicat((int)str.data[i])){
            return i;
        }
    }
    return (size_t)(-1);
}

//!===============================================================
//! Ввід-вивід
//!===============================================================

int my_str_read_file(my_str_t* str, FILE* file);
{
    // make later
}

int my_str_read(my_str_t* str);
{
    // make later
}

int my_str_read_file_delim(my_str_t* str, FILE* file, char delimiter);
{
    // make later
}

int my_str_write_file(const my_str_t* str, FILE* file);
{
    // make later
}

int my_str_write(const my_str_t* str);
{
    // make later
}