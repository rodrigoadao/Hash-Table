typedef struct student {
    int id;
    char name[50];
    struct student *next;
} Student;

typedef struct {
    int count, TABLE_SIZE;
    struct student **itens;
} Hash;

Hash * create_hash(int TABLE_SIZE);
void free_table(Hash* hash);
void hash_dump(Hash* hash);
int insert_closed_hash(Hash* hash, Student student);
void hash_search( Hash* hash, int id);
int hash_delete(Hash* hash, int id);
