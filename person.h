#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED
typedef struct {
    char fullName[161];
    int dni;
} Person;

int cmpPersons(Person p1, Person p2) {
    if ((strcmp(p1.fullName, p2.fullName) == 0) &&
        (p1.dni == p2.dni)) {
        return 0; // Las estructuras son iguales
    } else {
        return 1; // Las estructuras son diferentes
    }
}

#endif // PERSON_H_INCLUDED
