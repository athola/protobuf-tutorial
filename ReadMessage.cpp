#include <iostream>
#include <fstream>
#include <string>
#include "addressbook.pb.h"

// Iterate through all people in the AddressBook and print info about them.
void ListPeople(tutorial::AddressBook const & address_book) {
    for (int i = 0; i < address_book.people_size(); i++) {
        tutorial::Person const & person = address_book.people(i);

        std::cout << "Person ID: " << person.id() << std::endl;
        std::cout << " Name: " << person.name() << std::endl;
        if (person.has_email()) {
            std::cout << " E-mail address: " << person.email() << std::endl;
        }

        for (int j = 0; j < person.phones_size(); j++) {
            tutorial::Person::PhoneNumber const & phone_number =
                    person.phones(j);

            switch (phone_number.type()) {
                case tutorial::Person::MOBILE:
                    std::cout << " Mobile phone #: ";
                    break;
                case tutorial::Person::HOME:
                    std::cout << " Home phone #: ";
                    break;
                case tutorial::Person::WORK:
                    std::cout << " Work phone #: ";
                    break;
            }
            std::cout << phone_number.number() << std::endl;
        }
    }
}

/* Main function: Read the entire address book from a file and print all
 * the information inside.
 */
int main(int argc, char* argv[]) {
    /* Verify that the version of the library the was linked against is
     * compatible with the version of the headers that are compiled against.
     */
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " ADDRESS_BOOK_FILE" << std::endl;
        return -1;
    }

    tutorial::AddressBook address_book;

    {
        // Read the existing address book.
        std::fstream input(argv[1], std::ios::in | std::ios::binary);
        if (!address_book.ParseFromIstream(&input)) {
            std::cerr << "Failed to parse address book." << std::endl;
            return -1;
        }
    }

    ListPeople(address_book);

    // Optional: Delete all global object allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}
