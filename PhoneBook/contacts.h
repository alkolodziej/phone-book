#ifndef CONTACTS_H_INCLUDED
#define CONTACTS_H_INCLUDED

#define COLUMN_WIDTH_ID 10
#define COLUMN_WIDTH_NAME 32
#define COLUMN_WIDTH_LAST_NAME 32
#define COLUMN_WIDTH_PHONE_NUMBER 15
#define COLUMN_WIDTH_STREET 32
#define COLUMN_WIDTH_NR 7
#define COLUMN_WIDTH_POST_CODE 10
#define COLUMN_WIDTH_TOWN 31

typedef struct Address {
  char street[30];
  char nr[6];
  char post_code[7];
  char town[30];
} Address;

typedef struct Contacts {
  int id;
  char name[30];
  char last_name[30];
  char phone_number[10];
  Address address;
  struct Contacts *next;
} Contacts;

void save_contacts_to_file(Contacts *head, const char *filename);
void load_contacts_from_file(Contacts **head, const char *filename);
void print_separator(int total_width);
void display_sorting_menu();
void display_list(Contacts **headRef);
void free_contacts_list(Contacts *head);


#endif // CONTACTS_H_INCLUDED
