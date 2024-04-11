#ifndef CONTACTS_H_INCLUDED
#define CONTACTS_H_INCLUDED

typedef struct Address {
  char street[30];
  char nr[5];
  char post_code[8];
  char town[30];
} Address;

typedef struct Contacts {
  int id;
  char name[30];
  char last_name[30];
  char phone_number[11];
  Address address;
  struct Contacts *next;
} Contacts;

void save_contacts_to_file(Contacts *head, const char *filename);
void print_separator(int total_width);
void load_contacts_from_file(Contacts **head, const char *filename);
void display_list(const Contacts *head);


#endif // CONTACTS_H_INCLUDED
