#ifndef CONTACTS_H_INCLUDED
#define CONTACTS_H_INCLUDED

typedef struct Address {
  char street[30];
  char nr[5];
  char post_code[6];
  char town[30];
} Address;

typedef struct Contacts {
  int id;
  char name[50];
  char last_name[50];
  char phone_number[11];
  Address address;
  struct Contacts *next;
} Contacts;

void add_contact(Contacts **head, char *name, char *last_name, char *phone_number, char *street, char *nr, char *post_code, char *town);
void edit_contact(Contacts *head, int id, char *name, char *last_name, char *phone_number, char *street, char *nr, char *post_code, char *town);
void delete_contact(Contacts **head, int index);
void display_list(const Contacts *head);
void load_contacts_from_file(Contacts **head, const char *filename);


#endif // CONTACTS_H_INCLUDED
